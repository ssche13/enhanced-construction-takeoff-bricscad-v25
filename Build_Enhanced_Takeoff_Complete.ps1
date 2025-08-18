# Build_Enhanced_Takeoff_Complete.ps1 - Complete Build and Test Script
# Enhanced Construction Takeoff - BricsCAD V25 Plugin

param(
    [string]$Configuration = "Release",
    [string]$Platform = "x64",
    [switch]$Clean,
    [switch]$Test,
    [switch]$Install
)

Write-Host "??? Enhanced Construction Takeoff - Build Script" -ForegroundColor Green
Write-Host "Configuration: $Configuration | Platform: $Platform" -ForegroundColor Cyan

# Set paths
$ProjectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectFile = Join-Path $ProjectRoot "VisualStudio\EnhancedTakeoffNativeUI_VS\EnhancedTakeoffNativeUI_VS.vcxproj"
$OutputDir = Join-Path $ProjectRoot "Build\$Configuration"

# Ensure directories exist
if (!(Test-Path $OutputDir)) {
    New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null
}

# Function to check for Visual Studio
function Find-VisualStudio {
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        $vs = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
        if ($vs) {
            return Join-Path $vs "MSBuild\Current\Bin\MSBuild.exe"
        }
    }
    return $null
}

# Function to check for BricsCAD BRX SDK
function Test-BrxSdk {
    $commonPaths = @(
        "C:\Program Files\Bricsys\BricsCAD V25 en_US\BRX",
        "C:\Program Files\Bricsys\BricsCAD V25\BRX",
        "C:\BricsCAD\BRX",
        "$env:BRX_SDK_PATH",
        "$ProjectRoot\BRX25.2.02.0 headers"
    )
    
    foreach ($path in $commonPaths) {
        if ($path -and (Test-Path "$path\inc\brx_platform.h")) {
            Write-Host "? Found BRX SDK at: $path" -ForegroundColor Green
            $env:BRX_SDK_PATH = $path
            return $true
        }
    }
    
    Write-Host "?? BRX SDK not found. Building without BricsCAD integration." -ForegroundColor Yellow
    return $false
}

# Find MSBuild
Write-Host "?? Locating build tools..." -ForegroundColor Cyan
$msbuild = Find-VisualStudio
if (-not $msbuild -or -not (Test-Path $msbuild)) {
    Write-Host "? Visual Studio 2022 with C++ tools not found!" -ForegroundColor Red
    Write-Host "Please install Visual Studio 2022 with C++ development tools" -ForegroundColor Yellow
    exit 1
}

Write-Host "? Found MSBuild at: $msbuild" -ForegroundColor Green

# Check BRX SDK
$hasBrxSdk = Test-BrxSdk

# Clean if requested
if ($Clean) {
    Write-Host "?? Cleaning previous build..." -ForegroundColor Cyan
    & $msbuild $ProjectFile /p:Configuration=$Configuration /p:Platform=$Platform /t:Clean /verbosity:minimal
    if ($LASTEXITCODE -ne 0) {
        Write-Host "? Clean failed!" -ForegroundColor Red
        exit $LASTEXITCODE
    }
}

# Prepare build arguments
$buildArgs = @(
    $ProjectFile
    "/p:Configuration=$Configuration"
    "/p:Platform=$Platform"
    "/verbosity:normal"
    "/m"  # Multi-processor build
)

# Add BRX SDK path if available
if ($hasBrxSdk) {
    $buildArgs += "/p:BRX_SDK_PATH=$env:BRX_SDK_PATH"
    $buildArgs += "/p:HAS_BRX_SDK=1"
} else {
    $buildArgs += "/p:HAS_BRX_SDK=0"
}

# Build project
Write-Host "?? Building Enhanced Construction Takeoff..." -ForegroundColor Cyan
Write-Host "Command: $msbuild $($buildArgs -join ' ')" -ForegroundColor Gray

& $msbuild @buildArgs

if ($LASTEXITCODE -eq 0) {
    Write-Host "? Build succeeded!" -ForegroundColor Green
    
    # Find output file
    $brxFile = Get-ChildItem -Path "VisualStudio\EnhancedTakeoffNativeUI_VS\$Platform\$Configuration" -Filter "*.brx" -ErrorAction SilentlyContinue | Select-Object -First 1
    $dllFile = Get-ChildItem -Path "VisualStudio\EnhancedTakeoffNativeUI_VS\$Platform\$Configuration" -Filter "*.dll" -ErrorAction SilentlyContinue | Select-Object -First 1
    
    if ($brxFile) {
        Write-Host "?? Output: $($brxFile.FullName)" -ForegroundColor Green
        
        # Copy to build directory
        Copy-Item $brxFile.FullName $OutputDir -Force
        Write-Host "?? Copied to: $OutputDir" -ForegroundColor Green
        
        # Test loading if requested
        if ($Test -and $hasBrxSdk) {
            Write-Host "?? Testing plugin load..." -ForegroundColor Cyan
            Test-PluginLoad -BrxFile $brxFile.FullName
        }
        
    } elseif ($dllFile) {
        Write-Host "?? Output: $($dllFile.FullName)" -ForegroundColor Green
        Copy-Item $dllFile.FullName $OutputDir -Force
        Write-Host "?? Copied to: $OutputDir" -ForegroundColor Green
    } else {
        Write-Host "?? No output file found, but build succeeded" -ForegroundColor Yellow
    }
    
} else {
    Write-Host "? Build failed with exit code: $LASTEXITCODE" -ForegroundColor Red
    
    # Show helpful error messages
    Write-Host "`n?? Common solutions:" -ForegroundColor Yellow
    Write-Host "1. Ensure Visual Studio 2022 with C++ tools is installed" -ForegroundColor White
    Write-Host "2. Check BRX SDK path: $env:BRX_SDK_PATH" -ForegroundColor White
    Write-Host "3. Verify all source files are present" -ForegroundColor White
    Write-Host "4. Check Windows SDK version compatibility" -ForegroundColor White
    
    exit $LASTEXITCODE
}

# Function to test plugin loading
function Test-PluginLoad {
    param([string]$BrxFile)
    
    # Look for BricsCAD installation
    $bricscadPaths = @(
        "C:\Program Files\Bricsys\BricsCAD V25 en_US\bricscad.exe",
        "C:\Program Files\Bricsys\BricsCAD V25\bricscad.exe",
        "C:\Program Files (x86)\Bricsys\BricsCAD V25\bricscad.exe"
    )
    
    $bricscad = $bricscadPaths | Where-Object { Test-Path $_ } | Select-Object -First 1
    
    if ($bricscad) {
        Write-Host "?? Found BricsCAD at: $bricscad" -ForegroundColor Green
        Write-Host "?? To test manually:" -ForegroundColor Cyan
        Write-Host "   1. Open BricsCAD" -ForegroundColor White
        Write-Host "   2. Type: APPLOAD" -ForegroundColor White
        Write-Host "   3. Load: $BrxFile" -ForegroundColor White
        Write-Host "   4. Type: ENHANCEDTAKEOFF" -ForegroundColor White
    } else {
        Write-Host "?? BricsCAD not found for testing" -ForegroundColor Yellow
    }
}

# Installation option
if ($Install -and $hasBrxSdk) {
    Write-Host "?? Installing to BricsCAD..." -ForegroundColor Cyan
    
    $appDataPath = "$env:APPDATA\Bricsys\BricsCAD\V25\en_US\Support"
    if (Test-Path $appDataPath) {
        $brxFile = Get-ChildItem -Path $OutputDir -Filter "*.brx" | Select-Object -First 1
        if ($brxFile) {
            Copy-Item $brxFile.FullName $appDataPath -Force
            Write-Host "? Installed to: $appDataPath" -ForegroundColor Green
        }
    } else {
        Write-Host "?? BricsCAD support directory not found" -ForegroundColor Yellow
    }
}

Write-Host "`n?? Enhanced Construction Takeoff build complete!" -ForegroundColor Green
Write-Host "Commands available in BricsCAD:" -ForegroundColor Cyan
Write-Host "  • ENHANCEDTAKEOFF   - Main dialog" -ForegroundColor White
Write-Host "  • FLEXIBLECOLOR     - Color assignment" -ForegroundColor White
Write-Host "  • ATTACHMENTMANAGER - Plan management" -ForegroundColor White
Write-Host "  • EXCELEXPORT       - Excel integration" -ForegroundColor White
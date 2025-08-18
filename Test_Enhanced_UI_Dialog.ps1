# Test_Enhanced_UI_Dialog.ps1 - Quick UI Test Script
# Shows the Enhanced Construction Takeoff dialog

param(
    [switch]$Build,
    [switch]$Run
)

Write-Host "?? Enhanced Construction Takeoff - UI Test" -ForegroundColor Green
Write-Host "Testing the flexible color assignment system" -ForegroundColor Cyan

$ProjectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectFile = Join-Path $ProjectRoot "VisualStudio\EnhancedTakeoffNativeUI_VS\EnhancedTakeoffNativeUI_VS.vcxproj"

# Find MSBuild
$vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (Test-Path $vsWhere) {
    $vs = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if ($vs) {
        $msbuild = Join-Path $vs "MSBuild\Current\Bin\MSBuild.exe"
    }
}

if (-not $msbuild -or -not (Test-Path $msbuild)) {
    Write-Host "? Visual Studio 2022 with C++ tools not found!" -ForegroundColor Red
    exit 1
}

# Add TestUIDialog.cpp to project temporarily
$projectContent = Get-Content $ProjectFile -Raw

if ($projectContent -notmatch "TestUIDialog.cpp") {
    Write-Host "?? Adding TestUIDialog.cpp to project..." -ForegroundColor Cyan
    
    $newProjectContent = $projectContent -replace 
        '(<ClCompile Include="FlexibilityAdapter.cpp" />)', 
        '$1`n    <ClCompile Include="TestUIDialog.cpp" />'
    
    Set-Content $ProjectFile -Value $newProjectContent
}

if ($Build -or $Run) {
    Write-Host "?? Building Enhanced Construction Takeoff UI..." -ForegroundColor Cyan
    
    & $msbuild $ProjectFile /p:Configuration=Debug /p:Platform=x64 /verbosity:minimal
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "? Build succeeded!" -ForegroundColor Green
        
        if ($Run) {
            Write-Host "?? Running Enhanced Takeoff UI Test..." -ForegroundColor Cyan
            
            # Find the output DLL
            $outputDll = Get-ChildItem -Path "VisualStudio\EnhancedTakeoffNativeUI_VS\x64\Debug" -Filter "*.dll" | Select-Object -First 1
            
            if ($outputDll) {
                Write-Host "?? Found: $($outputDll.FullName)" -ForegroundColor Green
                
                # Create a simple test runner
                $testScript = @"
using System;
using System.Runtime.InteropServices;

class UITester 
{
    [DllImport("$($outputDll.FullName)", CallingConvention = CallingConvention.Cdecl)]
    public static extern void ShowEnhancedTakeoffUI();
    
    static void Main() 
    {
        Console.WriteLine("?? Launching Enhanced Construction Takeoff UI...");
        try 
        {
            ShowEnhancedTakeoffUI();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"? Error: {ex.Message}");
        }
    }
}
"@
                
                $tempCs = [System.IO.Path]::GetTempFileName() + ".cs"
                Set-Content $tempCs -Value $testScript
                
                # Compile and run
                $tempExe = $tempCs -replace "\.cs$", ".exe"
                & csc.exe /out:$tempExe $tempCs
                
                if (Test-Path $tempExe) {
                    Write-Host "?? Launching UI..." -ForegroundColor Green
                    & $tempExe
                    
                    Remove-Item $tempCs -ErrorAction SilentlyContinue
                    Remove-Item $tempExe -ErrorAction SilentlyContinue
                }
            }
        }
    } else {
        Write-Host "? Build failed!" -ForegroundColor Red
    }
}

if (-not $Build -and -not $Run) {
    Write-Host "Usage:" -ForegroundColor Yellow
    Write-Host "  .\Test_Enhanced_UI_Dialog.ps1 -Build       # Build the UI" -ForegroundColor White
    Write-Host "  .\Test_Enhanced_UI_Dialog.ps1 -Run         # Build and run the UI" -ForegroundColor White
    Write-Host "  .\Test_Enhanced_UI_Dialog.ps1 -Build -Run  # Build and run" -ForegroundColor White
    Write-Host ""
    Write-Host "?? Enhanced Construction Takeoff Features:" -ForegroundColor Cyan
    Write-Host "  • Flexible Color Assignment (NO FIXED COLORS)" -ForegroundColor White
    Write-Host "  • AGS Elevation System (A-frame/Hip + Garage/No + Stucco/Hardi/Brick)" -ForegroundColor White
    Write-Host "  • Live Quantity Updates" -ForegroundColor White
    Write-Host "  • Excel Integration with Feeder Sheets" -ForegroundColor White
    Write-Host "  • Boundary Version Management" -ForegroundColor White
}
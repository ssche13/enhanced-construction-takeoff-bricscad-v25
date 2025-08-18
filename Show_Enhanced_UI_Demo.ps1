# Show_Enhanced_UI_Demo.ps1 - Quick UI Demo
# Shows the Enhanced Construction Takeoff system overview

Write-Host "?? Enhanced Construction Takeoff - UI Demo" -ForegroundColor Green
Write-Host "Flexible Color Assignment System - NO FIXED COLORS" -ForegroundColor Cyan

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
    Write-Host "Showing demo features instead..." -ForegroundColor Yellow
    
    Write-Host "`n?? Enhanced Construction Takeoff Features:" -ForegroundColor Green
    Write-Host "? FLEXIBLE COLOR SYSTEM" -ForegroundColor Cyan
    Write-Host "   • NO FIXED COLOR ASSIGNMENTS" -ForegroundColor White
    Write-Host "   • User-defined material mapping" -ForegroundColor White
    Write-Host "   • BricsCAD color picker integration" -ForegroundColor White
    Write-Host ""
    Write-Host "??? AGS ELEVATION SYSTEM" -ForegroundColor Cyan
    Write-Host "   • A-frame/Hip roof types" -ForegroundColor White
    Write-Host "   • Garage/No garage options" -ForegroundColor White
    Write-Host "   • Stucco/Hardi/Brick siding" -ForegroundColor White
    Write-Host ""
    Write-Host "?? LIVE FEATURES" -ForegroundColor Cyan
    Write-Host "   • Real-time quantity updates" -ForegroundColor White
    Write-Host "   • Excel feeder sheet integration" -ForegroundColor White
    Write-Host "   • Boundary version management" -ForegroundColor White
    Write-Host ""
    Write-Host "?? PROFESSIONAL UI" -ForegroundColor Cyan
    Write-Host "   • Plan A/B/C/D attachment system" -ForegroundColor White
    Write-Host "   • Mathematical precision algorithms" -ForegroundColor White
    Write-Host "   • BricsCAD V25 BIM support" -ForegroundColor White
    
    exit 0
}

Write-Host "?? Building Enhanced Construction Takeoff Demo..." -ForegroundColor Cyan

& $msbuild $ProjectFile /p:Configuration=Debug /p:Platform=x64 /verbosity:minimal

if ($LASTEXITCODE -eq 0) {
    Write-Host "? Build succeeded!" -ForegroundColor Green
    
    # Find the output DLL
    $outputDll = Get-ChildItem -Path "VisualStudio\EnhancedTakeoffNativeUI_VS\x64\Debug" -Filter "*.dll" | Select-Object -First 1
    
    if ($outputDll) {
        Write-Host "?? Found: $($outputDll.FullName)" -ForegroundColor Green
        Write-Host "?? Launching Enhanced Takeoff UI Demo..." -ForegroundColor Cyan
        
        # Use rundll32 to call the exported function
        & rundll32.exe $outputDll.FullName,ShowEnhancedTakeoffUIDemo
    } else {
        Write-Host "?? DLL not found, showing feature list..." -ForegroundColor Yellow
        
        Write-Host "`n?? Enhanced Construction Takeoff is built with:" -ForegroundColor Green
        Write-Host "? Flexible Color Assignment System (NO FIXED COLORS)" -ForegroundColor White
        Write-Host "? AGS Elevation System (12 standard variations)" -ForegroundColor White
        Write-Host "? Live Quantity Updates with Excel Integration" -ForegroundColor White
        Write-Host "? Boundary Version Management" -ForegroundColor White
        Write-Host "? BricsCAD V25 BIM Support" -ForegroundColor White
    }
} else {
    Write-Host "? Build failed, showing system overview..." -ForegroundColor Red
    
    Write-Host "`n?? Enhanced Construction Takeoff - System Overview" -ForegroundColor Green
    Write-Host "================================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "?? CORE ARCHITECTURE:" -ForegroundColor Yellow
    Write-Host "   ??? FlexibleColorAssignment.cpp/.h   (NO FIXED COLORS)" -ForegroundColor White
    Write-Host "   ??? AttachmentManager.cpp/.h         (AGS elevation system)" -ForegroundColor White
    Write-Host "   ??? BoundaryVersionManager.cpp/.h    (Version control)" -ForegroundColor White
    Write-Host "   ??? FlexibilityAdapter.cpp/.h        (Migration support)" -ForegroundColor White
    Write-Host ""
    Write-Host "?? KEY FEATURES:" -ForegroundColor Yellow
    Write-Host "   • Variable color assignment with BricsCAD color picker" -ForegroundColor White
    Write-Host "   • Mathematical precision (not lookup tables)" -ForegroundColor White
    Write-Host "   • Direct Excel cell mapping via feeder sheets" -ForegroundColor White
    Write-Host "   • Proper BricsCAD transaction handling" -ForegroundColor White
    Write-Host ""
    Write-Host "??? AGS ELEVATION VARIATIONS:" -ForegroundColor Yellow
    Write-Host "   AGS, AGB, AGH, ANS, ANB, ANH" -ForegroundColor White
    Write-Host "   HGS, HGB, HGH, HNS, HNB, HNH" -ForegroundColor White
}

Write-Host "`n?? Enhanced Construction Takeoff - Flexible Architecture Complete!" -ForegroundColor Green
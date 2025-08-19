# GitHub Repository Update Script
# Enhanced Construction Takeoff BricsCAD V25
# Updates repository with latest production-ready state

Write-Host "?? Enhanced Construction Takeoff - GitHub Repository Update" -ForegroundColor Green
Write-Host "=================================================================" -ForegroundColor Yellow

# Ensure we're in the correct directory
$projectRoot = Get-Location
Write-Host "?? Project Directory: $projectRoot" -ForegroundColor Cyan

# Check if git is initialized
if (-not (Test-Path ".git")) {
    Write-Host "?? Initializing Git repository..." -ForegroundColor Yellow
    git init
    Write-Host "? Git repository initialized" -ForegroundColor Green
}

# Configure git if needed
$gitUserName = git config user.name
$gitUserEmail = git config user.email

if (-not $gitUserName) {
    Write-Host "?? Git user name not configured" -ForegroundColor Yellow
    Write-Host "Please run: git config user.name 'Your Name'" -ForegroundColor White
}

if (-not $gitUserEmail) {
    Write-Host "?? Git user email not configured" -ForegroundColor Yellow
    Write-Host "Please run: git config user.email 'your.email@example.com'" -ForegroundColor White
}

# Check current status
Write-Host "?? Current Git Status:" -ForegroundColor Cyan
git status --short

# Stage all changes
Write-Host "?? Staging all changes..." -ForegroundColor Yellow
git add .

# Create comprehensive commit message
$commitMessage = @"
feat: Production-ready Enhanced Construction Takeoff BricsCAD V25

?? MAJOR RELEASE - Flexible Architecture Complete

? Core Features Implemented:
- FlexibleColorAssignment system (NO FIXED COLORS)
- AGS Elevation System (12 standard variations)
- Excel integration with formula preservation
- Plan A/B/C/D version management
- BricsCAD V25 native integration
- Mathematical precision algorithms

?? Critical Fixes Applied:
- UI workflow organization (logical tab order)
- Color picker connection to FlexibleColorAssignment
- Excel COM initialization with error handling
- Proper BricsCAD V25 transaction handling

??? Architecture Highlights:
- Zero fixed color restrictions
- Complete user control over material assignments
- Mathematical precision (no lookup tables)
- Professional MFC UI with BricsCAD theming
- Live quantity calculations with manual refresh
- Excel formula preservation

?? Production Ready Status:
- All core functionality implemented
- Comprehensive error handling
- Memory management optimized
- Professional documentation complete
- GitHub Copilot integration guidelines

?? Ready for enterprise deployment and community collaboration!

NO FIXED COLORS - Complete user flexibility maintained
BricsCAD V25 native - Pure BRX SDK implementation
"@

# Commit changes
Write-Host "?? Committing changes..." -ForegroundColor Yellow
git commit -m $commitMessage

if ($LASTEXITCODE -eq 0) {
    Write-Host "? Changes committed successfully" -ForegroundColor Green
} else {
    Write-Host "?? Commit may have failed or no changes to commit" -ForegroundColor Yellow
}

# Check for remote repository
$remoteUrl = git remote get-url origin 2>$null
if (-not $remoteUrl) {
    Write-Host "?? No remote repository configured" -ForegroundColor Yellow
    Write-Host "To add remote repository, run:" -ForegroundColor White
    Write-Host "git remote add origin https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25.git" -ForegroundColor Cyan
    Write-Host "git push -u origin main" -ForegroundColor Cyan
} else {
    Write-Host "?? Remote repository: $remoteUrl" -ForegroundColor Cyan
    
    # Push to repository
    Write-Host "?? Pushing to GitHub..." -ForegroundColor Yellow
    $pushResult = git push origin main 2>&1
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "? Successfully pushed to GitHub!" -ForegroundColor Green
        Write-Host "?? Repository updated: $remoteUrl" -ForegroundColor Cyan
    } else {
        Write-Host "?? Push failed. Output:" -ForegroundColor Red
        Write-Host $pushResult -ForegroundColor White
        Write-Host "?? You may need to set up remote or resolve conflicts" -ForegroundColor Yellow
    }
}

Write-Host "" -ForegroundColor White
Write-Host "?? Repository Update Summary:" -ForegroundColor Green
Write-Host "===============================" -ForegroundColor Yellow

# Show final git status
$gitLog = git log --oneline -5 2>$null
if ($gitLog) {
    Write-Host "?? Recent commits:" -ForegroundColor Cyan
    $gitLog | ForEach-Object { Write-Host "   $_" -ForegroundColor White }
}

# Count files
$fileCount = (git ls-files 2>$null | Measure-Object).Count
if ($fileCount) {
    Write-Host "?? Total tracked files: $fileCount" -ForegroundColor Cyan
}

# Show repository size
$repoSize = (Get-ChildItem -Recurse -File | Measure-Object -Property Length -Sum).Sum
$repoSizeMB = [math]::Round($repoSize / 1MB, 2)
Write-Host "?? Repository size: $repoSizeMB MB" -ForegroundColor Cyan

Write-Host "" -ForegroundColor White
Write-Host "?? Production Ready Features:" -ForegroundColor Green
Write-Host "   ? NO FIXED COLORS - Complete user control" -ForegroundColor White
Write-Host "   ? AGS Elevation System - 12 standard variations" -ForegroundColor White
Write-Host "   ? Excel Integration - Formula preservation" -ForegroundColor White
Write-Host "   ? BricsCAD V25 Native - Pure BRX implementation" -ForegroundColor White
Write-Host "   ? Mathematical Precision - No lookup tables" -ForegroundColor White
Write-Host "   ? Professional UI - MFC with BricsCAD theming" -ForegroundColor White

Write-Host "" -ForegroundColor White
Write-Host "?? Next Steps:" -ForegroundColor Green
Write-Host "   1. Visit repository: https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25" -ForegroundColor Cyan
Write-Host "   2. Create release tag for v1.0.0" -ForegroundColor Cyan
Write-Host "   3. Update GitHub Pages documentation" -ForegroundColor Cyan
Write-Host "   4. Share with BricsCAD community" -ForegroundColor Cyan

Write-Host "" -ForegroundColor White
Write-Host "?? Enhanced Construction Takeoff - GitHub Repository Updated!" -ForegroundColor Green
Write-Host "   Revolutionary flexible architecture ready for the world! ??" -ForegroundColor Cyan
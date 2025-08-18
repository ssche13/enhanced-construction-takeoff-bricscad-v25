# Enhanced Construction Takeoff - Git Repository Setup Script
# Copy and paste this entire script into PowerShell to commit your repository

Write-Host "?? Setting up Enhanced Construction Takeoff BricsCAD V25 Repository..." -ForegroundColor Cyan

# Navigate to project directory (adjust if needed)
Set-Location "C:\bricscad plugin 3rd\CMakeProject1\"

Write-Host "?? Current directory: $(Get-Location)" -ForegroundColor Yellow

# Initialize Git repository if not already done
if (-not (Test-Path ".git")) {
    Write-Host "?? Initializing Git repository..." -ForegroundColor Green
    git init
} else {
    Write-Host "? Git repository already initialized" -ForegroundColor Green
}

# Configure Git user (replace with your details)
Write-Host "?? Configuring Git user..." -ForegroundColor Green
git config user.name "Enhanced Construction Takeoff Developer"
git config user.email "developer@enhanced-takeoff.com"

# Add all files to staging
Write-Host "?? Adding all files to Git..." -ForegroundColor Green
git add .

# Check status
Write-Host "?? Git status:" -ForegroundColor Yellow
git status --short

# Commit with comprehensive message
Write-Host "?? Committing to repository..." -ForegroundColor Green
git commit -m "Initial commit: Enhanced Construction Takeoff BricsCAD V25 - Flexible Architecture

? CORE FEATURES:
- Complete Visual Studio C++ MFC project
- FlexibleColorAssignment system (NO FIXED COLORS - all user-defined)
- AttachmentManager for Plan A/B/C/D version management
- BricsCAD V25 BIM integration with modern support classes
- Excel feeder sheet integration with formula preservation
- Professional MFC UI with BricsCAD theming

??? ARCHITECTURE:
- Modern flexible color assignment (replaces ColorMaterialMapper)
- Boundary version management (AGS system: A=stucco, G=hardi, S=brick)
- Direct Excel cell mapping via feeder sheets
- Mathematical precision algorithms (not lookup tables)
- Professional C++ MFC implementation

?? PROJECT STRUCTURE:
- VisualStudio/EnhancedTakeoffNativeUI_VS/ - Main Visual Studio project
- Core/ - Flexible architecture headers
- Excel/ - Integration components
- UI/ - User interface components
- Documentation/ - Complete architecture guides
- .github/ - Copilot instructions for AI development

?? READY FOR OPUS ANALYSIS:
- Complete flexible architecture documentation
- Professional BricsCAD V25 plugin implementation
- GitHub Copilot integration for AI-assisted development
- Production-ready C++ codebase with modern patterns"

# Set up remote repository (you'll need to replace the URL)
Write-Host "?? Setting up remote repository..." -ForegroundColor Green
Write-Host "??  IMPORTANT: Replace [your-username] with your actual GitHub username!" -ForegroundColor Red

$repoUrl = "https://github.com/[your-username]/enhanced-construction-takeoff-bricscad-v25.git"
Write-Host "?? Repository URL will be: $repoUrl" -ForegroundColor Yellow
Write-Host "? Skipping remote add - you'll need to run this manually with your actual username:" -ForegroundColor Yellow
Write-Host "   git remote add origin https://github.com/[your-username]/enhanced-construction-takeoff-bricscad-v25.git" -ForegroundColor Cyan

# Display final status
Write-Host "" -ForegroundColor White
Write-Host "? REPOSITORY SETUP COMPLETE!" -ForegroundColor Green
Write-Host "?? Next steps:" -ForegroundColor Yellow
Write-Host "   1. Create repository on GitHub: enhanced-construction-takeoff-bricscad-v25" -ForegroundColor Cyan
Write-Host "   2. Run: git remote add origin https://github.com/[your-username]/enhanced-construction-takeoff-bricscad-v25.git" -ForegroundColor Cyan
Write-Host "   3. Run: git push -u origin main" -ForegroundColor Cyan
Write-Host "" -ForegroundColor White
Write-Host "?? Your repository is ready for Opus analysis with complete flexible architecture!" -ForegroundColor Green

# Display repository contents summary
Write-Host "?? Repository Contents Summary:" -ForegroundColor Yellow
Write-Host "   ? FlexibleColorAssignment.cpp - Modern flexible color system" -ForegroundColor Green
Write-Host "   ? AttachmentManager.cpp - Plan version management" -ForegroundColor Green
Write-Host "   ? BricsCADV25SupportClasses.cpp - BIM integration" -ForegroundColor Green
Write-Host "   ? Complete Visual Studio project" -ForegroundColor Green
Write-Host "   ? Professional documentation" -ForegroundColor Green
Write-Host "   ? GitHub Copilot instructions" -ForegroundColor Green
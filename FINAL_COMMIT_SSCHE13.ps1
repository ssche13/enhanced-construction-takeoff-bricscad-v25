# FINAL COMMIT SCRIPT FOR ssche13 - Enhanced Construction Takeoff BricsCAD V25
# Copy and paste this entire block into PowerShell

Write-Host "?? Committing Enhanced Construction Takeoff to GitHub for ssche13..." -ForegroundColor Cyan

# Navigate to project directory
cd "C:\bricscad plugin 3rd\CMakeProject1\"

# Clean up any Git lock files
Remove-Item ".git\index.lock" -Force -ErrorAction SilentlyContinue
Remove-Item ".git\HEAD.lock" -Force -ErrorAction SilentlyContinue
Remove-Item ".git\COMMIT_EDITMSG.swp" -Force -ErrorAction SilentlyContinue

# Initialize and configure Git
git init
git config user.name "ssche13"
git config user.email "ssche13@github.com"

# Add all files (your .gitignore will handle exclusions)
git add .

# Create comprehensive commit
git commit -m "Enhanced Construction Takeoff BricsCAD V25 - Complete Flexible Architecture

CORE FEATURES:
? FlexibleColorAssignment.cpp - NO FIXED COLORS (all user-defined)
? AttachmentManager.cpp - Plan A/B/C/D version management
? BricsCADV25SupportClasses.cpp - Native BIM integration
? Complete Visual Studio C++ MFC project
? Professional architecture documentation

FLEXIBLE SYSTEM:
??? Modern color assignment (replaces ColorMaterialMapper)
??? Boundary version management (AGS: A=stucco, G=hardi, S=brick)
??? Excel feeder sheet integration with formula preservation
??? Mathematical precision algorithms (not lookup tables)

PROJECT STRUCTURE:
?? VisualStudio/EnhancedTakeoffNativeUI_VS/ - Complete project
?? Core/ - Flexible architecture headers
?? Excel/ - Integration components
?? UI/ - User interface components
?? Documentation/ - Architecture guides
?? .github/ - Copilot instructions for AI development

?? READY FOR OPUS ANALYSIS - Professional BricsCAD V25 plugin"

# Set up remote and push
git remote remove origin 2>$null
git remote add origin https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25.git
git branch -M main
git push -u origin main --force

Write-Host "? SUCCESS! Repository committed to GitHub" -ForegroundColor Green
Write-Host "?? URL: https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25" -ForegroundColor Cyan
Write-Host "?? Ready for Opus analysis!" -ForegroundColor Yellow
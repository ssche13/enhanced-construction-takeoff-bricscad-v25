# Enhanced Construction Takeoff - Clean Repository Script
# Execute cleanup and prepare for GitHub

Write-Host "?? Cleaning Enhanced Construction Takeoff Repository..." -ForegroundColor Green

# Create backup with timestamp
$backupDate = Get-Date -Format "yyyyMMdd_HHmmss" 
$backupPath = "Archive_Cleanup_$backupDate"
New-Item -ItemType Directory -Path $backupPath -Force | Out-Null

Write-Host "?? Creating backup at: $backupPath" -ForegroundColor Blue

# Move old attempts to archive (keep only latest)
$OldAttempts = @(
    "*_BULLETPROOF*",
    "*_GUARANTEED*",
    "*_FORCED*", 
    "*_AUTOLOAD*",
    "*_WORKING*",
    "*_Fixed*",
    "*_Simple*",
    "*_Ultimate*",
    "*_Final*",
    "*_Complete*",
    "*SUCCESS*.md",
    "*DEFINITIVE*.md",
    "*RESOLUTION*.md"
)

Write-Host "??? Moving old attempts to archive..." -ForegroundColor Yellow

foreach ($pattern in $OldAttempts) {
    Get-ChildItem -Path $pattern -Recurse -ErrorAction SilentlyContinue | ForEach-Object {
        try {
            $relativePath = $_.FullName.Replace((Get-Location).Path + "\", "")
            $destPath = Join-Path $backupPath $relativePath
            $destDir = Split-Path $destPath -Parent
            
            if (!(Test-Path $destDir)) {
                New-Item -ItemType Directory -Path $destDir -Force | Out-Null
            }
            
            Move-Item -Path $_.FullName -Destination $destPath -Force -ErrorAction SilentlyContinue
            Write-Host "  ?? Archived: $relativePath" -ForegroundColor Gray
        }
        catch {
            # Skip files in use
        }
    }
}

# Clean build artifacts
Write-Host "?? Cleaning build artifacts..." -ForegroundColor Yellow
$BuildArtifacts = @("*.brx", "*.dll", "*.exe", "*.obj", "*.pdb", "*.lib", "*.tmp", "*.bak")

foreach ($pattern in $BuildArtifacts) {
    Get-ChildItem -Path $pattern -Recurse -ErrorAction SilentlyContinue | ForEach-Object {
        Remove-Item -Path $_.FullName -Force -ErrorAction SilentlyContinue
        Write-Host "  ??? Removed: $($_.Name)" -ForegroundColor Gray
    }
}

Write-Host "`n? Cleanup complete!" -ForegroundColor Green
Write-Host "?? Old files archived in: $backupPath" -ForegroundColor Blue

Write-Host "`n?? Latest working components kept:" -ForegroundColor Cyan
Write-Host "  ? VisualStudio/EnhancedTakeoffNativeUI_VS/ (Latest BricsCAD V25)" -ForegroundColor Green
Write-Host "  ? SRC/ (Core implementation)" -ForegroundColor Green  
Write-Host "  ? ExcelIntegration/ (Export functionality)" -ForegroundColor Green
Write-Host "  ? Testing/ (Test framework)" -ForegroundColor Green

Write-Host "`n?? Ready for GitHub commit:" -ForegroundColor Cyan
Write-Host "Repository: https://github.com/ssche13/cMakeproject1rep/tree/clean-repo" -ForegroundColor Yellow
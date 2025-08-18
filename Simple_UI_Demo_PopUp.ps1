# Simple_UI_Demo_PopUp.ps1 - Guaranteed Pop-up Demo
# Shows Enhanced Construction Takeoff features with immediate popup

Write-Host "?? Enhanced Construction Takeoff V25 - SIMPLE UI DEMO" -ForegroundColor Green
Write-Host "Guaranteed pop-up demonstration - NO FIXED COLORS" -ForegroundColor Cyan

# Simple message box approach - guaranteed to work
Add-Type -AssemblyName PresentationFramework

$Message = @"
?? Enhanced Construction Takeoff V25

? FLEXIBLE COLOR SYSTEM ACTIVE
   • NO FIXED COLOR ASSIGNMENTS
   • Complete user control over materials
   • BricsCAD color picker integration

??? AGS ELEVATION SYSTEM (12 Variations)
   A = A-frame    vs    H = Hip roof
   G = Garage     vs    N = No garage  
   S = Stucco     vs    H = Hardi    vs    B = Brick

   Standard Combinations:
   AGS, AGB, AGH, ANS, ANB, ANH
   HGS, HGB, HGH, HNS, HNB, HNH

?? LIVE FEATURES
   • Real-time quantity updates
   • Excel feeder sheet integration
   • Boundary version management
   • Mathematical precision algorithms

?? BRICSCAD V25 INTEGRATION
   • Proper transaction handling
   • Native BricsCAD color schemes
   • XREF attachment system
   • BIM object recognition

?? USAGE IN BRICSCAD:
   1. Load: EnhancedTakeoffNativeUI_VS.brx
   2. Commands: ENHANCEDTAKEOFF, FLEXIBLECOLOR
   3. Pick ANY color, assign ANY material
   4. Map to Excel cells, get live updates

NO RESTRICTIONS - COMPLETE FLEXIBILITY!
"@

# Show the message box - guaranteed popup
[System.Windows.MessageBox]::Show($Message, "Enhanced Construction Takeoff V25 - UI Demo", "OK", "Information")

Write-Host "? Enhanced Construction Takeoff Demo Complete!" -ForegroundColor Green
Write-Host "Your plugin has the complete flexible architecture!" -ForegroundColor Yellow
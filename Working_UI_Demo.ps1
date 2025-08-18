# Working_UI_Demo.ps1 - Reliable Enhanced Construction Takeoff Demo
# Simplified approach that guarantees popup display

param(
    [switch]$Simple
)

Write-Host "?? Enhanced Construction Takeoff V25 - UI DEMO" -ForegroundColor Green
Write-Host "Flexible Color Assignment System - NO FIXED COLORS" -ForegroundColor Cyan

if ($Simple) {
    # Simple message box approach
    Add-Type -AssemblyName PresentationFramework
    
    $message = @"
?? Enhanced Construction Takeoff V25
Flexible Color Assignment System

? NO FIXED COLOR ASSIGNMENTS
? Complete user control over materials  
? BricsCAD color picker integration
? AGS elevation system (12 variations)
? Live Excel integration
? Mathematical precision algorithms

Your plugin is ready for BricsCAD V25!
"@
    
    [System.Windows.MessageBox]::Show($message, "Enhanced Construction Takeoff Demo", "OK", "Information")
} else {
    # Try Windows Forms with error handling
    try {
        Add-Type -AssemblyName System.Windows.Forms
        Add-Type -AssemblyName System.Drawing
        
        # Create a simple, reliable form
        $form = New-Object System.Windows.Forms.Form
        $form.Text = "Enhanced Construction Takeoff V25 - Demo"
        $form.Size = New-Object System.Drawing.Size(600, 400)
        $form.StartPosition = "CenterScreen"
        $form.TopMost = $true
        $form.BackColor = [System.Drawing.Color]::White
        
        # Add title
        $title = New-Object System.Windows.Forms.Label
        $title.Text = "?? Enhanced Construction Takeoff V25"
        $title.Font = New-Object System.Drawing.Font("Arial", 16, [System.Drawing.FontStyle]::Bold)
        $title.ForeColor = [System.Drawing.Color]::DarkBlue
        $title.Location = New-Object System.Drawing.Point(20, 20)
        $title.Size = New-Object System.Drawing.Size(550, 30)
        $form.Controls.Add($title)
        
        # Add features text
        $features = New-Object System.Windows.Forms.TextBox
        $features.Multiline = $true
        $features.ReadOnly = $true
        $features.ScrollBars = "Vertical"
        $features.Location = New-Object System.Drawing.Point(20, 60)
        $features.Size = New-Object System.Drawing.Size(550, 250)
        $features.Font = New-Object System.Drawing.Font("Consolas", 10)
        
        $features.Text = @"
? FLEXIBLE COLOR SYSTEM ACTIVE
   • NO FIXED COLOR ASSIGNMENTS
   • Any color ? Any material mapping
   • BricsCAD color picker integration
   • User-defined cost assignments

??? AGS ELEVATION SYSTEM (12 Variations)
   A=A-frame vs H=Hip | G=Garage vs N=None | S=Stucco vs H=Hardi vs B=Brick
   Combinations: AGS, AGB, AGH, ANS, ANB, ANH, HGS, HGB, HGH, HNS, HNB, HNH

?? LIVE FEATURES
   • Real-time quantity calculation
   • Excel feeder sheet integration  
   • Boundary version management
   • Mathematical precision algorithms

?? BRICSCAD V25 INTEGRATION
   • Proper transaction handling
   • Native BricsCAD API usage
   • XREF attachment system
   • BIM object recognition

?? PLUGIN USAGE
   1. Load: APPLOAD ? EnhancedTakeoffNativeUI_VS.brx
   2. Commands: ENHANCEDTAKEOFF, FLEXIBLECOLOR
   3. Pick colors, assign materials, map Excel cells
   4. Live updates, no restrictions!

Your Enhanced Construction Takeoff plugin is ready!
"@
        
        $form.Controls.Add($features)
        
        # Add close button
        $closeBtn = New-Object System.Windows.Forms.Button
        $closeBtn.Text = "Close Demo"
        $closeBtn.Location = New-Object System.Drawing.Point(250, 320)
        $closeBtn.Size = New-Object System.Drawing.Size(100, 30)
        $closeBtn.Add_Click({ $form.Close() })
        $form.Controls.Add($closeBtn)
        
        # Show form
        Write-Host "?? Launching Enhanced Construction Takeoff UI Demo..." -ForegroundColor Green
        $form.ShowDialog() | Out-Null
        
    } catch {
        Write-Host "?? Windows Forms error, using simple message box..." -ForegroundColor Yellow
        
        Add-Type -AssemblyName PresentationFramework
        $message = @"
?? Enhanced Construction Takeoff V25

? FLEXIBLE COLOR SYSTEM ACTIVE
? NO FIXED COLOR ASSIGNMENTS  
? Complete user control
? AGS elevation system
? Live Excel integration

Ready for BricsCAD V25!
"@
        [System.Windows.MessageBox]::Show($message, "Enhanced Construction Takeoff Demo", "OK", "Information")
    }
}

Write-Host "? Enhanced Construction Takeoff Demo Complete!" -ForegroundColor Green
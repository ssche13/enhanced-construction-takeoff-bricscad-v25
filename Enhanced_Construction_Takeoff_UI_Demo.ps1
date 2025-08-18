# Enhanced_Construction_Takeoff_UI_Demo.ps1 - Realistic UI Preview
# Shows the actual Enhanced Construction Takeoff plugin interface

Write-Host "?? Enhanced Construction Takeoff V25 - REALISTIC UI DEMO" -ForegroundColor Green
Write-Host "BricsCAD Plugin Interface Preview - NO FIXED COLORS" -ForegroundColor Cyan
Write-Host "======================================================" -ForegroundColor Yellow

# Create Windows Forms assemblies
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

# Create main form to match the actual BricsCAD plugin
$mainForm = New-Object System.Windows.Forms.Form
$mainForm.Text = "Enhanced Construction Takeoff V25 - BricsCAD Plugin"
$mainForm.Size = New-Object System.Drawing.Size(1200, 800)
$mainForm.StartPosition = "CenterScreen"
$mainForm.BackColor = [System.Drawing.Color]::FromArgb(240, 240, 240)
$mainForm.FormBorderStyle = "FixedDialog"
$mainForm.MaximizeBox = $false

# Title section
$titlePanel = New-Object System.Windows.Forms.Panel
$titlePanel.Location = New-Object System.Drawing.Point(10, 10)
$titlePanel.Size = New-Object System.Drawing.Size(1160, 60)
$titlePanel.BackColor = [System.Drawing.Color]::FromArgb(45, 45, 48)
$mainForm.Controls.Add($titlePanel)

$titleLabel = New-Object System.Windows.Forms.Label
$titleLabel.Text = "?? Enhanced Construction Takeoff V25"
$titleLabel.Font = New-Object System.Drawing.Font("Segoe UI", 18, [System.Drawing.FontStyle]::Bold)
$titleLabel.ForeColor = [System.Drawing.Color]::White
$titleLabel.Location = New-Object System.Drawing.Point(20, 15)
$titleLabel.Size = New-Object System.Drawing.Size(500, 30)
$titlePanel.Controls.Add($titleLabel)

$statusLabel = New-Object System.Windows.Forms.Label
$statusLabel.Text = "? FLEXIBLE COLOR SYSTEM ACTIVE - NO FIXED ASSIGNMENTS"
$statusLabel.Font = New-Object System.Drawing.Font("Segoe UI", 10, [System.Drawing.FontStyle]::Bold)
$statusLabel.ForeColor = [System.Drawing.Color]::LimeGreen
$statusLabel.Location = New-Object System.Drawing.Point(600, 20)
$statusLabel.Size = New-Object System.Drawing.Size(520, 20)
$titlePanel.Controls.Add($statusLabel)

# Top control panel (Plan selection)
$topPanel = New-Object System.Windows.Forms.GroupBox
$topPanel.Text = "?? Plan & Elevation Management"
$topPanel.Font = New-Object System.Drawing.Font("Segoe UI", 10, [System.Drawing.FontStyle]::Bold)
$topPanel.Location = New-Object System.Drawing.Point(20, 80)
$topPanel.Size = New-Object System.Drawing.Size(1150, 100)
$topPanel.BackColor = [System.Drawing.Color]::White
$mainForm.Controls.Add($topPanel)

# Area dropdown
$areaLabel = New-Object System.Windows.Forms.Label
$areaLabel.Text = "Area:"
$areaLabel.Location = New-Object System.Drawing.Point(20, 30)
$areaLabel.Size = New-Object System.Drawing.Size(60, 20)
$topPanel.Controls.Add($areaLabel)

$areaCombo = New-Object System.Windows.Forms.ComboBox
$areaCombo.Location = New-Object System.Drawing.Point(80, 27)
$areaCombo.Size = New-Object System.Drawing.Size(150, 25)
$areaCombo.DropDownStyle = "DropDownList"
$areaCombo.Items.AddRange(@("Southeast", "Southwest", "Northeast", "Northwest", "Midwest", "Custom"))
$areaCombo.SelectedIndex = 0
$topPanel.Controls.Add($areaCombo)

# Plan dropdown
$planLabel = New-Object System.Windows.Forms.Label
$planLabel.Text = "Plan:"
$planLabel.Location = New-Object System.Drawing.Point(250, 30)
$planLabel.Size = New-Object System.Drawing.Size(40, 20)
$topPanel.Controls.Add($planLabel)

$planCombo = New-Object System.Windows.Forms.ComboBox
$planCombo.Location = New-Object System.Drawing.Point(290, 27)
$planCombo.Size = New-Object System.Drawing.Size(100, 25)
$planCombo.DropDownStyle = "DropDownList"
$planCombo.Items.AddRange(@("Plan A", "Plan B", "Plan C", "Plan D"))
$planCombo.SelectedIndex = 0
$topPanel.Controls.Add($planCombo)

# AGS Elevation dropdown
$elevationLabel = New-Object System.Windows.Forms.Label
$elevationLabel.Text = "AGS Elevation:"
$elevationLabel.Location = New-Object System.Drawing.Point(410, 30)
$elevationLabel.Size = New-Object System.Drawing.Size(90, 20)
$topPanel.Controls.Add($elevationLabel)

$elevationCombo = New-Object System.Windows.Forms.ComboBox
$elevationCombo.Location = New-Object System.Drawing.Point(500, 27)
$elevationCombo.Size = New-Object System.Drawing.Size(200, 25)
$elevationCombo.DropDownStyle = "DropDownList"
$elevationCombo.Items.AddRange(@(
    "AGS - A-frame, Garage, Stucco",
    "AGB - A-frame, Garage, Brick", 
    "AGH - A-frame, Garage, Hardi",
    "ANS - A-frame, No garage, Stucco",
    "ANB - A-frame, No garage, Brick",
    "ANH - A-frame, No garage, Hardi",
    "HGS - Hip, Garage, Stucco",
    "HGB - Hip, Garage, Brick",
    "HGH - Hip, Garage, Hardi",
    "HNS - Hip, No garage, Stucco",
    "HNB - Hip, No garage, Brick",
    "HNH - Hip, No garage, Hardi"
))
$elevationCombo.SelectedIndex = 0
$topPanel.Controls.Add($elevationCombo)

# Auto refresh controls
$autoRefreshCheck = New-Object System.Windows.Forms.CheckBox
$autoRefreshCheck.Text = "Auto Refresh"
$autoRefreshCheck.Location = New-Object System.Drawing.Point(720, 30)
$autoRefreshCheck.Size = New-Object System.Drawing.Size(100, 20)
$autoRefreshCheck.Checked = $true
$topPanel.Controls.Add($autoRefreshCheck)

$refreshButton = New-Object System.Windows.Forms.Button
$refreshButton.Text = "?? Refresh Now"
$refreshButton.Location = New-Object System.Drawing.Point(830, 25)
$refreshButton.Size = New-Object System.Drawing.Size(120, 30)
$refreshButton.BackColor = [System.Drawing.Color]::LightBlue
$topPanel.Controls.Add($refreshButton)

$settingsButton = New-Object System.Windows.Forms.Button
$settingsButton.Text = "?? Settings"
$settingsButton.Location = New-Object System.Drawing.Point(960, 25)
$settingsButton.Size = New-Object System.Drawing.Size(100, 30)
$settingsButton.BackColor = [System.Drawing.Color]::LightGray
$topPanel.Controls.Add($settingsButton)

# Main content area with tabs
$mainTabControl = New-Object System.Windows.Forms.TabControl
$mainTabControl.Location = New-Object System.Drawing.Point(20, 190)
$mainTabControl.Size = New-Object System.Drawing.Size(1150, 520)
$mainTabControl.Font = New-Object System.Drawing.Font("Segoe UI", 9)
$mainForm.Controls.Add($mainTabControl)

# TAB 1: Color Assignment (Flexible System)
$colorTab = New-Object System.Windows.Forms.TabPage
$colorTab.Text = "?? Flexible Color Assignment"
$colorTab.BackColor = [System.Drawing.Color]::White

# Color assignment controls
$colorGroup = New-Object System.Windows.Forms.GroupBox
$colorGroup.Text = "User-Defined Color Assignments (NO FIXED COLORS)"
$colorGroup.Location = New-Object System.Drawing.Point(10, 10)
$colorGroup.Size = New-Object System.Drawing.Size(1120, 460)
$colorTab.Controls.Add($colorGroup)

# Color list
$colorList = New-Object System.Windows.Forms.ListView
$colorList.Location = New-Object System.Drawing.Point(20, 30)
$colorList.Size = New-Object System.Drawing.Size(800, 350)
$colorList.View = "Details"
$colorList.FullRowSelect = $true
$colorList.GridLines = $true

$colorList.Columns.Add("Color Index", 80)
$colorList.Columns.Add("Color Preview", 100)
$colorList.Columns.Add("Material Name", 150)
$colorList.Columns.Add("Unit Cost", 80)
$colorList.Columns.Add("Measurement", 80)
$colorList.Columns.Add("Excel Cell", 100)
$colorList.Columns.Add("Active", 60)
$colorList.Columns.Add("Quantity", 100)

# Add sample data
$sampleColors = @(
    @("1", "Red", "Interior Walls", "$2.50", "LF", "A15", "?", "2,450 LF"),
    @("5", "Blue", "Foundation", "$8.75", "LF", "B22", "?", "890 LF"),
    @("12", "Green", "Roofing", "$12.30", "SF", "C8", "?", "3,200 SF"),
    @("25", "Yellow", "Siding", "$6.45", "SF", "D12", "?", "1,850 SF"),
    @("30", "Orange", "Framing", "$4.20", "LF", "E5", "?", "5,600 LF"),
    @("User", "Purple", "Custom Material", "$15.00", "EA", "F9", "?", "45 EA")
)

foreach ($row in $sampleColors) {
    $item = New-Object System.Windows.Forms.ListViewItem($row[0])
    for ($i = 1; $i -lt $row.Count; $i++) {
        $item.SubItems.Add($row[$i])
    }
    $colorList.Items.Add($item)
}

$colorGroup.Controls.Add($colorList)

# Color assignment buttons
$pickColorBtn = New-Object System.Windows.Forms.Button
$pickColorBtn.Text = "?? Pick Color from Drawing"
$pickColorBtn.Location = New-Object System.Drawing.Point(840, 50)
$pickColorBtn.Size = New-Object System.Drawing.Size(180, 35)
$pickColorBtn.BackColor = [System.Drawing.Color]::LightGreen
$colorGroup.Controls.Add($pickColorBtn)

$matchColorBtn = New-Object System.Windows.Forms.Button
$matchColorBtn.Text = "?? Match Color by Index"
$matchColorBtn.Location = New-Object System.Drawing.Point(840, 95)
$matchColorBtn.Size = New-Object System.Drawing.Size(180, 35)
$matchColorBtn.BackColor = [System.Drawing.Color]::LightBlue
$colorGroup.Controls.Add($matchColorBtn)

$addMaterialBtn = New-Object System.Windows.Forms.Button
$addMaterialBtn.Text = "? Add New Material"
$addMaterialBtn.Location = New-Object System.Drawing.Point(840, 140)
$addMaterialBtn.Size = New-Object System.Drawing.Size(180, 35)
$addMaterialBtn.BackColor = [System.Drawing.Color]::LightYellow
$colorGroup.Controls.Add($addMaterialBtn)

$clearAssignBtn = New-Object System.Windows.Forms.Button
$clearAssignBtn.Text = "??? Clear Assignment"
$clearAssignBtn.Location = New-Object System.Drawing.Point(840, 185)
$clearAssignBtn.Size = New-Object System.Drawing.Size(180, 35)
$clearAssignBtn.BackColor = [System.Drawing.Color]::LightCoral
$colorGroup.Controls.Add($clearAssignBtn)

# Totals section
$totalsLabel = New-Object System.Windows.Forms.Label
$totalsLabel.Text = "?? Live Totals:"
$totalsLabel.Font = New-Object System.Drawing.Font("Segoe UI", 10, [System.Drawing.FontStyle]::Bold)
$totalsLabel.Location = New-Object System.Drawing.Point(840, 240)
$totalsLabel.Size = New-Object System.Drawing.Size(100, 20)
$colorGroup.Controls.Add($totalsLabel)

$totalCostLabel = New-Object System.Windows.Forms.Label
$totalCostLabel.Text = "Total Cost: $127,450.75"
$totalCostLabel.Location = New-Object System.Drawing.Point(840, 265)
$totalCostLabel.Size = New-Object System.Drawing.Size(180, 20)
$colorGroup.Controls.Add($totalCostLabel)

$mainTabControl.TabPages.Add($colorTab)

# TAB 2: Excel Integration
$excelTab = New-Object System.Windows.Forms.TabPage
$excelTab.Text = "?? Excel Feeder Sheets"
$excelTab.BackColor = [System.Drawing.Color]::White

$excelGroup = New-Object System.Windows.Forms.GroupBox
$excelGroup.Text = "Direct Excel Cell Mapping - Live Updates"
$excelGroup.Location = New-Object System.Drawing.Point(10, 10)
$excelGroup.Size = New-Object System.Drawing.Size(1120, 460)
$excelTab.Controls.Add($excelGroup)

# Excel connection
$excelPathLabel = New-Object System.Windows.Forms.Label
$excelPathLabel.Text = "Excel Workbook:"
$excelPathLabel.Location = New-Object System.Drawing.Point(20, 30)
$excelPathLabel.Size = New-Object System.Drawing.Size(100, 20)
$excelGroup.Controls.Add($excelPathLabel)

$excelPathText = New-Object System.Windows.Forms.TextBox
$excelPathText.Text = "C:\Projects\TakeoffTemplate.xlsx"
$excelPathText.Location = New-Object System.Drawing.Point(120, 27)
$excelPathText.Size = New-Object System.Drawing.Size(400, 25)
$excelGroup.Controls.Add($excelPathText)

$browseExcelBtn = New-Object System.Windows.Forms.Button
$browseExcelBtn.Text = "?? Browse"
$browseExcelBtn.Location = New-Object System.Drawing.Point(530, 25)
$browseExcelBtn.Size = New-Object System.Drawing.Size(80, 30)
$excelGroup.Controls.Add($browseExcelBtn)

$connectExcelBtn = New-Object System.Windows.Forms.Button
$connectExcelBtn.Text = "?? Connect"
$connectExcelBtn.Location = New-Object System.Drawing.Point(620, 25)
$connectExcelBtn.Size = New-Object System.Drawing.Size(80, 30)
$connectExcelBtn.BackColor = [System.Drawing.Color]::LightGreen
$excelGroup.Controls.Add($connectExcelBtn)

# Excel mapping list
$excelMappingList = New-Object System.Windows.Forms.ListView
$excelMappingList.Location = New-Object System.Drawing.Point(20, 70)
$excelMappingList.Size = New-Object System.Drawing.Size(800, 300)
$excelMappingList.View = "Details"
$excelMappingList.FullRowSelect = $true
$excelMappingList.GridLines = $true

$excelMappingList.Columns.Add("Material", 150)
$excelMappingList.Columns.Add("Worksheet", 100)
$excelMappingList.Columns.Add("Cell", 60)
$excelMappingList.Columns.Add("Current Value", 100)
$excelMappingList.Columns.Add("Live Quantity", 120)
$excelMappingList.Columns.Add("Formula", 200)
$excelMappingList.Columns.Add("Status", 70)

# Add sample Excel mappings
$excelMappings = @(
    @("Interior Walls", "Feeder", "A15", "2450", "2,450 LF", "=A15*$Z$5", "? Live"),
    @("Foundation", "Feeder", "B22", "890", "890 LF", "=B22*$Z$8", "? Live"),
    @("Roofing", "Materials", "C8", "3200", "3,200 SF", "=C8*VLOOKUP(D8,Costs,2)", "? Live"),
    @("Siding", "Feeder", "D12", "1850", "1,850 SF", "=D12*1.1", "? Live"),
    @("Framing", "Structure", "E5", "5600", "5,600 LF", "=E5*CostTable!F12", "? Live")
)

foreach ($row in $excelMappings) {
    $item = New-Object System.Windows.Forms.ListViewItem($row[0])
    for ($i = 1; $i -lt $row.Count; $i++) {
        $item.SubItems.Add($row[$i])
    }
    $excelMappingList.Items.Add($item)
}

$excelGroup.Controls.Add($excelMappingList)

# Excel controls
$mapCellBtn = New-Object System.Windows.Forms.Button
$mapCellBtn.Text = "?? Map to Cell"
$mapCellBtn.Location = New-Object System.Drawing.Point(840, 100)
$mapCellBtn.Size = New-Object System.Drawing.Size(120, 35)
$mapCellBtn.BackColor = [System.Drawing.Color]::LightBlue
$excelGroup.Controls.Add($mapCellBtn)

$updateNowBtn = New-Object System.Windows.Forms.Button
$updateNowBtn.Text = "?? Update Now"
$updateNowBtn.Location = New-Object System.Drawing.Point(840, 145)
$updateNowBtn.Size = New-Object System.Drawing.Size(120, 35)
$updateNowBtn.BackColor = [System.Drawing.Color]::LightGreen
$excelGroup.Controls.Add($updateNowBtn)

$preserveFormulasCheck = New-Object System.Windows.Forms.CheckBox
$preserveFormulasCheck.Text = "Preserve Formulas"
$preserveFormulasCheck.Location = New-Object System.Drawing.Point(840, 200)
$preserveFormulasCheck.Size = New-Object System.Drawing.Size(140, 20)
$preserveFormulasCheck.Checked = $true
$excelGroup.Controls.Add($preserveFormulasCheck)

$mainTabControl.TabPages.Add($excelTab)

# TAB 3: Boundary Management
$boundaryTab = New-Object System.Windows.Forms.TabPage
$boundaryTab.Text = "?? Boundary Version Management"
$boundaryTab.BackColor = [System.Drawing.Color]::White

$boundaryGroup = New-Object System.Windows.Forms.GroupBox
$boundaryGroup.Text = "AGS Version Control & Boundary Boxes"
$boundaryGroup.Location = New-Object System.Drawing.Point(10, 10)
$boundaryGroup.Size = New-Object System.Drawing.Size(1120, 460)
$boundaryTab.Controls.Add($boundaryGroup)

# Boundary tree
$boundaryTree = New-Object System.Windows.Forms.TreeView
$boundaryTree.Location = New-Object System.Drawing.Point(20, 30)
$boundaryTree.Size = New-Object System.Drawing.Size(400, 350)
$boundaryTree.CheckBoxes = $true

# Add sample boundary structure
$planANode = New-Object System.Windows.Forms.TreeNode("?? Plan A")
$agsNode = New-Object System.Windows.Forms.TreeNode("AGS - A-frame, Garage, Stucco")
$agsNode.Checked = $true
$agbNode = New-Object System.Windows.Forms.TreeNode("AGB - A-frame, Garage, Brick")
$planANode.Nodes.Add($agsNode)
$planANode.Nodes.Add($agbNode)

$planBNode = New-Object System.Windows.Forms.TreeNode("?? Plan B")
$hgsNode = New-Object System.Windows.Forms.TreeNode("HGS - Hip, Garage, Stucco")
$hgsNode.Checked = $true
$planBNode.Nodes.Add($hgsNode)

$boundaryTree.Nodes.Add($planANode)
$boundaryTree.Nodes.Add($planBNode)
$boundaryTree.ExpandAll()

$boundaryGroup.Controls.Add($boundaryTree)

# Version details
$versionDetailsGroup = New-Object System.Windows.Forms.GroupBox
$versionDetailsGroup.Text = "Version Details"
$versionDetailsGroup.Location = New-Object System.Drawing.Point(440, 30)
$versionDetailsGroup.Size = New-Object System.Drawing.Size(350, 200)
$boundaryGroup.Controls.Add($versionDetailsGroup)

$versionDetails = New-Object System.Windows.Forms.TextBox
$versionDetails.Multiline = $true
$versionDetails.ReadOnly = $true
$versionDetails.ScrollBars = "Vertical"
$versionDetails.Location = New-Object System.Drawing.Point(10, 20)
$versionDetails.Size = New-Object System.Drawing.Size(330, 170)
$versionDetails.Text = @"
ACTIVE VERSION: AGS
????????????????????????????

A = A-frame roof structure
G = Garage included
S = Stucco exterior siding

BOUNDARY COLORS ACTIVE:
• Color 1  ? Interior Walls
• Color 5  ? Foundation  
• Color 12 ? Roofing
• Color 25 ? Siding (Stucco)
• Color 30 ? Framing

VERSION CHANGES:
If switched to AGB:
• Color 25 ? Brick siding
• All other colors unchanged

TOTAL QUANTITIES:
LF: 8,940 | SF: 5,050 | EA: 45
"@
$versionDetailsGroup.Controls.Add($versionDetails)

# Boundary controls
$createBoundaryBtn = New-Object System.Windows.Forms.Button
$createBoundaryBtn.Text = "?? Create Boundary"
$createBoundaryBtn.Location = New-Object System.Drawing.Point(810, 60)
$createBoundaryBtn.Size = New-Object System.Drawing.Size(140, 35)
$createBoundaryBtn.BackColor = [System.Drawing.Color]::LightGreen
$boundaryGroup.Controls.Add($createBoundaryBtn)

$switchVersionBtn = New-Object System.Windows.Forms.Button
$switchVersionBtn.Text = "?? Switch Version"
$switchVersionBtn.Location = New-Object System.Drawing.Point(810, 105)
$switchVersionBtn.Size = New-Object System.Drawing.Size(140, 35)
$switchVersionBtn.BackColor = [System.Drawing.Color]::LightBlue
$boundaryGroup.Controls.Add($switchVersionBtn)

$mainTabControl.TabPages.Add($boundaryTab)

# Bottom status bar
$statusBar = New-Object System.Windows.Forms.StatusStrip
$statusBar.BackColor = [System.Drawing.Color]::FromArgb(45, 45, 48)

$connectionStatus = New-Object System.Windows.Forms.ToolStripStatusLabel
$connectionStatus.Text = "?? BricsCAD V25 Connected"
$connectionStatus.ForeColor = [System.Drawing.Color]::LimeGreen

$pluginStatus = New-Object System.Windows.Forms.ToolStripStatusLabel
$pluginStatus.Text = "?? Flexible System Active"
$pluginStatus.ForeColor = [System.Drawing.Color]::Yellow

$quantityStatus = New-Object System.Windows.Forms.ToolStripStatusLabel
$quantityStatus.Text = "?? Live Updates: ON"
$quantityStatus.ForeColor = [System.Drawing.Color]::LightBlue

$statusBar.Items.Add($connectionStatus)
$statusBar.Items.Add($pluginStatus)
$statusBar.Items.Add($quantityStatus)
$mainForm.Controls.Add($statusBar)

# Add event handlers for interactivity
$pickColorBtn.Add_Click({
    [System.Windows.Forms.MessageBox]::Show("?? BricsCAD Color Picker would launch here!`n`nUser can pick ANY color from the drawing`nNo restrictions - complete flexibility", "Color Picker", "OK", "Information")
})

$refreshButton.Add_Click({
    [System.Windows.Forms.MessageBox]::Show("?? Live quantities refreshed!`n`nAll values updated from BricsCAD drawing`nExcel cells updated automatically", "Refresh Complete", "OK", "Information")
})

$connectExcelBtn.Add_Click({
    [System.Windows.Forms.MessageBox]::Show("?? Connected to Excel workbook!`n`nFormulas preserved`nLive updates enabled`nDirect cell mapping active", "Excel Connected", "OK", "Information")
})

$elevationCombo.Add_SelectedIndexChanged({
    $selectedElevation = $elevationCombo.SelectedItem.ToString()
    [System.Windows.Forms.MessageBox]::Show("??? Switched to: $selectedElevation`n`nBoundary colors updated`nQuantities recalculated`nExcel cells refreshed", "Version Switched", "OK", "Information")
})

# Show the realistic UI demo
Write-Host "?? Launching Enhanced Construction Takeoff Realistic UI Demo..." -ForegroundColor Green
Write-Host "This shows what the actual BricsCAD plugin interface will look like!" -ForegroundColor Cyan

$mainForm.ShowDialog() | Out-Null

Write-Host "? UI Demo Complete!" -ForegroundColor Green
Write-Host "This demonstrates the actual Enhanced Construction Takeoff plugin interface!" -ForegroundColor Yellow
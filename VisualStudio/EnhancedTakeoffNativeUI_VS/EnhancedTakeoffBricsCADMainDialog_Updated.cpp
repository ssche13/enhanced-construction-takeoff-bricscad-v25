// EnhancedTakeoffBricsCADMainDialog.cpp - Main Dialog Implementation
// Enhanced Construction Takeoff - BricsCAD V25
// COPILOT-HINT: NO FIXED COLORS - All user-defined assignments

#include "pch.h"
#include "EnhancedTakeoffBricsCADMainDialog.h"
#include "FlexibleColorAssignment.h"
#include "AttachmentManager.h"
#include "BoundaryVersionManager.h"
#include "FeederSheetManager.h"

#ifdef HAS_BRX_SDK
#include "acedads.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "acutads.h"
#endif

using namespace EnhancedTakeoff;

IMPLEMENT_DYNAMIC(CEnhancedTakeoffBricsCADMainDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CEnhancedTakeoffBricsCADMainDialog, CDialogEx)
    ON_BN_CLICKED(IDC_PICK_COLOR, &CEnhancedTakeoffBricsCADMainDialog::OnPickColor)
    ON_BN_CLICKED(IDC_MATCH_COLOR, &CEnhancedTakeoffBricsCADMainDialog::OnMatchColor)
    ON_BN_CLICKED(IDC_REFRESH_BTN, &CEnhancedTakeoffBricsCADMainDialog::OnRefreshQuantities)
    ON_BN_CLICKED(IDC_EXPORT_EXCEL_BTN, &CEnhancedTakeoffBricsCADMainDialog::OnExportExcel)
    ON_CBN_SELCHANGE(IDC_AREA_COMBO, &CEnhancedTakeoffBricsCADMainDialog::OnAreaSelChange)
    ON_CBN_SELCHANGE(IDC_PLAN_COMBO, &CEnhancedTakeoffBricsCADMainDialog::OnPlanSelChange)
    ON_CBN_SELCHANGE(IDC_ELEVATION_COMBO, &CEnhancedTakeoffBricsCADMainDialog::OnElevationSelChange)
    ON_BN_CLICKED(IDC_AUTO_REFRESH_CHECK, &CEnhancedTakeoffBricsCADMainDialog::OnAutoRefreshToggle)
    ON_WM_TIMER()
    
    // Legacy method mappings for compatibility
    ON_BN_CLICKED(IDC_PICK_COLOR, &CEnhancedTakeoffBricsCADMainDialog::OnBnClickedPickColor)
    ON_BN_CLICKED(IDC_MATCH_COLOR, &CEnhancedTakeoffBricsCADMainDialog::OnBnClickedMatchColor)
    ON_BN_CLICKED(IDC_REFRESH_BTN, &CEnhancedTakeoffBricsCADMainDialog::OnBnClickedRefresh)
    ON_BN_CLICKED(IDC_EXPORT_EXCEL_BTN, &CEnhancedTakeoffBricsCADMainDialog::OnBnClickedExportExcel)
    ON_CBN_SELCHANGE(IDC_ATTACHMENT_COMBO, &CEnhancedTakeoffBricsCADMainDialog::OnAttachmentSelChange)
    ON_CBN_SELCHANGE(IDC_VERSION_COMBO, &CEnhancedTakeoffBricsCADMainDialog::OnVersionSelChange)
    ON_BN_CLICKED(IDC_AUTO_REFRESH, &CEnhancedTakeoffBricsCADMainDialog::OnAutoRefreshToggle)
END_MESSAGE_MAP()

CEnhancedTakeoffBricsCADMainDialog::CEnhancedTakeoffBricsCADMainDialog(CWnd* pParent)
    : CDialogEx(IDD_ENHANCED_TAKEOFF_MAIN, pParent)
    , m_autoRefreshEnabled(false)
    , m_refreshTimerID(0)
{
    // Initialize flexible managers - NO FIXED SYSTEMS
    m_pColorAssignment = std::make_unique<FlexibleColorAssignment>();
    m_pAttachmentMgr = std::make_unique<AttachmentManager>();
    m_pBoundaryMgr = std::make_unique<BoundaryVersionManager>();
    m_pFeederSheet = std::make_unique<FeederSheetManager>();
}

CEnhancedTakeoffBricsCADMainDialog::~CEnhancedTakeoffBricsCADMainDialog()
{
    if (m_refreshTimerID) {
        KillTimer(m_refreshTimerID);
    }
}

BOOL CEnhancedTakeoffBricsCADMainDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    
    // Initialize elevation variations (AGS system)
    InitializeElevationVariations();
    
    // Set up flexible color assignment callbacks
    m_pColorAssignment->RegisterColorChangeCallback(
        [this](int colorIndex) { OnColorAssignmentChanged(colorIndex); }
    );
    
    // Initialize UI
    InitializeDropdowns();
    InitializeColorList();
    InitializeQuantityList();
    InitializeAttachmentTree();
    
    // Set window title
    SetWindowText(_T("Enhanced Construction Takeoff - BricsCAD V25 (Flexible System)"));
    
    return TRUE;
}

void CEnhancedTakeoffBricsCADMainDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_AREA_COMBO, m_areaCombo);
    DDX_Control(pDX, IDC_PLAN_COMBO, m_planCombo);
    DDX_Control(pDX, IDC_ELEVATION_COMBO, m_elevationCombo);
    DDX_Control(pDX, IDC_COLOR_LIST, m_colorList);
    DDX_Control(pDX, IDC_QUANTITY_LIST, m_quantityList);
    DDX_Control(pDX, IDC_ATTACHMENT_TREE, m_attachmentTree);
    DDX_Control(pDX, IDC_MATERIAL_TYPE_COMBO, m_materialTypeCombo);
    DDX_Control(pDX, IDC_EXCEL_CELL_EDIT, m_excelCellEdit);
    DDX_Control(pDX, IDC_UNIT_COST_EDIT, m_unitCostEdit);
    DDX_Control(pDX, IDC_PITCH_VALUE_EDIT, m_pitchValueEdit);
    DDX_Control(pDX, IDC_PITCH_MODIFIER_CHECK, m_pitchModifierCheck);
    DDX_Control(pDX, IDC_AUTO_REFRESH_CHECK, m_autoRefreshCheck);
}

void CEnhancedTakeoffBricsCADMainDialog::InitializeElevationVariations()
{
    // Initialize AGS elevation system
    m_elevationVariations = {
        {"AGS", "A-Frame + Garage + Stucco", 'A', 'G', 'S'},
        {"AGB", "A-Frame + Garage + Brick", 'A', 'G', 'B'},
        {"AGH", "A-Frame + Garage + Hardi", 'A', 'G', 'H'},
        {"ANS", "A-Frame + No Garage + Stucco", 'A', 'N', 'S'},
        {"ANB", "A-Frame + No Garage + Brick", 'A', 'N', 'B'},
        {"ANH", "A-Frame + No Garage + Hardi", 'A', 'N', 'H'},
        {"HGS", "Hip Roof + Garage + Stucco", 'H', 'G', 'S'},
        {"HGB", "Hip Roof + Garage + Brick", 'H', 'G', 'B'},
        {"HGH", "Hip Roof + Garage + Hardi", 'H', 'G', 'H'},
        {"HNS", "Hip Roof + No Garage + Stucco", 'H', 'N', 'S'},
        {"HNB", "Hip Roof + No Garage + Brick", 'H', 'N', 'B'},
        {"HNH", "Hip Roof + No Garage + Hardi", 'H', 'N', 'H'}
    };
}

// Main event handlers
void CEnhancedTakeoffBricsCADMainDialog::OnPickColor()
{
    // Use BricsCAD color picker - NO FIXED ASSIGNMENTS
    FlexibleColorAssignment::ColorAssignment assignment;
    
    if (m_pColorAssignment->ShowColorPicker(assignment)) {
        // User picked a color and defined material - completely flexible
        m_pColorAssignment->AssignColor(assignment.colorIndex, assignment);
        UpdateColorList();
        RefreshQuantities();
        
        AfxMessageBox(_T("Color assignment created successfully!"));
    }
}

void CEnhancedTakeoffBricsCADMainDialog::OnMatchColor()
{
    // Match color from existing entity
#ifdef HAS_BRX_SDK
    ads_name ename;
    ads_point pt;
    
    acutPrintf(_T("\nSelect entity to match color: "));
    if (acedEntSel(NULL, ename, pt) == RTNORM) {
        AcDbObjectId objId;
        acdbGetObjectId(objId, ename);
        
        FlexibleColorAssignment::ColorAssignment assignment;
        if (m_pColorAssignment->MatchColorFromEntity(objId, assignment)) {
            // Let user define what this color represents
            CString materialName;
            if (GetMaterialNameFromUser(materialName)) {
                assignment.materialName = CT2A(materialName);
                
                // Get additional details from user
                if (GetAssignmentDetailsFromUser(assignment)) {
                    m_pColorAssignment->AssignColor(assignment.colorIndex, assignment);
                    UpdateColorList();
                    RefreshQuantities();
                }
            }
        }
    }
#else
    AfxMessageBox(_T("Color matching requires BricsCAD SDK integration."));
#endif
}

void CEnhancedTakeoffBricsCADMainDialog::OnAreaSelChange()
{
    int sel = m_areaCombo.GetCurSel();
    if (sel != CB_ERR) {
        CString area;
        m_areaCombo.GetLBText(sel, area);
        m_currentArea = CT2A(area);
        
        // Update plan combo based on selected area
        PopulatePlanCombo(m_currentArea);
        
        // Disable elevation until plan is selected
        m_elevationCombo.EnableWindow(FALSE);
        m_elevationCombo.ResetContent();
    }
}

void CEnhancedTakeoffBricsCADMainDialog::OnPlanSelChange()
{
    int sel = m_planCombo.GetCurSel();
    if (sel != CB_ERR) {
        CString plan;
        m_planCombo.GetLBText(sel, plan);
        m_currentPlan = CT2A(plan);
        
        // Update elevation combo based on selected plan
        PopulateElevationCombo(m_currentPlan);
        
        // Enable elevation selection
        m_elevationCombo.EnableWindow(TRUE);
    }
}

void CEnhancedTakeoffBricsCADMainDialog::OnElevationSelChange()
{
    int sel = m_elevationCombo.GetCurSel();
    if (sel != CB_ERR) {
        CString elevation;
        m_elevationCombo.GetLBText(sel, elevation);
        m_currentElevation = CT2A(elevation);
        
        // Apply elevation variation
        ApplyElevationVariation(m_currentElevation);
        RefreshQuantities();
    }
}

void CEnhancedTakeoffBricsCADMainDialog::ApplyElevationVariation(const std::string& elevationCode)
{
    if (elevationCode.length() < 3) return;
    
    // Apply the elevation using AttachmentManager
    if (m_pAttachmentMgr && !m_currentPlan.empty()) {
        m_pAttachmentMgr->ApplyElevationVariation(m_currentPlan, elevationCode);
    }
    
    // Update UI to reflect the change
    UpdateUIState();
}

void CEnhancedTakeoffBricsCADMainDialog::OnRefreshQuantities()
{
    RefreshQuantities();
    AfxMessageBox(_T("Quantities refreshed successfully!"));
}

void CEnhancedTakeoffBricsCADMainDialog::RefreshQuantities()
{
    m_quantityList.DeleteAllItems();
    
    // Calculate quantities based on active colors and boundaries
    auto assignments = m_pColorAssignment->GetAllAssignments();
    
    int row = 0;
    double totalCost = 0.0;
    
    for (const auto& assignment : assignments) {
        if (assignment.isActive) {
            // Calculate quantities for this color
            double quantity = CalculateColorQuantity(assignment.colorIndex);
            double cost = m_pColorAssignment->CalculateCost(assignment.colorIndex, quantity);
            
            CString colorStr;
            colorStr.Format(_T("%d"), assignment.colorIndex);
            m_quantityList.InsertItem(row, colorStr);
            
            m_quantityList.SetItemText(row, 1, CString(assignment.materialName.c_str()));
            
            CString qtyStr;
            qtyStr.Format(_T("%.2f"), quantity);
            m_quantityList.SetItemText(row, 2, qtyStr);
            
            // Show measurement unit
            if (!assignment.measurementTypes.empty()) {
                CString unitStr = GetMeasurementTypeString(assignment.measurementTypes[0]);
                m_quantityList.SetItemText(row, 3, unitStr);
            }
            
            CString costStr;
            costStr.Format(_T("$%.2f"), assignment.unitCost);
            m_quantityList.SetItemText(row, 4, costStr);
            
            CString totalStr;
            totalStr.Format(_T("$%.2f"), cost);
            m_quantityList.SetItemText(row, 5, totalStr);
            
            totalCost += cost;
            row++;
        }
    }
    
    // Update total cost display
    UpdateTotalCostDisplay(totalCost);
}

void CEnhancedTakeoffBricsCADMainDialog::OnExportExcel()
{
    // Connect to Excel and export with flexible mappings
    CString excelPath;
    if (GetExcelPathFromUser(excelPath)) {
        if (m_pFeederSheet->ConnectToWorkbook(CT2A(excelPath))) {
            // Map colors to cells based on user assignments
            auto assignments = m_pColorAssignment->GetAllAssignments();
            
            int exported = 0;
            for (const auto& assignment : assignments) {
                if (!assignment.excelCell.empty()) {
                    double qty = CalculateColorQuantity(assignment.colorIndex);
                    if (m_pFeederSheet->UpdateCellValue(assignment.colorIndex, qty)) {
                        exported++;
                    }
                }
            }
            
            m_pFeederSheet->RefreshAllCells();
            
            CString message;
            message.Format(_T("Exported %d color assignments to Excel successfully!"), exported);
            AfxMessageBox(message);
        } else {
            AfxMessageBox(_T("Failed to connect to Excel workbook."));
        }
    }
}

void CEnhancedTakeoffBricsCADMainDialog::OnAutoRefreshToggle()
{
    m_autoRefreshEnabled = m_autoRefreshCheck.GetCheck() == BST_CHECKED;
    
    if (m_autoRefreshEnabled) {
        m_refreshTimerID = SetTimer(1, 500, NULL); // 500ms interval
    } else {
        if (m_refreshTimerID) {
            KillTimer(m_refreshTimerID);
            m_refreshTimerID = 0;
        }
    }
}

void CEnhancedTakeoffBricsCADMainDialog::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == m_refreshTimerID && m_autoRefreshEnabled) {
        RefreshQuantities();
    }
    CDialogEx::OnTimer(nIDEvent);
}

// Helper methods implementation
double CEnhancedTakeoffBricsCADMainDialog::CalculateColorQuantity(int colorIndex)
{
    // Placeholder calculation - real implementation would scan drawing for entities
    // This would integrate with BricsCAD to calculate actual quantities
    return 100.0 + (colorIndex * 10.0);
}

bool CEnhancedTakeoffBricsCADMainDialog::GetMaterialNameFromUser(CString& materialName)
{
    // Simple input - real implementation would show material selection dialog
    materialName = _T("User Defined Material");
    return true;
}

bool CEnhancedTakeoffBricsCADMainDialog::GetAssignmentDetailsFromUser(FlexibleColorAssignment::ColorAssignment& assignment)
{
    // Real implementation would show detailed assignment dialog
    assignment.unitCost = 1.50; // Default
    assignment.excelCell = "B15"; // Default
    return true;
}

bool CEnhancedTakeoffBricsCADMainDialog::GetExcelPathFromUser(CString& excelPath)
{
    CFileDialog dlg(TRUE, _T("xlsx"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                   _T("Excel Files (*.xlsx)|*.xlsx|All Files (*.*)|*.*||"));
    
    if (dlg.DoModal() == IDOK) {
        excelPath = dlg.GetPathName();
        return true;
    }
    return false;
}

void CEnhancedTakeoffBricsCADMainDialog::UpdateTotalCostDisplay(double totalCost)
{
    CString totalText;
    totalText.Format(_T("Total Cost: $%.2f"), totalCost);
    SetDlgItemText(IDC_TOTAL_COST_STATIC, totalText);
}

CString CEnhancedTakeoffBricsCADMainDialog::GetMeasurementTypeString(FlexibleColorAssignment::MeasurementType type)
{
    switch (type) {
        case FlexibleColorAssignment::MeasurementType::LF: return _T("LF");
        case FlexibleColorAssignment::MeasurementType::SF: return _T("SF");
        case FlexibleColorAssignment::MeasurementType::EA: return _T("EA");
        case FlexibleColorAssignment::MeasurementType::LF_PITCH: return _T("LF_PITCH");
        case FlexibleColorAssignment::MeasurementType::SF_PITCH: return _T("SF_PITCH");
        case FlexibleColorAssignment::MeasurementType::LF_HIP: return _T("LF_HIP");
        case FlexibleColorAssignment::MeasurementType::CUSTOM: return _T("CUSTOM");
        default: return _T("LF");
    }
}

// Placeholder implementations for UI initialization methods
void CEnhancedTakeoffBricsCADMainDialog::InitializeDropdowns() 
{
    PopulateAreaCombo();
    // Plan and elevation combos are populated dynamically
}

void CEnhancedTakeoffBricsCADMainDialog::PopulateAreaCombo()
{
    m_areaCombo.ResetContent();
    m_areaCombo.AddString(_T("Southeast"));
    m_areaCombo.AddString(_T("Southwest"));
    m_areaCombo.AddString(_T("Northeast"));
    m_areaCombo.AddString(_T("Northwest"));
    m_areaCombo.AddString(_T("Midwest"));
    m_areaCombo.AddString(_T("Custom"));
}

void CEnhancedTakeoffBricsCADMainDialog::PopulatePlanCombo(const std::string& selectedArea)
{
    m_planCombo.ResetContent();
    m_planCombo.EnableWindow(TRUE);
    
    // Add standard plans
    m_planCombo.AddString(_T("Plan A"));
    m_planCombo.AddString(_T("Plan B"));
    m_planCombo.AddString(_T("Plan C"));
    m_planCombo.AddString(_T("Plan D"));
    
    // Area-specific plans could be added here
}

void CEnhancedTakeoffBricsCADMainDialog::PopulateElevationCombo(const std::string& selectedPlan)
{
    m_elevationCombo.ResetContent();
    m_elevationCombo.EnableWindow(TRUE);
    
    // Add all AGS elevation variations
    for (const auto& elevation : m_elevationVariations) {
        CString text;
        text.Format(_T("%s - %s"), CString(elevation.code.c_str()), 
                   CString(elevation.description.c_str()));
        m_elevationCombo.AddString(text);
    }
}

void CEnhancedTakeoffBricsCADMainDialog::InitializeColorList()
{
    // Setup color list control
    m_colorList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    
    m_colorList.InsertColumn(0, _T("Color"), LVCFMT_LEFT, 60);
    m_colorList.InsertColumn(1, _T("Material"), LVCFMT_LEFT, 120);
    m_colorList.InsertColumn(2, _T("Unit Cost"), LVCFMT_RIGHT, 80);
    m_colorList.InsertColumn(3, _T("Excel Cell"), LVCFMT_LEFT, 80);
    m_colorList.InsertColumn(4, _T("Active"), LVCFMT_CENTER, 60);
}

void CEnhancedTakeoffBricsCADMainDialog::InitializeQuantityList()
{
    // Setup quantity list control
    m_quantityList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    
    m_quantityList.InsertColumn(0, _T("Color"), LVCFMT_LEFT, 60);
    m_quantityList.InsertColumn(1, _T("Material"), LVCFMT_LEFT, 120);
    m_quantityList.InsertColumn(2, _T("Quantity"), LVCFMT_RIGHT, 80);
    m_quantityList.InsertColumn(3, _T("Unit"), LVCFMT_CENTER, 60);
    m_quantityList.InsertColumn(4, _T("Unit Cost"), LVCFMT_RIGHT, 80);
    m_quantityList.InsertColumn(5, _T("Total Cost"), LVCFMT_RIGHT, 100);
}

void CEnhancedTakeoffBricsCADMainDialog::InitializeAttachmentTree()
{
    // Initialize tree control for attachment management
    // Real implementation would populate with actual attachments
}

void CEnhancedTakeoffBricsCADMainDialog::UpdateColorList()
{
    m_colorList.DeleteAllItems();
    
    auto assignments = m_pColorAssignment->GetAllAssignments();
    int row = 0;
    
    for (const auto& assignment : assignments) {
        CString colorStr;
        colorStr.Format(_T("%d"), assignment.colorIndex);
        m_colorList.InsertItem(row, colorStr);
        
        m_colorList.SetItemText(row, 1, CString(assignment.materialName.c_str()));
        
        CString costStr;
        costStr.Format(_T("$%.2f"), assignment.unitCost);
        m_colorList.SetItemText(row, 2, costStr);
        
        m_colorList.SetItemText(row, 3, CString(assignment.excelCell.c_str()));
        m_colorList.SetItemText(row, 4, assignment.isActive ? _T("Yes") : _T("No"));
        
        row++;
    }
}

void CEnhancedTakeoffBricsCADMainDialog::UpdateUIState()
{
    // Update UI state based on current selections
    bool hasArea = !m_currentArea.empty();
    bool hasPlan = !m_currentPlan.empty();
    bool hasElevation = !m_currentElevation.empty();
    
    // Enable/disable controls based on state
    m_planCombo.EnableWindow(hasArea);
    m_elevationCombo.EnableWindow(hasPlan);
    
    // Update status or other UI elements as needed
}

void CEnhancedTakeoffBricsCADMainDialog::OnColorAssignmentChanged(int colorIndex)
{
    // Handle color assignment change
    UpdateColorList();
    if (m_autoRefreshEnabled) {
        RefreshQuantities();
    }
}

// Legacy compatibility method implementations
void CEnhancedTakeoffBricsCADMainDialog::OnBnClickedPickColor() { OnPickColor(); }
void CEnhancedTakeoffBricsCADMainDialog::OnBnClickedMatchColor() { OnMatchColor(); }
void CEnhancedTakeoffBricsCADMainDialog::OnBnClickedRefresh() { OnRefreshQuantities(); }
void CEnhancedTakeoffBricsCADMainDialog::OnBnClickedExportExcel() { OnExportExcel(); }

// Additional placeholder methods
void CEnhancedTakeoffBricsCADMainDialog::OnAttachmentSelChange() {}
void CEnhancedTakeoffBricsCADMainDialog::OnVersionSelChange() {}
void CEnhancedTakeoffBricsCADMainDialog::OnAssignToBoundary() {}
void CEnhancedTakeoffBricsCADMainDialog::OnToggleAttachment() {}
void CEnhancedTakeoffBricsCADMainDialog::OnColorListSelChange() {}
void CEnhancedTakeoffBricsCADMainDialog::OnExcelCellChange() {}
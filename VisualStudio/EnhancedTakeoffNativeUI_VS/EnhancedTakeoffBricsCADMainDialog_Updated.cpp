// EnhancedTakeoffBricsCADMainDialog.cpp - Updated with flexible system
// COPILOT-HINT: NO FIXED COLORS - All user-defined assignments
#include "pch.h"
#include "EnhancedTakeoffBricsCADMainDialog.h"

// NEW: Flexible system includes (replacing ColorMaterialMapper)
#include "FlexibleColorAssignment.h"
#include "AttachmentManager.h"
#include "BoundaryVersionManager.h"
#include "FeederSheetManager.h"
#include "FlexibilityAdapter.h"

#ifdef HAS_BRX_SDK
#include "acedads.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "acutads.h"
#endif

// Dialog resource IDs
#define IDD_ENHANCED_TAKEOFF_MAIN   2000
#define IDC_COLOR_LIST              1001
#define IDC_PICK_COLOR              1002
#define IDC_MATCH_COLOR             1003
#define IDC_ATTACHMENT_COMBO        1004
#define IDC_VERSION_COMBO           1005
#define IDC_AREA_COMBO              1006
#define IDC_QUANTITY_LIST           1007
#define IDC_REFRESH_BTN             1008
#define IDC_EXPORT_EXCEL            1009
#define IDC_BOUNDARY_TREE           1010
#define IDC_AUTO_REFRESH            1011

using namespace EnhancedTakeoff;

IMPLEMENT_DYNAMIC(CEnhancedTakeoffBricsCADMainDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CEnhancedTakeoffBricsCADMainDialog, CDialogEx)
    ON_BN_CLICKED(IDC_PICK_COLOR, &CEnhancedTakeoffBricsCADMainDialog::OnBnClickedPickColor)
    ON_BN_CLICKED(IDC_MATCH_COLOR, &CEnhancedTakeoffBricsCADMainDialog::OnBnClickedMatchColor)
    ON_BN_CLICKED(IDC_REFRESH_BTN, &CEnhancedTakeoffBricsCADMainDialog::OnBnClickedRefresh)
    ON_BN_CLICKED(IDC_EXPORT_EXCEL, &CEnhancedTakeoffBricsCADMainDialog::OnBnClickedExportExcel)
    ON_CBN_SELCHANGE(IDC_ATTACHMENT_COMBO, &CEnhancedTakeoffBricsCADMainDialog::OnAttachmentSelChange)
    ON_CBN_SELCHANGE(IDC_VERSION_COMBO, &CEnhancedTakeoffBricsCADMainDialog::OnVersionSelChange)
    ON_CBN_SELCHANGE(IDC_AREA_COMBO, &CEnhancedTakeoffBricsCADMainDialog::OnAreaSelChange)
    ON_BN_CLICKED(IDC_AUTO_REFRESH, &CEnhancedTakeoffBricsCADMainDialog::OnAutoRefreshToggle)
    ON_WM_TIMER()
END_MESSAGE_MAP()

CEnhancedTakeoffBricsCADMainDialog::CEnhancedTakeoffBricsCADMainDialog(CWnd* pParent)
    : CDialogEx(IDD_ENHANCED_TAKEOFF_MAIN, pParent)
    , m_pColorList(nullptr)
    , m_pQuantityList(nullptr)
    , m_pAttachmentCombo(nullptr)
    , m_pVersionCombo(nullptr)
    , m_pAreaCombo(nullptr)
    , m_pBoundaryTree(nullptr)
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
    
    // Initialize UI controls
    InitializeControls();
    
    // Set up flexible color assignment callbacks
    m_pColorAssignment->RegisterColorChangeCallback(
        [this](int colorIndex) { OnColorAssignmentChanged(colorIndex); }
    );
    
    // Populate dropdowns with flexible options
    PopulateAttachmentCombo();
    PopulateAreaCombo();
    PopulateVersionCombo();
    
    // Initialize lists
    InitializeQuantityList();
    InitializeColorList();
    
    // Initialize with NO fixed colors - all user-defined
    UpdateColorList();
    
    // Set window title
    SetWindowText(_T("Enhanced Construction Takeoff - BricsCAD V25 (Flexible System)"));
    
    return TRUE;
}

void CEnhancedTakeoffBricsCADMainDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

void CEnhancedTakeoffBricsCADMainDialog::OnBnClickedPickColor()
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

void CEnhancedTakeoffBricsCADMainDialog::OnBnClickedMatchColor()
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

void CEnhancedTakeoffBricsCADMainDialog::OnAttachmentSelChange()
{
    int sel = m_pAttachmentCombo->GetCurSel();
    if (sel != CB_ERR) {
        CString planName;
        m_pAttachmentCombo->GetLBText(sel, planName);
        
        // Toggle attachment visibility
        std::string plan = CT2A(planName);
        m_pAttachmentMgr->ToggleAttachment(plan, true);
        
        // Update version combo for this plan
        UpdateVersionCombo(plan);
        RefreshQuantities();
        
        // Update boundary tree
        PopulateBoundaryTree();
    }
}

void CEnhancedTakeoffBricsCADMainDialog::OnVersionSelChange()
{
    // Handle AGS version switching (A=stucco, G=hardi, S=brick)
    int sel = m_pVersionCombo->GetCurSel();
    if (sel != CB_ERR) {
        CString version;
        m_pVersionCombo->GetLBText(sel, version);
        
        // Switch to selected version
        HandleVersionSwitch(CT2A(version));
        RefreshQuantities();
        
        // Update Excel mappings for this version
        UpdateExcelMappings();
    }
}

void CEnhancedTakeoffBricsCADMainDialog::OnAreaSelChange()
{
    // Apply regional presets
    int sel = m_pAreaCombo->GetCurSel();
    if (sel != CB_ERR) {
        CString area;
        m_pAreaCombo->GetLBText(sel, area);
        ApplyAreaPreset(CT2A(area));
        RefreshQuantities();
    }
}

void CEnhancedTakeoffBricsCADMainDialog::RefreshQuantities()
{
    if (!m_pQuantityList) return;
    
    m_pQuantityList->DeleteAllItems();
    
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
            m_pQuantityList->InsertItem(row, colorStr);
            
            m_pQuantityList->SetItemText(row, 1, CString(assignment.materialName.c_str()));
            
            CString qtyStr;
            qtyStr.Format(_T("%.2f"), quantity);
            m_pQuantityList->SetItemText(row, 2, qtyStr);
            
            // Show measurement unit
            if (!assignment.measurementTypes.empty()) {
                CString unitStr = GetMeasurementTypeString(assignment.measurementTypes[0]);
                m_pQuantityList->SetItemText(row, 3, unitStr);
            }
            
            CString costStr;
            costStr.Format(_T("$%.2f"), assignment.unitCost);
            m_pQuantityList->SetItemText(row, 4, costStr);
            
            CString totalStr;
            totalStr.Format(_T("$%.2f"), cost);
            m_pQuantityList->SetItemText(row, 5, totalStr);
            
            totalCost += cost;
            row++;
        }
    }
    
    // Update total cost display
    UpdateTotalCostDisplay(totalCost);
}

void CEnhancedTakeoffBricsCADMainDialog::OnBnClickedExportExcel()
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

// Additional implementation methods...
double CEnhancedTakeoffBricsCADMainDialog::CalculateColorQuantity(int colorIndex)
{
    // Placeholder calculation - real implementation would scan drawing
    return 100.0 + (colorIndex * 10.0);
}
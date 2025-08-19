// EnhancedTakeoffBricsCADMainDialog.h - Main Dialog Header
// Enhanced Construction Takeoff - BricsCAD V25 Plugin
// COPILOT-HINT: Main UI dialog with flexible color system

#pragma once

#include "framework.h"
#include "resource.h"
#include <memory>
#include <vector>
#include <map>

// Forward declarations
namespace EnhancedTakeoff {
    class FlexibleColorAssignment;
    class AttachmentManager;
    class BoundaryVersionManager;
    class FeederSheetManager;
}

/**
 * Main dialog class for Enhanced Construction Takeoff
 * Implements flexible color assignment system - NO FIXED COLORS
 */
class CEnhancedTakeoffBricsCADMainDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CEnhancedTakeoffBricsCADMainDialog)

public:
    CEnhancedTakeoffBricsCADMainDialog(CWnd* pParent = nullptr);
    virtual ~CEnhancedTakeoffBricsCADMainDialog();

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ENHANCED_TAKEOFF_MAIN };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

public:
    // Message handlers
    afx_msg void OnPickColor();
    afx_msg void OnMatchColor();
    afx_msg void OnRefreshQuantities();
    afx_msg void OnExportExcel();
    afx_msg void OnAreaSelChange();
    afx_msg void OnPlanSelChange();
    afx_msg void OnElevationSelChange();
    afx_msg void OnAutoRefreshToggle();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    
    // Legacy compatibility methods
    afx_msg void OnBnClickedPickColor();
    afx_msg void OnBnClickedMatchColor();
    afx_msg void OnBnClickedRefresh();
    afx_msg void OnBnClickedExportExcel();
    afx_msg void OnAttachmentSelChange();
    afx_msg void OnVersionSelChange();

    // Additional message handlers referenced in implementation
    afx_msg void OnColorAssignmentChanged(int colorIndex);
    afx_msg void OnAssignToBoundary();
    afx_msg void OnToggleAttachment();
    afx_msg void OnColorListSelChange();
    afx_msg void OnExcelCellChange();

private:
    // Core managers - flexible system
    std::unique_ptr<EnhancedTakeoff::FlexibleColorAssignment> m_pColorAssignment;
    std::unique_ptr<EnhancedTakeoff::AttachmentManager> m_pAttachmentMgr;
    std::unique_ptr<EnhancedTakeoff::BoundaryVersionManager> m_pBoundaryMgr;
    std::unique_ptr<EnhancedTakeoff::FeederSheetManager> m_pFeederSheet;
    
    // UI Controls that are referenced in the implementation
    CComboBox m_areaCombo;
    CComboBox m_planCombo;
    CComboBox m_elevationCombo;
    CComboBox m_materialTypeCombo;    // Added missing control
    CEdit m_excelCellEdit;            // Added missing control
    CEdit m_unitCostEdit;             // Added missing control
    CEdit m_pitchValueEdit;           // Added missing control
    CButton m_pitchModifierCheck;     // Added missing control
    CListCtrl m_colorList;
    CListCtrl m_quantityList;
    CListCtrl m_colorAssignmentList;
    CTreeCtrl m_boundaryTree;
    CTreeCtrl m_attachmentTree;       // Added missing control
    CButton m_autoRefreshCheck;
    CButton m_pickColorBtn;
    CButton m_matchColorBtn;
    CButton m_refreshBtn;
    CButton m_exportBtn;
    CStatic m_totalCostLabel;
    
    // State variables
    bool m_autoRefreshEnabled;
    UINT_PTR m_refreshTimerID;
    std::string m_currentArea;        // Added missing member
    std::string m_currentPlan;        // Added missing member  
    std::string m_currentElevation;   // Added missing member
    
    // AGS Elevation system
    struct ElevationVariation {
        std::string code;
        std::string description;
        char frameType;     // A or H
        char garageType;    // G or N
        char sidingType;    // S, H, or B
        
        ElevationVariation(const std::string& c, const std::string& d, 
                          char f, char g, char s) 
            : code(c), description(d), frameType(f), garageType(g), sidingType(s) {}
    };
    std::vector<ElevationVariation> m_elevationVariations;
    
    // Initialization helpers
    void InitializeElevationVariations();
    void InitializeFlexibleSystem();
    void PopulateControls();
    void UpdateQuantityDisplay();
    void InitializeDropdowns();
    void PopulateAreaCombo();
    void PopulatePlanCombo(const std::string& selectedArea);
    void PopulateElevationCombo(const std::string& selectedPlan);
    void InitializeColorList();
    void InitializeQuantityList();
    void InitializeAttachmentTree();
    void RefreshColorAssignments();
    void RefreshQuantityDisplay();
    void UpdateTotalCost();
    void ApplyElevationVariation(const std::string& elevationCode);
    void UpdateUIState();
    void RefreshQuantities();
    void UpdateColorList();
    
    // Helper methods referenced in implementation
    CString GetMeasurementTypeString(int measurementType) const;
    double CalculateColorQuantity(int colorIndex);
    bool GetMaterialNameFromUser(CString& materialName);
    bool GetAssignmentDetailsFromUser(EnhancedTakeoff::FlexibleColorAssignment::ColorAssignment& assignment);
    bool GetExcelPathFromUser(CString& excelPath);
    void UpdateTotalCostDisplay(double totalCost);
};
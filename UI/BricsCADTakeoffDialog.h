// BricsCADTakeoffDialog.h - Main UI dialog for Enhanced Construction Takeoff
#pragma once

#include <memory>
#include <vector>
#include <map>
#include <chrono>
#include "framework.h"
#include "resource.h"

// Forward declarations
namespace EnhancedTakeoff {
    class AttachmentManager;
    class FlexibleColorAssignment;
    class BoundaryVersionManager;
    class FeederSheetManager;
    class LiveQuantityMonitor;
}

/**
 * Main dialog for Enhanced Construction Takeoff BricsCAD V25
 * Implements the flexible UI design with live updates
 * COPILOT-HINT: This is the main UI - no fixed colors or materials
 */
class CBricsCADTakeoffDialog : public CDialogEx {
    DECLARE_DYNAMIC(CBricsCADTakeoffDialog)
    
public:
    CBricsCADTakeoffDialog(CWnd* pParent = nullptr);
    virtual ~CBricsCADTakeoffDialog();
    
    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TAKEOFF_MAIN };
#endif
    
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    
    DECLARE_MESSAGE_MAP()
    
private:
    // Core managers
    std::unique_ptr<EnhancedTakeoff::AttachmentManager> m_attachmentMgr;
    std::unique_ptr<EnhancedTakeoff::FlexibleColorAssignment> m_colorAssignment;
    std::unique_ptr<EnhancedTakeoff::BoundaryVersionManager> m_boundaryMgr;
    std::unique_ptr<EnhancedTakeoff::FeederSheetManager> m_feederSheet;
    std::unique_ptr<EnhancedTakeoff::LiveQuantityMonitor> m_quantityMonitor;
    
    // UI Controls - Top Section
    CComboBox m_projectCombo;
    CComboBox m_areaCombo;          // Southeast, Northeast, etc.
    CComboBox m_attachmentCombo;    // Plan A, B, C, D
    CComboBox m_versionCombo;       // AGS versions
    CButton m_autoRefreshCheck;
    CEdit m_refreshIntervalEdit;
    CButton m_settingsBtn;
    
    // UI Controls - Live Quantities Panel
    CListCtrl m_quantityList;       // Live quantity display
    CStatic m_lfTotalLabel;
    CStatic m_sfTotalLabel;
    CStatic m_sfPitchTotalLabel;
    CStatic m_eaCountLabel;
    CTreeCtrl m_boundaryTree;       // Boundary checkboxes
    
    // UI Controls - Color Assignment Panel
    CListCtrl m_colorAssignmentList;
    CButton m_pickColorBtn;
    CButton m_matchColorBtn;
    CButton m_clearColorBtn;
    CButton m_addAssignmentBtn;
    
    // UI Controls - Tab Control
    CTabCtrl m_mainTabCtrl;
    
    // Tab panels
    CWnd* m_pMaterialsTab;
    CWnd* m_pExcelMappingTab;
    CWnd* m_pBoundariesTab;
    CWnd* m_pReportsTab;
    CWnd* m_pLiveMonitorTab;
    
    // Status bar
    CStatusBar m_statusBar;
    CButton m_refreshBtn;
    CButton m_exportBtn;
    
    // State variables
    bool m_autoRefreshEnabled;
    int m_refreshIntervalMs;
    std::string m_activeProject;
    std::string m_activeArea;
    std::string m_activeAttachment;
    std::string m_activeVersion;
    
    // Live update tracking
    std::chrono::steady_clock::time_point m_lastRefresh;
    std::map<int, double> m_colorQuantities;
    std::map<int, double> m_colorCosts;
    
    // Initialization methods
    void InitializeManagers();
    void InitializeControls();
    void InitializeTabs();
    void LoadProjectSettings();
    
    // UI population methods
    void PopulateProjectCombo();
    void PopulateAreaCombo();
    void PopulateAttachmentCombo();
    void PopulateVersionCombo();
    void PopulateColorAssignments();
    void PopulateBoundaryTree();
    
    // Update methods
    void UpdateLiveQuantities();
    void UpdateTotals();
    void RefreshColorList();
    void RefreshBoundaries();
    
    // Event handlers - Top controls
    afx_msg void OnProjectSelChange();
    afx_msg void OnAreaSelChange();
    afx_msg void OnAttachmentSelChange();
    afx_msg void OnVersionSelChange();
    afx_msg void OnAutoRefreshToggle();
    afx_msg void OnRefreshIntervalChange();
    afx_msg void OnSettingsClick();
    
    // Event handlers - Color assignment
    afx_msg void OnPickColor();
    afx_msg void OnMatchColor();
    afx_msg void OnClearColor();
    afx_msg void OnAddColorAssignment();
    afx_msg void OnColorSelChange(NMHDR* pNMHDR, LRESULT* pResult);
    
    // Event handlers - Boundaries
    afx_msg void OnBoundaryCheck(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBoundaryExpand(NMHDR* pNMHDR, LRESULT* pResult);
    
    // Event handlers - Actions
    afx_msg void OnRefreshClick();
    afx_msg void OnExportClick();
    afx_msg void OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult);
    
    // Timer for auto-refresh
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    
    // Helper methods
    void ShowTab(int tabIndex);
    void EnableAutoRefresh(bool enable);
    std::vector<int> GetCheckedBoundaryColors() const;
    void ApplyAreaFactors(const std::string& areaPreset);
    
    // BricsCAD integration
    void ConnectToBricsCAD();
    void RefreshFromDrawing();
    void HandleEntitySelection();
    
    // Excel operations
    void ConnectToExcel();
    void UpdateExcelFeederSheet();
    void ExportToExcel();
    
    // Settings persistence
    void SaveSettings();
    void LoadSettings();
};
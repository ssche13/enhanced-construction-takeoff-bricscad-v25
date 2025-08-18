// SimpleUITest.cpp - Simplified UI Test for demonstration
#include "pch.h"
#include "resource.h"

// Simple dialog for UI demonstration
class CSimpleEnhancedTakeoffDialog : public CDialogEx
{
public:
    CSimpleEnhancedTakeoffDialog() : CDialogEx(IDD_ENHANCED_TAKEOFF_MAIN) {}
    
protected:
    virtual BOOL OnInitDialog() override
    {
        CDialogEx::OnInitDialog();
        
        // Set window title
        SetWindowText(_T("Enhanced Construction Takeoff - Flexible Color System"));
        
        // Show message about the system
        CString message = _T("?? Enhanced Construction Takeoff V25\n\n");
        message += _T("? FLEXIBLE COLOR SYSTEM ACTIVE\n");
        message += _T("   • NO FIXED COLOR ASSIGNMENTS\n");
        message += _T("   • User-defined material mapping\n");
        message += _T("   • BricsCAD color picker integration\n\n");
        message += _T("??? AGS ELEVATION SYSTEM\n");
        message += _T("   • A-frame/Hip roof types\n");
        message += _T("   • Garage/No garage options\n");
        message += _T("   • Stucco/Hardi/Brick siding\n\n");
        message += _T("?? LIVE QUANTITY UPDATES\n");
        message += _T("   • Real-time calculation refresh\n");
        message += _T("   • Excel feeder sheet integration\n");
        message += _T("   • Boundary version management\n\n");
        message += _T("?? PROFESSIONAL UI FEATURES\n");
        message += _T("   • Plan A/B/C/D attachment\n");
        message += _T("   • Mathematical precision\n");
        message += _T("   • BricsCAD V25 BIM support");
        
        AfxMessageBox(message, MB_OK | MB_ICONINFORMATION);
        
        return TRUE;
    }
    
    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CSimpleEnhancedTakeoffDialog, CDialogEx)
END_MESSAGE_MAP()

// Export function to show the UI
extern "C" __declspec(dllexport) void ShowEnhancedTakeoffUIDemo()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    try 
    {
        CSimpleEnhancedTakeoffDialog dlg;
        dlg.DoModal();
    }
    catch (...)
    {
        AfxMessageBox(_T("Enhanced Construction Takeoff - Demo Mode\n\nThis demonstrates the flexible architecture with:\n• NO FIXED COLORS\n• User-defined materials\n• AGS elevation system\n• Live Excel integration"));
    }
}
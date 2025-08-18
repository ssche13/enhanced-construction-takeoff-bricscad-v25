// TestUIDialog.cpp - Quick UI Test for Enhanced Construction Takeoff
// This creates a standalone test to show the dialog

#include "pch.h"
#include "EnhancedTakeoffBricsCADMainDialog.h"
#include "resource.h"

// Quick test application class
class CTestUIApp : public CWinApp
{
public:
    virtual BOOL InitInstance() override
    {
        // Initialize MFC
        if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
        {
            return FALSE;
        }

        // Create and show the Enhanced Construction Takeoff dialog
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
        
        try 
        {
            CEnhancedTakeoffBricsCADMainDialog dlg;
            dlg.DoModal();
        }
        catch (const std::exception& e)
        {
            CString errorMsg;
            errorMsg.Format(_T("Error showing Enhanced Takeoff UI: %s"), CString(e.what()));
            AfxMessageBox(errorMsg);
        }
        catch (...)
        {
            AfxMessageBox(_T("Unknown error showing Enhanced Takeoff UI"));
        }

        return FALSE; // Exit after dialog closes
    }
};

// Global application instance
CTestUIApp theApp;

// Entry point for quick UI test
extern "C" __declspec(dllexport) void ShowEnhancedTakeoffUI()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    try 
    {
        CEnhancedTakeoffBricsCADMainDialog dlg;
        dlg.DoModal();
    }
    catch (...)
    {
        AfxMessageBox(_T("Error showing Enhanced Construction Takeoff UI"));
    }
}
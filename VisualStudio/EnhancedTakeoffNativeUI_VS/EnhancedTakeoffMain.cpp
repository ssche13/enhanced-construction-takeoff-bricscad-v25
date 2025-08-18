// EnhancedTakeoffMain.cpp - BricsCAD Plugin Entry Point
// Enhanced Construction Takeoff - BricsCAD V25 Plugin
// COPILOT-HINT: BricsCAD .brx plugin entry point with command registration

#include "pch.h"
#include "EnhancedTakeoffBricsCADMainDialog.h"  // Use the correct header that matches the implementation

#ifdef HAS_BRX_SDK
#include "rxregsvc.h"
#include "acedinpt.h"
#include "acedCmdNF.h"
#include "aced.h"
#include "acutads.h"
#include "acrxEntryPoint.h"
#endif

// Forward declarations for dialog class
class CEnhancedTakeoffBricsCADMainDialog;  // Use correct class name

// Enhanced Construction Takeoff Commands
void EnhancedTakeoffCommand();
void FlexibleColorCommand();
void AttachmentManagerCommand();
void ExcelExportCommand();

#ifdef HAS_BRX_SDK

//////////////////////////////////////////////////////////////////////////
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(theArxDLL);

// Now you can use the CAcModuleResourceOverride class.
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        // Comment out the following line if your
        // application should be locked into memory
        acrxUnlockApplication(pkt);
        acrxRegisterAppMDIAware(pkt);
        
        // Register Enhanced Construction Takeoff commands
        acedRegCmds->addCommand(_T("ENHANCED_TAKEOFF_COMMANDS"),
                               _T("ENHANCEDTAKEOFF"),
                               _T("ENHANCEDTAKEOFF"),
                               ACRX_CMD_MODAL,
                               EnhancedTakeoffCommand);
        
        acedRegCmds->addCommand(_T("ENHANCED_TAKEOFF_COMMANDS"),
                               _T("FLEXIBLECOLOR"),
                               _T("FLEXIBLECOLOR"),
                               ACRX_CMD_MODAL,
                               FlexibleColorCommand);
        
        acedRegCmds->addCommand(_T("ENHANCED_TAKEOFF_COMMANDS"),
                               _T("ATTACHMENTMANAGER"),
                               _T("ATTACHMENTMANAGER"),
                               ACRX_CMD_MODAL,
                               AttachmentManagerCommand);
        
        acedRegCmds->addCommand(_T("ENHANCED_TAKEOFF_COMMANDS"),
                               _T("EXCELEXPORT"),
                               _T("EXCELEXPORT"),
                               ACRX_CMD_MODAL,
                               ExcelExportCommand);
        
        // Display loading message
        acutPrintf(_T("\nEnhanced Construction Takeoff V25 loaded successfully\n"));
        acutPrintf(_T("Flexible Color System Active - NO FIXED ASSIGNMENTS\n"));
        acutPrintf(_T("Commands: ENHANCEDTAKEOFF, FLEXIBLECOLOR, ATTACHMENTMANAGER, EXCELEXPORT\n"));
        
        break;
        
    case AcRx::kUnloadAppMsg:
        // Remove command group
        acedRegCmds->removeGroup(_T("ENHANCED_TAKEOFF_COMMANDS"));
        break;
        
    default:
        break;
    }
    return AcRx::kRetOK;
}

#endif // HAS_BRX_SDK

// Command implementations

void EnhancedTakeoffCommand()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    try {
        // Use the correct dialog class name that exists in the implementation
        CEnhancedTakeoffBricsCADMainDialog dlg;
        dlg.DoModal();
    }
    catch (const std::exception& e) {
#ifdef HAS_BRX_SDK
        CString errorMsg;
        errorMsg.Format(_T("Error in Enhanced Takeoff: %s"), CString(e.what()));
        acutPrintf(_T("\n%s\n"), errorMsg);
#else
        // For non-BRX builds, just show a message box
        AfxMessageBox(_T("Enhanced Construction Takeoff - Error in plugin"));
#endif
    }
    catch (...) {
#ifdef HAS_BRX_SDK
        acutPrintf(_T("\nUnknown error in Enhanced Takeoff\n"));
#else
        AfxMessageBox(_T("Enhanced Construction Takeoff - Unknown error"));
#endif
    }
}

void FlexibleColorCommand()
{
#ifdef HAS_BRX_SDK
    acutPrintf(_T("\nFlexible Color Assignment System\n"));
    acutPrintf(_T("This system allows you to assign ANY color to ANY material\n"));
    acutPrintf(_T("No fixed color restrictions - complete user control\n"));
    acutPrintf(_T("Use ENHANCEDTAKEOFF command to open the main dialog\n"));
#else
    AfxMessageBox(_T("Flexible Color Assignment System\nNo fixed color restrictions - complete user control\nUse ENHANCEDTAKEOFF command to open the main dialog"));
#endif
}

void AttachmentManagerCommand()
{
#ifdef HAS_BRX_SDK
    acutPrintf(_T("\nAttachment Manager - AGS Elevation System\n"));
    acutPrintf(_T("Manages Plan A/B/C/D with elevation variations\n"));
    acutPrintf(_T("AGS System: A-frame/Hip + Garage/No + Stucco/Hardi/Brick\n"));
    acutPrintf(_T("Use ENHANCEDTAKEOFF command to access attachment management\n"));
#else
    AfxMessageBox(_T("Attachment Manager - AGS Elevation System\nManages Plan A/B/C/D with elevation variations\nAGS System: A-frame/Hip + Garage/No + Stucco/Hardi/Brick"));
#endif
}

void ExcelExportCommand()
{
#ifdef HAS_BRX_SDK
    acutPrintf(_T("\nExcel Export - Feeder Sheet Integration\n"));
    acutPrintf(_T("Direct cell mapping with formula preservation\n"));
    acutPrintf(_T("Live quantity updates to Excel workbooks\n"));
    acutPrintf(_T("Use ENHANCEDTAKEOFF command to configure Excel export\n"));
#else
    AfxMessageBox(_T("Excel Export - Feeder Sheet Integration\nDirect cell mapping with formula preservation\nLive quantity updates to Excel workbooks"));
#endif
}

#ifndef HAS_BRX_SDK
// Fallback implementations for non-BricsCAD builds

extern "C" __declspec(dllexport) int InitializePlugin()
{
    return 1; // Success
}

extern "C" __declspec(dllexport) void UnloadPlugin()
{
    // Cleanup
}

extern "C" __declspec(dllexport) void ShowEnhancedTakeoff()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    try {
        CEnhancedTakeoffBricsCADMainDialog dlg;
        dlg.DoModal();
    }
    catch (...) {
        AfxMessageBox(_T("Error showing Enhanced Construction Takeoff dialog"));
    }
}

#endif // !HAS_BRX_SDK
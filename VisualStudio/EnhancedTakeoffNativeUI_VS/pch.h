// pch.h - Precompiled header for Enhanced Construction Takeoff
// Enhanced Construction Takeoff - BricsCAD V25 Plugin

#pragma once

#ifndef PCH_H
#define PCH_H

// Windows and framework headers
#include "targetver.h"
#include "framework.h"

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "resource.h"
#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdialogex.h>    // MFC dialog extensions
#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#include <afxcmn.h>         // MFC support for Windows Common Controls

// Standard library headers
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

// BricsCAD SDK headers (conditional compilation)
#ifdef HAS_BRX_SDK
#define BCAD_EXPORTS            // Required for BricsCAD
#include "brx_platform.h"
#include "AcDb.h"
#include "AcDbDatabase.h"
#include "AcDbTransactionManager.h"
#include "AcDbBlockTable.h"
#include "AcDbBlockTableRecord.h"
#include "AcDbLayerTable.h"
#include "AcDbLayerTableRecord.h"
#include "AcDbEntity.h"
#include "AcDbPolyline.h"
#include "AcDbText.h"
#include "AcDbMText.h"
#include "AcDbLine.h"
#include "AcDbCircle.h"
#include "AcDbArc.h"
#include "AcDbRegion.h"
#include "AcCmColor.h"
#include "AcGePoint3d.h"
#include "AcGePoint2d.h"
#include "AcGeVector3d.h"
#include "AcGeMatrix3d.h"
#include "AcGePlane.h"
#include "AcDbXref.h"
#include "dbapserv.h"
#include "aced.h"
#include "acedads.h"
#include "acedCmdNF.h"
#include "acutads.h"
#include "adscodes.h"
#include "acstring.h"
#include "rxobject.h"
#include "rxregsvc.h"
#include "acutmem.h"
#include "adslib.h"
#include "acestext.h"
#include "acgi.h"
#include "AcDbObjectId.h"
#include "dbsymtb.h"
#include "dbents.h"
#include "dbxrecrd.h"
#include "dbfiler.h"
#include "dblayout.h"
#include "dbviewtb.h"
#include "acedsel.h"
#include "acedss.h"
#include "ads.h"
#include "acrxEntryPoint.h"
#endif // HAS_BRX_SDK

// Preprocessor definitions for flexible architecture
#ifndef BUILDING_ENHANCED_TAKEOFF
#define BUILDING_ENHANCED_TAKEOFF 1
#endif

#ifndef FLEXIBLE_COLOR_SYSTEM
#define FLEXIBLE_COLOR_SYSTEM 1
#endif

#ifndef NO_FIXED_COLORS
#define NO_FIXED_COLORS 1
#endif

// Enhanced Takeoff namespace and forward declarations
namespace EnhancedTakeoff {
    class FlexibleColorAssignment;
    class AttachmentManager;
    class BoundaryVersionManager;
    class FeederSheetManager;
    class BricsCADV25Support;
}

// Excel integration headers (optional, only if needed)
#ifdef HAS_EXCEL_INTEGRATION
#include <comdef.h>
#include <comutil.h>
#include <ole2.h>
#include <oleauto.h>
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#endif

// Common utility macros
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = nullptr; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr; } }
#endif

// Debug macros for Enhanced Takeoff
#ifdef _DEBUG
#define ET_TRACE(msg) TRACE(_T("EnhancedTakeoff: %s\n"), msg)
#define ET_ASSERT(expr) ASSERT(expr)
#else
#define ET_TRACE(msg) ((void)0)
#define ET_ASSERT(expr) ((void)0)
#endif

// Version information
#define ENHANCED_TAKEOFF_VERSION_MAJOR 1
#define ENHANCED_TAKEOFF_VERSION_MINOR 0
#define ENHANCED_TAKEOFF_VERSION_PATCH 0
#define ENHANCED_TAKEOFF_VERSION_STRING _T("1.0.0")

// Application name
#define ENHANCED_TAKEOFF_APP_NAME _T("Enhanced Construction Takeoff")
#define ENHANCED_TAKEOFF_APP_DESCRIPTION _T("Professional Construction Takeoff for BricsCAD V25")

#endif // PCH_H#endif // PCH_H
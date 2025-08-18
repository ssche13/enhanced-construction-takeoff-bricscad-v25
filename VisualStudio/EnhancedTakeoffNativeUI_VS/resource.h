// resource.h - Resource definitions for Enhanced Construction Takeoff
// Enhanced Construction Takeoff - BricsCAD V25 Plugin

#pragma once

#ifndef RESOURCE_H
#define RESOURCE_H

//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by EnhancedTakeoffBricsCAD.rc

// Dialog resource IDs
#define IDD_ENHANCED_TAKEOFF_MAIN           2100
#define IDD_MATERIAL_ASSIGNMENT_DIALOG      2101
#define IDD_EXCEL_MAPPING_DIALOG           2102
#define IDD_BOUNDARY_SETUP_DIALOG          2103
#define IDD_ELEVATION_SELECTOR_DIALOG      2104

// Control IDs for main dialog
#define IDC_AREA_COMBO                     2000
#define IDC_PLAN_COMBO                     2001
#define IDC_ELEVATION_COMBO                2002
#define IDC_COLOR_LIST                     2003
#define IDC_PICK_COLOR                     2004
#define IDC_MATCH_COLOR                    2005
#define IDC_MATERIAL_TYPE_COMBO            2006
#define IDC_EXCEL_CELL_EDIT                2007
#define IDC_UNIT_COST_EDIT                 2008
#define IDC_PITCH_MODIFIER_CHECK           2009
#define IDC_PITCH_VALUE_EDIT               2010
#define IDC_BOUNDARY_ASSIGN_BTN            2011
#define IDC_QUANTITY_LIST                  2012
#define IDC_ATTACHMENT_TREE                2013
#define IDC_TOGGLE_ATTACHMENT_BTN          2014
#define IDC_REFRESH_BTN                    2015
#define IDC_AUTO_REFRESH_CHECK             2016
#define IDC_EXPORT_EXCEL_BTN               2017
#define IDC_TOTAL_COST_STATIC              2018

// Additional control IDs
#define IDC_VERSION_COMBO                  2019
#define IDC_ATTACHMENT_COMBO               2020
#define IDC_BOUNDARY_TREE                  2021
#define IDC_AUTO_REFRESH                   2022
#define IDC_EXPORT_EXCEL                   2023

// String resource IDs
#define IDS_APP_TITLE                      61440
#define IDS_ENHANCED_TAKEOFF_TITLE         61441
#define IDS_FLEXIBLE_COLOR_SYSTEM          61442
#define IDS_AGS_ELEVATION_SYSTEM           61443
#define IDS_EXCEL_INTEGRATION              61444
#define IDS_BRICSCAD_V25_PLUGIN            61445

// Icon resource IDs
#define IDI_ENHANCED_TAKEOFF               128
#define IDI_COLOR_PICKER                   129
#define IDI_EXCEL_EXPORT                   130
#define IDI_BOUNDARY_TOOL                  131
#define IDI_ELEVATION_SELECTOR             132

// Bitmap resource IDs
#define IDB_TOOLBAR_MAIN                   200
#define IDB_COLOR_SWATCH                   201
#define IDB_MATERIAL_ICONS                 202

// Menu resource IDs
#define IDM_MAIN_MENU                      300
#define IDM_CONTEXT_COLOR                  301
#define IDM_CONTEXT_MATERIAL               302
#define IDM_CONTEXT_EXCEL                  303

// Menu command IDs (using higher range to avoid conflicts)
#define ID_FILE_NEW_PROJECT                40001
#define ID_FILE_OPEN_PROJECT               40002
#define ID_FILE_SAVE_PROJECT               40003
#define ID_FILE_EXPORT_EXCEL               40004
#define ID_EDIT_COPY_ASSIGNMENTS           40005
#define ID_EDIT_PASTE_ASSIGNMENTS          40006
#define ID_EDIT_CLEAR_ALL_ASSIGNMENTS      40007  // Renamed to avoid conflict
#define ID_VIEW_REFRESH                    40008
#define ID_VIEW_AUTO_REFRESH               40009
#define ID_TOOLS_COLOR_PICKER              40010
#define ID_TOOLS_MATERIAL_LIBRARY          40011
#define ID_TOOLS_BOUNDARY_SETUP            40012
#define ID_TOOLS_ELEVATION_MANAGER         40013
#define ID_HELP_ABOUT                      40014
#define ID_HELP_USER_GUIDE                 40015

// Toolbar button IDs
#define ID_TB_PICK_COLOR                   41001
#define ID_TB_MATCH_COLOR                  41002
#define ID_TB_EXPORT_EXCEL                 41003
#define ID_TB_REFRESH                      41004
#define ID_TB_BOUNDARY_TOOL                41005
#define ID_TB_ELEVATION_SELECTOR           41006

// Status bar pane IDs
#define ID_STATUS_PANE_READY               59392
#define ID_STATUS_PANE_COLORS              59393
#define ID_STATUS_PANE_TOTAL_COST          59394
#define ID_STATUS_PANE_EXCEL_STATUS        59395

// Accelerator table ID
#define IDR_MAIN_ACCELERATOR               400

// Version resource
#define VS_VERSION_INFO                    1

// Dialog styles and extended styles
#define DS_ENHANCED_TAKEOFF                (DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU)
#define DS_ENHANCED_TAKEOFF_EX             (WS_EX_CONTROLPARENT | WS_EX_APPWINDOW)

// List control column indices
#define COL_COLOR_INDEX                    0
#define COL_MATERIAL_NAME                  1
#define COL_UNIT_COST                      2
#define COL_EXCEL_CELL                     3
#define COL_ACTIVE_STATUS                  4

#define COL_QTY_COLOR                      0
#define COL_QTY_MATERIAL                   1
#define COL_QTY_QUANTITY                   2
#define COL_QTY_UNIT                       3
#define COL_QTY_UNIT_COST                  4
#define COL_QTY_TOTAL_COST                 5

// Tree control image indices
#define IMG_PLAN_A                         0
#define IMG_PLAN_B                         1
#define IMG_PLAN_C                         2
#define IMG_PLAN_D                         3
#define IMG_ELEVATION_AGS                  4
#define IMG_ELEVATION_HGB                  5
#define IMG_BOUNDARY_BOX                   6
#define IMG_ATTACHMENT_LOADED              7
#define IMG_ATTACHMENT_UNLOADED            8

// Color picker constants
#define MAX_COLORS                         256
#define DEFAULT_COLOR_INDEX                7
#define INVALID_COLOR_INDEX                -1

// Excel integration constants
#define MAX_EXCEL_CELL_REF                 32
#define MAX_FORMULA_LENGTH                 256
#define DEFAULT_WORKSHEET_NAME             "Feeder"

// AGS elevation system constants
#define AGS_FRAME_TYPE_A                   'A'
#define AGS_FRAME_TYPE_H                   'H'
#define AGS_GARAGE_TYPE_G                  'G'
#define AGS_GARAGE_TYPE_N                  'N'
#define AGS_SIDING_TYPE_S                  'S'
#define AGS_SIDING_TYPE_H                  'H'
#define AGS_SIDING_TYPE_B                  'B'

// Timer IDs
#define TIMER_AUTO_REFRESH                 1001
#define TIMER_EXCEL_UPDATE                 1002
#define TIMER_UI_UPDATE                    1003

// Error codes
#define ET_SUCCESS                         0
#define ET_ERROR_GENERAL                   -1
#define ET_ERROR_INVALID_COLOR             -2
#define ET_ERROR_EXCEL_CONNECTION          -3
#define ET_ERROR_BRICSCAD_API              -4
#define ET_ERROR_FILE_IO                   -5
#define ET_ERROR_INVALID_PARAMETER         -6

// Next default values for new objects
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE           2105
#define _APS_NEXT_COMMAND_VALUE            41007
#define _APS_NEXT_CONTROL_VALUE            2024
#define _APS_NEXT_SYMED_VALUE              2100
#endif
#endif

#endif // RESOURCE_H
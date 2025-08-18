# Enhanced Construction Takeoff - BricsCAD V25 Development Guidelines

## Project Type
Professional BricsCAD V25 BIM plugin for construction estimation with proper transaction handling

## NEVER USE (Deprecated Systems)
- Fixed color assignments (ColorMaterialMapper old patterns)
- AutoCAD ARX APIs (BricsCAD BRX only)
- Hardcoded material lists
- Legacy .NET plugin approaches
- Old LISP bridge implementations
- Mixed AutoCAD/BricsCAD namespaces

## ALWAYS USE (Current Architecture)
- Variable color assignment with BricsCAD color picker
- BricsCAD BRX SDK V25 only with proper transaction handling
- Flexible boundary boxes for version management
- User-defined material systems
- Direct Excel cell mapping via feeder sheets
- Mathematical precision (not lookup tables)
- Proper BricsCAD transaction scoping

## Current Implementation Focus
- EnhancedTakeoffBricsCADMainDialog.cpp/.h (Latest UI with proper transaction handling)
- BricsCADV25SupportClasses.cpp/.h (BIM integration with proper API usage)
- AttachmentManager.cpp/.h (Enhanced plan management with AGS elevation system)
- FlexibleColorAssignment.cpp/.h (Completely flexible color system)
- Mathematical Roof Pitch Calculator (precision formulas)
- Excel Integration (Live feed with COM Interop + EPPlus)

## Architecture Rules
- NO fixed color assignments - all user-defined
- Proper BricsCAD transaction handling - no AutoCAD patterns
- Boundary boxes for version management (AGS system)
- Flexible attachment system (Plan A/B/C/D with elevation variations)
- Live quantity updates with manual refresh option
- Formula preservation in Excel feeder sheets
- BricsCAD-specific API usage only

## Build Configuration
- Platform: x64 only
- Framework: MFC DLL with BricsCAD V25 SDK
- Target: .brx plugin for BricsCAD
- No .NET dependencies in final plugin
- Preprocessor: HAS_BRX_SDK=1, NO_AUTOCAD_APIS=1

## BricsCAD V25 Specific Implementation
- Use acdbHostApplicationServices()->workingDatabase() for database access
- Proper transaction scoping with startTransaction() and endTransaction()
- Layer management with BricsCAD-specific methods
- XREF attachment using BricsCAD attachXref() method
- Color management with AcCmColor and BricsCAD color schemes
- Block reference creation with proper BricsCAD API calls

## AGS Elevation System
- A = A-frame roof vs H = Hip roof
- G = With garage vs N = No garage  
- S = Stucco vs H = Hardi vs B = Brick
- Examples: AGS, AGB, AGH, ANS, ANB, ANH, HGS, HGB, HGH, HNS, HNB, HNH

## Excel Integration Architecture
- COM Interop for live updates
- EPPlus for batch operations
- Debounced update queue (500ms)
- Formula preservation in feeder sheets
- Direct cell mapping (no fixed formats)

# Enhanced Construction Takeoff - BricsCAD V25 Development Guidelines

## Project Type
Professional BricsCAD V25 BIM plugin for construction estimation

## NEVER USE (Deprecated Systems)
- Fixed color assignments (ColorMaterialMapper old patterns)
- AutoCAD ARX APIs (BricsCAD BRX only)
- Hardcoded material lists
- Legacy .NET plugin approaches
- Old LISP bridge implementations

## ALWAYS USE (Current Architecture)
- Variable color assignment with BricsCAD color picker
- BricsCAD BRX SDK V25 only
- Flexible boundary boxes for version management
- User-defined material systems
- Direct Excel cell mapping via feeder sheets
- Mathematical precision (not lookup tables)

## Current Implementation Focus
- EnhancedTakeoffBricsCADMainDialog.cpp/.h (Latest UI)
- BricsCADV25SupportClasses.cpp/.h (BIM integration)
- Mathematical Roof Pitch Calculator (precision formulas)
- 8 Color Family System (unlimited height variants)
- Excel Integration (5 professional export formats)

## Architecture Rules
- NO fixed color assignments - all user-defined
- Boundary boxes for version management (AGS system)
- Flexible attachment system (Plan A/B/C/D)
- Live quantity updates with manual refresh option
- Formula preservation in Excel feeder sheets

## Build Configuration
- Platform: x64 only
- Framework: MFC DLL with BricsCAD V25 SDK
- Target: .brx plugin for BricsCAD
- No .NET dependencies in final plugin

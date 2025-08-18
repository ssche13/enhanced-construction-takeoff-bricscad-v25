# Enhanced Construction Takeoff - BricsCAD V25 Plugin

**Professional construction takeoff plugin for BricsCAD V25 with advanced material estimation, flexible color assignment, and Excel integration.**

## ?? **Project Overview**

This is a comprehensive Enhanced Construction Takeoff solution for BricsCAD V25 featuring:

### **? Core Features:**
- **Advanced BricsCAD V25 Integration** with BIM support classes
- **Flexible Color Assignment System** - NO FIXED COLORS, all user-defined
- **Mathematical Roof Pitch Calculator** with precision formulas
- **Excel Integration** with direct cell mapping via feeder sheets
- **Smart CAD Object Recognition** and automated boundary detection
- **Professional MFC UI** with BricsCAD V25 theming

## ??? **Architecture Highlights**

### **Modern Flexible System:**
- **FlexibleColorAssignment.cpp** - Replaces old fixed color patterns
- **AttachmentManager** - Plan A/B/C/D version management
- **BoundaryVersionManager** - AGS version switching
- **FeederSheetManager** - Excel formula preservation

### **NO FIXED COLORS:**
```cpp
// Users can assign ANY color to ANY material
FlexibleColorAssignment::AssignColor(colorIndex, userDefinedAssignment);
```

## ?? **Build Requirements**

- **Visual Studio 2022** (Community or higher)
- **BricsCAD V25** with BRX SDK
- **Windows 10/11** (x64)
- **MFC Libraries**

## ?? **Project Structure**

```
VisualStudio/EnhancedTakeoffNativeUI_VS/
??? FlexibleColorAssignment.cpp     # Modern flexible color system
??? EnhancedTakeoffBricsCADMainDialog.cpp # Main UI dialog
??? BricsCADV25SupportClasses.cpp  # BIM integration layer
??? AttachmentManager.cpp           # Plan version management
??? EnhancedTakeoffNativeUI_VS.vcxproj # Visual Studio project
??? ... (other core files)
```

## ?? **Current Implementation Focus**

- ? **Variable color assignment** with BricsCAD color picker
- ? **Flexible boundary boxes** for version management
- ? **User-defined material systems**
- ? **Direct Excel cell mapping** via feeder sheets
- ? **Mathematical precision** (not lookup tables)

## ?? **Getting Started**

1. **Clone Repository:**
   ```bash
   git clone https://github.com/[your-username]/enhanced-construction-takeoff-bricscad-v25.git
   ```

2. **Open in Visual Studio:**
   ```
   VisualStudio/EnhancedTakeoffNativeUI_VS/EnhancedTakeoffNativeUI_VS.sln
   ```

3. **Build Configuration:**
   - Platform: **x64**
   - Configuration: **Release**
   - Target: **.brx plugin**

4. **Load in BricsCAD:**
   ```
   Command: APPLOAD
   Load: EnhancedTakeoffNativeUI_VS.brx
   ```

## ?? **Architecture Rules**

### **NEVER USE (Deprecated):**
- Fixed color assignments (ColorMaterialMapper old patterns)
- AutoCAD ARX APIs (BricsCAD BRX only)
- Hardcoded material lists
- Legacy .NET plugin approaches

### **ALWAYS USE (Current):**
- Variable color assignment with BricsCAD color picker
- BricsCAD BRX SDK V25 only
- Flexible boundary boxes for version management
- User-defined material systems
- Direct Excel cell mapping via feeder sheets
- Mathematical precision (not lookup tables)

## ?? **GitHub Copilot Integration**

This repository includes `.github/copilot-instructions.md` with complete development guidelines for AI-assisted development.

## ?? **Development Status**

- ? **Core Architecture** - Modern flexible system implemented
- ? **Visual Studio Project** - Complete C++ MFC implementation
- ? **BricsCAD Integration** - V25 BIM support classes
- ? **Excel Integration** - Feeder sheet management
- ?? **UI Polish** - Final UI enhancements
- ?? **Testing** - Comprehensive validation

---

**?? Enhanced Construction Takeoff - Professional BricsCAD V25 Solution**

*Complete flexible architecture with no fixed color assignments - everything user-defined*
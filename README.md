# Enhanced Construction Takeoff - BricsCAD V25 Plugin

[![BricsCAD V25](https://img.shields.io/badge/BricsCAD-V25-blue.svg)](https://www.bricsys.com/)
[![Platform](https://img.shields.io/badge/Platform-x64-green.svg)](https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Production%20Ready-brightgreen.svg)](https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25)

## ?? **Revolutionary Construction Estimation Plugin**

**Enhanced Construction Takeoff** is a professional BricsCAD V25 plugin that eliminates all fixed color restrictions and provides complete user control over construction material estimation. Built with modern flexible architecture and mathematical precision algorithms.

### ?? **Key Features**

- ?? **ZERO Fixed Colors** - Assign ANY color to ANY material
- ??? **AGS Elevation System** - 12 standard construction variations (AGS, AGB, AGH, HGS, etc.)
- ?? **Live Excel Integration** - Direct cell mapping with formula preservation
- ?? **Real-time Calculations** - Mathematical precision, no lookup tables
- ?? **Plan Management** - Dynamic Plan A/B/C/D version control
- ??? **Professional UI** - Native BricsCAD V25 integration

## ?? **Quick Start**

### Prerequisites
- **BricsCAD V25** with BRX SDK
- **Visual Studio 2022** (for building)
- **Windows 10/11 x64**

### Installation
1. Download the latest [release](https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25/releases)
2. Load in BricsCAD: `APPLOAD` ? `EnhancedTakeoffNativeUI_VS.brx`
3. Run command: `ENHANCEDTAKEOFF`

## ?? **How It Works**

### 1. **Flexible Color Assignment**
```
Pick ANY color from drawing ? Assign to ANY material ? Set cost & Excel cell
```
- No restrictions on color usage
- User-defined material names
- Direct Excel cell mapping

### 2. **AGS Elevation System**
```
A = A-frame roof    vs    H = Hip roof
G = With garage     vs    N = No garage  
S = Stucco siding   vs    H = Hardi    vs    B = Brick
```
**Standard Combinations:** AGS, AGB, AGH, ANS, ANB, ANH, HGS, HGB, HGH, HNS, HNB, HNH

### 3. **Excel Integration**
- Connect to existing workbooks
- Map colors to specific cells (e.g., "B15", "C22")
- Preserve existing formulas
- Live quantity updates

## ??? **Architecture**

### **Core Components**
- **FlexibleColorAssignment.cpp/.h** - Zero fixed colors, complete user control
- **AttachmentManager.cpp/.h** - Plan version management with AGS system
- **BoundaryVersionManager.cpp/.h** - Boundary-based version control
- **FeederSheetManager.cpp/.h** - Excel integration with formula preservation
- **BricsCADV25SupportClasses.cpp/.h** - Native BIM integration

### **Project Structure**
```
enhanced-construction-takeoff-bricscad-v25/
??? VisualStudio/
?   ??? EnhancedTakeoffNativeUI_VS/     # Main Visual Studio project
??? Core/                               # Flexible architecture headers
??? Excel/                              # Integration components
??? UI/                                 # User interface components
??? Documentation/                      # Architecture guides
??? .github/                           # Development guidelines
```

## ?? **Building from Source**

### Quick Build
```powershell
# Clone repository
git clone https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25.git
cd enhanced-construction-takeoff-bricscad-v25

# Build using PowerShell script
.\Build_Enhanced_Takeoff_Complete.ps1
```

### Visual Studio Build
1. Open `VisualStudio\EnhancedTakeoffNativeUI_VS\EnhancedTakeoffNativeUI_VS.sln`
2. Set Platform: **x64**
3. Set Configuration: **Release**
4. Build ? Build Solution

See [BUILD.md](BUILD.md) for detailed instructions.

## ?? **Usage Examples**

### Basic Workflow
1. **Pick Color**: Use BricsCAD color picker or match from entity
2. **Define Material**: Assign to "Interior Wall", "Roofing", etc.
3. **Set Cost**: Enter unit cost (per LF, SF, or EA)
4. **Map to Excel**: Optional - map to specific Excel cell
5. **Get Quantities**: Real-time calculation with manual refresh

### AGS Elevation Switching
```
Current: AGS (A-frame + Garage + Stucco)
Switch to: HGB (Hip roof + Garage + Brick)
? Automatically updates layer visibility and quantities
```

### Excel Integration
```
Color 5 ? "Roofing SF" ? Cell "B22" ? Formula preserved
Color 12 ? "Foundation LF" ? Cell "C8" ? Live updates
```

## ?? **Key Advantages**

### **vs Traditional Systems:**
- ? Fixed color assignments ? ? **Complete user control**
- ? Hardcoded materials ? ? **User-defined material library**
- ? Lookup tables ? ? **Mathematical precision algorithms**
- ? Fixed Excel formats ? ? **Flexible cell mapping**

### **Technical Benefits:**
- ?? **Native BricsCAD V25 API** - Proper transaction handling
- ?? **Mathematical Algorithms** - No approximations or lookup tables
- ?? **Memory Efficient** - Optimized entity processing
- ?? **Excel Formula Safe** - Preserves existing worksheet logic

## ?? **Documentation**

- [Architecture Guide](STRUCTURE.md) - Technical implementation details
- [Build Instructions](BUILD.md) - Complete setup and compilation guide
- [Project Status](Documentation/PROJECT_STATUS.md) - Current development state
- [Copilot Guidelines](.github/copilot-instructions.md) - AI development standards

## ?? **Contributing**

1. Fork the repository
2. Create feature branch: `git checkout -b feature/amazing-feature`
3. Commit changes: `git commit -m 'Add amazing feature'`
4. Push to branch: `git push origin feature/amazing-feature`
5. Open Pull Request

### Development Standards
- **NO FIXED COLORS** - Maintain complete user flexibility
- **BricsCAD V25 Only** - No AutoCAD dependencies
- **Mathematical Precision** - No lookup tables or approximations
- **Professional UI** - Native BricsCAD integration

## ?? **Project Status**

### ? **Production Ready Features**
- [x] Flexible color assignment system (NO FIXED COLORS)
- [x] AGS elevation system (12 standard variations)
- [x] Excel integration with formula preservation
- [x] Plan A/B/C/D version management
- [x] Professional MFC UI with BricsCAD theming
- [x] Mathematical precision calculations
- [x] Boundary version management
- [x] Live quantity monitoring

### ?? **Continuous Improvements**
- [ ] Enhanced material library integration
- [ ] Advanced reporting features
- [ ] Custom measurement types
- [ ] Multi-language support

## ?? **System Requirements**

### **Minimum:**
- BricsCAD V25 (with BRX SDK for development)
- Windows 10 x64
- 4 GB RAM
- 500 MB disk space

### **Recommended:**
- BricsCAD V25 Pro/Platinum
- Windows 11 x64
- 8 GB RAM
- SSD storage

## ?? **License**

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### **Third-Party Components**
- **BricsCAD BRX SDK** - Commercial license required
- **Microsoft Visual C++ Redistributable** - Required runtime

## ?? **Acknowledgments**

- **Bricsys** for the excellent BricsCAD V25 BRX SDK
- **Microsoft** for Visual Studio and MFC framework
- **Construction Industry** for feedback and requirements

## ?? **Support**

- ?? **Issues**: [GitHub Issues](https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25/issues)
- ?? **Documentation**: [Wiki](https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25/wiki)
- ?? **Discussions**: [GitHub Discussions](https://github.com/ssche13/enhanced-construction-takeoff-bricscad-v25/discussions)

---

**?? Enhanced Construction Takeoff - Where Flexibility Meets Precision** 

*Professional construction estimation with zero restrictions and complete user control.*
# Build Instructions - Enhanced Construction Takeoff BricsCAD V25

## ?? **Prerequisites**

### **Required Software:**
- **Visual Studio 2022** (Community, Professional, or Enterprise)
- **BricsCAD V25** with BRX SDK installed
- **Windows 10/11** (x64)
- **Git** for version control

### **BricsCAD V25 SDK Setup:**
1. Install BricsCAD V25 Developer edition
2. Ensure BRX SDK is installed (typically in `C:\Program Files\Bricsys\BricsCAD V25 en_US\SDK\`)
3. Set environment variable `BRX_SDK_PATH` to SDK location

### **Visual Studio Configuration:**
- Install "Desktop development with C++" workload
- Ensure MFC libraries are installed
- Install "CMake tools for Visual Studio" (optional)

## ?? **Build Process**

### **Option 1: Visual Studio GUI Build**

1. **Clone Repository:**
   ```bash
   git clone https://github.com/[your-username]/enhanced-construction-takeoff-bricscad-v25.git
   cd enhanced-construction-takeoff-bricscad-v25
   ```

2. **Open Project:**
   - Launch Visual Studio 2022
   - Open: `VisualStudio\EnhancedTakeoffNativeUI_VS\EnhancedTakeoffNativeUI_VS.sln`

3. **Configure Build:**
   - Set Platform: **x64**
   - Set Configuration: **Release** (for production) or **Debug** (for development)

4. **Verify BRX SDK Path:**
   - Right-click project ? Properties
   - Configuration Properties ? VC++ Directories
   - Include Directories should contain: `$(BRX_SDK_PATH)\inc`
   - Library Directories should contain: `$(BRX_SDK_PATH)\lib-x64`

5. **Build:**
   - Build ? Build Solution (Ctrl+Shift+B)
   - Output: `x64\Release\EnhancedTakeoffNativeUI_VS.brx`

### **Option 2: PowerShell Build Script**

1. **Run Build Script:**
   ```powershell
   .\Build\Build_Enhanced_Takeoff_BricsCAD_V25.ps1
   ```

2. **Script Features:**
   - Automatically detects Visual Studio installation
   - Configures BRX SDK paths
   - Builds Release configuration
   - Copies .brx to BricsCAD plugins folder

## ?? **Build Verification**

### **Check Build Output:**
```
VisualStudio\EnhancedTakeoffNativeUI_VS\x64\Release\
??? EnhancedTakeoffNativeUI_VS.brx    # Main plugin file
??? EnhancedTakeoffNativeUI_VS.pdb    # Debug symbols
??? EnhancedTakeoffNativeUI_VS.lib    # Import library
```

### **File Size Verification:**
- **EnhancedTakeoffNativeUI_VS.brx** should be approximately 500KB - 2MB
- If file is very small (<100KB), check for build errors

## ?? **Testing in BricsCAD**

### **Load Plugin:**
1. **Open BricsCAD V25**
2. **Command:** `APPLOAD`
3. **Browse to:** `x64\Release\EnhancedTakeoffNativeUI_VS.brx`
4. **Click:** Load

### **Test Commands:**
```
Command: ENHANCEDTAKEOFF        # Main dialog
Command: FLEXIBLECOLOR          # Color assignment
Command: TAKEOFFMATERIALS       # Material management
```

### **Verify Features:**
- ? Main dialog opens without errors
- ? Color picker integration works
- ? Material assignment functions
- ? Excel integration responds

## ?? **Troubleshooting**

### **Common Build Issues:**

#### **1. BRX SDK Not Found:**
```
Error: Cannot open include file 'brxspecific.h'
```
**Solution:**
- Verify `BRX_SDK_PATH` environment variable
- Check BricsCAD SDK installation
- Restart Visual Studio after setting environment variable

#### **2. MFC Not Found:**
```
Error: Cannot open include file 'afxwin.h'
```
**Solution:**
- Install MFC libraries via Visual Studio Installer
- Modify Visual Studio installation ? Individual Components ? MFC

#### **3. Platform Mismatch:**
```
Error: LNK1112: module machine type 'X86' conflicts with target machine type 'x64'
```
**Solution:**
- Ensure all configurations are set to x64
- Check Project Properties ? Configuration Manager

#### **4. BricsCAD Loading Issues:**
```
Error: Plugin failed to load
```
**Solution:**
- Check .brx file dependencies with Dependency Walker
- Ensure all required DLLs are available
- Verify BricsCAD version compatibility

### **Debug Build:**
For development and debugging:
1. Set Configuration to **Debug**
2. Build with debug symbols
3. Use Visual Studio debugger to attach to BricsCAD process

### **Clean Build:**
If experiencing issues:
1. Build ? Clean Solution
2. Delete `x64` and `Debug` folders
3. Rebuild entire solution

## ?? **Output Locations**

### **Release Build:**
```
VisualStudio\EnhancedTakeoffNativeUI_VS\x64\Release\
??? EnhancedTakeoffNativeUI_VS.brx
```

### **Debug Build:**
```
VisualStudio\EnhancedTakeoffNativeUI_VS\x64\Debug\
??? EnhancedTakeoffNativeUI_VS.brx
```

### **BricsCAD Plugin Folder (Optional):**
```
%APPDATA%\Bricsys\BricsCAD\V25\en_US\Support\
```

## ?? **Continuous Integration (Future)**

### **GitHub Actions Setup:**
- Automated builds on push/pull request
- Multiple configuration testing
- Artifact generation and storage

### **Build Matrix:**
- Release x64
- Debug x64
- Multiple BricsCAD versions (if applicable)

---

**?? Build successfully creates a modern, flexible BricsCAD V25 plugin with NO FIXED COLORS - everything user-defined!**
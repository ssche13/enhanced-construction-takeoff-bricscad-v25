# Contributing to Enhanced Construction Takeoff

?? Thank you for considering contributing to Enhanced Construction Takeoff! This document provides guidelines for contributing to this BricsCAD V25 plugin project.

## ?? **Core Principles**

Before contributing, understand our fundamental principles:

- **NO FIXED COLORS** - Maintain complete user flexibility in color assignments
- **BricsCAD V25 Only** - No AutoCAD dependencies or mixed namespaces
- **Mathematical Precision** - Use direct algorithms, not lookup tables
- **User-Defined Everything** - No hardcoded materials, templates, or workflows
- **Professional Quality** - Enterprise-grade code and documentation

## ?? **Getting Started**

### Prerequisites
- **BricsCAD V25** with BRX SDK
- **Visual Studio 2022** (Community, Professional, or Enterprise)
- **Git** for version control
- **Windows 10/11 x64**

### Development Setup
1. **Fork the repository**
   ```bash
   git clone https://github.com/[your-username]/enhanced-construction-takeoff-bricscad-v25.git
   cd enhanced-construction-takeoff-bricscad-v25
   ```

2. **Set up BRX SDK environment**
   ```bash
   # Set environment variable
   set BRX_SDK_PATH=C:\Program Files\Bricsys\BricsCAD V25 en_US\SDK\
   ```

3. **Open in Visual Studio**
   ```
   VisualStudio\EnhancedTakeoffNativeUI_VS\EnhancedTakeoffNativeUI_VS.sln
   ```

4. **Verify build configuration**
   - Platform: x64
   - Configuration: Debug (for development)
   - Build and test

## ?? **Types of Contributions**

### ?? **Bug Reports**
Create detailed issue reports with:
- **Environment**: BricsCAD version, Windows version, system specs
- **Steps to reproduce**: Clear, numbered steps
- **Expected behavior**: What should happen
- **Actual behavior**: What actually happens
- **Screenshots/logs**: If applicable
- **Minimal test case**: If possible

### ?? **Bug Fixes**
- Create issue first (unless trivial)
- Follow existing code style
- Add tests if applicable
- Update documentation if needed

### ? **New Features**
- **Discuss first**: Create issue to discuss the feature
- **Follow architecture**: Maintain flexible, user-controlled design
- **No fixed restrictions**: Ensure feature maintains user flexibility
- **Document thoroughly**: Update README, comments, and guides

### ?? **Documentation**
- Fix typos and clarify instructions
- Add examples and use cases
- Update technical documentation
- Improve code comments

## ??? **Development Guidelines**

### **Code Standards**

#### **Architecture Rules**
```cpp
// ? CORRECT: User-defined flexibility
class FlexibleColorAssignment {
public:
    bool AssignColor(int colorIndex, const ColorAssignment& assignment);
    // User defines everything - no restrictions
};

// ? WRONG: Fixed assignments
class FixedColorMapper {
    static const int WALL_COLOR = 5;  // Never do this!
};
```

#### **BricsCAD V25 Integration**
```cpp
// ? CORRECT: Proper transaction handling
AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
AcDbTransaction* pTrans = pDb->startTransaction();
// ... operations ...
pTrans->endTransaction();

// ? WRONG: AutoCAD references
#include "adslib.h"  // Don't use AutoCAD headers
```

#### **Naming Conventions**
- **Classes**: PascalCase (`FlexibleColorAssignment`)
- **Functions**: PascalCase (`AssignColor`)
- **Variables**: camelCase (`colorIndex`)
- **Constants**: UPPER_SNAKE_CASE (`MAX_COLORS`)
- **Files**: PascalCase (`FlexibleColorAssignment.cpp`)

#### **Code Style**
```cpp
// Function documentation
/**
 * Assigns a color to user-defined material with flexible mapping
 * @param colorIndex BricsCAD color index (1-255)
 * @param assignment User-defined assignment details
 * @return true if assignment successful
 */
bool AssignColor(int colorIndex, const ColorAssignment& assignment);

// Error handling
try {
    // Operation
    return true;
} catch (const std::exception& e) {
    LogError("Operation failed: " + std::string(e.what()));
    return false;
}

// Resource management
std::unique_ptr<Manager> m_manager = std::make_unique<Manager>();
```

### **Architectural Constraints**

#### **? ALWAYS Use**
- `FlexibleColorAssignment` for color management
- `AttachmentManager` for plan version control
- `BoundaryVersionManager` for AGS elevation system
- `FeederSheetManager` for Excel integration
- BricsCAD BRX SDK V25 APIs
- Mathematical precision algorithms
- User-defined material systems

#### **? NEVER Use**
- Fixed color assignments or hardcoded colors
- AutoCAD ARX APIs or mixed namespaces
- Lookup tables instead of calculations
- Hardcoded material libraries
- Fixed Excel cell formats
- Legacy ColorMaterialMapper patterns

### **Testing Requirements**

#### **Before Submitting**
1. **Build successfully** in both Debug and Release configurations
2. **Test in BricsCAD V25** - Load plugin and verify functionality
3. **No memory leaks** - Check with debugging tools
4. **No fixed restrictions** - Ensure user maintains complete control
5. **Documentation updated** - Update relevant docs

#### **Test Scenarios**
```cpp
// Example test cases
void TestFlexibleColorAssignment() {
    // Test user can assign ANY color to ANY material
    FlexibleColorAssignment assigner;
    
    // Should allow any color-material combination
    assert(assigner.AssignColor(1, {"Interior Wall", 2.50, "B15"}));
    assert(assigner.AssignColor(1, {"Roofing", 15.00, "C22"}));  // Same color, different material
    assert(assigner.AssignColor(255, {"Custom Material", 100.00, "Z99"}));
}
```

## ?? **Pull Request Process**

### **Before Submitting**
1. **Create feature branch**
   ```bash
   git checkout -b feature/amazing-feature
   # or
   git checkout -b fix/critical-bug
   ```

2. **Follow commit conventions**
   ```bash
   git commit -m "feat: add flexible material library management
   
   - Implement user-defined material categories
   - Add import/export functionality
   - Maintain NO FIXED COLORS principle
   - Update documentation
   
   Refs: #123"
   ```

3. **Update documentation**
   - Update README if user-facing changes
   - Update CHANGELOG.md with changes
   - Add code comments for complex logic

### **PR Template**
```markdown
## Description
Brief description of changes and motivation.

## Type of Change
- [ ] Bug fix (non-breaking change that fixes an issue)
- [ ] New feature (non-breaking change that adds functionality)
- [ ] Breaking change (fix or feature that would cause existing functionality to not work as expected)
- [ ] Documentation update

## Architecture Compliance
- [ ] Maintains NO FIXED COLORS principle
- [ ] Uses BricsCAD V25 APIs only (no AutoCAD)
- [ ] Preserves user flexibility and control
- [ ] Follows mathematical precision approach

## Testing
- [ ] Builds successfully (Debug and Release)
- [ ] Tested in BricsCAD V25
- [ ] No memory leaks detected
- [ ] Documentation updated

## Screenshots/Examples
If applicable, add screenshots or code examples.
```

### **Review Process**
1. **Automated checks** must pass
2. **Code review** by maintainers
3. **Architecture compliance** verification
4. **Testing verification** in BricsCAD V25
5. **Documentation review**

## ?? **Contribution Ideas**

### **High Priority**
- Enhanced material library management
- Advanced Excel integration features
- Performance optimizations
- Additional measurement types
- Improved error handling

### **Medium Priority**
- Multi-language support
- Enhanced reporting capabilities
- Advanced BIM object recognition
- Cloud storage integration

### **Documentation**
- Video tutorials
- Code examples
- Architecture deep dives
- User guides
- Best practices

## ?? **Technical Areas**

### **UI/UX Improvements**
- Enhance material selection dialogs
- Improve color assignment workflow
- Add keyboard shortcuts
- Better error messages

### **Core Functionality**
- Mathematical algorithm optimizations
- Memory usage improvements
- Better entity processing
- Enhanced calculation precision

### **Integration Features**
- Advanced Excel functions
- Better BIM object recognition
- Enhanced AGS elevation support
- Improved attachment management

## ?? **Getting Help**

### **Questions?**
- ?? **GitHub Discussions**: General questions and ideas
- ?? **GitHub Issues**: Bug reports and feature requests
- ?? **Direct Contact**: For complex architectural questions

### **Resources**
- [BricsCAD BRX SDK Documentation](https://help.bricsys.com/)
- [Project Architecture Guide](STRUCTURE.md)
- [Build Instructions](BUILD.md)
- [Copilot Guidelines](.github/copilot-instructions.md)

## ?? **Recognition**

All contributors will be:
- Listed in project credits
- Mentioned in release notes
- Recognized in documentation

Significant contributions may lead to:
- Maintainer privileges
- Technical review responsibilities
- Architecture decision participation

---

## ?? **Checklist for Contributors**

- [ ] I have read and understand the core principles
- [ ] I have set up the development environment
- [ ] I follow the coding standards and architecture rules
- [ ] I maintain the NO FIXED COLORS principle
- [ ] I use BricsCAD V25 APIs exclusively
- [ ] I test thoroughly before submitting
- [ ] I update documentation as needed
- [ ] I follow the PR process

---

**?? Thank you for contributing to Enhanced Construction Takeoff!**

*Together, we're building a construction estimation tool with unprecedented flexibility and precision.*
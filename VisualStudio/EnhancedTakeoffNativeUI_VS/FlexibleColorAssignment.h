// FlexibleColorAssignment.h - User-defined color to material mapping
#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

#ifndef BUILDING_TESTS
#if HAS_BRX_SDK
#include "acadstrc.h"
#include "dbcolor.h"
#endif
#endif

namespace EnhancedTakeoff {

/**
 * Flexible color assignment system - NO FIXED COLORS
 * Users can assign any color to any material with any measurement type
 * COPILOT-HINT: This replaces the old ColorMaterialMapper fixed system
 */
class FlexibleColorAssignment {
public:
    enum class MeasurementType {
        LF,           // Linear feet
        SF,           // Square feet  
        EA,           // Each/count
        LF_PITCH,     // Linear feet on pitch
        SF_PITCH,     // Square feet on pitch
        LF_HIP,       // Linear feet for hip between pitches
        CUSTOM        // User-defined measurement
    };
    
    struct ColorAssignment {
        int colorIndex;                          // BricsCAD color index (1-255)
        std::string materialName;                // User-defined material name
        std::vector<MeasurementType> measurementTypes;  // Multiple types allowed
        double unitCost;                         // Cost per unit
        std::string excelCell;                   // Direct Excel cell mapping
        std::string excelFormula;                // Optional Excel formula
        std::string description;                 // User notes
        bool isActive;
        
        // RGB values for true color support
        int red, green, blue;
        bool isTrueColor;
        
        ColorAssignment() : colorIndex(0), unitCost(0.0), isActive(true),
                           red(0), green(0), blue(0), isTrueColor(false) {}
    };
    
    FlexibleColorAssignment();
    ~FlexibleColorAssignment();
    
    // Color assignment operations - completely flexible
    bool AssignColor(int colorIndex, const ColorAssignment& assignment);
    bool AssignTrueColor(int r, int g, int b, const ColorAssignment& assignment);
    bool RemoveColorAssignment(int colorIndex);
    void ClearAllAssignments();
    
    // Material management
    bool UpdateMaterial(int colorIndex, const std::string& materialName);
    bool UpdateUnitCost(int colorIndex, double unitCost);
    bool UpdateExcelMapping(int colorIndex, const std::string& cell, 
                           const std::string& formula = "");
    
    // Measurement type management
    bool AddMeasurementType(int colorIndex, MeasurementType type);
    bool RemoveMeasurementType(int colorIndex, MeasurementType type);
    std::vector<MeasurementType> GetMeasurementTypes(int colorIndex) const;
    
    // Query methods
    ColorAssignment* GetAssignment(int colorIndex);
    std::vector<ColorAssignment> GetAllAssignments() const;
    std::vector<int> GetAssignedColors() const;
    bool IsColorAssigned(int colorIndex) const;
    
    // Material library integration
    std::vector<std::string> GetAvailableMaterials() const;
    bool ImportMaterialLibrary(const std::string& libraryPath);
    
    // Excel mapping
    std::map<std::string, int> GetExcelMappings() const;
    std::string GenerateExcelFormula(int colorIndex, MeasurementType type) const;
    
    // BricsCAD color picker integration
#ifndef BUILDING_TESTS
#if HAS_BRX_SDK
    bool ShowColorPicker(ColorAssignment& assignment);
    bool MatchColorFromEntity(const AcDbObjectId& entityId, ColorAssignment& assignment);
#endif
#endif
    
    // Calculation methods
    double CalculateQuantity(int colorIndex, double rawValue, MeasurementType type,
                            double pitchFactor = 1.0) const;
    double CalculateCost(int colorIndex, double quantity) const;
    
    // Presets and templates
    bool SavePreset(const std::string& presetName, const std::string& filePath) const;
    bool LoadPreset(const std::string& filePath);
    std::vector<std::string> GetAvailablePresets() const;
    
    // Boundary box color filtering
    std::vector<int> GetColorsInBoundary(const std::string& boundaryName) const;
    void SetBoundaryFilter(const std::string& boundaryName, 
                          const std::vector<int>& colorIndices);
    
    // Event callbacks for UI updates
    using ColorChangeCallback = std::function<void(int colorIndex)>;
    void RegisterColorChangeCallback(ColorChangeCallback callback);
    
private:
    std::map<int, ColorAssignment> m_assignments;
    std::map<std::string, std::vector<int>> m_boundaryFilters;
    std::vector<ColorChangeCallback> m_callbacks;
    std::vector<std::string> m_materialLibrary;
    
    void NotifyColorChange(int colorIndex);
    int GetColorFromRGB(int r, int g, int b) const;
    std::string GetMeasurementTypeString(MeasurementType type) const;
};

} // namespace EnhancedTakeoff
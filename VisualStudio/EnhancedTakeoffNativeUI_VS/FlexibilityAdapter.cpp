// FlexibilityAdapter.cpp - Implementation for compatibility layer
#include "pch.h"
#include "FlexibilityAdapter.h"

namespace EnhancedTakeoff {

void FlexibilityAdapter::MigrateExistingAssignments(
    FlexibleColorAssignment* newSystem,
    const void* oldSystem) {  // Changed to void* since ColorMaterialMapper is deprecated
    
    if (!newSystem) return;
    
    // Initialize with some default assignments for migration
    InitializeCommonMaterials(newSystem);
}

std::vector<int> FlexibilityAdapter::GetLegacyColorAssignments() {
    // Return old fixed color assignments for compatibility
    std::vector<int> legacyColors;
    
    // Old fixed families (DEPRECATED - for compatibility only)
    for (int i = 1; i <= 64; ++i) {  // Old 8 families x 8 heights
        legacyColors.push_back(i);
    }
    
    return legacyColors;
}

bool FlexibilityAdapter::ConvertLegacyMapping(int oldColorFamily, int newColorIndex) {
    // Convert old fixed family mapping to new flexible system
    // This is for migration only
    return (oldColorFamily >= 1 && oldColorFamily <= 8) && 
           (newColorIndex >= 1 && newColorIndex <= 255);
}

void FlexibilityAdapter::InitializeLegacyCompatibility(FlexibleColorAssignment* flexSystem) {
    if (!flexSystem) return;
    
    InitializeCommonMaterials(flexSystem);
}

void FlexibilityAdapter::InitializeCommonMaterials(FlexibleColorAssignment* flexSystem) {
    if (!flexSystem) return;
    
    // Define common material templates for migration
    struct MaterialTemplate {
        std::string name;
        double defaultCost;
        std::string description;
    };
    
    std::vector<MaterialTemplate> materials = {
        {"Interior Wall", 2.50, "Interior wall framing and drywall"},
        {"Exterior Wall", 4.75, "Exterior wall with siding"},
        {"Roofing", 8.50, "Roofing materials and labor"},
        {"Foundation", 6.25, "Foundation concrete and rebar"},
        {"Flooring", 5.00, "Flooring materials and installation"},
        {"Electrical", 3.50, "Electrical rough and finish"},
        {"Plumbing", 4.25, "Plumbing rough and finish"},
        {"HVAC", 7.00, "HVAC ductwork and equipment"},
        {"Insulation", 1.85, "Wall and ceiling insulation"},
        {"Windows", 12.50, "Window units and installation"},
        {"Doors", 8.75, "Door units and hardware"},
        {"Trim", 3.25, "Interior and exterior trim"},
        {"Cabinets", 15.00, "Kitchen and bathroom cabinets"},
        {"Appliances", 25.00, "Built-in appliances"},
        {"User Defined 1", 0.00, "Custom material 1"},
        {"User Defined 2", 0.00, "Custom material 2"}
    };
    
    // Create default assignments - users can override these
    for (size_t i = 0; i < materials.size() && i < 16; ++i) {
        FlexibleColorAssignment::ColorAssignment assignment;
        assignment.colorIndex = static_cast<int>(i + 1);
        assignment.materialName = materials[i].name;
        assignment.unitCost = materials[i].defaultCost;
        assignment.description = materials[i].description;
        assignment.measurementTypes.push_back(FlexibleColorAssignment::MeasurementType::LF);
        assignment.isActive = true;
        
        flexSystem->AssignColor(assignment.colorIndex, assignment);
    }
}

} // namespace EnhancedTakeoff
// FlexibilityAdapter.cpp - Implementation for compatibility layer
#include "FlexibilityAdapter.h"

namespace EnhancedTakeoff {

void FlexibilityAdapter::MigrateExistingAssignments(
    FlexibleColorAssignment* newSystem) {
    
    if (!newSystem) return;
    
    // Migrate from old fixed color families to flexible assignments
    // This provides a starting point for users to customize
    
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
    
    // Initialize with some default assignments for backward compatibility
    // Users can override these with their own assignments
    
    FlexibleColorAssignment::ColorAssignment redWall;
    redWall.colorIndex = 1;
    redWall.materialName = "Interior Wall (User Defined)";
    redWall.materialType = FlexibleColorAssignment::MaterialType::WALL;
    redWall.unitCost = 0.0;  // User will set
    redWall.description = "Migrated from legacy system - customize as needed";
    redWall.isUserDefined = true;
    
    flexSystem->AssignColor(1, redWall);
    
    // Note: Users should define their own color assignments
    // This is just for migration compatibility
}

void FlexibilityAdapter::InitializeCommonMaterials(FlexibleColorAssignment* flexSystem) {
    if (!flexSystem) return;
    
    // Initialize common material templates that users can customize
    struct MaterialTemplate {
        int colorIndex;
        std::string name;
        FlexibleColorAssignment::MaterialType type;
        std::string description;
    };
    
    std::vector<MaterialTemplate> templates = {
        {1, "Interior Wall", FlexibleColorAssignment::MaterialType::WALL, "Standard interior wall construction"},
        {2, "Exterior Wall", FlexibleColorAssignment::MaterialType::WALL, "Exterior wall with insulation"},
        {3, "Structural Beam", FlexibleColorAssignment::MaterialType::STRUCTURAL, "Steel or wood beam"},
        {4, "Floor Joist", FlexibleColorAssignment::MaterialType::FRAMING, "Floor framing member"},
        {5, "Roof Material", FlexibleColorAssignment::MaterialType::ROOFING, "Roofing system"},
        {6, "Foundation", FlexibleColorAssignment::MaterialType::CONCRETE, "Concrete foundation"},
        {7, "MEP System", FlexibleColorAssignment::MaterialType::MEP, "Mechanical/Electrical/Plumbing"},
        {8, "Custom Material", FlexibleColorAssignment::MaterialType::CUSTOM, "User-defined material"}
    };
    
    for (const auto& template_ : templates) {
        FlexibleColorAssignment::ColorAssignment assignment;
        assignment.colorIndex = template_.colorIndex;
        assignment.materialName = template_.name;
        assignment.materialType = template_.type;
        assignment.description = template_.description;
        assignment.unitCost = 0.0; // User will set
        assignment.isUserDefined = true;
        assignment.isActive = false; // User must activate
        
        flexSystem->AssignColor(template_.colorIndex, assignment);
    }
}

} // namespace EnhancedTakeoff
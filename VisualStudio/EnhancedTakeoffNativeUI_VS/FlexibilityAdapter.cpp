// FlexibilityAdapter.cpp - Implementation for compatibility layer
#include "FlexibilityAdapter.h"
#include "ColorMaterialMapper.h"  // Legacy system

namespace EnhancedTakeoff {

void FlexibilityAdapter::MigrateExistingAssignments(
    FlexibleColorAssignment* newSystem,
    const ColorMaterialMapper* oldSystem) {
    
    if (!newSystem || !oldSystem) return;
    
    // Migrate old fixed color families to flexible assignments
    // LEGACY: Red family (1-8) -> User-defined assignments
    // LEGACY: Blue family (9-16) -> User-defined assignments
    // etc.
    
    // Get old assignments and convert to flexible
    for (int i = 1; i <= 255; ++i) {
        // Check if old system had this color assigned
        auto oldMaterial = oldSystem->GetMaterialForColor(i);
        if (!oldMaterial.empty()) {
            FlexibleColorAssignment::ColorAssignment assignment;
            assignment.colorIndex = i;
            assignment.materialName = oldMaterial;
            assignment.unitCost = oldSystem->GetUnitCost(i);
            assignment.isActive = true;
            
            // Convert old measurement type
            assignment.measurementTypes.push_back(
                FlexibleColorAssignment::MeasurementType::LF
            );
            
            newSystem->AssignColor(i, assignment);
        }
    }
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
    redWall.measurementTypes.push_back(FlexibleColorAssignment::MeasurementType::LF);
    redWall.unitCost = 0.0;  // User will set
    redWall.description = "Migrated from legacy system - customize as needed";
    
    flexSystem->AssignColor(1, redWall);
    
    // Note: Users should define their own color assignments
    // This is just for migration compatibility
}

} // namespace EnhancedTakeoff
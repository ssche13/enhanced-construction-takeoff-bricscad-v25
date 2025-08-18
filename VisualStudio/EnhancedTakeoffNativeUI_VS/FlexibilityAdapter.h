// FlexibilityAdapter.h - Compatibility layer for smooth transition
#pragma once

#include "FlexibleColorAssignment.h"

namespace EnhancedTakeoff {

/**
 * Compatibility adapter for smooth transition from fixed to flexible system
 * COPILOT-HINT: Use this to migrate existing code gradually
 */
class FlexibilityAdapter {
public:
    // Convert old fixed assignments to new flexible system
    static void MigrateExistingAssignments(
        FlexibleColorAssignment* newSystem,
        const void* oldSystem  // Changed from deprecated ColorMaterialMapper
    );
    
    // Provide fallback for existing code
    static std::vector<int> GetLegacyColorAssignments();
    
    // Bridge old material mapping to new system
    static bool ConvertLegacyMapping(int oldColorFamily, int newColorIndex);
    
    // Temporary compatibility methods
    static void InitializeLegacyCompatibility(FlexibleColorAssignment* flexSystem);
    
private:
    // Initialize common materials for migration
    static void InitializeCommonMaterials(FlexibleColorAssignment* flexSystem);
};

} // namespace EnhancedTakeoff

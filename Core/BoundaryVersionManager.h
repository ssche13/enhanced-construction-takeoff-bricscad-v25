// BoundaryVersionManager.h - Manages boundary boxes with version toggling
#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>

#ifndef BUILDING_TESTS
#if HAS_BRX_SDK
#include "geassign.h"
#include "dbents.h"
#endif
#endif

namespace EnhancedTakeoff {

/**
 * Manages boundary boxes for version control (AGS system)
 * Allows toggling different siding/material versions within boundaries
 * COPILOT-HINT: Flexible boundary system for multi-version house plans
 */
class BoundaryVersionManager {
public:
    struct BoundaryBox {
        std::string name;                    // "Main House", "Garage", "Porch"
        std::string attachmentPlan;          // "Plan B"
        std::vector<int> baseColors;         // Base colors in boundary
        std::map<char, std::vector<int>> versionColors;  // 'A'->stucco colors, 'G'->hardi colors
        bool isActive;
        
#ifndef BUILDING_TESTS
#if HAS_BRX_SDK
        AcGePoint3d minPoint;
        AcGePoint3d maxPoint;
        AcDbObjectId boundaryEntity;
#else
        double minX, minY, minZ;
        double maxX, maxY, maxZ;
#endif
#endif
        
        BoundaryBox() : isActive(true) {
#ifndef BUILDING_TESTS
#if !HAS_BRX_SDK
            minX = minY = minZ = 0.0;
            maxX = maxY = maxZ = 0.0;
#endif
#endif
        }
    };
    
    BoundaryVersionManager();
    ~BoundaryVersionManager();
    
    // Boundary management
    bool CreateBoundary(const std::string& name, const std::string& attachmentPlan);
    bool DeleteBoundary(const std::string& name);
    bool ToggleBoundary(const std::string& name, bool active);
    
    // Version color management
    bool AssignVersionColors(const std::string& boundaryName, 
                            char versionComponent,  // 'A', 'G', 'S'
                            const std::vector<int>& colorIndices);
    std::vector<int> GetActiveVersionColors(const std::string& boundaryName,
                                           const std::string& activeVersion) const;
    
    // Boundary operations
    BoundaryBox* GetBoundary(const std::string& name);
    std::vector<std::string> GetAllBoundaryNames() const;
    std::vector<BoundaryBox> GetBoundariesForPlan(const std::string& planName) const;
    
    // Entity detection
#ifndef BUILDING_TESTS
#if HAS_BRX_SDK
    bool SetBoundaryExtents(const std::string& name, 
                           const AcGePoint3d& minPt, 
                           const AcGePoint3d& maxPt);
    std::vector<AcDbObjectId> GetEntitiesInBoundary(const std::string& name) const;
    bool IsEntityInBoundary(const AcDbObjectId& entityId, const std::string& name) const;
#endif
#endif
    
    // Auto-detection
    bool AutoDetectBoundaries(const std::string& attachmentPlan);
    bool DetectBoundaryFromSelection(const std::string& name);
    
    // Version switching
    void SwitchVersion(const std::string& boundaryName, const std::string& newVersion);
    std::set<int> GetColorDifference(const std::string& boundaryName,
                                     const std::string& version1,
                                     const std::string& version2) const;
    
    // Quantity calculation support
    std::map<int, double> CalculateQuantitiesInBoundary(const std::string& name) const;
    
    // Serialization
    bool SaveBoundaries(const std::string& filePath) const;
    bool LoadBoundaries(const std::string& filePath);
    
private:
    std::map<std::string, BoundaryBox> m_boundaries;
    std::string m_activeAttachment;
    
    bool ValidateBoundaryName(const std::string& name) const;
    void UpdateActiveColors(BoundaryBox& boundary, const std::string& activeVersion);
    
#ifndef BUILDING_TESTS
#if HAS_BRX_SDK
    bool IsPointInBoundary(const AcGePoint3d& pt, const BoundaryBox& boundary) const;
#endif
#endif
};

} // namespace EnhancedTakeoff
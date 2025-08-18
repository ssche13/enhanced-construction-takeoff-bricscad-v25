// BoundaryVersionManager.cpp - Flexible boundary management implementation
// Enhanced Construction Takeoff - BricsCAD V25 Plugin
// COPILOT-HINT: Manages boundary boxes for version control (AGS system)

#include "pch.h"
#include "BoundaryVersionManager.h"

namespace EnhancedTakeoff {

BoundaryVersionManager::BoundaryVersionManager() {
    // Initialize empty boundary collection
}

BoundaryVersionManager::~BoundaryVersionManager() {
    // Cleanup
    m_boundaries.clear();
}

bool BoundaryVersionManager::CreateBoundary(const std::string& name, const std::string& attachmentPlan) {
    if (!ValidateBoundaryName(name)) {
        return false;
    }
    
    BoundaryBox boundary;
    boundary.name = name;
    boundary.attachmentPlan = attachmentPlan;
    boundary.isActive = true;
    
    m_boundaries[name] = boundary;
    return true;
}

bool BoundaryVersionManager::DeleteBoundary(const std::string& name) {
    auto it = m_boundaries.find(name);
    if (it != m_boundaries.end()) {
        m_boundaries.erase(it);
        return true;
    }
    return false;
}

bool BoundaryVersionManager::ToggleBoundary(const std::string& name, bool active) {
    auto it = m_boundaries.find(name);
    if (it != m_boundaries.end()) {
        it->second.isActive = active;
        return true;
    }
    return false;
}

bool BoundaryVersionManager::AssignVersionColors(const std::string& boundaryName, 
                                                char versionComponent,
                                                const std::vector<int>& colorIndices) {
    auto it = m_boundaries.find(boundaryName);
    if (it != m_boundaries.end()) {
        it->second.versionColors[versionComponent] = colorIndices;
        return true;
    }
    return false;
}

std::vector<int> BoundaryVersionManager::GetActiveVersionColors(const std::string& boundaryName,
                                                              const std::string& activeVersion) const {
    auto it = m_boundaries.find(boundaryName);
    if (it == m_boundaries.end() || activeVersion.length() < 3) {
        return {};
    }
    
    const BoundaryBox& boundary = it->second;
    std::vector<int> activeColors = boundary.baseColors;
    
    // Apply version-specific colors
    char frameType = activeVersion[0];  // A or H
    char garageType = activeVersion[1]; // G or N  
    char sidingType = activeVersion[2]; // S, H, or B
    
    // Add colors for active version components
    auto frameIt = boundary.versionColors.find(frameType);
    if (frameIt != boundary.versionColors.end()) {
        activeColors.insert(activeColors.end(), frameIt->second.begin(), frameIt->second.end());
    }
    
    auto garageIt = boundary.versionColors.find(garageType);
    if (garageIt != boundary.versionColors.end()) {
        activeColors.insert(activeColors.end(), garageIt->second.begin(), garageIt->second.end());
    }
    
    auto sidingIt = boundary.versionColors.find(sidingType);
    if (sidingIt != boundary.versionColors.end()) {
        activeColors.insert(activeColors.end(), sidingIt->second.begin(), sidingIt->second.end());
    }
    
    return activeColors;
}

BoundaryVersionManager::BoundaryBox* BoundaryVersionManager::GetBoundary(const std::string& name) {
    auto it = m_boundaries.find(name);
    return (it != m_boundaries.end()) ? &it->second : nullptr;
}

std::vector<std::string> BoundaryVersionManager::GetAllBoundaryNames() const {
    std::vector<std::string> names;
    names.reserve(m_boundaries.size());
    
    for (const auto& pair : m_boundaries) {
        names.push_back(pair.first);
    }
    
    return names;
}

std::vector<BoundaryVersionManager::BoundaryBox> BoundaryVersionManager::GetBoundariesForPlan(const std::string& planName) const {
    std::vector<BoundaryBox> result;
    
    for (const auto& pair : m_boundaries) {
        if (pair.second.attachmentPlan == planName) {
            result.push_back(pair.second);
        }
    }
    
    return result;
}

bool BoundaryVersionManager::AutoDetectBoundaries(const std::string& attachmentPlan) {
    // Placeholder implementation - would scan drawing for boundary objects
    return false;
}

bool BoundaryVersionManager::DetectBoundaryFromSelection(const std::string& name) {
    // Placeholder implementation - would create boundary from user selection
    return false;
}

void BoundaryVersionManager::SwitchVersion(const std::string& boundaryName, const std::string& newVersion) {
    auto it = m_boundaries.find(boundaryName);
    if (it != m_boundaries.end()) {
        UpdateActiveColors(it->second, newVersion);
    }
}

std::set<int> BoundaryVersionManager::GetColorDifference(const std::string& boundaryName,
                                                       const std::string& version1,
                                                       const std::string& version2) const {
    std::vector<int> colors1 = GetActiveVersionColors(boundaryName, version1);
    std::vector<int> colors2 = GetActiveVersionColors(boundaryName, version2);
    
    std::set<int> difference;
    
    // Find colors in version1 but not in version2
    for (int color : colors1) {
        if (std::find(colors2.begin(), colors2.end(), color) == colors2.end()) {
            difference.insert(color);
        }
    }
    
    // Find colors in version2 but not in version1
    for (int color : colors2) {
        if (std::find(colors1.begin(), colors1.end(), color) == colors1.end()) {
            difference.insert(color);
        }
    }
    
    return difference;
}

std::map<int, double> BoundaryVersionManager::CalculateQuantitiesInBoundary(const std::string& name) const {
    // Placeholder implementation - would calculate actual quantities
    std::map<int, double> quantities;
    
    auto it = m_boundaries.find(name);
    if (it != m_boundaries.end()) {
        const BoundaryBox& boundary = it->second;
        
        // Mock calculation for base colors
        for (int color : boundary.baseColors) {
            quantities[color] = 100.0; // Placeholder value
        }
    }
    
    return quantities;
}

bool BoundaryVersionManager::SaveBoundaries(const std::string& filePath) const {
    // Placeholder implementation - would save to file
    return false;
}

bool BoundaryVersionManager::LoadBoundaries(const std::string& filePath) {
    // Placeholder implementation - would load from file
    return false;
}

bool BoundaryVersionManager::ValidateBoundaryName(const std::string& name) const {
    return !name.empty() && name.length() < 256;
}

void BoundaryVersionManager::UpdateActiveColors(BoundaryBox& boundary, const std::string& activeVersion) {
    // Implementation would update the active color set based on version
    // This is called when switching between AGS variations
}

} // namespace EnhancedTakeoff
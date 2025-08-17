// FlexibleColorAssignment.cpp - Implementation for flexible color system
// Enhanced Construction Takeoff - BricsCAD V25
// COPILOT-HINT: Completely flexible - NO FIXED COLORS, all user-defined

#include "pch.h"
#include "FlexibleColorAssignment.h"

#ifdef HAS_BRX_SDK
#include "dbcolor.h"
#include "acedads.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "acutads.h"
#include "aced.h"
#endif

#include <fstream>
#include <sstream>
#include <algorithm>

namespace EnhancedTakeoff {

FlexibleColorAssignment::FlexibleColorAssignment() {
    // Initialize with NO fixed assignments - everything user-defined
    // COPILOT-HINT: This replaces ColorMaterialMapper fixed patterns
    
    m_materialLibrary = {
        "Interior Wall", "Exterior Wall", "Framing", "Roofing", 
        "Foundation", "MEP", "Siding", "Trim", "Windows", "Doors",
        "Flooring", "Electrical", "Plumbing", "HVAC", "Insulation",
        "Custom Material", "User Defined"
    };
}

FlexibleColorAssignment::~FlexibleColorAssignment() {
    // Clean up all callbacks
    m_callbacks.clear();
    m_assignments.clear();
    m_boundaryFilters.clear();
}

bool FlexibleColorAssignment::AssignColor(int colorIndex, const ColorAssignment& assignment) {
    if (colorIndex < 1 || colorIndex > 255) return false;
    
    // Store the assignment - completely flexible, no restrictions
    m_assignments[colorIndex] = assignment;
    m_assignments[colorIndex].colorIndex = colorIndex; // Ensure consistency
    
    NotifyColorChange(colorIndex);
    return true;
}

bool FlexibleColorAssignment::AssignTrueColor(int r, int g, int b, const ColorAssignment& assignment) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) return false;
    
    ColorAssignment trueColorAssignment = assignment;
    trueColorAssignment.red = r;
    trueColorAssignment.green = g;
    trueColorAssignment.blue = b;
    trueColorAssignment.isTrueColor = true;
    trueColorAssignment.colorIndex = GetColorFromRGB(r, g, b);
    
    return AssignColor(trueColorAssignment.colorIndex, trueColorAssignment);
}

bool FlexibleColorAssignment::RemoveColorAssignment(int colorIndex) {
    auto it = m_assignments.find(colorIndex);
    if (it != m_assignments.end()) {
        m_assignments.erase(it);
        NotifyColorChange(colorIndex);
        return true;
    }
    return false;
}

void FlexibleColorAssignment::ClearAllAssignments() {
    m_assignments.clear();
    NotifyColorChange(-1); // -1 indicates all colors changed
}

bool FlexibleColorAssignment::UpdateMaterial(int colorIndex, const std::string& materialName) {
    auto it = m_assignments.find(colorIndex);
    if (it != m_assignments.end()) {
        it->second.materialName = materialName;
        NotifyColorChange(colorIndex);
        return true;
    }
    return false;
}

bool FlexibleColorAssignment::UpdateUnitCost(int colorIndex, double unitCost) {
    auto it = m_assignments.find(colorIndex);
    if (it != m_assignments.end()) {
        it->second.unitCost = unitCost;
        NotifyColorChange(colorIndex);
        return true;
    }
    return false;
}

bool FlexibleColorAssignment::UpdateExcelMapping(int colorIndex, const std::string& cell, 
                                                 const std::string& formula) {
    auto it = m_assignments.find(colorIndex);
    if (it != m_assignments.end()) {
        it->second.excelCell = cell;
        it->second.excelFormula = formula;
        NotifyColorChange(colorIndex);
        return true;
    }
    return false;
}

bool FlexibleColorAssignment::AddMeasurementType(int colorIndex, MeasurementType type) {
    auto it = m_assignments.find(colorIndex);
    if (it != m_assignments.end()) {
        auto& types = it->second.measurementTypes;
        if (std::find(types.begin(), types.end(), type) == types.end()) {
            types.push_back(type);
            NotifyColorChange(colorIndex);
            return true;
        }
    }
    return false;
}

bool FlexibleColorAssignment::RemoveMeasurementType(int colorIndex, MeasurementType type) {
    auto it = m_assignments.find(colorIndex);
    if (it != m_assignments.end()) {
        auto& types = it->second.measurementTypes;
        auto typeIt = std::find(types.begin(), types.end(), type);
        if (typeIt != types.end()) {
            types.erase(typeIt);
            NotifyColorChange(colorIndex);
            return true;
        }
    }
    return false;
}

std::vector<FlexibleColorAssignment::MeasurementType> 
FlexibleColorAssignment::GetMeasurementTypes(int colorIndex) const {
    auto it = m_assignments.find(colorIndex);
    if (it != m_assignments.end()) {
        return it->second.measurementTypes;
    }
    return {};
}

FlexibleColorAssignment::ColorAssignment* FlexibleColorAssignment::GetAssignment(int colorIndex) {
    auto it = m_assignments.find(colorIndex);
    return (it != m_assignments.end()) ? &it->second : nullptr;
}

std::vector<FlexibleColorAssignment::ColorAssignment> FlexibleColorAssignment::GetAllAssignments() const {
    std::vector<ColorAssignment> result;
    result.reserve(m_assignments.size());
    
    for (const auto& pair : m_assignments) {
        result.push_back(pair.second);
    }
    return result;
}

std::vector<int> FlexibleColorAssignment::GetAssignedColors() const {
    std::vector<int> result;
    result.reserve(m_assignments.size());
    
    for (const auto& pair : m_assignments) {
        result.push_back(pair.first);
    }
    return result;
}

bool FlexibleColorAssignment::IsColorAssigned(int colorIndex) const {
    return m_assignments.find(colorIndex) != m_assignments.end();
}

std::vector<std::string> FlexibleColorAssignment::GetAvailableMaterials() const {
    return m_materialLibrary;
}

bool FlexibleColorAssignment::ImportMaterialLibrary(const std::string& libraryPath) {
    std::ifstream file(libraryPath);
    if (!file.is_open()) return false;
    
    m_materialLibrary.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            m_materialLibrary.push_back(line);
        }
    }
    return true;
}

std::map<std::string, int> FlexibleColorAssignment::GetExcelMappings() const {
    std::map<std::string, int> mappings;
    for (const auto& pair : m_assignments) {
        if (!pair.second.excelCell.empty()) {
            mappings[pair.second.excelCell] = pair.first;
        }
    }
    return mappings;
}

std::string FlexibleColorAssignment::GenerateExcelFormula(int colorIndex, MeasurementType type) const {
    auto it = m_assignments.find(colorIndex);
    if (it == m_assignments.end()) return "";
    
    const auto& assignment = it->second;
    if (!assignment.excelFormula.empty()) {
        return assignment.excelFormula;
    }
    
    // Generate default formula based on measurement type
    std::string typeStr = GetMeasurementTypeString(type);
    return "=SUM(" + assignment.excelCell + "*" + std::to_string(assignment.unitCost) + ")";
}

#ifdef HAS_BRX_SDK
bool FlexibleColorAssignment::ShowColorPicker(ColorAssignment& assignment) {
    // Use BricsCAD's native color picker dialog
    // COPILOT-HINT: This allows users to pick ANY color - no restrictions
    
    AcCmColor color;
    color.setColorIndex(7); // Default white
    
    // Show BricsCAD color dialog
    if (acedSetColorDialog(color.colorIndex(), Adesk::kFalse, 256)) {
        assignment.colorIndex = color.colorIndex();
        assignment.isTrueColor = false;
        
        // If it's a true color, get RGB values
        if (color.isByColor()) {
            assignment.red = color.red();
            assignment.green = color.green();
            assignment.blue = color.blue();
            assignment.isTrueColor = true;
        }
        
        // Let user define the material name - completely flexible
        ACHAR materialName[256] = {0};
        int result = acedGetString(0, _T("\nEnter material name: "), materialName);
        if (result == RTNORM && materialName[0] != 0) {
            assignment.materialName = CW2A(materialName);
            
            // Get unit cost
            double unitCost = 0.0;
            if (acedGetReal(_T("\nEnter unit cost: "), &unitCost) == RTNORM) {
                assignment.unitCost = unitCost;
            }
            
            // Get Excel cell mapping
            ACHAR excelCell[64] = {0};
            if (acedGetString(0, _T("\nEnter Excel cell (e.g., B15): "), excelCell) == RTNORM) {
                assignment.excelCell = CW2A(excelCell);
            }
            
            // Set default measurement type
            assignment.measurementTypes.clear();
            assignment.measurementTypes.push_back(MeasurementType::LF);
            assignment.isActive = true;
            
            return true;
        }
    }
    return false;
}

bool FlexibleColorAssignment::MatchColorFromEntity(const AcDbObjectId& entityId, ColorAssignment& assignment) {
    AcDbEntity* pEnt = nullptr;
    if (acdbOpenObject(pEnt, entityId, AcDb::kForRead) == Acad::eOk) {
        AcCmColor color = pEnt->color();
        assignment.colorIndex = color.colorIndex();
        
        if (color.isByColor()) {
            assignment.red = color.red();
            assignment.green = color.green();
            assignment.blue = color.blue();
            assignment.isTrueColor = true;
        } else {
            assignment.isTrueColor = false;
        }
        
        pEnt->close();
        return true;
    }
    return false;
}
#endif

double FlexibleColorAssignment::CalculateQuantity(int colorIndex, double rawValue, 
                                                  MeasurementType type, double pitchFactor) const {
    auto it = m_assignments.find(colorIndex);
    if (it == m_assignments.end()) return rawValue;
    
    double quantity = rawValue;
    
    // Apply mathematical precision calculations (not lookup tables)
    switch (type) {
        case MeasurementType::LF_PITCH:
        case MeasurementType::SF_PITCH:
            quantity *= pitchFactor;
            break;
        case MeasurementType::LF_HIP:
            quantity *= 1.414213562; // sqrt(2) for 45-degree hip
            break;
        case MeasurementType::SF:
        case MeasurementType::LF:
        case MeasurementType::EA:
        case MeasurementType::CUSTOM:
        default:
            // No modification for standard measurements
            break;
    }
    
    return quantity;
}

double FlexibleColorAssignment::CalculateCost(int colorIndex, double quantity) const {
    auto it = m_assignments.find(colorIndex);
    if (it != m_assignments.end()) {
        return quantity * it->second.unitCost;
    }
    return 0.0;
}

bool FlexibleColorAssignment::SavePreset(const std::string& presetName, const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file.is_open()) return false;
    
    // Save as simple CSV format
    file << "ColorIndex,MaterialName,UnitCost,ExcelCell,ExcelFormula,MeasurementType,Description\n";
    
    for (const auto& pair : m_assignments) {
        const auto& assignment = pair.second;
        file << assignment.colorIndex << ","
             << assignment.materialName << ","
             << assignment.unitCost << ","
             << assignment.excelCell << ","
             << assignment.excelFormula << ",";
             
        // Save first measurement type
        if (!assignment.measurementTypes.empty()) {
            file << GetMeasurementTypeString(assignment.measurementTypes[0]);
        }
        file << "," << assignment.description << "\n";
    }
    
    return true;
}

bool FlexibleColorAssignment::LoadPreset(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;
    
    m_assignments.clear();
    
    std::string line;
    std::getline(file, line); // Skip header
    
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        ColorAssignment assignment;
        
        // Parse CSV line
        if (std::getline(ss, token, ',')) assignment.colorIndex = std::stoi(token);
        if (std::getline(ss, token, ',')) assignment.materialName = token;
        if (std::getline(ss, token, ',')) assignment.unitCost = std::stod(token);
        if (std::getline(ss, token, ',')) assignment.excelCell = token;
        if (std::getline(ss, token, ',')) assignment.excelFormula = token;
        if (std::getline(ss, token, ',')) {
            // Parse measurement type
            assignment.measurementTypes.clear();
            assignment.measurementTypes.push_back(MeasurementType::LF); // Default
        }
        if (std::getline(ss, token, ',')) assignment.description = token;
        
        assignment.isActive = true;
        m_assignments[assignment.colorIndex] = assignment;
    }
    
    NotifyColorChange(-1); // Notify all colors changed
    return true;
}

std::vector<std::string> FlexibleColorAssignment::GetAvailablePresets() const {
    // Return list of preset files (implementation would scan directory)
    return {"Default.csv", "Residential.csv", "Commercial.csv", "Custom.csv"};
}

std::vector<int> FlexibleColorAssignment::GetColorsInBoundary(const std::string& boundaryName) const {
    auto it = m_boundaryFilters.find(boundaryName);
    return (it != m_boundaryFilters.end()) ? it->second : std::vector<int>();
}

void FlexibleColorAssignment::SetBoundaryFilter(const std::string& boundaryName, 
                                               const std::vector<int>& colorIndices) {
    m_boundaryFilters[boundaryName] = colorIndices;
}

void FlexibleColorAssignment::RegisterColorChangeCallback(ColorChangeCallback callback) {
    if (callback) {
        m_callbacks.push_back(callback);
    }
}

void FlexibleColorAssignment::NotifyColorChange(int colorIndex) {
    for (auto& callback : m_callbacks) {
        if (callback) {
            callback(colorIndex);
        }
    }
}

int FlexibleColorAssignment::GetColorFromRGB(int r, int g, int b) const {
    // Convert RGB to nearest AutoCAD color index
    // This is a simplified mapping - could be enhanced with color distance calculation
    if (r == 255 && g == 0 && b == 0) return 1;     // Red
    if (r == 255 && g == 255 && b == 0) return 2;   // Yellow
    if (r == 0 && g == 255 && b == 0) return 3;     // Green
    if (r == 0 && g == 255 && b == 255) return 4;   // Cyan
    if (r == 0 && g == 0 && b == 255) return 5;     // Blue
    if (r == 255 && g == 0 && b == 255) return 6;   // Magenta
    if (r == 255 && g == 255 && b == 255) return 7; // White
    
    // For other colors, return a computed index
    return ((r & 0xE0) >> 5) | ((g & 0xE0) >> 2) | ((b & 0xC0) << 1);
}

std::string FlexibleColorAssignment::GetMeasurementTypeString(MeasurementType type) const {
    switch (type) {
        case MeasurementType::LF: return "LF";
        case MeasurementType::SF: return "SF";
        case MeasurementType::EA: return "EA";
        case MeasurementType::LF_PITCH: return "LF_PITCH";
        case MeasurementType::SF_PITCH: return "SF_PITCH";
        case MeasurementType::LF_HIP: return "LF_HIP";
        case MeasurementType::CUSTOM: return "CUSTOM";
        default: return "LF";
    }
}

} // namespace EnhancedTakeoff
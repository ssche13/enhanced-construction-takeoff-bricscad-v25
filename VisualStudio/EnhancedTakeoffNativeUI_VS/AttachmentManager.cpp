// AttachmentManager.cpp - Enhanced Implementation for BricsCAD V25
// Enhanced Construction Takeoff - Professional Plan Management
// COPILOT-HINT: BricsCAD-specific implementation with proper transaction handling

#include "pch.h"
#include "AttachmentManager.h"

#include <fstream>
#include <algorithm>

namespace EnhancedTakeoff {

AttachmentManager::AttachmentManager() {
    // Initialize with empty configurations
    m_planConfigurations.clear();
    m_layerStates.clear();
    m_boundaryFilters.clear();
    
    // Initialize standard elevation types
    InitializeElevationTypes();
}

AttachmentManager::~AttachmentManager() {
    // Clean up all configurations
    m_planConfigurations.clear();
    m_layerStates.clear();
    m_boundaryFilters.clear();
    m_callbacks.clear();
}

void AttachmentManager::InitializeElevationTypes() {
    // AGS system: A=Aframe/Hip, G=Garage/No, S=Stucco/Hardi/Brick
    m_elevationTypes = {
        {"AGS", "A-Frame with Garage and Stucco"},
        {"AGB", "A-Frame with Garage and Brick"},
        {"AGH", "A-Frame with Garage and Hardi"},
        {"ANS", "A-Frame without Garage and Stucco"},
        {"ANB", "A-Frame without Garage and Brick"},
        {"ANH", "A-Frame without Garage and Hardi"},
        {"HGS", "Hip Roof with Garage and Stucco"},
        {"HGB", "Hip Roof with Garage and Brick"},
        {"HGH", "Hip Roof with Garage and Hardi"},
        {"HNS", "Hip Roof without Garage and Stucco"},
        {"HNB", "Hip Roof without Garage and Brick"},
        {"HNH", "Hip Roof without Garage and Hardi"}
    };
}

bool AttachmentManager::InitializeDocument() {
#ifdef HAS_BRX_SDK
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (!pDb) return false;
    
    AcDbTransactionManager* pTrans = pDb->transactionManager();
    AcDbTransaction* pTr = pTrans->startTransaction();
    
    if (!pTr) return false;
    
    try {
        // Create standard layers for BricsCAD
        CreateStandardLayers(pDb, pTr);
        
        // Setup layer states
        SetupLayerStates(pDb, pTr);
        
        // Create material boundary layers
        CreateMaterialBoundaryLayers(pDb, pTr);
        
        // Setup default views
        SetupDefaultViews(pDb, pTr);
        
        pTrans->endTransaction();
        
        NotifyChange("Document initialized with BricsCAD V25 structure");
        return true;
    }
    catch (...) {
        pTrans->abortTransaction();
        NotifyChange("Error initializing document structure");
        return false;
    }
#else
    // Placeholder implementation without BRX SDK
    NotifyChange("Document initialization (BRX SDK not available)");
    return true;
#endif
}

#ifdef HAS_BRX_SDK
bool AttachmentManager::CreateStandardLayers(AcDbDatabase* pDb, AcDbTransaction* pTr) {
    AcDbLayerTable* pLayerTable;
    if (pDb->getLayerTable(pLayerTable, AcDb::kForWrite) != Acad::eOk)
        return false;
    
    // Standard construction layers with BricsCAD color scheme
    std::vector<LayerDefinition> standardLayers = {
        {"FOUNDATION", 8, "Foundation elements"},
        {"FOUNDATION_SLAB", 8, "Foundation slab"},
        {"FOUNDATION_FOOTING", 251, "Foundation footings"},
        {"FRAMING", 30, "Framing elements"},
        {"FRAMING_WALL", 30, "Wall framing"},
        {"FRAMING_FLOOR", 32, "Floor framing"},
        {"FRAMING_ROOF", 34, "Roof framing"},
        {"ROOFING", 5, "Roofing materials"},
        {"ROOFING_SHINGLES", 5, "Roof shingles"},
        {"ROOFING_UNDERLAYMENT", 252, "Roof underlayment"},
        {"SIDING", 3, "Siding materials"},
        {"SIDING_HARDI", 3, "Hardi board siding"},
        {"SIDING_STUCCO", 151, "Stucco siding"},
        {"SIDING_BRICK", 1, "Brick siding"},
        {"ELECTRICAL", 1, "Electrical systems"},
        {"ELECTRICAL_ROUGH", 11, "Rough electrical"},
        {"ELECTRICAL_FINISH", 21, "Finish electrical"},
        {"PLUMBING", 4, "Plumbing systems"},
        {"PLUMBING_ROUGH", 14, "Rough plumbing"},
        {"PLUMBING_FINISH", 24, "Finish plumbing"},
        {"HVAC", 6, "HVAC systems"},
        {"HVAC_DUCT", 16, "HVAC ductwork"},
        {"HVAC_EQUIPMENT", 26, "HVAC equipment"},
        {"INSULATION", 52, "Insulation"},
        {"DRYWALL", 254, "Drywall"},
        {"FLOORING", 62, "Flooring"},
        {"CABINETS", 72, "Cabinets"},
        {"BOUNDARY", 2, "Boundary lines"},
        {"ANNOTATION", 7, "Annotations"},
        {"DIMENSION", 141, "Dimensions"}
    };
    
    for (const auto& layerDef : standardLayers) {
        if (!pLayerTable->has(layerDef.name.c_str())) {
            AcDbLayerTableRecord* pLayer = new AcDbLayerTableRecord();
            pLayer->setName(layerDef.name.c_str());
            
            AcCmColor color;
            color.setColorIndex(layerDef.colorIndex);
            pLayer->setColor(color);
            
            AcDbObjectId layerId;
            pLayerTable->add(layerId, pLayer);
            pTr->addNewlyCreatedDBObject(pLayer, true);
        }
    }
    
    pLayerTable->close();
    return true;
}

bool AttachmentManager::CreateMaterialBoundaryLayers(AcDbDatabase* pDb, AcDbTransaction* pTr) {
    AcDbLayerTable* pLayerTable;
    if (pDb->getLayerTable(pLayerTable, AcDb::kForWrite) != Acad::eOk)
        return false;
    
    // Material types with specific colors for boundary detection
    std::vector<MaterialDefinition> materials = {
        {"CONCRETE", 8, 18, 251},     // Gray, Dark Gray, Light Gray
        {"WOOD", 30, 40, 50},         // Orange variants
        {"STEEL", 250, 251, 252},     // Gray variants
        {"DRYWALL", 254, 253, 252},   // Light gray variants
        {"MASONRY", 1, 11, 21},       // Red variants
        {"GLASS", 131, 141, 151},     // Cyan variants
        {"INSULATION", 52, 62, 72}    // Yellow-green variants
    };
    
    for (const auto& material : materials) {
        // Create boundary, fill, and background layers for each material
        CreateLayerIfNotExists(pLayerTable, pTr, "BOUNDARY_" + material.name, material.boundaryColor);
        CreateLayerIfNotExists(pLayerTable, pTr, "FILL_" + material.name, material.fillColor);
        CreateLayerIfNotExists(pLayerTable, pTr, "BACKGROUND_" + material.name, material.backgroundColor);
    }
    
    pLayerTable->close();
    return true;
}

bool AttachmentManager::CreateLayerIfNotExists(AcDbLayerTable* pLayerTable, AcDbTransaction* pTr, 
                                              const std::string& name, int colorIndex) {
    if (!pLayerTable->has(name.c_str())) {
        AcDbLayerTableRecord* pLayer = new AcDbLayerTableRecord();
        pLayer->setName(name.c_str());
        
        AcCmColor color;
        color.setColorIndex(colorIndex);
        pLayer->setColor(color);
        
        AcDbObjectId layerId;
        pLayerTable->add(layerId, pLayer);
        pTr->addNewlyCreatedDBObject(pLayer, true);
        return true;
    }
    return false;
}

bool AttachmentManager::SetupLayerStates(AcDbDatabase* pDb, AcDbTransaction* pTr) {
    // Create predefined layer states for different views
    std::vector<std::string> layerStates = {
        "All_Visible",
        "Foundation_Only", 
        "Framing_Only",
        "Roofing_Only",
        "MEP_Systems",
        "Takeoff_View",
        "Plan_A", "Plan_B", "Plan_C", "Plan_D"
    };
    
    for (const auto& stateName : layerStates) {
        m_layerStates[stateName] = LayerStateManager();
        m_layerStates[stateName].name = stateName;
        m_layerStates[stateName].isActive = false;
    }
    
    return true;
}

bool AttachmentManager::SetupDefaultViews(AcDbDatabase* pDb, AcDbTransaction* pTr) {
    AcDbViewTable* pViewTable;
    if (pDb->getViewTable(pViewTable, AcDb::kForWrite) != Acad::eOk)
        return false;
    
    // Create standard views for construction takeoff
    std::vector<ViewDefinition> views = {
#ifdef HAS_BRX_SDK
        {"Plan_View", 1000.0, AcGePoint2d(500, 500)},
        {"Foundation_View", 1000.0, AcGePoint2d(500, 500)},
        {"Framing_View", 1000.0, AcGePoint2d(500, 500)},
        {"Roof_View", 1000.0, AcGePoint2d(500, 500)},
        {"MEP_View", 1000.0, AcGePoint2d(500, 500)}
#else
        {"Plan_View", 1000.0, 500, 500},
        {"Foundation_View", 1000.0, 500, 500},
        {"Framing_View", 1000.0, 500, 500},
        {"Roof_View", 1000.0, 500, 500},
        {"MEP_View", 1000.0, 500, 500}
#endif
    };
    
    for (const auto& viewDef : views) {
        if (!pViewTable->has(viewDef.name.c_str())) {
            AcDbViewTableRecord* pView = new AcDbViewTableRecord();
            pView->setName(viewDef.name.c_str());
            pView->setHeight(viewDef.height);
#ifdef HAS_BRX_SDK
            pView->setCenterPoint(viewDef.center);
#else
            // Placeholder for when BRX SDK is not available
#endif
            
            AcDbObjectId viewId;
            pViewTable->add(viewId, pView);
            pTr->addNewlyCreatedDBObject(pView, true);
        }
    }
    
    pViewTable->close();
    return true;
}

bool AttachmentManager::AttachPlan(const std::string& planPath, const std::string& planName,
                                  const AcGePoint3d& insertPoint, double scale, double rotation) {
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (!pDb) return false;
    
    AcDbTransactionManager* pTrans = pDb->transactionManager();
    AcDbTransaction* pTr = pTrans->startTransaction();
    
    if (!pTr) return false;
    
    try {
        // Attach XREF using BricsCAD specific method
        AcDbObjectId xrefBlockId;
        if (pDb->attachXref(planPath.c_str(), planName.c_str(), xrefBlockId) == Acad::eOk) {
            
            // Create block reference
            AcDbBlockReference* pBlockRef = new AcDbBlockReference();
            pBlockRef->setBlockTableRecord(xrefBlockId);
            pBlockRef->setPosition(insertPoint);
            pBlockRef->setScaleFactors(AcGeScale3d(scale, scale, scale));
            pBlockRef->setRotation(rotation);
            
            // Add to model space
            AcDbBlockTable* pBlockTable;
            pDb->getBlockTable(pBlockTable, AcDb::kForRead);
            
            AcDbBlockTableRecord* pModelSpace;
            pBlockTable->getAt(ACDB_MODEL_SPACE, pModelSpace, AcDb::kForWrite);
            
            AcDbObjectId blockRefId;
            pModelSpace->appendAcDbEntity(blockRefId, pBlockRef);
            pTr->addNewlyCreatedDBObject(pBlockRef, true);
            
            pModelSpace->close();
            pBlockTable->close();
            
            // Store configuration
            PlanConfiguration config;
            config.name = planName;
            config.path = planPath;
            config.xrefId = xrefBlockId;
            config.insertPoint = insertPoint;
            config.scale = scale;
            config.rotation = rotation;
            config.isLoaded = true;
            config.elevationType = "AGS"; // Default
            
            m_planConfigurations[planName] = config;
            
            pTrans->endTransaction();
            NotifyChange("Plan '" + planName + "' attached successfully");
            return true;
        }
        
        pTrans->abortTransaction();
        return false;
    }
    catch (...) {
        pTrans->abortTransaction();
        NotifyChange("Error attaching plan: " + planName);
        return false;
    }
}

bool AttachmentManager::SetLayerVisibility(AcDbLayerTable* pLayerTable, AcDbTransaction* pTr, 
                                          const std::string& layerName, bool visible) {
    if (pLayerTable->has(layerName.c_str())) {
        AcDbLayerTableRecord* pLayer;
        if (pLayerTable->getAt(layerName.c_str(), pLayer, AcDb::kForWrite) == Acad::eOk) {
            pLayer->setIsOff(!visible);
            pLayer->close();
            return true;
        }
    }
    return false;
}

AcDbObjectId AttachmentManager::CreateBoundaryBox(const std::vector<AcGePoint3d>& points, 
                                                 const std::string& boundaryType, int colorIndex) {
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (!pDb) return AcDbObjectId::kNull;
    
    AcDbTransactionManager* pTrans = pDb->transactionManager();
    AcDbTransaction* pTr = pTrans->startTransaction();
    
    if (!pTr) return AcDbObjectId::kNull;
    
    try {
        // Create polyline boundary
        AcDbPolyline* pPoly = new AcDbPolyline();
        
        for (size_t i = 0; i < points.size(); ++i) {
            AcGePoint2d pt2d(points[i].x, points[i].y);
            pPoly->addVertexAt(i, pt2d, 0, 0, 0);
        }
        pPoly->setClosed(Adesk::kTrue);
        
        // Set properties
        pPoly->setLayer(("BOUNDARY_" + boundaryType).c_str());
        
        AcCmColor color;
        color.setColorIndex(colorIndex);
        pPoly->setColor(color);
        
        // Add to model space
        AcDbBlockTable* pBlockTable;
        pDb->getBlockTable(pBlockTable, AcDb::kForRead);
        
        AcDbBlockTableRecord* pModelSpace;
        pBlockTable->getAt(ACDB_MODEL_SPACE, pModelSpace, AcDb::kForWrite);
        
        AcDbObjectId polyId;
        pModelSpace->appendAcDbEntity(polyId, pPoly);
        pTr->addNewlyCreatedDBObject(pPoly, true);
        
        // Add XData for boundary tracking
        AddBoundaryXData(pPoly, boundaryType, pTr);
        
        pModelSpace->close();
        pBlockTable->close();
        
        pTrans->endTransaction();
        NotifyChange("Boundary box created for '" + boundaryType + "'");
        return polyId;
    }
    catch (...) {
        pTrans->abortTransaction();
        return AcDbObjectId::kNull;
    }
}

void AttachmentManager::AddBoundaryXData(AcDbEntity* pEntity, const std::string& boundaryType, 
                                        AcDbTransaction* pTr) {
    // Register application if not exists
    AcDbRegAppTable* pRegAppTable;
    pEntity->database()->getRegAppTable(pRegAppTable, AcDb::kForWrite);
    
    const char* appName = "ENHANCED_TAKEOFF_BOUNDARY";
    if (!pRegAppTable->has(appName)) {
        AcDbRegAppTableRecord* pRegApp = new AcDbRegAppTableRecord();
        pRegApp->setName(appName);
        
        AcDbObjectId regAppId;
        pRegAppTable->add(regAppId, pRegApp);
        pTr->addNewlyCreatedDBObject(pRegApp, true);
    }
    pRegAppTable->close();
    
    // Create XData
    struct resbuf* pXData = acutBuildList(
        AcDb::kDxfRegAppName, appName,
        AcDb::kDxfXdAsciiString, boundaryType.c_str(),
        AcDb::kDxfXdReal, (double)time(nullptr),
        NULL);
    
    pEntity->setXData(pXData);
    acutRelRb(pXData);
}

#endif // HAS_BRX_SDK

bool AttachmentManager::TogglePlan(const std::string& planName) {
    auto it = m_planConfigurations.find(planName);
    if (it == m_planConfigurations.end()) return false;
    
#ifdef HAS_BRX_SDK
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (!pDb) return false;
    
    AcDbTransactionManager* pTrans = pDb->transactionManager();
    AcDbTransaction* pTr = pTrans->startTransaction();
    
    if (!pTr) return false;
    
    try {
        AcDbBlockTable* pBlockTable;
        pDb->getBlockTable(pBlockTable, AcDb::kForRead);
        
        AcDbBlockTableRecord* pXrefBlock;
        if (pBlockTable->getAt(it->second.xrefId, pXrefBlock, AcDb::kForWrite) == Acad::eOk) {
            
            // Toggle unload state
            bool wasUnloaded = pXrefBlock->isUnloaded();
            pXrefBlock->setIsUnloaded(!wasUnloaded);
            
            // Update configuration
            it->second.isLoaded = wasUnloaded; // Inverted because we toggled
            
            pXrefBlock->close();
            pTrans->endTransaction();
            
            NotifyChange("Plan '" + planName + "' " + (wasUnloaded ? "loaded" : "unloaded"));
            return true;
        }
        
        pBlockTable->close();
        pTrans->abortTransaction();
        return false;
    }
    catch (...) {
        pTrans->abortTransaction();
        NotifyChange("Error toggling plan: " + planName);
        return false;
    }
#else
    // Placeholder implementation without BRX SDK
    it->second.isLoaded = !it->second.isLoaded;
    NotifyChange("Plan '" + planName + "' " + (it->second.isLoaded ? "loaded" : "unloaded") + " (simulated)");
    return true;
#endif
}

bool AttachmentManager::ApplyElevationVariation(const std::string& planName, const std::string& elevationType) {
    auto it = m_planConfigurations.find(planName);
    if (it == m_planConfigurations.end()) return false;
    
    // Validate elevation type
    if (m_elevationTypes.find(elevationType) == m_elevationTypes.end()) {
        NotifyChange("Invalid elevation type: " + elevationType);
        return false;
    }
    
    // Update configuration
    it->second.elevationType = elevationType;
    
    // Apply layer visibility based on elevation
    ApplyElevationLayers(elevationType);
    
    NotifyChange("Applied elevation '" + elevationType + "' to plan '" + planName + "'");
    return true;
}

void AttachmentManager::ApplyElevationLayers(const std::string& elevationType) {
#ifdef HAS_BRX_SDK
    if (elevationType.length() < 3) return;
    
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (!pDb) return;
    
    AcDbTransactionManager* pTrans = pDb->transactionManager();
    AcDbTransaction* pTr = pTrans->startTransaction();
    
    if (!pTr) return;
    
    try {
        AcDbLayerTable* pLayerTable;
        pDb->getLayerTable(pLayerTable, AcDb::kForRead);
        
        // Parse elevation code: AGS = A-frame, Garage, Stucco
        char frameType = elevationType[0];  // A=A-frame, H=Hip
        char garageType = elevationType[1]; // G=Garage, N=No garage
        char sidingType = elevationType[2]; // S=Stucco, H=Hardi, B=Brick
        
        // Apply frame type rules
        if (frameType == 'A') {
            SetLayerVisibility(pLayerTable, pTr, "FRAMING_ROOF_AFRAME", true);
            SetLayerVisibility(pLayerTable, pTr, "FRAMING_ROOF_HIP", false);
        } else if (frameType == 'H') {
            SetLayerVisibility(pLayerTable, pTr, "FRAMING_ROOF_HIP", true);
            SetLayerVisibility(pLayerTable, pTr, "FRAMING_ROOF_AFRAME", false);
        }
        
        // Apply garage rules
        if (garageType == 'G') {
            SetLayerVisibility(pLayerTable, pTr, "FOUNDATION_GARAGE", true);
            SetLayerVisibility(pLayerTable, pTr, "FRAMING_GARAGE", true);
        } else if (garageType == 'N') {
            SetLayerVisibility(pLayerTable, pTr, "FOUNDATION_GARAGE", false);
            SetLayerVisibility(pLayerTable, pTr, "FRAMING_GARAGE", false);
        }
        
        // Apply siding rules
        SetLayerVisibility(pLayerTable, pTr, "SIDING_STUCCO", sidingType == 'S');
        SetLayerVisibility(pLayerTable, pTr, "SIDING_HARDI", sidingType == 'H');
        SetLayerVisibility(pLayerTable, pTr, "SIDING_BRICK", sidingType == 'B');
        
        pLayerTable->close();
        pTrans->endTransaction();
    }
    catch (...) {
        pTrans->abortTransaction();
    }
#else
    // Placeholder implementation without BRX SDK
    NotifyChange("Applied elevation layers for: " + elevationType + " (simulated)");
#endif
}

std::vector<AttachmentManager::PlanConfiguration> AttachmentManager::GetPlanConfigurations() const {
    std::vector<PlanConfiguration> configs;
    configs.reserve(m_planConfigurations.size());
    
    for (const auto& pair : m_planConfigurations) {
        configs.push_back(pair.second);
    }
    
    return configs;
}

std::vector<std::string> AttachmentManager::GetElevationTypes() const {
    std::vector<std::string> types;
    types.reserve(m_elevationTypes.size());
    
    for (const auto& pair : m_elevationTypes) {
        types.push_back(pair.first);
    }
    
    return types;
}

void AttachmentManager::SetBoundaryFilter(const std::string& boundaryName, 
                                         const std::vector<int>& colorIndices) {
    m_boundaryFilters[boundaryName] = colorIndices;
}

std::vector<int> AttachmentManager::GetBoundaryFilter(const std::string& boundaryName) const {
    auto it = m_boundaryFilters.find(boundaryName);
    return (it != m_boundaryFilters.end()) ? it->second : std::vector<int>();
}

void AttachmentManager::RegisterChangeCallback(ChangeCallback callback) {
    if (callback) {
        m_callbacks.push_back(callback);
    }
}

void AttachmentManager::NotifyChange(const std::string& message) {
    for (auto& callback : m_callbacks) {
        if (callback) {
            callback(message);
        }
    }
}

bool AttachmentManager::LoadTemplate(const std::string& templatePath) {
    m_templatePath = templatePath;
    
    // Load template configuration if exists
    std::string configPath = templatePath;
    size_t dotPos = configPath.find_last_of('.');
    if (dotPos != std::string::npos) {
        configPath = configPath.substr(0, dotPos) + ".config";
    }
    
    if (std::ifstream(configPath).good()) {
        return LoadTemplateConfiguration(configPath);
    }
    
    return true; // No configuration file is OK
}

bool AttachmentManager::LoadTemplateConfiguration(const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file.is_open()) return false;
    
    // Simple key=value configuration format
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip comments and empty lines
        
        size_t equalsPos = line.find('=');
        if (equalsPos != std::string::npos) {
            std::string key = line.substr(0, equalsPos);
            std::string value = line.substr(equalsPos + 1);
            
            // Process configuration
            if (key == "default_elevation") {
                // Set default elevation type
            } else if (key.substr(0, 5) == "plan_") {
                // Plan configuration
            }
        }
    }
    
    return true;
}

} // namespace EnhancedTakeoff
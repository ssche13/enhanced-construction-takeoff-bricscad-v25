// AttachmentManager.h - Enhanced Plan Management for BricsCAD V25
#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

#ifdef HAS_BRX_SDK
#include "acdb.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "dbxrecrd.h"
#include "dbapserv.h"
#include "gedll.h"
#include "gepnt3d.h"
#include "gepnt2d.h"
#include "gescl3d.h"
#endif

namespace EnhancedTakeoff {

/**
 * Enhanced Attachment Manager for BricsCAD V25 
 * Manages construction plan attachments with AGS elevation system
 * COPILOT-HINT: Complete BricsCAD-specific implementation with proper transaction handling
 */
class AttachmentManager {
public:
    // Plan configuration structure
    struct PlanConfiguration {
        std::string name;
        std::string path;
        std::string elevationType;      // AGS system code
        bool isLoaded;
        double scale;
        double rotation;
        std::map<std::string, std::string> customProperties;
        
#ifdef HAS_BRX_SDK
        AcDbObjectId xrefId;
        AcGePoint3d insertPoint;
#else
        // Placeholder types when BRX SDK is not available
        int xrefId;
        double insertX, insertY, insertZ;
#endif
        
        PlanConfiguration() : isLoaded(false), scale(1.0), rotation(0.0), xrefId(0) {
#ifndef HAS_BRX_SDK
            insertX = insertY = insertZ = 0.0;
#endif
        }
    };
    
    // Layer definition structure
    struct LayerDefinition {
        std::string name;
        int colorIndex;
        std::string description;
        
        LayerDefinition(const std::string& n, int c, const std::string& d)
            : name(n), colorIndex(c), description(d) {}
    };
    
    // Material definition for boundary layers
    struct MaterialDefinition {
        std::string name;
        int boundaryColor;
        int fillColor; 
        int backgroundColor;
        
        MaterialDefinition(const std::string& n, int b, int f, int bg)
            : name(n), boundaryColor(b), fillColor(f), backgroundColor(bg) {}
    };
    
    // View definition structure
    struct ViewDefinition {
        std::string name;
        double height;
#ifdef HAS_BRX_SDK
        AcGePoint2d center;
        
        ViewDefinition(const std::string& n, double h, const AcGePoint2d& c)
            : name(n), height(h), center(c) {}
#else
        double centerX, centerY;
        
        ViewDefinition(const std::string& n, double h, double cx, double cy)
            : name(n), height(h), centerX(cx), centerY(cy) {}
#endif
    };
    
    // Layer state manager
    struct LayerStateManager {
        std::string name;
        bool isActive;
        std::vector<std::string> visibleLayers;
        std::vector<std::string> hiddenLayers;
        
        LayerStateManager() : isActive(false) {}
    };
    
    // Callback type for change notifications
    using ChangeCallback = std::function<void(const std::string&)>;

    AttachmentManager();
    ~AttachmentManager();
    
    // Document initialization
    bool InitializeDocument();
    
    // Plan attachment management
#ifdef HAS_BRX_SDK
    bool AttachPlan(const std::string& planPath, const std::string& planName,
                   const AcGePoint3d& insertPoint = AcGePoint3d::kOrigin,
                   double scale = 1.0, double rotation = 0.0);
#else
    bool AttachPlan(const std::string& planPath, const std::string& planName,
                   double insertX = 0.0, double insertY = 0.0, double insertZ = 0.0,
                   double scale = 1.0, double rotation = 0.0);
#endif
    bool DetachPlan(const std::string& planName);
    bool TogglePlan(const std::string& planName);
    
    // Elevation system (AGS: A-frame/Hip, Garage/No, Stucco/Hardi/Brick)
    bool ApplyElevationVariation(const std::string& planName, const std::string& elevationType);
    std::vector<std::string> GetElevationTypes() const;
    std::string GetElevationDescription(const std::string& elevationType) const;
    
    // Boundary management
#ifdef HAS_BRX_SDK
    AcDbObjectId CreateBoundaryBox(const std::vector<AcGePoint3d>& points, 
                                  const std::string& boundaryType, int colorIndex);
#else
    int CreateBoundaryBox(const std::vector<std::vector<double>>& points, 
                         const std::string& boundaryType, int colorIndex);
#endif
    void SetBoundaryFilter(const std::string& boundaryName, const std::vector<int>& colorIndices);
    std::vector<int> GetBoundaryFilter(const std::string& boundaryName) const;
    
    // Layer management
    bool ApplyLayerState(const std::string& stateName);
    std::vector<std::string> GetLayerStates() const;
    
    // Query methods
    std::vector<PlanConfiguration> GetPlanConfigurations() const;
    PlanConfiguration* GetPlanConfiguration(const std::string& planName);
    bool IsPlanLoaded(const std::string& planName) const;
    
    // Template management
    bool LoadTemplate(const std::string& templatePath);
    bool SaveTemplate(const std::string& templatePath) const;
    
    // Event handling
    void RegisterChangeCallback(ChangeCallback callback);
    
private:
    // Core data
    std::map<std::string, PlanConfiguration> m_planConfigurations;
    std::map<std::string, LayerStateManager> m_layerStates;
    std::map<std::string, std::vector<int>> m_boundaryFilters;
    std::map<std::string, std::string> m_elevationTypes;
    std::vector<ChangeCallback> m_callbacks;
    std::string m_templatePath;
    
    // Layer and document setup (BRX SDK only)
#ifdef HAS_BRX_SDK
    bool CreateStandardLayers(AcDbDatabase* pDb, AcDbTransaction* pTr);
    bool CreateMaterialBoundaryLayers(AcDbDatabase* pDb, AcDbTransaction* pTr);
    bool CreateLayerIfNotExists(AcDbLayerTable* pLayerTable, AcDbTransaction* pTr,
                               const std::string& name, int colorIndex);
    bool SetupLayerStates(AcDbDatabase* pDb, AcDbTransaction* pTr);
    bool SetupDefaultViews(AcDbDatabase* pDb, AcDbTransaction* pTr);
    bool SetLayerVisibility(AcDbLayerTable* pLayerTable, AcDbTransaction* pTr,
                           const std::string& layerName, bool visible);
    void AddBoundaryXData(AcDbEntity* pEntity, const std::string& boundaryType, 
                         AcDbTransaction* pTr);
#endif
    
    // Elevation management
    void InitializeElevationTypes();
    void ApplyElevationLayers(const std::string& elevationType);
    
    // Configuration management
    bool LoadTemplateConfiguration(const std::string& configPath);
    bool SaveTemplateConfiguration(const std::string& configPath) const;
    
    // Utilities
    void NotifyChange(const std::string& message);
};

} // namespace EnhancedTakeoff
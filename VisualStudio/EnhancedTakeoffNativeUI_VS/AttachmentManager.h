// AttachmentManager.h - Manages Plan A/B/C/D attachments with version control
#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

#ifndef BUILDING_TESTS
#if HAS_BRX_SDK
#include "acdb.h"
#include "dbents.h"
#include "dbxrefgraph.h"
#endif
#endif

namespace EnhancedTakeoff {

/**
 * Manages construction plan attachments (Plan A/B/C/D) with version control
 * COPILOT-HINT: This replaces fixed attachment systems with flexible management
 */
class AttachmentManager {
public:
    // Version structure for AGS system (A=stucco, G=hardi, S=brick)
    struct PlanVersion {
        std::string versionCode;        // "AGS", "AHS", etc.
        std::string description;        // "Stucco/Hardi/Brick"
        std::map<char, std::string> components;  // 'A'->Stucco, 'G'->Hardi, 'S'->Brick
        std::vector<int> activeColors;  // Colors active in this version
        bool isActive;
        
        PlanVersion() : isActive(false) {}
    };
    
    // Attachment structure for plans
    struct Attachment {
        std::string planName;           // "Plan A", "Plan B", etc.
        std::string filePath;           // DWG file path
        std::vector<PlanVersion> versions;  // Available versions
        std::string activeVersion;      // Currently active version code
        bool isLoaded;
        bool isVisible;
        std::string areaPreset;        // "Southeast", "Northeast", etc.
        
#ifndef BUILDING_TESTS
#if HAS_BRX_SDK
        AcDbObjectId xrefId;           // BricsCAD XRef ID
#endif
#endif
        
        Attachment() : isLoaded(false), isVisible(false) {}
    };

    AttachmentManager();
    ~AttachmentManager();
    
    // Attachment management
    bool LoadAttachment(const std::string& planName, const std::string& dwgPath);
    bool UnloadAttachment(const std::string& planName);
    bool ToggleAttachment(const std::string& planName, bool visible);
    
    // Version management
    bool AddVersion(const std::string& planName, const PlanVersion& version);
    bool SetActiveVersion(const std::string& planName, const std::string& versionCode);
    PlanVersion* GetActiveVersion(const std::string& planName);
    std::vector<std::string> GetVersionCodes(const std::string& planName);
    
    // Area preset management
    void SetAreaPreset(const std::string& planName, const std::string& preset);
    std::string GetAreaPreset(const std::string& planName) const;
    std::map<std::string, double> GetAreaFactors(const std::string& preset) const;
    
    // Query methods
    std::vector<std::string> GetLoadedPlans() const;
    Attachment* GetAttachment(const std::string& planName);
    bool IsAttachmentVisible(const std::string& planName) const;
    
    // Color management for versions
    std::vector<int> GetActiveColors(const std::string& planName) const;
    void ToggleColorInVersion(const std::string& planName, 
                             const std::string& versionCode, 
                             int colorIndex, 
                             bool active);
    
    // BricsCAD integration
#ifndef BUILDING_TESTS
#if HAS_BRX_SDK
    bool RefreshFromDrawing();
    void OnXrefAttached(const AcDbObjectId& xrefId);
    void OnXrefDetached(const AcDbObjectId& xrefId);
#endif
#endif
    
    // Serialization
    bool SaveConfiguration(const std::string& filePath) const;
    bool LoadConfiguration(const std::string& filePath);
    
private:
    std::map<std::string, Attachment> m_attachments;
    std::map<std::string, std::map<std::string, double>> m_areaFactors;
    
    void InitializeAreaFactors();
    bool ValidatePlanName(const std::string& planName) const;
};

} // namespace EnhancedTakeoff
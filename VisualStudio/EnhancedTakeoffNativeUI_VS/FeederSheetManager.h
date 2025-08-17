// FeederSheetManager.h - Direct Excel cell mapping for feeder sheets
#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace EnhancedTakeoff {

/**
 * Manages Excel feeder sheet integration with direct cell mapping
 * COPILOT-HINT: Preserves formulas and enables live updates to Excel
 */
class FeederSheetManager {
public:
    struct CellMapping {
        int colorIndex;
        std::string materialName;
        std::string worksheet;         // "Feeder", "Plan_B", etc.
        std::string cellReference;     // "B15", "C22:C25", etc.
        std::string formula;           // Optional formula to preserve
        std::string measurementType;   // "LF", "SF", "EA", etc.
        double lastValue;
        bool preserveFormula;
        
        CellMapping() : colorIndex(0), lastValue(0.0), preserveFormula(true) {}
    };
    
    struct WorkbookConnection {
        std::string filePath;
        bool isConnected;
        bool autoRefresh;
        int refreshIntervalMs;
        std::string lastError;
        
        WorkbookConnection() : isConnected(false), autoRefresh(false), 
                              refreshIntervalMs(500) {}
    };
    
    FeederSheetManager();
    ~FeederSheetManager();
    
    // Excel connection management
    bool ConnectToWorkbook(const std::string& excelPath);
    bool DisconnectWorkbook();
    bool IsConnected() const;
    std::string GetWorkbookPath() const;
    
    // Cell mapping operations
    bool MapColorToCell(int colorIndex, const std::string& cellRef, 
                       const std::string& worksheet = "Feeder");
    bool UnmapColor(int colorIndex);
    bool UpdateCellValue(int colorIndex, double value);
    bool UpdateMultipleCells(const std::map<int, double>& colorValues);
    
    // Formula management
    bool SetCellFormula(const std::string& cellRef, const std::string& formula);
    std::string GetCellFormula(const std::string& cellRef) const;
    bool PreserveFormulas(bool preserve);
    
    // Worksheet operations
    bool CreateFeederSheet(const std::string& sheetName);
    bool SelectWorksheet(const std::string& sheetName);
    std::vector<std::string> GetWorksheetNames() const;
    bool CreatePlanSheet(const std::string& planName);
    
    // Batch operations
    bool ExportAllMappings();
    bool RefreshAllCells();
    bool ClearFeederSheet();
    
    // Named range support
    bool CreateNamedRange(const std::string& name, const std::string& cellRef);
    bool MapColorToNamedRange(int colorIndex, const std::string& rangeName);
    std::vector<std::string> GetNamedRanges() const;
    
    // Template operations
    bool LoadTemplate(const std::string& templatePath);
    bool SaveAsTemplate(const std::string& templatePath) const;
    
    // Auto-refresh configuration
    void SetAutoRefresh(bool enable, int intervalMs = 500);
    bool IsAutoRefreshEnabled() const;
    void ManualRefresh();
    
    // Query methods
    CellMapping* GetMapping(int colorIndex);
    std::vector<CellMapping> GetAllMappings() const;
    std::map<std::string, std::vector<int>> GetMappingsByWorksheet() const;
    
    // Error handling
    std::string GetLastError() const;
    bool HasErrors() const;
    
    // Event notifications
    using UpdateCallback = std::function<void(const std::string& cell, double value)>;
    void RegisterUpdateCallback(UpdateCallback callback);
    
private:
    std::unique_ptr<class ExcelAutomation> m_excel;
    WorkbookConnection m_connection;
    std::map<int, CellMapping> m_mappings;
    std::vector<UpdateCallback> m_callbacks;
    std::string m_lastError;
    bool m_preserveFormulas;
    
    void NotifyCellUpdate(const std::string& cell, double value);
    bool ValidateCellReference(const std::string& cellRef) const;
    std::string ExpandCellRange(const std::string& cellRef) const;
};

} // namespace EnhancedTakeoff
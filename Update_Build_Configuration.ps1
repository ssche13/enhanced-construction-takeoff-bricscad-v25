# Update_Build_Configuration.ps1
# Update Visual Studio project with flexible system build configuration

Write-Host "?? Updating Build Configuration for Enhanced Construction Takeoff" -ForegroundColor Cyan
Write-Host "=" * 70 -ForegroundColor DarkGray

$projectFile = "VisualStudio\EnhancedTakeoffNativeUI_VS\EnhancedTakeoffNativeUI_VS.vcxproj"

if (Test-Path $projectFile) {
    Write-Host "?? Found project file: $projectFile" -ForegroundColor Green
    
    # Read the project file
    [xml]$project = Get-Content $projectFile
    
    # Find or create PropertyGroup for preprocessor definitions
    $propertyGroups = $project.Project.PropertyGroup
    
    foreach ($group in $propertyGroups) {
        if ($group.Condition -like "*Release*" -or $group.Condition -like "*Debug*") {
            Write-Host "?? Updating PropertyGroup: $($group.Condition)" -ForegroundColor Yellow
            
            # Update preprocessor definitions
            if ($group.PreprocessorDefinitions) {
                $existingDefs = $group.PreprocessorDefinitions
                $newDefs = $existingDefs + ";HAS_BRX_SDK=1;BUILDING_ENHANCED_TAKEOFF=1;FLEXIBLE_COLOR_SYSTEM=1;NO_FIXED_COLORS=1;_AFXEXT;_BRXTARGET"
                $group.PreprocessorDefinitions = $newDefs
            } else {
                # Create new preprocessor definitions
                $defElement = $project.CreateElement("PreprocessorDefinitions")
                $defElement.InnerText = "WIN32;_WINDOWS;_USRDLL;HAS_BRX_SDK=1;BUILDING_ENHANCED_TAKEOFF=1;FLEXIBLE_COLOR_SYSTEM=1;NO_FIXED_COLORS=1;_AFXEXT;_BRXTARGET;%(PreprocessorDefinitions)"
                $group.AppendChild($defElement) | Out-Null
            }
            
            # Update additional include directories
            if ($group.AdditionalIncludeDirectories) {
                $existingInc = $group.AdditionalIncludeDirectories
                $newInc = "`$(BRX_SDK_PATH)\inc;`$(BRX_SDK_PATH)\inc-x64;`$(ProjectDir);" + $existingInc
                $group.AdditionalIncludeDirectories = $newInc
            } else {
                # Create new include directories
                $incElement = $project.CreateElement("AdditionalIncludeDirectories")
                $incElement.InnerText = "`$(BRX_SDK_PATH)\inc;`$(BRX_SDK_PATH)\inc-x64;`$(ProjectDir);%(AdditionalIncludeDirectories)"
                $group.AppendChild($incElement) | Out-Null
            }
        }
    }
    
    # Save the updated project file
    $project.Save($projectFile)
    Write-Host "? Project file updated successfully!" -ForegroundColor Green
    
} else {
    Write-Host "? Project file not found: $projectFile" -ForegroundColor Red
    Write-Host "Creating sample project configuration..." -ForegroundColor Yellow
    
    # Create sample vcxproj content
    $sampleProject = @"
<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|x64">
      <Configuration>Debug</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|x64">
      <Configuration>Release</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  
  <PropertyGroup Label="Globals">
    <VCProjectVersion>16.0</VCProjectVersion>
    <ProjectGuid>{12345678-1234-5678-9ABC-123456789012}</ProjectGuid>
    <RootNamespace>EnhancedTakeoffNativeUI_VS</RootNamespace>
    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
  </PropertyGroup>
  
  <Import Project="`$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
    <UseOfMfc>Dynamic</UseOfMfc>
  </PropertyGroup>
  
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
    <UseOfMfc>Dynamic</UseOfMfc>
  </PropertyGroup>
  
  <Import Project="`$(VCTargetsPath)\Microsoft.Cpp.props" />
  
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Debug|x64'">
    <PreprocessorDefinitions>WIN32;_WINDOWS;_DEBUG;_USRDLL;HAS_BRX_SDK=1;BUILDING_ENHANCED_TAKEOFF=1;FLEXIBLE_COLOR_SYSTEM=1;NO_FIXED_COLORS=1;_AFXEXT;_BRXTARGET;%(PreprocessorDefinitions)</PreprocessorDefinitions>
    <AdditionalIncludeDirectories>`$(BRX_SDK_PATH)\inc;`$(BRX_SDK_PATH)\inc-x64;`$(ProjectDir);%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    <TargetExt>.brx</TargetExt>
  </PropertyGroup>
  
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Release|x64'">
    <PreprocessorDefinitions>WIN32;_WINDOWS;NDEBUG;_USRDLL;HAS_BRX_SDK=1;BUILDING_ENHANCED_TAKEOFF=1;FLEXIBLE_COLOR_SYSTEM=1;NO_FIXED_COLORS=1;_AFXEXT;_BRXTARGET;%(PreprocessorDefinitions)</PreprocessorDefinitions>
    <AdditionalIncludeDirectories>`$(BRX_SDK_PATH)\inc;`$(BRX_SDK_PATH)\inc-x64;`$(ProjectDir);%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    <TargetExt>.brx</TargetExt>
  </PropertyGroup>
  
  <ItemGroup>
    <ClInclude Include="EnhancedTakeoffBricsCADMainDialog.h" />
    <ClInclude Include="BricsCADV25SupportClasses.h" />
    <ClInclude Include="FlexibleColorAssignment.h" />
    <ClInclude Include="AttachmentManager.h" />
    <ClInclude Include="BoundaryVersionManager.h" />
    <ClInclude Include="FeederSheetManager.h" />
    <ClInclude Include="FlexibilityAdapter.h" />
    <ClInclude Include="BricsCADTakeoffDialog.h" />
  </ItemGroup>
  
  <ItemGroup>
    <ClCompile Include="EnhancedTakeoffBricsCADMainDialog.cpp" />
    <ClCompile Include="BricsCADV25SupportClasses.cpp" />
    <ClCompile Include="FlexibleColorAssignment.cpp" />
    <ClCompile Include="FlexibilityAdapter.cpp" />
  </ItemGroup>
  
  <ItemGroup>
    <None Include="EnhancedTakeoffNativeUI_VS.def" />
  </ItemGroup>
  
  <ItemGroup>
    <ResourceCompile Include="EnhancedTakeoffBricsCAD.rc" />
  </ItemGroup>
  
  <Import Project="`$(VCTargetsPath)\Microsoft.Cpp.targets" />
</Project>
"@

    $sampleProject | Out-File -FilePath $projectFile -Encoding UTF8
    Write-Host "? Sample project file created!" -ForegroundColor Green
}

Write-Host "`n?? Build Configuration Summary:" -ForegroundColor Cyan
Write-Host "=" * 50 -ForegroundColor DarkGray

Write-Host "`n?? Preprocessor Definitions Added:" -ForegroundColor Yellow
Write-Host "  ? HAS_BRX_SDK=1" -ForegroundColor Green
Write-Host "  ? BUILDING_ENHANCED_TAKEOFF=1" -ForegroundColor Green  
Write-Host "  ? FLEXIBLE_COLOR_SYSTEM=1" -ForegroundColor Green
Write-Host "  ? NO_FIXED_COLORS=1" -ForegroundColor Green
Write-Host "  ? _AFXEXT" -ForegroundColor Green
Write-Host "  ? _BRXTARGET" -ForegroundColor Green

Write-Host "`n?? Additional Include Directories Added:" -ForegroundColor Yellow
Write-Host "  ? `$(BRX_SDK_PATH)\inc" -ForegroundColor Green
Write-Host "  ? `$(BRX_SDK_PATH)\inc-x64" -ForegroundColor Green
Write-Host "  ? `$(ProjectDir)" -ForegroundColor Green

Write-Host "`n?? Target Configuration:" -ForegroundColor Yellow
Write-Host "  ? Platform: x64 only" -ForegroundColor Green
Write-Host "  ? Target Extension: .brx" -ForegroundColor Green
Write-Host "  ? Framework: MFC Dynamic" -ForegroundColor Green
Write-Host "  ? Character Set: Unicode" -ForegroundColor Green

Write-Host "`n?? Next Steps:" -ForegroundColor Cyan
Write-Host "  1. Open Visual Studio 2022" -ForegroundColor White
Write-Host "  2. Load the updated project file" -ForegroundColor White
Write-Host "  3. Set BRX_SDK_PATH environment variable" -ForegroundColor White
Write-Host "  4. Build in Release|x64 configuration" -ForegroundColor White
Write-Host "  5. Test .brx plugin in BricsCAD V25" -ForegroundColor White

Write-Host "`n? Enhanced Construction Takeoff - Flexible Build Configuration Ready!" -ForegroundColor Green
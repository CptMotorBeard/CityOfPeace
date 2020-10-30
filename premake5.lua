workspace "CityOfPeace"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"OptDebug",
		"Distribution"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
project "City"
	location "City"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
		
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines "CT_WIN"
		
	filter "configurations:Debug"
		defines "CT_DEBUG"
		symbols "On"
		
	filter "configurations:OptDebug"
		defines "CT_OPTDEBUG"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "CT_DIST"
		optimize "On"
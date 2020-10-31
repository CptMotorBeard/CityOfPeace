function defaultConfigurations()
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CT_DEBUG"
		symbols "On"
		
	filter "configurations:OptDebug"
		defines "CT_OPTDEBUG"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "CT_DIST"
		optimize "On"
end

function copyOutputToMain()
	postbuildcommands { ("{MKDIR} ../../../bin/" .. outputdir .. "/City"), ("{COPY} %{cfg.buildtarget.relpath} ../../../bin/" .. outputdir .. "/City")}
end

function basicVendorProject(prjName)
	project(prjName)
		location "City/vendor/projects"		
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
end

function sfmlProject(libname)
	basicVendorProject ("sfml-" .. libname)
		kind "SharedLib"
		configuration "windows"
			defines { "WIN32", "_WIN32" }
			libdirs { sfmlPath .. "/extlibs/libs-msvc-universal/x64" }
			
		configuration {}
end

workspace "CityOfPeace"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"OptDebug",
		"Distribution"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
vendorPath = "City/vendor"

sfmlPath = (vendorPath .. "/sfml")

sfmlProject "graphics"
	files { sfmlPath .. "/src/SFML/Graphics/*.cpp" }	
	defines { "GLEW_STATIC", "STBI_FAILURE_USERMSG", "SFML_GRAPHICS_EXPORTS" }
	links { "sfml-system", "sfml-window", "freetype", "opengl32" }
	
	includedirs
	{
		sfmlPath .. "/include",
		sfmlPath .. "/src",
		sfmlPath .. "/extlibs/headers",
		sfmlPath .. "/extlibs/headers/glad/include",
		sfmlPath .. "/extlibs/headers/stb_image",
		sfmlPath .. "/extlibs/headers/freetype2",
		sfmlPath .. "/extlibs/headers/libfreetype/windows"
	}
	copyOutputToMain()
	
sfmlProject "system"
        files { sfmlPath .. "/src/SFML/System/*.cpp", sfmlPath .. "/src/SFML/System/Win32/*.cpp"}
        includedirs { sfmlPath .. "/include", sfmlPath ..  "/src" }
		defines { "SFML_SYSTEM_EXPORTS" }

		links
		{
			"winmm",
			"kernel32",
			"user32",
			"gdi32",
			"winspool",
			"shell32",
			"ole32",
			"oleaut32",
			"uuid",
			"comdlg32",
			"advapi32"
		}
		copyOutputToMain()

sfmlProject "window"
        files { sfmlPath .. "/src/SFML/Window/*.cpp", sfmlPath .. "/src/SFML/Window/Win32/*.cpp" }
		defines { "SFML_WINDOW_EXPORTS" }
		links { "sfml-system", "opengl32", "winmm", "gdi32" }
		includedirs
		{
			sfmlPath .. "/include",
			sfmlPath .. "/src",
			sfmlPath .. "/extlibs/headers/glad/include",
			sfmlPath .. "/extlibs/headers/vulkan"
		}
		copyOutputToMain()

basicVendorProject "sfml-main"
	kind "StaticLib"
	files { sfmlPath .. "/src/SFML/Main/MainWin32.cpp" }
	includedirs { sfmlPath .. "/include", sfmlPath .. "/src" }
	copyOutputToMain()

basicVendorProject "imgui"
	kind "StaticLib"
	files
	{
		vendorPath .. "/%{prj.name}/*.h",
		vendorPath .. "/%{prj.name}/*.cpp"
	}

	copyOutputToMain()
	defaultConfigurations()	
	
basicVendorProject "imgui-sfml"	
	kind "StaticLib"
	files
	{
		vendorPath .. "/%{prj.name}/*.h",
		vendorPath .. "/%{prj.name}/*.cpp"
	}

	includedirs { vendorPath .. "/imgui", vendorPath .. "/sfml/include" }	
	links { "sfml-main", "imgui", "opengl32" }
	copyOutputToMain()
	defaultConfigurations()

basicVendorProject "yaml"
	kind "StaticLib"
	files
	{
		vendorPath .. "/%{prj.name}/src/*.h",
		vendorPath .. "/%{prj.name}/src/*.cpp"
	}
	
	includedirs { vendorPath .. "/%{prj.name}/include" }
	copyOutputToMain()
	defaultConfigurations()
	
basicVendorProject "sqlite3"
	kind "StaticLib"
	files
	{
		vendorPath .. "/%{prj.name}/*.h",
		vendorPath .. "/%{prj.name}/*.c"
	}
	
	copyOutputToMain()
	defaultConfigurations()
	
project "City"
	location "City/project"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		vendorPath .. "/imgui",
		vendorPath .. "/imgui-sfml",
		vendorPath .. "/sfml/include",
		vendorPath .. "/yaml/include",
		vendorPath .. "/sqlite3"
	}
	
	links
	{
		"imgui",
		"imgui-sfml",		
		"yaml",
		"sqlite3",
		"sfml-main",
		"sfml-window",
		"sfml-system",
		"sfml-graphics"
	}
		
	defaultConfigurations()
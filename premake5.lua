workspace "Air-Engine"
	architecture  "x32"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-${cfg.architecture}"

project "Air-Engine"
	location "Air-Engine"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Dependencies/glew/include"
	}

	links {
		"opengl32",
		"Dependencies/glew/lib/Debug/Win32/glew32sd.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"GLEW_STATIC",
			"AIR_PLATFORM_WINDOWS",
			"AIR_TEST",
			"WIN32",
			"_DEBUG",
			"_WINDOWS"
		}

	filter "configurations:Debug"
		symbols "On"	

		defines {
			"AIR_DEBUG",
			"ASSERTIONS_ENABLED"
		}

	filter "configurations:Release"
		optimize "On"

		defines {
			"AIR_RELEASE"
		}

	filter "configurations:Distribution"
		optimize "On"

		defines {
			"AIR_DISTRIBUTION"
		}

project "Sandbox"
	location "Sandbox"
	kind "WindowedApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	links {
		"Air-Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"GLEW_STATIC",
			"AIR_PLATFORM_WINDOWS",
			"WIN32",
			"_DEBUG",
			"_CONSOLE"
		}

		includedirs {
			"Air-Engine/src/"
		}

	filter "configurations:Debug"
		defines {
			"ASSERTIONS_ENABLED"
		}
project "Air-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}/int")

	files {
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp"
	}

	defines {
		"GLEW_STATIC"
	}

	includedirs {
		"Dependencies/glad/include",
		"src"
	}

	links {
		"opengl32",
		"glad"
	}

	pchheader "airpch.h"
	pchsource "src/airpch.cpp"

	filter "configurations:Debug"
		optimize "Debug"
		symbols "Full"

		defines {
			"_DEBUG",
			"AIR_BUILD_DEBUG",
			"AIR_ASSERTIONS_ENABLED",
			"AIR_ENABLE_LOGGING"
		}
	filter "configurations:Release"
		optimize "On"
		
		defines {
			"AIR_BUILD_RELEASE",
			"AIR_ENABLE_LOGGING"
		}

	filter "configurations:Distribution"
		optimize "Full"
		symbols "Off"
		
		defines {
			"AIR_BUILD_DISTR"
		}

	filter "system:windows"
		defines {
			"AIR_PLATFORM_WINDOWS"
		}
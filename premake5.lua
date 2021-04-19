workspace "Air-Engine"
	architecture  "x86_64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

	filter "configurations:Debug"
		symbols "Full"

		defines {
			"AIR_DEBUG",
			"_DEBUG"
		}

	filter "configurations:Release"
		optimize "On"

		defines {
			"AIR_RELEASE"
		}

	filter "configurations:Distribution"
		symbols "Full"
		optimize "Full"

		defines {
			"AIR_DISTRIBUTION"
		}

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

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
			"AIR_PLATFORM_WINDOWS"
		}

		includedirs {
			"Air-Engine/src/"
		}

filter {}
include "Air-Engine"
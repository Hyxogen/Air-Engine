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
		symbols "Off"
		optimize "Full"

		defines {
			"AIR_DISTR"
		}

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/"

filter {}
include "Sandbox"
include "Air-Engine"
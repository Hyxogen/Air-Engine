project "Sandbox"
    language "C++"
    kind "WindowedApp"
	cppdialect "C++17"
	staticruntime "On"
    systemversion "latest"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}/int")

    files {
		"**.h",
		"**.hpp",
		"**.cpp"
	}

    includedirs {
        "%{wks.location}/Air-Engine/src/"
    }

    links {
        "Air-Engine"
    }

	filter "platforms:Win64"
		defines {
			"AIR_PLATFORM_WINDOWS"
		}

	filter "platforms:OSX"
		defines {
			"AIR_PLATFORM_OSX"
		}

	filter "platforms:Linux"
		defines {
			"AIR_PLATFORM_LINUX"
		}

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
			"AIR_BUILD_DISTR",
			"AIR_ENABLE_LOGGING"
		}
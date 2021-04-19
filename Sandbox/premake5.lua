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

    defines {
        "GLEW_STATIC"
    }

    includedirs {
        "%{wks.location}/Air-Engine/src/"
    }

    links {
        "Air-Engine"
    }

	filter "configurations:Debug"
		optimize "Off"
		symbols "Full"

		defines {
			"_DEBUG",
			"AIR_BUILD_DEBUG"
		}

	filter "configurations:Release"
		optimize "On"
		
		defines {
			"AIR_BUILD_RELEASE"
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
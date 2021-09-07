project "Air-Engine Tests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
    staticruntime "On"
    
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
		"src/",
        "%{wks.location}/Air-Engine/src/",
        "Dependencies/googletest/googlemock/include",
        "Dependencies/googletest/googletest/include"
    }

    links {
        "Air-Engine"
    }

    pchheader "pch.h"
    pchsource "src/pch.cpp"

	filter "configurations:Debug"
		optimize "Debug"
		symbols "Full"

		defines {
			"_DEBUG",
			"AIR_BUILD_DEBUG",
            "AIR_ASSERTIONS_ENABLED",
			"AIR_ENABLE_LOGGING"
		}

		links {
            "Dependencies/googletest/lib/Debug/gtestd.lib"
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
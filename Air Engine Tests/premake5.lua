project "Air Engine Tests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
    staticruntime "On"
	systemversion "latest"
    
	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}/int")

    pchheader "pch.h"
    pchsource "src/pch.cpp"

    files {
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp"
	}

    includedirs {
        "%{wks.location}/Air-Engine/src/",
        "%{wks.location}/Vendor/googletest/googletest/include",
		"%{wks.location}/Vendor/googletest/googletest/"
    }

    links {
        "Air-Engine",
        "%{wks.location}/Vendor/googletest/lib/Debug/gtestd.lib"
    }

	includedirs {
		"%{wks.location}/Vendor/googletest/googletest/include"
	}

    filter "configurations:Debug"
    optimize "Off"
    symbols "Full"

    defines {
        "_DEBUG",
        "AIR_BUILD_DEBUG",
        "AIR_ASSERTIONS_ENABLED"
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
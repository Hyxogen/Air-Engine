project "Air-Engine Tests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
        "%{wks.location}/Air-Engine/src/",
        "%Dependencies/googletest/googlemock/include",
        "%Dependencies/googletest/googletest/include"
    }

    links {
        "Air-Engine"
    }

    pchheader "src/pch.h"
    pchsource "src/pch.cpp"

    nuget { "references" }
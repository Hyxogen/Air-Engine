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

    filter "system:windows"
        defines {
            "AIR_PLATFORM_WINDOWS"
        }
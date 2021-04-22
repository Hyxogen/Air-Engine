project "Air Engine Tests"
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
        "%{wks.location}/Vendor/googletest/googletest/include",
		"%{wks.location}/Vendor/googletest/googletest"
    }

    links {
        "Air-Engine",
        "GoogleTest"
    }
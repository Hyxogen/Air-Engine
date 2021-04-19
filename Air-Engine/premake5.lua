project "Air-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

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
		"Dependencies/glew-2.1.0/include"
	}

	links {
		"opengl32"
	}

	filter "configurations:Debug"
		libdirs {
			"Dependencies/glew-2.1.0/lib/Debug"
		}

		links {
			"glew32d.lib"
		}

	filter "configurations:Release"
		libdirs {
			"Dependencies/glew-2.1.0/lib/RelWithDebInfo"
		}

		links {
			"glew32.lib"
		}
	filter "configurations:Distribution"
		libdirs {
			"Dependencies/glew-2.1.0/lib/Release"
		}

		links {
			"glew32.lib"
		}

	filter "system:windows"
		defines {
			"AIR_PLATFORM_WINDOWS"
		}
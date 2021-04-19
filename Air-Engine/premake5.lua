project "Air-Engine"
	kind "StaticLib"
	language "C++"
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
		"Dependencies/glew-2.1.0/include"
	}

	links {
		"opengl32"
	}

	filter "configurations:Debug"
		optimize "Off"
		symbols "Full"

		defines {
			"_DEBUG",
			"AIR_BUILD_DEBUG"
		}

		libdirs {
			"Dependencies/glew-2.1.0/lib/Debug"
		}

		links {
			"glew32d.lib"
		}

	filter "configurations:Release"
		optimize "On"
		
		defines {
			"AIR_BUILD_RELEASE"
		}

		libdirs {
			"Dependencies/glew-2.1.0/lib/RelWithDebInfo"
		}

		links {
			"glew32.lib"
		}
	filter "configurations:Distribution"
		optimize "Full"
		symbols "Off"
		
		defines {
			"AIR_BUILD_DISTR"
		}

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
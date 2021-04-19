project "Air-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("%{wks.location}/" .. outputdir .. "/bin/%{prj.name}}")
	objdir ("%{wks.location}/" .. outputdir .. "/int/%{prj.name}}")

	files {
		"**.h",
		"**.hpp",
		"**.cpp"
	}

	defines {
		"GLEW_STATIC"
	}

	includedirs {
		"%{wks.location}/Dependencies/glew-2.1.0/include"
	}

	links {
		"opengl32"
	}

	filter "configurations:Debug"
		libdirs {
			"%{wks.location}/Dependencies/glew-2.1.0/lib/Debug"
		}

		links {
			"glew32d.lib"
		}

	filter "configurations:Release"
		libdirs {
			"%{wks.location}/Dependencies/glew-2.1.0/lib/RelWithDebInfo"
		}

		links {
			"glew32.lib"
		}
	filter "configurations:Distribution"
		libdirs {
			"%{wks.location}/Dependencies/glew-2.1.0/lib/Release"
		}

		links {
			"glew32.lib"
		}

	filter "system:windows"
		defines {
			"AIR_PLATFORM_WINDOWS"
		}
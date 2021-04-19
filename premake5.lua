workspace "Air-Engine"
	architecture  "x86_64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

	filter "configurations:Debug"
		symbols "Full"

		defines {
			"AIR_DEBUG"
		}

	filter "configurations:Release"
		optimize "On"

		defines {
			"AIR_RELEASE"
		}

	filter "configurations:Distribution"
		symbols "Full"
		optimize "Full"

		defines {
			"AIR_DISTRIBUTION"
		}

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

project "Sandbox"
	location "Sandbox"
	kind "WindowedApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	links {
		"Air-Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"GLEW_STATIC",
			"AIR_PLATFORM_WINDOWS",
			"WIN32",
			"_DEBUG",
			"_CONSOLE"
		}

		includedirs {
			"Air-Engine/src/"
		}

project "Air-Engine"
	location "Air-Engine"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"GLEW_STATIC",
			"AIR_PLATFORM_WINDOWS",
			"AIR_TEST",
			"WIN32",
			"_DEBUG",
			"_WINDOWS"
		}
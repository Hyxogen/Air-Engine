workspace "Air-Engine"
	architecture  "x86_64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/"

project "googletest"
	kind "StaticLib"
	files {
		"Vendor/googletest/googletest/src/gtest-all"
	}

	includedirs {
		"Vendor/googletest/googletest/include",
		"Vendor/googletest/googletest"
	}

filter {}
include "Sandbox"
include "Air-Engine"
include "Air Engine Tests"
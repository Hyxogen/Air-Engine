workspace "Air-Engine"
	architecture  "x86_64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/"

filter {}
include "Sandbox"
include "Air-Engine"
include "Air Engine Tests"
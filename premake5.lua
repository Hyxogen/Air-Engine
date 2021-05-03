workspace "Air-Engine"
	architecture  "x86_64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/"

group "Dependencies"
	include "Air-Engine/Dependencies/glad"

group ""

filter {}
include "Sandbox"
include "Air-Engine"
workspace "Air-Engine"
	architecture  "x86_64"

	platforms {
		"Win64",
		"OSX",
		"Linux"
	}

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}


outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/"

group "Dependencies"
group ""

filter {}
include "Sandbox"
include "Air-Engine"

filter {}

files {
	"Generic/*.h",
	"Generic/*.cpp"
}

filter "platforms:Win64"
	files {
		"Windows/**.cpp",
		"Windows/**.h"
	}

filter "platforms:Linux"
	files {
		"Linux/**.cpp",
		"Linux/**.h"
	}

filter "platforms:OSX"
	files {
		"Linux/**.cpp",
		"Linux/**.h"
	}
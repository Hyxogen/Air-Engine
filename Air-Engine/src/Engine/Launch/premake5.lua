--LAUNCH PREMAKE FILE--
filter {}
filter "platforms:Win64"
	files {
		"Windows/**.cpp",
		"Windows/**.h",
		"*.h"
	}

filter "platforms:Linux"
	files {
		"Linux/**.cpp",
		"Linux/**.h",
		"*.h"
	}

filter "platforms:OSX"
	files {
		"Linux/**.cpp",
		"Linux/**.h",
		"*.h"
	}
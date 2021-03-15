#pragma once

namespace platform {
	namespace opengl {

		/*
		Ik wil het liefst de implementatie van OpenGL en Windows niet mixen behalve als de class daarvoor specifiek gemaakt is

		Misschien een goed idee voor de WindowsWindow een soort context class te maken die verder kan worden geextend

		Stel ik wil een andere api gebruiken (zeg Direct3D) dan wil ik simpelweg de WindowsWindow kunnen geven aan een Direct3D helperclass en de context e.d. laten maken. Hetzelfde voor openglz`
		*/

		class GLHandler {

		public:
			GLHandler();

			//Returns 0 (false) if no errors ocurred
			bool Initialize();
		};

	}
}
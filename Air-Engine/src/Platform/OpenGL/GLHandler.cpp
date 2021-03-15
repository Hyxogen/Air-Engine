#include "GLHandler.hpp"
#include <GL/glew.h>
#include <GL/wglew.h>

namespace platform {
	namespace opengl {

		GLHandler::GLHandler() {

		}

		bool GLHandler::Initialize() {
			GLuint err = glewInit();

			if (err != 0) {
				return 1;
			}
			return 0;
		}
	}
}
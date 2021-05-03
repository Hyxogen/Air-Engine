#pragma once

namespace engine {
	namespace util {

		class Sink {
		protected:
			const char* m_Name;

		public:
			Sink(const char* name) : m_Name(name) {}


			virtual bool Print(unsigned char severity, const char* str) = 0;
		};

	}
}
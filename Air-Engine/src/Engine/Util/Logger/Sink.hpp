#pragma once

namespace engine {
	namespace util {

		class Sink {
		protected:
			const char* m_Name;

		public:
			Sink(const char* name) : m_Name(name) {}

			virtual ~Sink() = 0;

			template<typename... Ts>
			bool Print(unsigned char severity, const char* format, Ts... ts) {
				return Print(severity, format, ts...);
			}
		};

	}
}
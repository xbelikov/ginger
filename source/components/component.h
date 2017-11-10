#ifndef GINGER_COMPONENT
#define GINGER_COMPONENT

#include <string>

namespace ginger {

	class Component {
	public:
		std::string getName();
		void setName(const char* name);

	private:
		std::string _name;
	};

}

#endif
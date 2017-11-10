#include "component.h"

namespace ginger {
	std::string Component::getName() {
		return _name;
	}

	void Component::setName(const char* name) {
		_name = name;
	}
}
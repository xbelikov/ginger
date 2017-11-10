#ifndef GINGER_NPC
#define GINGER_NPC

#include "../map/map.h"


namespace ginger {
	
	class Npc
	{
	public:
		virtual void update(float time, std::vector<ginger::MapObject*>* objects);
	};
}

#endif //GINGER_NPC
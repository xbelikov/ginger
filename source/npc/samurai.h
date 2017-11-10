#ifndef SAMURAI_H
#define SAMURAI_H

#include "npc.h"
#include "../animation/animation_list.h"

namespace ginger {
	
	class Samurai : public Npc, public AnimationList, public Physical
	{
	public:
		Samurai(ginger::Logger* log);

		void update(float time, std::vector<ginger::MapObject*>* objects);

	private:
		int health = 100;

	};

}

#endif //SAMURAI_H
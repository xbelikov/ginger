#ifndef GINGER_CHARACTER_STATS
#define GINGER_CHARACTER_STATS

#include "component.h"

namespace ginger {

	class CharacterStats: public Component {
	public:
		CharacterStats();
		
		void setHealth(int v);
		void setDefence(int v);
		void setDamage(int v);
		void setSpeed(int v);

		int getHealth();
		int getDefence();
		int getDamage();
		int getSpeed();

	private:
		int health;
		int defence;
		int damage;
		int speed;
	};

}

#endif
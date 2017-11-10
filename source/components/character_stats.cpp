#include "character_stats.h"

namespace ginger {
	CharacterStats::CharacterStats() {
		setName("CharacterStats");
	}

	void CharacterStats::setHealth(int v) {
		health = v;
	}
	
	void CharacterStats::setDefence(int v) {
		defence = v;
	}
	
	void CharacterStats::setDamage(int v) {
		damage = v;
	}
	
	void CharacterStats::setSpeed(int v) {
		speed = v;
	}

	int CharacterStats::getHealth() {
		return health;
	}

	int CharacterStats::getDefence() {
		return defence;
	}
	
	int CharacterStats::getDamage() {
		return damage;
	}
	
	int CharacterStats::getSpeed() {
		return speed;
	}
}
#pragma once
#ifndef SRC_CHARACTERPANEL_H
#define SRC_CHARACTERPANEL_H

#include "engine/design-patterns/Singleton.h"

#include "BaseImGuiPanel.h"


class CharacterPanel : public Singleton<CharacterPanel>, public BaseImGuiPanel
{
	friend class Singleton<CharacterPanel>;

	virtual void BuildPanel(const sf::RenderWindow& window);
	virtual void Update(uint32_t dt) {};
};

#endif // !SRC_CHARACTERPANEL_H

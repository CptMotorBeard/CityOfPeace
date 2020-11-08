#pragma once
#ifndef SRC_OPTIONSMENU_H
#define SRC_OPTIONSMENU_H

#include "engine/design-patterns/Singleton.h"

#include "BaseImGuiPanel.h"

class OptionsMenu : public Singleton<OptionsMenu>, public BaseImGuiPanel
{
	virtual void BuildPanel(const sf::RenderWindow& window) override;
	virtual void Update(uint32_t dt) override {};
};

#endif // !SRC_OPTIONSMENU_H

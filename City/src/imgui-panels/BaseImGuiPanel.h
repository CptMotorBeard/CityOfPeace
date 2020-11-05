#pragma once
#ifndef SRC_BASEIMGUIPANEL_H
#define SRC_BASEIMGUIPANEL_H

#include <SFML\Graphics\RenderWindow.hpp>

class BaseImGuiPanel
{
public:
	bool IsVisible = false;
	virtual void BuildPanel(const sf::RenderWindow& window) = 0;
	virtual void Update(uint32_t dt) = 0;
};

#endif // !SRC_BASEIMGUIPANEL_H

#pragma once
#ifndef SRC_SIDEPANEL_H
#define SRC_SIDEPANEL_H

#include "engine/design-patterns/Singleton.h"
#include "BaseImGuiPanel.h"
#include "World/GameManager.h"

class SidePanel : public Singleton<SidePanel>, public BaseImGuiPanel
{
	friend class Singleton<SidePanel>;

public:
	virtual void BuildPanel(const sf::RenderWindow& window) override;
	virtual void Update(uint32_t dt) override {};

private:
	const uint32_t kMaxHeight = 400;
	const uint32_t kMaxWidth  = 75;
};

#endif // !SRC_SIDEPANEL_H

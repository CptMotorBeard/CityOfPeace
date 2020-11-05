#pragma once
#ifndef SRC_DEBUGPANEL_H
#define SRC_DEBUGPANEL_H

#include "engine/design-patterns/Singleton.h"

#include "BaseImGuiPanel.h"

class DebugPanel final : public Singleton<DebugPanel>, public BaseImGuiPanel
{
public:
	virtual void BuildPanel(const sf::RenderWindow& window) override;
	virtual void Update(uint32_t dt) override;

private:
	const float kDistance = 10.0f;

	uint32_t m_Dt;
	uint8_t m_Corner = 0;

	float m_FrameValues[90] = {};
	uint32_t m_ValueOffset = 0;
};

#endif // !SRC_DEBUGPANEL_H

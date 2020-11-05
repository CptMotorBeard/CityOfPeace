#pragma once
#ifndef SRC_DISPLAYLOG_H
#define SRC_DISPLAYLOG_H

#include "engine/design-patterns/Singleton.h"
#include "BaseImGuiPanel.h"

class DisplayLog final : public Singleton<DisplayLog>, public BaseImGuiPanel
{
	friend class Singleton<DisplayLog>;

public:
	static const uint32_t kLogSize = 75;

	virtual void BuildPanel(const sf::RenderWindow& window) override;
	virtual void Update(uint32_t dt) override {};
	void AddString(const std::string& text);

private:
	DisplayLog();	

	std::vector<std::string> m_Logs;
	bool m_HasNewLog;
};

#endif // !SRC_DISPLAYLOG_H

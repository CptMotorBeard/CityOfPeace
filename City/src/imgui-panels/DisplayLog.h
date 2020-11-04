#pragma once
#ifndef SRC_DISPLAYLOG_H
#define SRC_DISPLAYLOG_H

#include "engine/design-patterns/Singleton.h"

class DisplayLog final : public Singleton<DisplayLog>
{
	friend class Singleton<DisplayLog>;

public:
	static const uint32_t kLogSize = 75;

	void BuildDisplayLog(const sf::RenderWindow& window);
	void AddString(const std::string& text);

private:
	DisplayLog();

	std::vector<std::string> m_Logs;
	bool m_HasNewLog;
};

#endif // !SRC_DISPLAYLOG_H

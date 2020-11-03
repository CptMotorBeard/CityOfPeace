#pragma once
#ifndef SRC_DISPLAYLOG_H
#define SRC_DISPLAYLOG_H

#include <string>

#include "engine/design-patterns/Singleton.h"

class DisplayLog final : public Singleton<DisplayLog>
{
	friend class Singleton<DisplayLog>;

public:
	void BuildDisplayLog(const sf::RenderWindow& window);
	void AddString(const std::string& text);

private:
	std::string m_String;
};

#endif // !SRC_DISPLAYLOG_H

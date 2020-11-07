#pragma once
#ifndef SRC_GAMEMANAGER_H
#define SRC_GAMEMANAGER_H

#include "engine/design-patterns/Singleton.h"

class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

public:
	void EndTurn();
	bool Shutdown();
	inline const bool& IsRunning() const { return b_IsRunning; };

	inline const uint32_t& GetCurrentWeek() const { return m_CurrentWeek; };
	inline const uint64_t& GetCurrentYear() const { return m_CurrentYear; };
private:
	const uint8_t kWeeksPerYear = 52;

	uint32_t m_CurrentWeek = 0;
	uint64_t m_CurrentYear = 0;

	bool b_IsRunning = true;
};

#endif // !SRC_GAMEMANAGER_H

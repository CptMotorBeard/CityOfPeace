#include "stdafx.h"

#include "GameManager.h"

void GameManager::EndTurn()
{
	++m_CurrentWeek;

	if (m_CurrentWeek >= kWeeksPerYear)
	{
		m_CurrentWeek = 0;
		++m_CurrentYear;
	}
}

bool GameManager::Shutdown()
{
	if (b_IsRunning)
	{
		b_IsRunning = false;
	}

	return true;
}
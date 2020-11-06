#include "stdafx.h"

#include "BaseImGuiPanel.h"
#include "CharacterPanel.h"
#include "DisplayLog.h"
#include "DebugPanel.h"
#include "ImGuiPanelManager.h"

ImGuiPanelManager::ImGuiPanelManager()
{
	m_Dt = 0;

	auto& displayLog = DisplayLog::Instance();
	displayLog.IsVisible = true;

	m_AllPanels.emplace_back(&displayLog);
	m_AllPanels.emplace_back(&DebugPanel::Instance());
	m_AllPanels.emplace_back(&CharacterPanel::Instance());
}

ImGuiPanelManager::~ImGuiPanelManager()
{
	ClearPanels();
}

void ImGuiPanelManager::Update(uint32_t dt)
{
	m_Dt = dt;
}

bool ImGuiPanelManager::AddNewPanel(BaseImGuiPanel* newPanel)
{
	auto existingPanel = std::find(m_AllPanels.begin(), m_AllPanels.end(), newPanel);

	if (existingPanel == m_AllPanels.end())
	{
		m_AllPanels.emplace_back(newPanel);

		return true;
	}	

	return false;
}

bool ImGuiPanelManager::RemovePanel(BaseImGuiPanel* newPanel)
{
	auto existingPanel = std::find(m_AllPanels.begin(), m_AllPanels.end(), newPanel);

	if (existingPanel != m_AllPanels.end())
	{
		m_AllPanels.erase(existingPanel);

		return true;
	}

	return false;
}

void ImGuiPanelManager::ClearPanels()
{
	m_AllPanels.clear();
}

void ImGuiPanelManager::BuildVisiblePanels(const sf::RenderWindow& window)
{
	for (const auto& panel : m_AllPanels)
	{
		if (panel->IsVisible)
		{
			panel->Update(m_Dt);
			panel->BuildPanel(window);			
		}
	}
}

void ImGuiPanelManager::BuildAllPanels(const sf::RenderWindow& window)
{
	for (const auto& panel : m_AllPanels)
	{
		panel->Update(m_Dt);
		panel->BuildPanel(window);		
	}
}
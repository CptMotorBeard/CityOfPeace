#pragma once
#ifndef SRC_IMGUIPANELMANAGER_H
#define SRC_IMGUIPANELMANAGER_H

#include "engine/design-patterns/Singleton.h"

class BaseImGuiPanel;

class ImGuiPanelManager final : public Singleton<ImGuiPanelManager>
{
	friend class Singleton<ImGuiPanelManager>;

public:
	void Update(uint32_t dt);

	bool AddNewPanel(BaseImGuiPanel* newPanel);
	bool RemovePanel(BaseImGuiPanel* newPanel);
	void ClearPanels();

	void BuildVisiblePanels(const sf::RenderWindow& window);
	void BuildAllPanels(const sf::RenderWindow& window);
	
private:
	ImGuiPanelManager();
	~ImGuiPanelManager();

	std::vector<BaseImGuiPanel*> m_AllPanels;
	uint32_t m_Dt;
};

#endif // !SRC_IMGUIPANELMANAGER_H

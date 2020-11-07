#include "stdafx.h"

#include "engine/imgui-addons/imgui-wrappedFormattedText.h"

#include "CharacterPanel.h"
#include "DisplayLog.h"

DisplayLog::DisplayLog()
{
	m_Logs.reserve(kLogSize);
	m_HasNewLog = false;
}

void DisplayLog::AddString(const std::string& text)
{
	while (m_Logs.size() >= kLogSize)
	{
		m_Logs.erase(m_Logs.begin());
	}

	m_Logs.emplace_back(text);
	m_HasNewLog = true;
}

void DisplayLog::BuildPanel(const sf::RenderWindow& window)
{
	if (!ImGui::Begin("Log", (bool*)0, ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
		return;
	}
	
	float regionWidth = ImGui::GetWindowContentRegionWidth();

	for (const auto& log : m_Logs)
	{
		ImGui::DisplayFormattedText(log, regionWidth);
	}

	if (m_HasNewLog && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
	{		
		ImGui::SetScrollHereY(1.0f);

		m_HasNewLog = false;
	}

	ImGui::End();
}
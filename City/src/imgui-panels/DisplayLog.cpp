#include "stdafx.h"

#include "engine/imgui-addons/imgui-wrappedFormattedText.h"

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
	int styleCount = 0;
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	++styleCount;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 5));
	++styleCount;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	++styleCount;

	ImGui::Begin("Log", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		ImGui::MenuItem("Test");

		ImGui::EndMenuBar();
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

	ImGui::PopStyleVar(styleCount);
}
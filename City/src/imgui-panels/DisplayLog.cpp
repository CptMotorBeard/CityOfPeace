#include "stdafx.h"

#include "engine/imgui-addons/imgui-wrappedFormattedText.h"

#include "DisplayLog.h"

void DisplayLog::AddString(const std::string& text)
{
	m_String = text;
}

void DisplayLog::BuildDisplayLog(const sf::RenderWindow& window)
{
	int styleCount = 0;
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	++styleCount;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 5));
	++styleCount;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	++styleCount;

	ImGui::Begin("Log");
	ImGui::DisplayFormattedText(m_String, ImGui::GetWindowContentRegionWidth());
	ImGui::End();

	ImGui::PopStyleVar(styleCount);
}
#include "stdafx.h"

#include "World/GameManager.h"
#include "OptionsMenu.h"

void OptionsMenu::BuildPanel(const sf::RenderWindow& window)
{
	auto& windowSize = window.getSize();

	ImGui::SetNextWindowSize(ImVec2(windowSize.x, windowSize.y));
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);

	if (ImGui::Begin("Options", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration))
	{
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - 60, windowSize.y / 2 - (20 + (40 * 2))));		
		if (ImGui::Button("Exit Menu", ImVec2(120, 40)))
		{
			this->IsVisible = false;
		}

		ImGui::SetCursorPosX(windowSize.x / 2 - 60);
		if (ImGui::Button("Exit Game", ImVec2(120, 40)))
		{
			GameManager::Instance().Shutdown();
		}
	}
		
	ImGui::End();
	ImGui::PopStyleVar();
}
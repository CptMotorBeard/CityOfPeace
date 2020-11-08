#include "stdafx.h"

#include <glm/glm.hpp>

#include "CharacterPanel.h"
#include "OptionsMenu.h"
#include "SidePanel.h"

void SidePanel::BuildPanel(const sf::RenderWindow& window)
{	
	auto& windowSize = window.getSize();

	float width = glm::min(windowSize.x - 25, kMaxWidth);
	float height = glm::min(windowSize.y - 50, kMaxHeight);	

	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowPos(ImVec2(25, 25));

	if (ImGui::Begin("Side Panel", (bool*)0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		ImGui::Text(std::to_string(GameManager::Instance().GetCurrentWeek()).c_str());
		ImGui::SameLine();
		ImGui::Text(std::to_string(GameManager::Instance().GetCurrentYear()).c_str());

		float buttonWidth = width - 20;
		float buttonHeight = height / 6;

		ImGui::SetCursorPosX(10);
		ImGui::SetCursorPosY((height - (5 * buttonHeight)) / 3);
		if (ImGui::Button("People", ImVec2(buttonWidth, buttonHeight)))
		{
			CharacterPanel::Instance().IsVisible = true;
		}

		ImGui::Spacing();
		ImGui::SetCursorPosX(10);
		if (ImGui::Button("Town", ImVec2(buttonWidth, buttonHeight)))
		{

		}

		ImGui::Spacing();
		ImGui::SetCursorPosX(10);
		if (ImGui::Button("World", ImVec2(buttonWidth, buttonHeight)))
		{

		}

		ImGui::Spacing();
		ImGui::SetCursorPosX(10);
		if (ImGui::Button("End", ImVec2(buttonWidth, buttonHeight)))
		{
			GameManager::Instance().EndTurn();
		}

		ImGui::Spacing();
		ImGui::SetCursorPosX(10);
		if (ImGui::Button("Options", ImVec2(buttonWidth, buttonHeight)))
		{
			OptionsMenu::Instance().IsVisible = true;
		}
	}
	
	ImGui::End();
}
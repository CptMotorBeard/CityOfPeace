#include "stdafx.h"

#include "CharacterPanel.h"

void CharacterPanel::BuildPanel(const sf::RenderWindow& window)
{
	if (!ImGui::Begin("Character Panel", (bool*)0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
		return;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 20);
	if (ImGui::BeginMenuBar() && ImGui::MenuItem("Close"))
	{
		this->IsVisible = false;
	}
	ImGui::EndMenuBar();
	ImGui::PopStyleVar();

	ImGui::Text("Test");

	ImGui::End();
}
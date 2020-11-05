#include "stdafx.h"

#include "DebugPanel.h"

void DebugPanel::BuildPanel(const sf::RenderWindow& window)
{
	ImGuiIO& io = ImGui::GetIO();

	ImVec2 window_pos = ImVec2((m_Corner & 1) ? io.DisplaySize.x - kDistance : kDistance, (m_Corner & 2) ? io.DisplaySize.y - kDistance : kDistance);
	ImVec2 window_pos_pivot = ImVec2((m_Corner & 1) ? 1.0f : 0.0f, (m_Corner & 2) ? 1.0f : 0.0f);
	
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.35f);

	if (!ImGui::Begin("Frame Debug Window", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::End();
		return;
	}

	m_FrameValues[m_ValueOffset] = m_Dt;
	m_ValueOffset = (m_ValueOffset + 1) % 90;

	ImGui::PlotLines("", m_FrameValues, IM_ARRAYSIZE(m_FrameValues), m_ValueOffset);

	std::string fps = "FPS: " + std::to_string(1.0f / (m_Dt / 1000.0f));
	ImGui::Text(fps.c_str());

	ImGui::SameLine();
	std::string delta = "MS per Frame: " + std::to_string(m_Dt);
	ImGui::Text(delta.c_str());

	ImGui::End();
}

void DebugPanel::Update(uint32_t dt)
{
	m_Dt = dt;
}
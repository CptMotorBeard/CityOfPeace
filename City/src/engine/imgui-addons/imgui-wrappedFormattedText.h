#pragma once
#ifndef SRC_IMGUI_WRAPPEDFORMATTEDTEXT_H
#define SRC_IMGUI_WRAPPEDFORMATTEDTEXT_H

namespace ImGui
{
	void DisplayFormattedText(const std::string& line, const float wrap_width = -1);
}

#endif // !SRC_IMGUI_WRAPPEDFORMATTEDTEXT_H
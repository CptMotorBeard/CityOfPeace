#include "stdafx.h"

#include "imgui-wrappedFormattedText.h"

namespace ImGui
{
	float ForceDisplayLine(std::string& line, const bool newLine, const bool isColoured, const ImVec4& colour)
	{
		if (line == "")
		{
			return 0;
		}

		float lineLength = ImGui::CalcTextSize(line.c_str()).x;
		if (!newLine)
		{
			ImGui::SameLine();
		}

		if (isColoured)
		{
			ImGui::TextColored(colour, line.c_str());
		}
		else
		{
			ImGui::TextUnformatted(line.c_str());
		}

		return lineLength;
	}

	bool BuildAndDisplayLine(std::string& line, const std::string& token, const bool isColoured, const ImVec4& colour, const float linePos = 0, const float wrap_width = -1)
	{
		if (token == "")
		{
			return false;
		}

		std::string newLine(line + (line == "" ? "" : " ") + token);
		ImVec2 textSize(ImGui::CalcTextSize(newLine.c_str(), (const char*)0, false, wrap_width));
		float height = ImGui::GetTextLineHeight();

		float lines = textSize.y / height;
		float actualWidth = textSize.x + linePos;
		if (lines > 1 || (wrap_width > 0 && actualWidth > wrap_width))
		{
			if (linePos != 0)
			{
				ImGui::SameLine();
			}

			if (isColoured)
			{
				ImGui::TextColored(colour, line.c_str());
			}
			else
			{
				ImGui::TextUnformatted(line.c_str());
			}

			line = token;

			return true;
		}
		else
		{
			line = newLine;

			return false;
		}
	}

	bool CheckColourAndFormatStart(std::string& testString, ImVec4& outputColour)
	{
		if (testString.length() < 8)
		{
			return false;
		}

		if (testString[1] == '#' && testString[0] == '#')
		{
			uint32_t colour = std::stol(testString.substr(2, 6), nullptr, 16);
			testString = testString.substr(8);

			outputColour.x = (colour & 0xFF0000) >> 16;
			outputColour.y = (colour & 0x00FF00) >> 8;
			outputColour.z = (colour & 0x0000FF);
			outputColour.w = 0xFF;

			return true;
		}

		return false;
	}

	bool CheckColourAndFormatEnd(std::string& testString)
	{
		if (testString.length() < 2)
		{
			return false;
		}

		if (testString[testString.length() - 2] == '$' && testString[testString.length() - 1] == '$')
		{
			testString.erase(testString.length() - 2);
			return true;
		}

		return false;
	}	

	void CheckColour(std::string& token, bool& isColoured, bool& isEndColour, bool& forceLine, ImVec4& colour)
	{
		if (CheckColourAndFormatStart(token, colour))
		{
			isColoured = true;
			forceLine = true;
		}

		if (CheckColourAndFormatEnd(token))
		{
			isEndColour = true;
		}
		else
		{
			isEndColour = false;
		}
	}

	void DisplayFormattedText(const std::string& line, const float wrap_width)
	{
		const char* delimiter = " ";

		size_t next = 0;
		size_t last = 0;

		std::string token;

		std::string output;

		float startPos = 0;
		ImVec4 colour;

		bool isColoured = false;
		bool endColour = false;
		bool forceLine = false;

		while ((next = line.find(delimiter, last)) != std::string::npos)
		{
			token = line.substr(last, next - last);
			last = next + 1;

			CheckColour(token, isColoured, endColour, forceLine, colour);

			if (forceLine)
			{
				startPos += ForceDisplayLine(output, startPos == 0, !isColoured, colour);
				output = "";
				forceLine = false;
			}

			if (BuildAndDisplayLine(output, token, isColoured, colour, startPos, wrap_width))
			{
				startPos = 0;
			}

			if (endColour)
			{
				isColoured = false;
				endColour = false;
				forceLine = true;
			}
		}

		token = line.substr(last);
		CheckColour(token, isColoured, endColour, forceLine, colour);

		bool newLine = BuildAndDisplayLine(output, token, isColoured, colour, startPos, wrap_width);

		if (output != "")
		{
			ForceDisplayLine(output, newLine, isColoured, colour);
		}

		ImGui::NewLine();
	}
}
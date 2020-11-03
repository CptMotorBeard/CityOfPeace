#include "stdafx.h"

#include <regex>

#include "engine/localization/LocalizationManager.h"

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

		ImGui::SameLine();
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

	void DisplayFormattedText(const std::string& line, float wrap_width=-1)
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
			
			if (CheckColourAndFormatStart(token, colour))
			{
				isColoured = true;
				endColour = false;
				forceLine = true;
			}

			if (CheckColourAndFormatEnd(token))
			{
				endColour = true;
			}

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
		BuildAndDisplayLine(output, token, isColoured, colour, startPos, wrap_width);
	}
}

int main()
{
	Engine::LocalizationManager& LocManagerInstance = Engine::LocalizationManager::Instance();

	std::string title(LocManagerInstance.NewStringFromLocKey("ENTRY_TITLE"));

	sf::RenderWindow window;
	window.create(sf::VideoMode(640, 480), title.c_str());
	ImGui::SFML::Init(window);

	window.resetGLStates();
	window.setFramerateLimit(24);

	sf::Clock deltaClock;

	while (window.isOpen())
	{
		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			ImGui::SFML::ProcessEvent(sfEvent);

			if (sfEvent.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (sfEvent.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, (float)sfEvent.size.width, (float)sfEvent.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		uint32_t deltaTime = deltaClock.getElapsedTime().asMicroseconds();
		ImGui::SFML::Update(window, deltaClock.restart());

		sf::Vector2u windowSize = window.getSize();

		ImVec2 textboxSize(windowSize.x, windowSize.y / 2);

		//ImGui::SetNextWindowSize(textboxSize);
		//ImGui::SetNextWindowPos(ImVec2(0, windowSize.y - textboxSize.y));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 5));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::Begin("Log");		
		float maxYScroll = ImGui::GetScrollMaxY();
		//ImGui::SetScrollY(maxYScroll);
		ImGui::DisplayFormattedText(
			"##FF0000[RED]:$$ Lorem ipsum dolor sit amet, consectetur adipiscing elit.Nam lectus ante, bibendum vitae egestas vel, ##DF0000mattis nec eros.Curabitur a felis sed massa scelerisque sollicitudin.Maecenas ac sagittis erat, vel luctus erat.In fringilla eros sit amet tellus lobortis, a fringilla enim euismod.Maecenas id suscipit ex, vel sagittis arcu.Phasellus ut pharetra lectus.Pellentesque vitae ex iaculis, auctor dolor eget, scelerisque dolor."
			" ##00FF00[GREEN]:$$ Nulla facilisi.Nullam vel ex dictum, euismod nisl sed, luctus tellus.Duis in velit tellus.Nunc eu tincidunt tellus.Duis lacinia nibh erat, in vulputate justo euismod in.Donec consequat rutrum egestas.Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Phasellus eget nibh pharetra, condimentum orci faucibus, malesuada sapien."
			" ##0000FF[BLUE]:$$ In id maximus erat, ac feugiat mauris.Praesent rutrum vitae enim sit amet congue.Sed aliquam dignissim libero ac lobortis.Interdum et malesuada fames ac ante ipsum primis in faucibus.Ut eget nisl tortor.Morbi vel nisl ac justo tempor facilisis sed eu odio.Nam mattis, nisi vel sollicitudin bibendum, purus sem finibus leo, sed condimentum dui nisl vel arcu."
			" ##FFFF00Curabitur in eros bibendum,$$ scelerisque urna ac, pharetra dui.Etiam id lacinia ante, in vestibulum neque.Nunc lacus nulla, finibus vel urna vel, sollicitudin gravida ex.Donec viverra diam ac consectetur iaculis.Donec vitae consequat elit.Quisque euismod pellentesque metus, et tristique elit vestibulum eu.Praesent semper, arcu in eleifend tempus, nisl nulla mattis orci, nec blandit diam mi vitae lorem.Proin aliquam finibus nibh quis finibus.Mauris egestas tellus libero, at commodo enim consequat vel.Cras facilisis mauris in pellentesque gravida."
			" ##00FFFFAliquam nec arcu placerat, convallis ex ac, facilisis risus.Curabitur venenatis commodo vestibulum.$$ Curabitur eros odio, hendrerit at turpis a, condimentum rutrum arcu.Nam sapien nulla, vulputate in ipsum nec, placerat ullamcorper arcu.Ut ultricies arcu id augue volutpat elementum.Suspendisse potenti.Donec tincidunt augue vel bibendum accumsan.",
			ImGui::GetWindowContentRegionWidth()
		);
		ImGui::End();
		ImGui::PopStyleVar(3);

		window.clear();
		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}
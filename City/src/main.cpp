#include "stdafx.h"

#include <regex>

#include "engine/localization/LocalizationManager.h"
#include "engine/imgui-addons/imgui-wrappedFormattedText.h"

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
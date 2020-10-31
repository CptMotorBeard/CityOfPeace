#include "stdafx.h"

#include "engine/localization/LocalizationManager.h"

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

		window.clear();
		ImGui::ShowDemoWindow();
		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}
#include "stdafx.h"

#include "engine/localization/LocalizationManager.h"

#include "World/GameManager.h"
#include "imgui-panels/DisplayLog.h"
#include "imgui-panels/ImGuiPanelManager.h"

int main()
{
	const char* longString =
		"##FF0000[RED]:$$ Lorem ipsum dolor sit amet, consectetur adipiscing elit.Nam lectus ante, bibendum vitae egestas vel, ##DF0000mattis nec eros.Curabitur a felis sed massa scelerisque sollicitudin.Maecenas ac sagittis erat, vel luctus erat.In fringilla eros sit amet tellus lobortis, a fringilla enim euismod.Maecenas id suscipit ex, vel sagittis arcu.Phasellus ut pharetra lectus.Pellentesque vitae ex iaculis, auctor dolor eget, scelerisque dolor."
		" ##00FF00[GREEN]:$$ Nulla facilisi.Nullam vel ex dictum, euismod nisl sed, luctus tellus.Duis in velit tellus.Nunc eu tincidunt tellus.Duis lacinia nibh erat, in vulputate justo euismod in.Donec consequat rutrum egestas.Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Phasellus eget nibh pharetra, condimentum orci faucibus, malesuada sapien."
		" ##0000FF[BLUE]:$$ In id maximus erat, ac feugiat mauris.Praesent rutrum vitae enim sit amet congue.Sed aliquam dignissim libero ac lobortis.Interdum et malesuada fames ac ante ipsum primis in faucibus.Ut eget nisl tortor.Morbi vel nisl ac justo tempor facilisis sed eu odio.Nam mattis, nisi vel sollicitudin bibendum, purus sem finibus leo, sed condimentum dui nisl vel arcu."
		" ##FFFF00Curabitur in eros bibendum,$$ scelerisque urna ac, pharetra dui.Etiam id lacinia ante, in vestibulum neque.Nunc lacus nulla, finibus vel urna vel, sollicitudin gravida ex.Donec viverra diam ac consectetur iaculis.Donec vitae consequat elit.Quisque euismod pellentesque metus, et tristique elit vestibulum eu.Praesent semper, arcu in eleifend tempus, nisl nulla mattis orci, nec blandit diam mi vitae lorem.Proin aliquam finibus nibh quis finibus.Mauris egestas tellus libero, at commodo enim consequat vel.Cras facilisis mauris in pellentesque gravida."
		" ##00FFFFAliquam nec arcu placerat, convallis ex ac, facilisis risus.Curabitur venenatis commodo vestibulum.$$ Curabitur eros odio, hendrerit at turpis a, condimentum rutrum arcu.Nam sapien nulla, vulputate in ipsum nec, placerat ullamcorper arcu.Ut ultricies arcu id augue volutpat elementum.Suspendisse potenti.Donec tincidunt augue vel bibendum accumsan.";

	BeardEngine::LocalizationManager& m_LocManagerInstance = BeardEngine::LocalizationManager::Instance();
	DisplayLog& m_DisplayLogInstance = DisplayLog::Instance();
	ImGuiPanelManager& m_ImGuiPanelManager = ImGuiPanelManager::Instance();

	m_DisplayLogInstance.AddString(longString);

	m_DisplayLogInstance.AddString("##00FF00Next Line Fool$$");
	m_DisplayLogInstance.AddString("No Colours");
	m_DisplayLogInstance.AddString("");
	m_DisplayLogInstance.AddString(".");
	m_DisplayLogInstance.AddString("..");
	m_DisplayLogInstance.AddString("...");
	m_DisplayLogInstance.AddString("Time for news");

	std::string title(m_LocManagerInstance.NewStringFromLocKey("ENTRY_TITLE"));
	sf::RenderWindow window;
	window.create(sf::VideoMode(1920, 1080), title.c_str(), sf::Style::Fullscreen);
	ImGui::SFML::Init(window);

	window.resetGLStates();
	window.setFramerateLimit(60);

	sf::Clock deltaClock;

	bool b_IsDebugMode = false;

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
			else if (sfEvent.type == sf::Event::MouseButtonReleased && sfEvent.mouseButton.button == sf::Mouse::Button::Left)
			{
				std::cout << "Click" << std::endl;
			}
			else if (sfEvent.type == sf::Event::KeyReleased && sfEvent.key.code == sf::Keyboard::Tilde)
			{
				b_IsDebugMode = !b_IsDebugMode;
			}
		}

		uint32_t deltaTime = deltaClock.getElapsedTime().asMilliseconds();
		ImGui::SFML::Update(window, deltaClock.restart());
		m_ImGuiPanelManager.Update(deltaTime);

		if (!b_IsDebugMode)
		{
			m_ImGuiPanelManager.BuildVisiblePanels(window);
		}
		else
		{
			m_ImGuiPanelManager.BuildAllPanels(window);
		}

		window.clear();
		ImGui::SFML::Render(window);

		window.display();

		if (!GameManager::Instance().IsRunning())
		{
			window.close();
		}
	}

	ImGui::SFML::Shutdown();

	return 0;
}
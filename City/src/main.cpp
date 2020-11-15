#include "stdafx.h"

#include "engine/localization/LocalizationManager.h"

#include "imgui-panels/DisplayLog.h"
#include "imgui-panels/ImGuiPanelManager.h"
#include "imgui-panels/OptionsMenu.h"
#include "World/WindowManager.h"

void f(sf::Event s)
{
	std::cout << "key press" << std::endl;
}

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
	WindowManager& m_WindowManager = WindowManager::Instance();	

	std::string title(m_LocManagerInstance.NewStringFromLocKey("ENTRY_TITLE"));
	m_WindowManager.Initialize(sf::VideoMode(1920, 1080), title.c_str(), sf::Style::Fullscreen);

	m_DisplayLogInstance.AddString(longString);

	m_DisplayLogInstance.AddString("##00FF00Next Line Fool$$");
	m_DisplayLogInstance.AddString("No Colours");
	m_DisplayLogInstance.AddString("");
	m_DisplayLogInstance.AddString(".");
	m_DisplayLogInstance.AddString("..");
	m_DisplayLogInstance.AddString("...");
	m_DisplayLogInstance.AddString("Time for news");

	sf::Clock deltaClock;

	bool b_IsDebugMode = false;

	m_WindowManager.KeyPressedEvent += std::function([&b_IsDebugMode](sf::Event keyEvent)
	{
		std::cout << "Pressed: " << keyEvent.key.code << std::endl;

		if (keyEvent.key.code == sf::Keyboard::Tilde)
		{
			b_IsDebugMode = !b_IsDebugMode;
		}
		else if (keyEvent.key.code == sf::Keyboard::Escape)
		{
			auto& options = OptionsMenu::Instance();
			options.IsVisible = !options.IsVisible;
		}
	});

	while (m_WindowManager.WindowIsOpen())
	{
		m_WindowManager.ProcessEvents();

		sf::Time deltaTime = deltaClock.restart();
		m_WindowManager.Update(deltaTime);
		m_ImGuiPanelManager.Update(deltaTime.asMilliseconds());

		if (!b_IsDebugMode)
		{
			m_ImGuiPanelManager.BuildVisiblePanels(m_WindowManager.GetWindow());
		}
		else
		{
			m_ImGuiPanelManager.BuildAllPanels(m_WindowManager.GetWindow());
		}

		m_WindowManager.DisplayWindow();
	}

	ImGui::SFML::Shutdown();

	return 0;
}
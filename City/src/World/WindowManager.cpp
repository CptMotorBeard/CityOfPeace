#include "stdafx.h"

#include "GameManager.h"
#include "WindowManager.h"

void WindowManager::Initialize(sf::VideoMode mode, const char* title, uint32_t style)
{
	m_Window.create(mode, title, style);

	ImGui::SFML::Init(m_Window);

	m_Window.resetGLStates();
	m_Window.setFramerateLimit(60);
}

void WindowManager::ProcessEvents()
{
	sf::Event sfEvent;
	while (m_Window.pollEvent(sfEvent))
	{
		ImGui::SFML::ProcessEvent(sfEvent);

		if (sfEvent.type == sf::Event::Closed)
		{
			m_Window.close();
		}
		else if (sfEvent.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, (float)sfEvent.size.width, (float)sfEvent.size.height);
			m_Window.setView(sf::View(visibleArea));
		}
		else if (sfEvent.type == sf::Event::MouseButtonReleased && sfEvent.mouseButton.button == sf::Mouse::Button::Left)
		{
			MouseClickedEvent.Invoke(sfEvent);
		}
		else if (sfEvent.type == sf::Event::KeyReleased)
		{
			KeyPressedEvent.Invoke(sfEvent);
		}
	}
}

void WindowManager::Update(sf::Time deltaTime)
{
	ImGui::SFML::Update(m_Window, deltaTime);
}

void WindowManager::DisplayWindow()
{
	m_Window.clear();

	ImGui::SFML::Render(m_Window);

	m_Window.display();

	if (!GameManager::Instance().IsRunning())
	{
		m_Window.close();
	}
}

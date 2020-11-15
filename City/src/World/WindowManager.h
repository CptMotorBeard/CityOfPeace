#pragma once
#ifndef SRC_WINDOWMANAGER_H
#define SRC_WINDOWMANAGER_H

#include "engine/design-patterns/Singleton.h"
#include "engine/events/Event.h"

class WindowManager : public Singleton<WindowManager>
{
	friend class Singleton<WindowManager>;

public:
	BeardEngine::Event< sf::Event > KeyPressedEvent;
	BeardEngine::Event< sf::Event > MouseClickedEvent;

	inline const bool WindowIsOpen() const { return m_Window.isOpen(); }
	inline const sf::RenderWindow& GetWindow() const { return m_Window; }

	void Initialize(sf::VideoMode mode, const char* title, uint32_t style);	
	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void DisplayWindow();

private:
	sf::RenderWindow m_Window;
};

#endif // !SRC_WINDOWMANAGER_H

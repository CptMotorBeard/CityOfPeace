#pragma once
#ifndef SRC_EVENT_H
#define SRC_EVENT_H

namespace BeardEngine
{
	template<class...Args>
	class Event
	{
	private:
		std::vector<std::function<void(Args...)>> m_ListeningFunctions;

	public:
		Event()
		{
			// Nothing to do here
		}

		~Event()
		{
			m_ListeningFunctions.clear();
		}

		template<class ...Args>
		Event<Args...>& operator=(std::function<void(Args...)> newListeningFunction)
		{
			m_ListeningFunctions.clear();

			if (newListeningFunction != nullptr)
			{
				m_ListeningFunctions.emplace_back(newListeningFunction);
			}
		}

		template<class ...Args>
		inline Event<Args...>& operator+=(void(*newListeningFunction)(Args...))
		{
			return operator+=(std::function(newListeningFunction));
		}

		template<class ...Args>
		inline Event<Args...>& operator+=(std::function<void(Args...)> newListeningFunction)
		{
			m_ListeningFunctions.emplace_back(newListeningFunction);

			return *this;
		}

		template<class ...Args>
		inline Event<Args...>& operator-=(void(*oldListeningFunction)(Args...))
		{
			return operator-=(std::function(oldListeningFunction));
		}

		template<class ...Args>
		Event<Args...>& operator-=(std::function<void(Args...)> oldListeningFunction)
		{
			auto& existingFunction = std::find(m_ListeningFunctions.begin(), m_ListeningFunctions.end(), oldListeningFunction);
			if (existingFunction != m_ListeningFunctions.end())
			{
				m_ListeningFunctions.erase(existingFunction);
			}

			return *this;
		}

		template<class ...Args>
		void Invoke(Args ...argument)
		{
			for (auto& function : m_ListeningFunctions)
			{
				function(argument...);
			}
		}
	};
}

#endif // !SRC_EVENT_H

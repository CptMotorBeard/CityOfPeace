#pragma once
#ifndef SRC_LOCALIZATIONMANAGER_H
#define SRC_LOCALIZATIONMANAGER_H

#include "engine/design-patterns/Singleton.h"

class sqlite3;

namespace Engine
{
	struct Language
	{
		static const char* EN;
	};

	class LocalizationManager final : public Singleton<LocalizationManager>
	{
		friend class Singleton<LocalizationManager>;

	public:		
		bool UseLocalizedString;
		void SetLanguage(const char*& newLanguage);
		std::string NewStringFromLocKey(const std::string& key);
	private:
		sqlite3* m_LocalizationDatabase;
		char m_Language[3];

		LocalizationManager();
		~LocalizationManager();
		bool OpenDatabase();
	};
}

#endif // !SRC_LOCALIZATIONMANAGER_H
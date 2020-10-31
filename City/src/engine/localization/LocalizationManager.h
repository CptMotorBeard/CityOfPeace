#pragma once
#ifndef SRC_LOCALIZATIONMANAGER_H
#define SRC_LOCALIZATIONMANAGER_H

#include <string>

class sqlite3;

namespace Engine
{
	struct Language
	{
		static const char* EN;
	};

	class LocalizationManager
	{
	public:		
		bool UseLocalizedString;

		~LocalizationManager();
		void SetLanguage(const char*& newLanguage);
		std::string NewStringFromLocKey(const std::string& key);
		static LocalizationManager& Instance()
		{
			static LocalizationManager localizationManager;
			return localizationManager;
		}

		LocalizationManager(const LocalizationManager&) = delete;
		LocalizationManager& operator=(const LocalizationManager&) = delete;
		LocalizationManager(const LocalizationManager&&) = delete;
		LocalizationManager& operator=(const LocalizationManager&&) = delete;

	private:
		sqlite3* m_LocalizationDatabase;
		char m_Language[3];

		LocalizationManager();
		bool OpenDatabase();
	};
}

#endif // SRC_LOCALIZATIONMANAGER_H
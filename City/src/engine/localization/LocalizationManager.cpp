#include "stdafx.h"

#include "LocalizationManager.h"

namespace SQLQuery
{
	const char* kLOC_TABLE = "loc";
	const char* kLOC_KEY = "loc_key";
	const char* kLOC_VALUE = "loc_value_";

	const int kREAD_FULL_QUERY = -1;
	const char** kNO_TAIL = nullptr;

	const int kLEFTMOST_COLUMN = 0;
}

namespace Engine
{
	const char* Language::EN = "en";

	LocalizationManager::LocalizationManager()
	{
		UseLocalizedString = true;
		SetLanguage(Language::EN);		

		OpenDatabase();
	}

	void LocalizationManager::SetLanguage(const char*& newLanguage)
	{
		sprintf_s(m_Language, 3, newLanguage);
	}

	LocalizationManager::~LocalizationManager()
	{
		sqlite3_close(m_LocalizationDatabase);
	}

	bool LocalizationManager::OpenDatabase()
	{
		int errorCode = sqlite3_open("../resources/loc.db", &m_LocalizationDatabase);

		if (errorCode)
		{
			sqlite3_close(m_LocalizationDatabase);
			return false;
		}

		return true;
	}
	
	std::string LocalizationManager::NewStringFromLocKey(const std::string& key)
	{
		if (UseLocalizedString)
		{
			char lang[16];
			char query[128];
			sprintf_s(lang, 16, "%s%s", SQLQuery::kLOC_VALUE, m_Language);
			sprintf_s(query, 128, "SELECT %s FROM %s WHERE %s==\"%s\"", lang, SQLQuery::kLOC_TABLE, SQLQuery::kLOC_KEY, key.c_str());

			sqlite3_stmt* stmt;
			int errorCode = sqlite3_prepare_v2(m_LocalizationDatabase, query, SQLQuery::kREAD_FULL_QUERY, &stmt, SQLQuery::kNO_TAIL);

			if (errorCode == SQLITE_OK)
			{
				errorCode = sqlite3_step(stmt);
				if (errorCode != SQLITE_ERROR)
				{
					std::string locValue;
					char* results = (char*)sqlite3_column_text(stmt, SQLQuery::kLEFTMOST_COLUMN);

					if (results != NULL)
					{
						std::string locValue(results);
						sqlite3_finalize(stmt);
						return locValue;
					}
				}
			}

			char errorMessage[128];
			sprintf_s(errorMessage, 128, "Error in retrieving loc key: %s", key.c_str());
			std::cout << errorMessage << std::endl;

			sqlite3_finalize(stmt);
		}

		return std::string(key);
	}
}
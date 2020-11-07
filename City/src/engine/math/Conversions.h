#pragma once
#ifndef SRC_CONVERSIONS_H
#define SRC_CONVERSIONS_H

#include <glm/glm.hpp>

#include "imgui.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"

namespace BeardEngine
{
	// GLM Conversions
	inline glm::vec2 glmVector2Convert(const ImVec2& rhs)
	{
		return glm::vec2(rhs.x, rhs.y);
	};

	inline glm::vec2 glmVector2Convert(const sf::Vector2u& rhs)
	{
		return glm::vec2(rhs.x, rhs.y);
	}

	inline glm::vec2 glmVector2Convert(const sf::Vector2i& rhs)
	{
		return glm::vec2(rhs.x, rhs.y);
	}

	inline glm::vec2 glmVector2Convert(const sf::Vector2f& rhs)
	{
		return glm::vec2(rhs.x, rhs.y);
	}

	template<typename T>
	inline glm::vec2 glmVector2Convert(const sf::Vector2<T>& rhs)
	{
		return glm::vec2(rhs.x, rhs.y);
	};

	inline glm::vec3 glmVector3Convert(const sf::Vector3i& rhs)
	{
		return glm::vec3(rhs.x, rhs.y, rhs.z);
	};

	inline glm::vec3 glmVector3Convert(const sf::Vector3f& rhs)
	{
		return glm::vec3(rhs.x, rhs.y, rhs.z);
	};

	template<typename T>
	inline glm::vec3 glmVector3Convert(const sf::Vector3<T>& rhs)
	{
		return glm::vec3(rhs.x, rhs.y, rhs.z);
	};

	inline glm::vec4 glmVector4Convert(const ImVec4& rhs)
	{
		return glm::vec4(rhs.x, rhs.y, rhs.z, rhs.w);
	};
	// End GLM Conversions

	// ImGui Conversions
	inline ImVec2 imVector2Convert(const glm::vec2& rhs)
	{
		return ImVec2(rhs.x, rhs.y);
	};

	inline ImVec2 imVector2Convert(const sf::Vector2u& rhs)
	{
		return ImVec2(rhs.x, rhs.y);
	};

	inline ImVec2 imVector2Convert(const sf::Vector2i& rhs)
	{
		return ImVec2(rhs.x, rhs.y);
	};

	inline ImVec2 imVector2Convert(const sf::Vector2f& rhs)
	{
		return ImVec2(rhs.x, rhs.y);
	};

	template<typename T>
	inline ImVec2 imVector2Convert(const sf::Vector2<T>& rhs)
	{
		return ImVec2(rhs.x, rhs.y);
	};

	inline ImVec4 imVector4Convert(const glm::vec4& rhs)
	{
		return ImVec4(rhs.x, rhs.y, rhs.z, rhs.w);
	};
	// End ImGui Conversions

	// SF Conversions
	template<typename T>
	inline sf::Vector2<T> sfVector2Convert(const ImVec2& rhs)
	{
		return sf::Vector2<T>(rhs.x, rhs.y);
	};

	template<typename T>
	inline sf::Vector2<T> sfVector2Convert(const glm::vec2& rhs)
	{
		return sf::Vector2<T>(rhs.x, rhs.y);
	};

	template<typename T>
	inline sf::Vector3<T> sfVector3Convert(const glm::vec3& rhs)
	{
		return sf::Vector3<T>(rhs.x, rhs.y, rhs.z);
	};
	// End SF Conversions
}

#endif // !SRC_CONVERSIONS_H
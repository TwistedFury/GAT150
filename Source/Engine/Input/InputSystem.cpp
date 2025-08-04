#pragma once
#include "InputSystem.h"
#include <SDL3/SDL.h>

namespace swaws {
	/// <summary>
	/// Initializes the input system by capturing the current keyboard and mouse states.
	/// </summary>
	/// <returns>Returns true if the input system was successfully initialized.</returns>
	bool InputSystem::Initialize() 
	{
		int numKeys;
		const bool* keyboardState = SDL_GetKeyboardState(&numKeys);

		m_keyboardState.resize(numKeys);

		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
		m_prevKeyboardState = m_keyboardState;

		SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
		m_prevMousePosition = m_mousePosition;

		return true;
	}

	void InputSystem::Shutdown()
	{
		// 
	}

	/// <summary>
	/// Updates the current and previous states of the keyboard and mouse input devices.
	/// </summary>
	void InputSystem::Update()
	{
		// KEYBOARD
		m_prevKeyboardState = m_keyboardState;
		const bool* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		// MOUSE
		m_prevMousePosition = m_mousePosition;

		m_prevMouseButtonState = m_mouseButtonState;
		uint32_t mouseButtonState = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);

		m_mouseButtonState[(uint8_t)MouseButton::Left] = mouseButtonState && SDL_BUTTON_LMASK;
		m_mouseButtonState[(uint8_t)MouseButton::Middle] = mouseButtonState && SDL_BUTTON_MMASK;
		m_mouseButtonState[(uint8_t)MouseButton::Right] = mouseButtonState && SDL_BUTTON_RMASK;

	}
}
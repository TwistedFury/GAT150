#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>

namespace swaws {
	class Renderer
	{
	public:
		Renderer() = default;

		bool Initialize();
		void ShutDown();
		bool CreateWindow(const std::string& name, int width, int height);

		void Clear();
		void Present();

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t = 255);
		void SetColor(float r, float g, float b, float a = 1.0f);

		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(float x1, float y1);

		void DrawTexture(class Texture* texture, float x, float y);
		void DrawTexture(class Texture* texture, float x, float y, float rot, float scale = 1);

		int GetWindowWidth() const { return windowWidth; }
		int GetWindowHeight() const { return windowHeight; }

	private:
		friend class Texture;
		friend class Text; // Allows Text class to access private data
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		int windowWidth = 1280;
		int windowHeight = 1024;
	};
}
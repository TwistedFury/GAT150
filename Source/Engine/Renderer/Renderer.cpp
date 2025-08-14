#pragma once
#include "Renderer.h"
#include "Texture.h"

namespace swaws {
    /// <summary>
    /// Initializes the renderer by setting up SDL and SDL_ttf subsystems.
    /// </summary>
    /// <returns>true if initialization succeeds; false if an error occurs during SDL or TTF initialization.</returns>
    bool Renderer::Initialize()
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            Logger::Error("SDL_Init Error: {}", SDL_GetError());
            return false;
        }

        if (!TTF_Init()) {
            Logger::Error("TTF_Init Error: {}", SDL_GetError());
            return false;
        }
        return true;
    }

    /// <summary>
    /// Shuts down the renderer by destroying the SDL renderer and window, and quitting the SDL library.
    /// </summary>
    void Renderer::ShutDown()
    {
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    /// <summary>
    /// Creates a window and initializes the renderer using SDL.
    /// </summary>
    /// <param name="name">The title of the window.</param>
    /// <param name="width">The width of the window in pixels.</param>
    /// <param name="height">The height of the window in pixels.</param>
    /// <returns>True if the window and renderer were successfully created; false otherwise.</returns>
    bool Renderer::CreateWindow(const std::string& name, int width, int height, bool fullscreen)
    {
        m_window = SDL_CreateWindow(name.c_str(), width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
        if (m_window == nullptr) {
            Logger::Error("SDL_CreateWindow Error: {}", SDL_GetError());
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            Logger::Error("SDL_CreateRenderer Error: {}", SDL_GetError());
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        windowWidth = width;
        windowHeight = height;

        SDL_SetRenderLogicalPresentation(m_renderer, windowWidth, windowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

        return true;
    }

    /// <summary>
    /// Clears the current rendering target, filling it with the drawing color.
    /// </summary>
    void Renderer::Clear()
    {
        SDL_RenderClear(m_renderer);
    }

    /// <summary>
    /// Updates the screen with any rendering performed since the previous call.
    /// </summary>
    void Renderer::Present()
    {
        SDL_RenderPresent(m_renderer);
    }

    /// <summary>
    /// Sets the current drawing color for the renderer.
    /// </summary>
    /// <param name="r">The red component of the color (0-255).</param>
    /// <param name="g">The green component of the color (0-255).</param>
    /// <param name="b">The blue component of the color (0-255).</param>
    /// <param name="a">The alpha (transparency) component of the color (0-255).</param>
    void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    /// <summary>
    /// Sets the current drawing color for the renderer using RGBA values.
    /// </summary>
    /// <param name="r">The red component of the color (0.0 to 1.0).</param>
    /// <param name="g">The green component of the color (0.0 to 1.0).</param>
    /// <param name="b">The blue component of the color (0.0 to 1.0).</param>
    /// <param name="a">The alpha (transparency) component of the color (0.0 to 1.0).</param>
    void Renderer::SetColor(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
    }

    /// <summary>
    /// Draws a line between two points on the rendering surface.
    /// </summary>
    /// <param name="x1">The x-coordinate of the starting point.</param>
    /// <param name="y1">The y-coordinate of the starting point.</param>
    /// <param name="x2">The x-coordinate of the ending point.</param>
    /// <param name="y2">The y-coordinate of the ending point.</param>
    void Renderer::DrawLine(float x1, float y1, float x2, float y2)
    {
        SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }

    /// <summary>
    /// Draws a point at the specified coordinates using the renderer.
    /// </summary>
    /// <param name="x1">The x-coordinate of the point to draw.</param>
    /// <param name="y1">The y-coordinate of the point to draw.</param>
    void Renderer::DrawPoint(float x1, float y1)
    {
        SDL_RenderPoint(m_renderer, x1, y1);
    }

    void Renderer::DrawTexture(Texture& texture, float x, float y)
    {
        vec2 size = texture.GetSize();

        SDL_FRect destRect;
        destRect.w = size.x;
        destRect.h = size.y;
        destRect.x = x - (destRect.w * 0.5f);
        destRect.y = y - (destRect.h * 0.5f);

        SDL_RenderTexture(m_renderer, texture.m_texture, NULL, &destRect);
    }
    void Renderer::DrawTexture(Texture& texture, float x, float y, float rot, float scale)
    {
        vec2 size = texture.GetSize();

        SDL_FRect destRect;
        destRect.w = size.x * scale;
        destRect.h = size.y * scale;
        destRect.x = x - (destRect.w * 0.5f);
        destRect.y = y - (destRect.h * 0.5f);

        SDL_RenderTextureRotated(m_renderer, texture.m_texture, NULL, &destRect, rot, NULL, SDL_FLIP_NONE);
    }
}

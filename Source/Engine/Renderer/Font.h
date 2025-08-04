#pragma once
#include <string>
#include "Renderer.h"

struct TTF_Font;

namespace swaws
{
	class Font {
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* m_ttfFont{ nullptr };
	};
}
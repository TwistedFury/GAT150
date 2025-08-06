#pragma once
#include "Renderer.h"
#include "Resources/Resource.h"
#include <string>

struct TTF_Font;

namespace swaws
{
	class Font : public Resource
	{
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* m_ttfFont{ nullptr };
	};
}
#include "TextureAnimation.h"

namespace swaws
{
	bool TextureAnimation::Load(const std::string& filename, class Renderer& renderer) {
		// load json
		swaws::json::document_t document;
		if (!swaws::json::Load(filename, document)) {
			Logger::Error("Could not load TextureAnimation json {}", filename);
			return false;
		}
		// read texture name
		std::string textureName;
		JSON_READ(document, textureName);
		// load texture
		m_texture = Resources().Get<Texture>(textureName, renderer);
		if (!m_texture) {
			Logger::Error("Could not load texture in Texture Animation {}", textureName);
		}
		JSON_READ_NAME(document, "columns", m_columns);
		JSON_READ_NAME(document, "rows", m_rows);
		JSON_READ_NAME(document, "start_frame", m_startFrame);
		JSON_READ_NAME(document, "total_frames", m_totalFrames);
		JSON_READ_NAME(document, "frames_per_second", m_framesPerSecond);
		JSON_READ_NAME(document, "loop", m_loop);
		return true;
	}
	vec2 TextureAnimation::GetSize() const {
		vec2 size = m_texture->GetSize();
		return { size.x / m_columns, size.y / m_rows };
	}
	rect TextureAnimation::GetFrameRect(int frame) const
	{
		if (!IsValidFrame(frame)) {
			Logger::Warning("Frame is outside bounds {}/{}", frame, m_totalFrames);
			frame = 0;
		}
		rect frameRect;
		vec2 size = GetSize();
		frameRect.w = size.x;
		frameRect.h = size.y;
		frameRect.x = ((m_startFrame + frame) % m_columns) * frameRect.w;
		frameRect.y = ((m_startFrame + frame) / m_columns) * frameRect.h;
		return frameRect;
	}
}
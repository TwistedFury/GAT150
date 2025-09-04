#pragma once

namespace swaws 
{
	class Tilemap : public Resource 
	{
	public:
		struct Layer 
		{
			int height{ 0 };
			int width{ 0 };
			int scale{ 2 };
			bool hasCollision{ true };
			std::vector<uint32_t> data; // was std::vector<int>
			res_t<Texture> texture;
		};

	public:
		Tilemap() = default;
		~Tilemap() = default;

		bool Load(const std::string& filename, class Renderer& renderer);

		const std::vector<Layer>& GetLayers() const { return layers; }
		rect GetTextureRect(const Layer& layer, int tileId);
		vec2 GetPosition(const Layer& layer, int tileIndex);

	private:
		int tileheight{ 0 };
		int tilewidth{ 0 };

		std::vector<Layer> layers;
	};
}

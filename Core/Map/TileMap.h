#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <random>
#include "raylib.h"
#include "../System/SystemCore.h"

namespace MythicalRuins {

    enum class BiomeType {
        Ocean,
        Beach,
        Plains,
        Forest,
        Desert,
        Swamp,
        Mountains,
        Snow,
        Jungle,
        Savanna
    };

    enum class TileType {
        // Water
        DeepWater,
        ShallowWater,

        // Ground
        Sand,
        Grass,
        DarkGrass,
        Dirt,
        Stone,
        Snow,
        Ice,
        Mud,

        // Special
        Flowers,
        TallGrass,
        Cactus,
        DeadBush,

        Count
    };

    struct Tile {
        TileType Type = TileType::Grass;
        BiomeType Biome = BiomeType::Plains;
        float Elevation = 0.0f;
        float Moisture = 0.0f;
        float Temperature = 0.0f;
        bool BlocksMovement = false;
        bool BlocksVision = false;
        int TextureVariant = 0;
    };

    class PerlinNoise {
    public:
        explicit PerlinNoise(unsigned int seed = 0);

        float Noise(float x, float y) const;
        float FBM(float x, float y, int octaves = 4, float persistence = 0.5f, float lacunarity = 2.0f) const;

    private:
        std::vector<int> permutation;

        float Fade(float t) const;
        float Lerp(float a, float b, float t) const;
        float Grad(int hash, float x, float y) const;
    };

    // World generation configuration
    struct WorldGenConfig {
        unsigned int Seed = 12345;
        int ChunkSize = 16;
        float TileWidth = 64.0f;
        float TileHeight = 32.0f;

        // Noise scales
        float ElevationScale = 0.02f;
        float MoistureScale = 0.03f;
        float TemperatureScale = 0.015f;
        float DetailScale = 0.1f;

        // Elevation thresholds
        float DeepWaterLevel = -0.3f;
        float ShallowWaterLevel = -0.1f;
        float BeachLevel = 0.0f;
        float PlainsLevel = 0.3f;
        float HillLevel = 0.6f;
        float MountainLevel = 0.8f;

        // Initial generation size
        int InitialWidth = 100;
        int InitialHeight = 100;
    };

    class TileMap : public SystemCore {
    public:
        TileMap();
        ~TileMap() override = default;

        void OnStart() override;
        void OnUpdate() override;
        void OnDestroy() override;

    private:
    };

} // namespace MythicalRuins

#endif // TILEMAP_H
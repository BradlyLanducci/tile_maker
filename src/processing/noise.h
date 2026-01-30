#include <fast_noise_lite.h>
#include <unordered_map>

//-------------------------------------------------------------------------------------------------//

class Noise
{
public:
    enum class Type
    {
        VALUE,
        PERLIN,
        CELLULAR,
        SIMPLEX
    };

    Noise(Type type, float frequency, int seed);
    float get2D(int x, int y) const;

private:
    FastNoiseLite m_noise;
    const std::unordered_map<Type, FastNoiseLite::NoiseType> m_typeMap{
        { Type::VALUE,    FastNoiseLite::NoiseType::NoiseType_Value        },
        { Type::PERLIN,   FastNoiseLite::NoiseType::NoiseType_Perlin       },
        { Type::CELLULAR, FastNoiseLite::NoiseType::NoiseType_Cellular     },
        { Type::SIMPLEX,  FastNoiseLite::NoiseType::NoiseType_OpenSimplex2 }
    };
};

//-------------------------------------------------------------------------------------------------//

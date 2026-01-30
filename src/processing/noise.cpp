#include <processing/noise.h>

//-------------------------------------------------------------------------------------------------//

Noise::Noise(Type type, float frequency, int seed)
    : m_noise(seed)
{
    m_noise.SetNoiseType(m_typeMap.at(type));
    m_noise.SetFrequency(frequency);
}

//-------------------------------------------------------------------------------------------------//

float Noise::get2D(int x, int y) const
{
    return m_noise.GetNoise((float)x, (float)y);
}

//-------------------------------------------------------------------------------------------------//

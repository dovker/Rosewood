#pragma once
#include "rwpch.h"
#include <glm/glm.hpp>

#define NOISE_M1 1597334677U     //1719413*929
#define NOISE_M2 3812015801U     //140473*2467*11

namespace Rosewood {
    
    class Noise
    {
    public:
        static float Hash(glm::uvec2 st, int seed)
        {
            st *= glm::uvec2(NOISE_M1, NOISE_M2); 
            
            uint n = (st.x ^ st.y ^ seed) * NOISE_M1 ;
            
            return float(n) * (1.0f/float(0xffffffffU));
        }
        static float Perlin(glm::vec2 st, float seed)
        {
            glm::vec2 i = glm::floor(st);
            glm::vec2 f = glm::fract(st);

            // Four corners in 2D of a tile
            float a = Hash(i, seed);
            float b = Hash(i + glm::vec2(1.0f, 0.0f), seed);
            float c = Hash(i + glm::vec2(0.0f, 1.0f), seed);
            float d = Hash(i + glm::vec2(1.0f, 1.0f), seed);

            // Smooth Interpolation

            // Cubic Hermine Curve.  Same as SmoothStep()
            glm::vec2 u = f*f*(3.0f-2.0f*f);

            return glm::mix(a, b, u.x) +
                    (c - a) * u.y * (1.0f - u.x) +
                    (d - b) * u.x * u.y;
        }
        static float FBM(glm::vec2 st, int octaves, float amplitude, float seed)
        {
            // Initial values
            float value = 0.0f;
            //
            // Loop of octaves
            for (int i = 0; i < octaves; i++)
            {
                value += amplitude *
                Perlin(st, seed);
                st *= 2.0f;
                amplitude *= 0.5f;
            }
            return value;
        }
    };
}

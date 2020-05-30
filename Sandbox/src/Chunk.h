#ifndef CHUNK_H
#define CHUNK_H

#include <Rosewood.h>
#include "glm/glm.hpp"
#include "Map.h"

#define BLOCK_AIR 0
#define BLOCK_DIRT 1

#define CHUNK_SIZE 32
//class Map;

class Chunk
{
public:

	typedef unsigned int uint;
	uint data[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

	uint xPos = 0, zPos = 0;

	Chunk::Chunk() {
		
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					data[i][j][k] = BLOCK_DIRT;
				}
			}
		}
	}
	Chunk::~Chunk() {}


};

#endif
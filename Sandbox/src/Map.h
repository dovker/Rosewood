#ifndef MAP_H
#define MAP_H
#include <Rosewood.h>

#include "glm/glm.hpp"
#include "Chunk.h"


#define BLOCK_AIR 0
#define BLOCK_DIRT 1

#define CHUNK_SIZE 32
#define ARR_CHUNK_SIZE 31


class Map
{

public:
	typedef unsigned int uint;
	uint MapWidth = 1;
	uint MapHeight = 1;
	//std::vector<Chunk*> chunks;
	std::unordered_map<glm::ivec2, Chunk*> chunks;
	std::vector<Rosewood::Mesh> meshes;
	//Rosewood::Texture* Texture;


	Map::Map(int width, int height)
		: MapWidth((uint)width), MapHeight((uint)height)
	{
		GenerateMap();
	};

	void Map::GenerateMap()
	{
		chunks = std::unordered_map<glm::ivec2, Chunk*>(glm::ivec2(0), glm::ivec2(MapWidth, MapHeight));

		int iterator = 0;
		//chunks = Chunk[width * height];
		for (auto item : chunks)
		{
			Chunk* chunk = item.second;
			for (int i = 0; i < CHUNK_SIZE; i++)
			{
				for (int j = 0; j < CHUNK_SIZE; j++)
				{
					for (int k = 0; k < CHUNK_SIZE; k++)
					{
						chunk->data[i][j][k] = BLOCK_DIRT;
					}
				}
			}
			//chunk->xPos = iterator % MapWidth;
			//chunk->zPos = iterator / MapHeight;  
			chunk->xPos = item.first.x;
			chunk->zPos = item.first.y;
			GenerateMesh(chunk);
			RW_TRACE("Mesh Generated sucessfully");
			  // where "/" is an integer division
			iterator++;
		}
	}


	void GenerateMesh(Chunk* chunk)
	{
		uint xPos = chunk->xPos;
		uint zPos = chunk->zPos;
		std::vector<Rosewood::Vertex> vertices;
		std::vector<unsigned int> indices;
		//chunk->mesh = Rosewood::Mesh(texture);
		
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					uint B = chunk->data[i][j][k]; // current block
					
					uint Block_t = j == ARR_CHUNK_SIZE ? 0 : chunk->data[i][j + 1][k]; // Block top
					uint Block_b = j == 0 ? 0 : chunk->data[i][j - 1][k]; // Block bottom
					uint Block_l = GetBlock(glm::ivec3(xPos * ARR_CHUNK_SIZE - 1, j, zPos * ARR_CHUNK_SIZE + k));
					uint Block_r = GetBlock(glm::ivec3(xPos * ARR_CHUNK_SIZE + i + 1, j, zPos * ARR_CHUNK_SIZE + k));
					uint Block_f = GetBlock(glm::ivec3(xPos * ARR_CHUNK_SIZE + i, j, zPos * ARR_CHUNK_SIZE - 1)); // Block front
					uint Block_B = GetBlock(glm::ivec3(xPos * ARR_CHUNK_SIZE + i, j, zPos * ARR_CHUNK_SIZE + k + 1)); // Block back
					/*
					uint Block_t = j == CHUNK_SIZE - 1 ? 0 : chunk->data[i][j + 1][k]; // Block top
					uint Block_b = j == 0 ? 0 : chunk->data[i][j - 1][k]; // Block bottom
					uint Block_l = i == 0 ? 0 : chunk->data[i - 1][j][k]; // Block left
					uint Block_r = i == CHUNK_SIZE - 1 ? 0 : chunk->data[i + 1][j][k]; // Block right
					uint Block_f = k == 0 ? 0 : chunk->data[i][j][k - 1]; // Block front
					uint Block_B = k == CHUNK_SIZE - 1 ? 0 : chunk->data[i][j][k + 1]; // Block back
					*/
					bool Bt = Block_t != 0 ? false : true;
					bool Bb = Block_b != 0 ? false : true;
					bool Bl = Block_l != 0 ? false : true;
					bool Br = Block_r != 0 ? false : true;
					bool Bf = Block_f != 0 ? false : true;
					bool BB = Block_B != 0 ? false : true;
					
					glm::vec3 blockPos(xPos * CHUNK_SIZE + i, j, (zPos * CHUNK_SIZE + k));
					//RW_TRACE("Pos: {0}, {1}, {2}", blockPos.x, blockPos.y, blockPos.z);
					if (B != 0)
					{
					

						if (Bt) Rosewood::Mesh::AddQuad(&indices, &vertices, blockPos, Rosewood::Orientation::Up, glm::vec2(0.0f), glm::vec2(1.0f));
						if (Bb) Rosewood::Mesh::AddQuad(&indices, &vertices, blockPos, Rosewood::Orientation::Down, glm::vec2(0.0f), glm::vec2(1.0f));
						if (Bl) Rosewood::Mesh::AddQuad(&indices, &vertices, blockPos, Rosewood::Orientation::Left, glm::vec2(0.0f), glm::vec2(1.0f));
						if (Br) Rosewood::Mesh::AddQuad(&indices, &vertices, blockPos, Rosewood::Orientation::Right, glm::vec2(0.0f), glm::vec2(1.0f));
						if (Bf) Rosewood::Mesh::AddQuad(&indices, &vertices, blockPos, Rosewood::Orientation::Front, glm::vec2(0.0f), glm::vec2(1.0f));
						if (BB) Rosewood::Mesh::AddQuad(&indices, &vertices, blockPos, Rosewood::Orientation::Back, glm::vec2(0.0f), glm::vec2(1.0f));
						
					}//dunno if I should put a - here
				}
			}
			
		}
		/*
		mesh.AddQuad(glm::vec3(1 + xPos * CHUNK_SIZE, 1, 1 + zPos * CHUNK_SIZE), Rosewood::Orientation::Down, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(1 + xPos * CHUNK_SIZE, 1, 1 + zPos * CHUNK_SIZE), Rosewood::Orientation::Up, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(1 + xPos * CHUNK_SIZE, 1, 1 + zPos * CHUNK_SIZE), Rosewood::Orientation::Left, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(1 + xPos * CHUNK_SIZE, 1, 1 + zPos * CHUNK_SIZE), Rosewood::Orientation::Right, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(1 + xPos * CHUNK_SIZE, 1, 1 + zPos * CHUNK_SIZE), Rosewood::Orientation::Back, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(1 + xPos * CHUNK_SIZE, 1, 1 + zPos * CHUNK_SIZE), Rosewood::Orientation::Front, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		*/
		Rosewood::Mesh mesh(vertices, indices, nullptr);
		meshes.push_back(mesh);
		//mesh = NULL;
	}
	

	bool Map::outOfBounds(glm::ivec3 pos)
	{
		return pos.x < 0 || pos.x > CHUNK_SIZE || pos.y < 0 || pos.y > CHUNK_SIZE || pos.z < 0 || pos.z > CHUNK_SIZE;
	}

	void Map::SetBlock(glm::vec3 pos, uint block) {};
	uint Map::GetBlock(glm::ivec3 pos)
	{
		pos = glm::max(pos, glm::ivec3(0));
		int chunkIndex = (pos.z / CHUNK_SIZE) * MapWidth + (pos.x / CHUNK_SIZE);
		Chunk* chunk = chunks[glm::ivec2(pos.x/CHUNK_SIZE, pos.z/CHUNK_SIZE)];
		if (outOfBounds(glm::ivec3(pos.x % CHUNK_SIZE, pos.y % CHUNK_SIZE, pos.z % CHUNK_SIZE)))
		{
			return 0;
		}
		else
		{
			return chunk->data[pos.x % CHUNK_SIZE][pos.y % CHUNK_SIZE][pos.z % CHUNK_SIZE];
		}
	}

	void Map::Draw(Rosewood::Texture* tex)
	{
		for (Rosewood::Mesh mesh : meshes)
		{
			//chunks.at(i)->mesh.Draw();
			mesh.texture = tex;
			mesh.Draw();
		}
	}

};

#endif
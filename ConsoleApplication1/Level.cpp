#include "stdafx.h"
#include "Level.h"
#include "graphics.h"
#include <SDL2/SDL.h>
#include "Globals.h"
#include "tinyxml2.h"
#include "RectangleCollision.h"
#include <sstream>
#include <algorithm>
#include <cmath>
#include "Camera.h"

using namespace tinyxml2;


Level::Level()
{
}

Level::Level(string mapName, Vector2 spawnPoint, Graphics & graphics) : mapName_(mapName), spawnPoint_(spawnPoint), size_(Vector2(0, 0))
{
	LoadMap(mapName, graphics);
}


Level::~Level()
{
}

void Level::Update()
{
}

void Level::Draw(Graphics & graphics, Camera &camera)
{
	int c = 0;
	for (auto i = 0; i < tileList_.size(); ++i)
	{
		auto position = tileList_[i].GetPosition();

		if (AreColliding(SDL_Rect{ position.x, position.y, tileSize_.x, tileSize_.y }, camera.GetRectangle()))
		{
			c++;
			tileList_[i].Draw(graphics, camera);
		}
	}
	c = 0;
}

void Level::LoadMap(string mapName, Graphics & graphics)
{
	// Parse .tmx file
	XMLDocument doc;
	
	stringstream stringStream;
	stringStream << "Content/Maps/" << mapName << ".tmx";

	doc.LoadFile((stringStream.str().c_str()));

	XMLElement* mapNode = doc.FirstChildElement("map");

	// Get map size
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	size_ = Vector2(width, height);

	// Get Tile size
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	tileSize_ = Vector2(tileWidth, tileHeight);

	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != nullptr)
	{
		while (pTileset)
		{
			int firstGid;
			const char* source = pTileset->Attribute("source");

			stringStream.str(""); 
			stringStream << source;

			pTileset->QueryIntAttribute("firstgid", &firstGid);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadImage(stringStream.str()));

			tileSets_.push_back(Tileset(texture, firstGid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != nullptr)
	{
		while (pLayer)
		{
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != nullptr)
			{
				while (pData)
				{
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != nullptr)
					{
						int tileCounter = 0;
						while (pTile)
						{
							if (pTile->IntAttribute("gid") == 0)
							{
								tileCounter++;

								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
								{
									break;
								}
							}

							int gid = pTile->IntAttribute("gid");
							Tileset tileset;

							for (auto i = 0; i < tileSets_.size(); ++i)
							{
								if (tileSets_[i].firstGid <= gid)
								{
									tileset = tileSets_[i];
									break;
								}
							}

							if (tileset.firstGid == -1)
							{
								tileCounter++;

								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
								{
									break;
								}
							}

							int x = 0, y = 0;
							x = tileCounter % width;
							x *= tileWidth;
							y += tileHeight * (tileCounter / width);
							Vector2 finalTilePosition = Vector2(x, y);

							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tileset.texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							int tsX = gid % (tilesetWidth / tileWidth) - 1;
							tsX *= tileWidth;

							int tsY = 0;
							int amount = gid / (tilesetWidth / tileWidth);
							tsY = tileHeight * amount;
							Vector2 finalTilesetPosition = Vector2(tsX, tsY);

							Tile tile(tileset.texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
							tileList_.push_back(tile);

							tileCounter++;
							pTile = pTile->NextSiblingElement("tile");
						}
					}
						
					pData = pData->NextSiblingElement("data");
				}
			}

			pLayer = pLayer->NextSiblingElement("layer");
		}
	}
}

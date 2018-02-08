#include "stdafx.h"
#include "Level.h"
#include "graphics.h"
#include <SDL2/SDL.h>
#include "Globals.h"
#include "tinyxml2.h"
#include "RectangleCollision.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "Camera.h"
#include <Box2D\Box2D.h>

using namespace tinyxml2;


Level::Level()
{
}

Level::Level(string mapName, Vector2 spawnPoint, Graphics & graphics, b2World &world) : mapName_(mapName), spawnPoint_(spawnPoint), size_(Vector2(0, 0))
{
	LoadMap(mapName, graphics, world);
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

void Level::LoadMap(string mapName, Graphics & graphics, b2World &world)
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

	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
	auto numObj = 0;
	if (pObjectGroup != nullptr)
	{
		b2PolygonShape polyShape;
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &polyShape;
		fixtureDef.density = 1;

		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(0, 0);
		b2Body* staticBody = world.CreateBody(&bodyDef);

		while (pObjectGroup)
		{
			XMLElement* pObject = pObjectGroup->FirstChildElement("object");
			if (pObject != nullptr)
			{
				float objHeight, objWidth, xPos, yPos;

				while (pObject)
				{
					xPos = pObject->FloatAttribute("x") / Globals::PIXELS_PER_METER;
					yPos = pObject->FloatAttribute("y") / Globals::PIXELS_PER_METER;

					XMLElement* pPoly = pObject->FirstChildElement("polygon");
					if (pPoly != nullptr)
					{
						while (pPoly)
						{
							vector<b2Vec2> pointList;
							stringstream points(pPoly->Attribute("points"));

							while (points.good())
							{
								string point;
								getline(points, point, ' ');

								auto commaIndex = point.find(',');
								auto x = xPos + (std::stof(point.substr(0, commaIndex)) / Globals::PIXELS_PER_METER);
								auto y = yPos + (std::stof(point.substr(commaIndex + 1, point.size() - 1)) / Globals::PIXELS_PER_METER);
								pointList.push_back(b2Vec2(x, y));
							}

							polyShape.Set(&pointList[0], pointList.size());

							pPoly = pPoly->NextSiblingElement("polygon");
						}
					}
					else
					{
						objHeight = pObject->FloatAttribute("height") / Globals::PIXELS_PER_METER;
						objWidth = pObject->FloatAttribute("width") / Globals::PIXELS_PER_METER;
						b2Vec2 center = b2Vec2(xPos + objWidth / 2, yPos + objHeight / 2);

						polyShape.SetAsBox(objWidth / 2, objHeight / 2, center, 0);
						numObj++;
					}

					staticBody->CreateFixture(&fixtureDef);
					pObject = pObject->NextSiblingElement("object");
				}
			}

			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}
}

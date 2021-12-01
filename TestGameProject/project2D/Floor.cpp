#include "Floor.h"
#include "FloorHeap.h"
#include <cmath>
#include "ResourceManager.h"


Floor::Floor(Vector2 v2Pos, int nWidth, int nHeight)
{
	//calculate number of tiles needed
	auto nTileCount = nWidth * nHeight;
	m_v2StartPos = v2Pos;

	m_nHeight = nHeight;
	m_nWidth = nWidth;


	//reserve that much space to avoid mass resizing
	m_apTiles.reserve(nTileCount);

	m_pOpenList = new FloorHeap();

	m_pTileTexture = new aie::Texture("Textures/Grass.jpg");

	for (int x = 0; x < nWidth; x++)
	{
		for (int y = 0; y < nHeight; y++)
		{
			Vector2 v2Tile = v2Pos;
			v2Tile.x = v2Tile.x + (m_pTileTexture->getWidth() * x);
			v2Tile.y = v2Tile.y + (m_pTileTexture->getHeight() * y);


			m_apTiles.push_back(new Tile(v2Tile,m_pTileTexture));

			


			auto nIndex = x * nHeight + y;

			//Up and down connections
			if(y > 0)
			{
				m_apTiles[nIndex]->AddNeighbour(m_apTiles[nIndex - 1], Tile::Connection::Down);
				m_apTiles[nIndex - 1]->AddNeighbour(m_apTiles[nIndex], Tile::Connection::Top);
			}

			//Left and Right Connections
			if (x > 0)
			{
				m_apTiles[nIndex]->AddNeighbour(m_apTiles[nIndex - nHeight], Tile::Connection::Left);
				m_apTiles[nIndex - nHeight]->AddNeighbour(m_apTiles[nIndex],Tile::Connection::Right);

				//Top right / Bottom Left
				if (y > 0)
				{
					m_apTiles[nIndex]->AddNeighbour(m_apTiles[nIndex - nHeight - 1], Tile::Connection::BottomLeft);
					m_apTiles[nIndex - nHeight - 1]->AddNeighbour(m_apTiles[nIndex], Tile::Connection::TopRight);
				}

				//Top Left / Bottom Right
				if (y < nHeight - 2) // nHeight is number of tiles high, -1 because indexes start at 0, and -1 so that this doesn't go out back another row by mistake
				{
					m_apTiles[nIndex]->AddNeighbour(m_apTiles[nIndex - nHeight + 1], Tile::Connection::TopLeft);
					m_apTiles[nIndex - nHeight + 1]->AddNeighbour(m_apTiles[nIndex], Tile::Connection::BottomRight);
				}

			}
		}
	}

}

Floor::~Floor()
{
	for (int i = 0; i < m_apTiles.size(); i++)
	{
		if (m_apTiles[i])
		{
			delete m_apTiles[i];
		}
	}

	if (m_pTileTexture)
	{
		delete m_pTileTexture;
		m_pTileTexture = nullptr;
	}

	if (m_pOpenList)
	{
		delete m_pOpenList;
		m_pOpenList = nullptr;
	}

}

void Floor::Update(float fDeltaTime)
{
	for (int i = 0; i < m_apTiles.size(); i++)
	{
		if (m_apTiles[i])
		{
			//Update
			m_apTiles[i]->Update(fDeltaTime);
		}
	}
}

void Floor::Draw(aie::Renderer2D* pRenderer)
{
	for (int i = 0; i < m_apTiles.size(); i++)
	{
		if (m_apTiles[i])
		{
			//Draw
			m_apTiles[i]->Draw(pRenderer);
		}
	}

}

void Floor::GetPath(Vector2 v2From, Vector2 v2To, Path& rav2Path)
{
	//clear the lists

	
	m_pOpenList->Clear();
	
	m_aClosedList.clear();
	rav2Path.clear();

	//find the tiles that they are on
	auto pFrom = PosToTile(v2From);
	auto pTo = PosToTile(v2To);
	
	//if both exist
	if (pFrom && pTo)
	{
		//setup a pointer to iterate through the tiles
		Tile* pTile;

		m_pOpenList->Add(pFrom);

		//while the pointer actually contains something
		while (m_pOpenList->Size())
		{
		
			pTile = m_pOpenList->GetTop();

			//if the current tile is the tile we are trying to find, then exit, we've found the path
			if (pTile == pTo)
			{
				break;
			}

			if (!pTile->GetOn())
			{
				continue;
			}

			//Check if it exists
			if (m_aClosedList[pTile])
			{
				continue;
			}

			//Add the tile to the closed list
			m_aClosedList.insert_or_assign(pTile,true);

			//get a reference to the array of neighbours
			auto& rapNeigh = pTile->GetNeighours();

			

			//for every neighbour
			for (int i = 0; i < rapNeigh.size(); i++)
			{


				auto pNeighbour = static_cast<Tile*>(rapNeigh[i]);

				if (!pNeighbour)
				{
					continue;
				}

				if (m_aClosedList[pNeighbour])
				{
					continue;
				}


				//set up Gscore -> distance from start tile to this tile(pNeighbour) -> this code added distance from pTile to pNeighbour
				//Use magnitudeSq because it will have the same effect, however it is way faster because it doesn't have to get the square root

				Vector2 v2ToNeighbour = pTile->GetPosition() - pNeighbour->GetPosition();
				

				auto fGScore = v2ToNeighbour.magnitudeSq();

			
				//Add GScore of previous node
				if(pTile->GetPrevious())
				{
					fGScore += pTile->GetPrevious()->GetGScore();
				}



				//setup Hscore

				Vector2 v2Heuristic = pNeighbour->GetPosition() - pTo->GetPosition();

				



				//if it has already been added to the openlist
				if (m_pOpenList->Find(pNeighbour))
				{
					//and the new gScore is less than its current GSCore
					if (fGScore < pNeighbour->GetGScore())
					{
						pNeighbour->SetGScore(fGScore);
						pNeighbour->SetHScore(v2Heuristic.magnitudeSq());
						pNeighbour->SetPrevious(pTile);
					}
				}
				else
				{

					pNeighbour->SetGScore(fGScore);
					pNeighbour->SetHScore(v2Heuristic.magnitudeSq());
					pNeighbour->SetPrevious(pTile);


					//Add neighbour to the openlist
					m_pOpenList->Add(pNeighbour);

				}

				



			}

			

		}


			//if pTile isn't null than path has been found
			while (pTile)
			{
				if (pTile == pFrom)
				{
					return;
				}

				rav2Path.push_front(pTile->GetPosition());

				pTile = pTile->GetPrevious();

				
			}

	}
}


Tile* Floor::PosToTile(Vector2 v2Position)
{

	//Vector from start position to the needed tile
	Vector2 v2ToPosition = v2Position - m_v2StartPos;


	if (v2ToPosition.x < -32 || v2ToPosition.y < -32)
	{
		return nullptr;
	}

	//    see how many times you can go across and then round down to nearest number, then convert it to an int
	auto nX = static_cast<int>(roundf( v2ToPosition.x / m_pTileTexture->getWidth()));
	

	auto nY = static_cast<int>(roundf(v2ToPosition.y / m_pTileTexture->getHeight()));


	//if they aren't negative
	if(nX >= 0 && nY >= 0)
	{
		auto nIndex = (m_nHeight * nX) + nY;


		if (nIndex > -1 && nIndex < m_apTiles.size())
		{
			return m_apTiles[nIndex];
		}

	}

	return nullptr;
}

#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Engine.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState(){}

void TitleState::Enter()
{
	
}

void TitleState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_N))
	{
		
		STMA::ChangeState( new GameState() );
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	
}

PauseState::PauseState(){}

void PauseState::Enter()
{
	
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
		STMA::PopState();
}

void PauseState::Render()
{
	// First render the GameState.
	STMA::GetStates().front()->Render();
	// Now render the rest of PauseState.
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 255, 128);
	SDL_Rect rect = { 255, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	State::Render();
}

void PauseState::Exit()
{
	
}

void GameState::ClearTurrets() // also can be use to clear the bullets
{
	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		delete m_turrets[i];
		m_turrets[i] = nullptr;


	}
	m_turrets.clear();
	m_turrets.shrink_to_fit();

	// you can assimilate some parts of this code for deleting bullets and enemies
}

GameState::GameState():m_spawnCtr(0) {}

void GameState::Enter()
{
	TEMA::Load("Img/Turret.png", "turret");
	TEMA::Load("Img/Enemies.png", "enemy");
	s_enemies.push_back(new Enemy({ 512, -200, 40, 57 }));
	// Create the DOM and load the XML file.
	XMLDocument xmlDoc; // create the DOM
	xmlDoc.LoadFile("Turrets2.xml");
	XMLNode* pRoot = xmlDoc.FirstChild();
	// Iterate through all turrets in the vector 

	//XMLElement* pElement = pRoot->FirstChildElement("Turret");
	//while (pElement != nullptr) 	// Iterate through the Turret elements in the file and push_back new Turrets into the m_turrets vector.
	//{
	//	SDL_Rect dst = { pElement->IntAttribute("x"), pElement->IntAttribute("y"),100,100 }; 	// keep the width and height as 100 
	//	m_turrets.push_back(new Turret(dst));
	//	pElement = pElement->NextSiblingElement("Turret");
	//}
}

void GameState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState());
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_T))
	{
		m_turrets.push_back(new Turret({ 50,618,100,100 }));
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_C)) // Press C to clear the turrets 
	{
		ClearTurrets();
	}
	if (m_spawnCtr++ % 180 == 0) // every 3s spawn a new enemy
		s_enemies.push_back(new Enemy({ rand() % (1024 - 40), -57, 40, 57 }));
	for (unsigned i = 0; i < m_turrets.size(); i++)
		m_turrets[i]->Update();
	for (unsigned i = 0; i < s_enemies.size(); i++)
		s_enemies[i]->Update();
	for (unsigned i = 0; i < s_bullets.size(); i++)
		s_bullets[i]->Update();

	// Cleanup bullets and enemies that go off screen.
	// if bullet goes off screen (four bounds checks)
	for (unsigned i = 0; i < s_bullets.size(); i++)
	{
		if (s_bullets[i]->deleteBullets() == true)
		{
			//s_bullets[i]->Update();
			std::cout << "Okey";

			//s_bullets[i] = 0;
			//delete s_bullets[i];

		}
	}
	// if enemies off screen
	for (unsigned i = 0; i < s_enemies.size(); i++)
	{
	if (s_enemies[i]->deleteEnemies() == true)
{
		/*s_enemies[i]->Update();
		delete s_enemies[i];
		s_enemies[i] = nullptr;
		s_enemies.shrink_to_fit();*/
		std::cout << " enemies goes off screen";
	}
	}

	// if ( position of bullets out of boder or colliding with enemies

	// 
			// or
			// if deleteMe of bullet is true
				// delete s_bullets[i]
				// set s_bullets[i] to nullptr
	
		// for all enemies, similar to above
	for (unsigned i = 0; i < s_bullets.size(); i++)
	{ 
		for (unsigned i = 0; i < s_enemies.size(); i++)
		{
			//if (COMA::AABBCheck(s_enemies[i]->m_dstEnemy, s_bullets[i]->m_dst  ))

			
				//std::cout << "Colliding";
			
			//{
			//	delete s_enemies[i];
			//	s_enemies[i] = nullptr;
			//	delete s_bullets[i];
			//	s_bullets[i] = nullptr;
			// 	s_enemies.clear();
			//s_enemies.shrink_to_fit();
			// 	s_bullets.clear();
			//s_bullets.shrink_to_fit();
			//	std::cout << "ok ";
			//}
		}
	}
	// Check for collisions with bullets and enemies.
	
		// for all bullets
			// for all enemies
				// check collision using AABB Check with SDL_Rect and SDL_FRect
	// if (COMA::AABBCheck(//SDL RECT, SDL_FRect))
	//then colliding and do the thing 


}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	for (unsigned i = 0; i < m_turrets.size(); i++)
		m_turrets[i]->Render();
	for (unsigned i = 0; i < s_enemies.size(); i++)
		s_enemies[i]->Render();
	for (unsigned i = 0; i < s_bullets.size(); i++)
		s_bullets[i]->Render();

	SDL_Rect spawnBox = { 50, 618, 100, 100 };
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &spawnBox);

	// This code below prevents SDL_RenderPresent from running twice in one frame.
	if ( dynamic_cast<GameState*>( STMA::GetStates().back() ) ) // If current state is GameState.
		State::Render();
}

void GameState::Exit()
{
	// You can clear all children of the root node by calling .DeleteChildren(); and this will essentially clear the DOM.
	// Iterate through all the turrets and save their positions as child elements of the root node in the DOM.
	// iterate through all turrets in the vector 
	XMLDocument xmlDoc; // create the DOM
	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		XMLNode* pRoot = xmlDoc.NewElement("Root");
		XMLElement* pElement = xmlDoc.NewElement("Turret");
		pElement->SetAttribute("x", m_turrets[i]->GetRect().x);
		pElement->SetAttribute("y", m_turrets[i]->GetRect().y);
		pRoot->InsertEndChild(pElement);
	}
	// Make sure to save to the XML file.
	xmlDoc.SaveFile("Turrents2.xml");

	ClearTurrets(); //Deallocate all turrets , then all other objects.
	for (unsigned i = 0; i < s_enemies.size(); i++)
	{
		delete s_enemies[i];
		s_enemies[i] = nullptr;
	}
	s_enemies.clear();
	s_enemies.shrink_to_fit();
	for (unsigned i = 0; i < s_bullets.size(); i++)
	{
		delete s_bullets[i];
		s_bullets[i] = nullptr;
	}
	s_bullets.clear();
	s_bullets.shrink_to_fit();
}

void GameState::Resume()
{
	
}

// This is how static properties are allocated.
std::vector<Bullet*> GameState::s_bullets;
std::vector<Enemy*> GameState::s_enemies;
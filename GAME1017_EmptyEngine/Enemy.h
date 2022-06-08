#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SDL.h>

class Enemy
{
private:
	SDL_Rect m_src;// Note just an int based SDL_Rect for dest rectangle
	int m_speed;
	int m_hits; // Maybe after 4 hits, the enemy is destroyed.
public:
	Enemy(SDL_Rect dst);
	void Update();
	void Render();
	SDL_Point GetPos() const { return {m_dstEnemy.x + m_dstEnemy.w/2, m_dstEnemy.y + m_dstEnemy.h/2}; }
	int& Hits() { return m_hits; } // Getter and setter.
	bool deleteEnemies ();

	SDL_Rect m_dstEnemy;
};

#endif
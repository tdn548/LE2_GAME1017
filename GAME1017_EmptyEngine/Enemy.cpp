#include "Enemy.h"
#include "Engine.h"
#include "TextureManager.h"
#include "EventManager.h"

Enemy::Enemy(SDL_Rect dst) :m_dstEnemy(dst), m_src({ 80,0,40,57 }), m_speed(1) 
{
	m_dstEnemy = dst;
}


void Enemy::Update()
{
	m_dstEnemy.y += m_speed;
	deleteEnemies();
}

void Enemy::Render()
{
	SDL_RenderCopyEx(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemy"), &m_src, &m_dstEnemy, 180.0, NULL, SDL_FLIP_NONE);
}

bool Enemy::deleteEnemies()
{
	if (m_dstEnemy.y + 57 > 700)
	return true;
}

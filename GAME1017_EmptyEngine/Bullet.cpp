#include "Bullet.h"
#include "Engine.h"

Bullet::Bullet(SDL_FRect dst, double dx, double dy):m_dst(dst), m_dx(dx), m_dy(dy) 
{ 
	m_dst = dst;
}

void Bullet::Update()
{
	m_dst.x += m_dx;
	m_dst.y += m_dy;
	// if( ( m_dst.x < 0 ) || ( m_dst.x + 4 > 1024 ) )
	//{
	//	 deleteBullets = true;
	//}
	//if ((m_dst.y < 0) || (m_dst.y + 4 > 680))
	//{
	//	deleteBullets = true;
	//}
	//Optional method of cleaning bullets
	// if bullet goes off screen (four bounds checks)
	//  flip deleteMe flag to true then in states cpp 
				// delete s_bullets[i]
				// set s_bullets[i] to nullptr
}

void Bullet::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 240, 255, 0, 255);
	SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_dst);
}

bool Bullet::deleteBullets()
{
	 if( ( m_dst.x < 0 ) || ( m_dst.x + 4 > 1024 ) )
{
	 return true;
}
if ((m_dst.y < 0) || (m_dst.y + 4 > 680))
{
	return true;
}
}

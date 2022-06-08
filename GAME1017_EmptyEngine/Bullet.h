#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include <SDL.h>

class Bullet
{
private:
	double m_dx, m_dy;


public:
	Bullet(SDL_FRect dst, double dx, double dy);
	void Update();
	void Render();
	// bool deleteBullets; if the bullets off screen delete it // flag that will let the program know we can delete it 
	bool deleteBullets();
	SDL_FRect m_dst;


};

#endif
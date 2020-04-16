#include "Falcon.h"

#include <iostream>
#include <ostream>


void Falcon::Update()
{
	SrcRect.w = 64;
	SrcRect.h = 64;
	SrcRect.x = 0;
	SrcRect.y = 0;

	DestRect.w = SrcRect.w;
	DestRect.h = SrcRect.h;
	//DestRect.x = xpos;
	//DestRect.y = ypos;

	FalconBulletInterval++;
}
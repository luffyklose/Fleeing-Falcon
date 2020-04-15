#include "ScoreStar.h"

const int STARSPEEDX = 1;
const int STARSPEEDY = 1;
bool StarHorDirX = true;
bool StarHorDirY = true;

ScoreStar::ScoreStar(const char* TextureSheet, int x, int y) :GameObject(TextureSheet, x, y)
{
	tag = "ScoreStar";
	SrcRect.w = 32;
	SrcRect.h = 32;
	SrcRect.x = 0;
	SrcRect.y = 0;

	DestRect.w = SrcRect.w;
	DestRect.h = SrcRect.h;
}

void ScoreStar::Update()
{
	//飞机碰到边缘改变飞行方向
	if (DestRect.x <= 0 || DestRect.x >= 736)
	{
		StarHorDirX = !StarHorDirX;
		//std::cout << "改变横向飞行方向!\n"<<DeathStarHorDir;
	}
	if (DestRect.y <= 0 || DestRect.y >= 576)
	{
		StarHorDirY = !StarHorDirY;
	}

	//根据飞行方向进行移动
	switch (StarHorDirX)
	{
	case true:
		DestRect.x += STARSPEEDX;
		//std::cout << "向右飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
		break;
	case false:
		DestRect.x -= STARSPEEDX;
		//std::cout << "向左飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
		break;
	default:
		break;
	}

	switch (StarHorDirY)
	{
	case true:
		DestRect.y -= STARSPEEDY;
		//std::cout << "向上飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
		break;
	case false:
		DestRect.y += STARSPEEDY;
		//std::cout << "向下飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
		break;
	default:
		break;
	}
}
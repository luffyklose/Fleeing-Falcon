#pragma once
#include"GameObject.h"

class ScoreStar:public GameObject
{
public:
	ScoreStar(const char* TextureSheet, int x, int y) ;

	void Update();

private:
	const int SCORE = 1;
};

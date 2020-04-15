#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* TextureSheet,int x,int y) {
	ObjTexture = TextureManager::LoadTexture(TextureSheet);

	xpos = x;
	ypos = y;
	DestRect.x = xpos;
	DestRect.y = ypos;
	isActive = true;
}

GameObject::~GameObject() {

}

void GameObject::Render() {
	//SDL_RenderCopy(Game::pRenderer, ObjTexture, &SrcRect, &DestRect);
	TextureManager::Draw(ObjTexture, SrcRect, DestRect);
}

void GameObject::Move(int x,int y)
{
	DestRect.x += x;
	DestRect.y += y;
}

void GameObject::Destroy()
{
	SDL_Rect TempRect = DestRect;
	SDL_DestroyTexture(ObjTexture);
	AniManager::Instance()->AddSmoke(Game::pRenderer, TempRect);
}


bool GameObject::isCollidingWith(const GameObject& other)
{
	int otherXMin = other.DestRect.x;
	int ourXMin = DestRect.x;

	int otherXMax = other.DestRect.x + other.DestRect.w;
	int ourXMax = DestRect.x + DestRect.w;

	bool overlapX = ourXMin < otherXMax && ourXMax > otherXMin;

	int otherYMin = other.DestRect.y;
	int ourYMin = DestRect.y;

	int otherYMax = other.DestRect.y + other.DestRect.h;
	int ourYMax = DestRect.y + DestRect.h;

	bool overlapY = ourYMin < otherYMax && ourYMax > otherYMin;

	if(overlapX==true&&overlapY==true)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void GameObject::setActive(bool NewStatus)
{
	isActive = NewStatus;
}

bool GameObject::isAtScreen() const
{
	if(DestRect.x>800&&DestRect.x<0&&DestRect.y>640&&DestRect.y<0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

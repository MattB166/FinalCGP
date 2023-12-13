#pragma once
#include "SDL.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"
#include "Vector2.h"
class GameObject
{

public: 
	GameObject();
	GameObject(SDL_Texture* texture);
 

	
	Vector2 Pos;	
	float m_w = 32;
	float m_h = 32;
	float rotation = 0;
	SDL_Texture* m_texture = nullptr;
	SDL_Renderer* renderer;
	BoxCollider boxCollider;
	virtual void Draw(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer);
	virtual void Destroy();
	void Rotate(float angle);
	bool isAnimated = false; 
	int animPixelHeight = 16;
	int animPixelWidth = 16;
	int animState = 0;
	int animFrames = 1;
	float timeInAnimationState = 0;
	float animationSpeed = 1; 
};


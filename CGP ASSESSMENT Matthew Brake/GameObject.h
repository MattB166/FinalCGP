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
 

	float m_x = 0; ///going to be obsolete when vector class complete 
	float m_y = 0;
	Vector2 Pos;	
	float m_w = 32;
	float m_h = 32;
	SDL_Texture* m_texture = nullptr;
	SDL_Renderer* renderer;
	BoxCollider boxCollider;
	virtual void Draw(SDL_Renderer* renderer, float CameraX, float CameraY);
	virtual void Destroy();
	bool isAnimated = false; 
	int animPixelHeight = 16;
	int animPixelWidth = 16;
	int animState = 0;
	int animFrames = 1;
	float timeInAnimationState = 0;
	float animationSpeed = 1; 
};


#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(SDL_Texture* texture)
{
	m_texture = texture;
}

 void GameObject::Draw(SDL_Renderer* renderer, float CameraX, float CameraY)
{
	 SDL_Rect srcRect;
	 if (isAnimated)
	 {
		 int currentFrameIndex = (int)(timeInAnimationState * animationSpeed) % animFrames;
		 srcRect = { currentFrameIndex * animPixelWidth, animState * animPixelHeight, animPixelWidth, animPixelHeight };
	 }
	 SDL_Rect dstRect{ m_x- CameraX,m_y-CameraY,m_w,m_h };
	 SDL_RenderCopy(renderer, m_texture, isAnimated ? &srcRect : NULL, &dstRect);
}

 void GameObject::Destroy()
 {
	 if (m_texture != nullptr)
	 {
		 SDL_DestroyTexture(m_texture);
		 m_texture = nullptr;

	 }
 }

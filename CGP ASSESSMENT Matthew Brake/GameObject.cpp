#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(SDL_Texture* texture)
{
	m_texture = texture;
}

 void GameObject::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect{ m_x,m_y,m_w,m_h };
	SDL_RenderCopy(renderer, m_texture, NULL, &dstRect);
}

 void GameObject::Destroy()
 {
	 if (m_texture != nullptr)
	 {
		 SDL_DestroyTexture(m_texture);
		 m_texture = nullptr;
	 }
 }

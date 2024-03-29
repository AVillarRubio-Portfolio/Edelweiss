#include "Texture.h"
#include "Camera.h"

unique_ptr<Texture> Texture::s_pInstance = nullptr;

Texture::Texture() :
		texture_(nullptr), width_(0), height_(0) {
	zoom = Camera::Instance()->getZoom();
}

Texture::Texture(SDL_Renderer* renderer, std::string fileName) :
		texture_(nullptr), width_(0), height_(0) {
	loadFromImg(renderer, fileName);
	zoom = Camera::Instance()->getZoom();
}

Texture::Texture(SDL_Renderer* renderer, std::string text, const Font& font,
		const SDL_Color color) :
		texture_(nullptr), width_(0), height_(0) {
	loadFromText(renderer, text, font, color);
	zoom = Camera::Instance()->getZoom();
}

Texture::~Texture() {
	close();
}

int Texture::getWidth() {
	return width_;
}

int Texture::getHeight() {
	return height_;
}

void Texture::close() {
	if (texture_ != nullptr) {
		SDL_DestroyTexture(texture_); // delete current texture
		texture_ = nullptr;
		width_ = 0;
		height_ = 0;
	}
}

bool Texture::loadFromImg(SDL_Renderer* renderer, std::string fileName) {
	SDL_Surface* surface = IMG_Load(fileName.c_str());

	if (surface != nullptr) {
		close(); // destroy current texture
		texture_ = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture_ != nullptr) {
			width_ = surface->w;
			height_ = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	return texture_ != nullptr;
}

bool Texture::loadFromText(SDL_Renderer* renderer, std::string text, const Font& font, const SDL_Color color) {
	SDL_Surface* textSurface = font.renderText(text, color);
	if (textSurface != nullptr) {
		close();
		texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture_ != nullptr) {
			width_ = textSurface->w;
			height_ = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return texture_ != nullptr;
}

void Texture::render(SDL_Renderer* renderer, int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = width_;
	dest.h = height_;
	render(renderer, dest);
}

void Texture::render(SDL_Renderer* renderer, const SDL_Rect& dest, SDL_Rect* clip) const {
	if (texture_) {
		SDL_Rect default_clip = { 0, 0, width_, height_ };
		if (clip == nullptr) {
			clip = &default_clip;
		}
		SDL_RenderCopy(renderer, texture_, clip, &dest);
	}
}

void Texture::render(SDL_Renderer* renderer, const SDL_Rect& dest, double angle, SDL_Rect* clip) const {
	if (texture_) {
		SDL_Rect default_clip = { 0, 0, width_, height_ };
		if (clip == nullptr) {
			clip = &default_clip;
		}
		SDL_RenderCopyEx(renderer, texture_, clip, &dest, angle, nullptr,
				SDL_FLIP_NONE);
	}
}

bool Texture::load(string fileName, std::string id, SDL_Renderer * pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load((FOLDER + "levels/" + fileName).c_str());
	if (pTempSurface == 0)
	{
		return false;
	}
	SDL_Texture* pTexture =
		SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	// everything went ok, add the texture to our list
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	// reaching here means something went wrong
	return false;
}

void Texture::drawTile(string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer * pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = margin + (spacing + width / zoom) * currentFrame;
	srcRect.y = margin + (spacing + height / zoom) * currentRow;
	srcRect.w = width / zoom;
	srcRect.h = height / zoom;

	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
		&destRect, 0, 0, SDL_FLIP_NONE);
}

void Texture::ChangeAlphaValue(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(getSdlTexture(), alpha);
}

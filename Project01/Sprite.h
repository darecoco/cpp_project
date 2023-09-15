#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Sprite {
public:
	Sprite(Texture texture, int width, int height)
		:texture_(texture), width_(width), height_(height)
	{
		//스프라이트 생성자
	}
	~Sprite()
	{
		//스프라이트 소멸자
	}
private:
	Texture texture_;
	int width_;
	int height_;
};
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Sprite {
public:
	Sprite(Texture texture, int width, int height)
		:texture_(texture), width_(width), height_(height)
	{
		//��������Ʈ ������
	}
	~Sprite()
	{
		//��������Ʈ �Ҹ���
	}
private:
	Texture texture_;
	int width_;
	int height_;
};
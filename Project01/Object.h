#pragma once
#include <SFML/Graphics.hpp>

class Object {
public:
	Object (int x, int y, int width, int height) : x_(x), y_(y), width_(width), height_(height)
	{
		//������
	}
	~Object() 
	{
		//�Ҹ���
	}
	
private:
	int x_;
	int y_;
	int width_;
	int height_;
};

//������
//class JudgeLine :public Object{
//public:
//	JudgeLine
//private:
//	
//};
#pragma once
#include <SFML/Graphics.hpp>

class Object {
public:
	Object (int x, int y, int width, int height) : x_(x), y_(y), width_(width), height_(height)
	{
		//생성자
	}
	~Object() 
	{
		//소멸자
	}
	
private:
	int x_;
	int y_;
	int width_;
	int height_;
};

//판정선
//class JudgeLine :public Object{
//public:
//	JudgeLine
//private:
//	
//};
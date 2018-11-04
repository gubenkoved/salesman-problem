#pragma once
using namespace System;
using namespace System::Drawing;

class city
{
	int x;
	int y;
	int num;
	static const size_t r = 15;
public:
	void draw( Graphics^ g );
	city( int _x, int _y, int _num);
	void setPos( int _x, int _y ) { x = _x; y = _y; }
	~city(void);
	friend class world;
	friend class solver;
};

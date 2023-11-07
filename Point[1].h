#ifndef POINT_H
#define POINT_H

class Point
{
public:  
	short x;
	short y;
	Point() : x(), y() {}
	Point(short x, short y) : x(x), y(y) {}
	bool operator==(Point pt) const { return x == pt.x && y == pt.y; }
};

#endif
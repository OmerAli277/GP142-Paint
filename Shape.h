#include "Utility.h"
#pragma once
class Shape{
protected:
	Point *points;
	const int numberOfPoints;
	int color;
public:
	Shape(Point *thePoints, int NumberOfPoints, int col)
	:numberOfPoints(NumberOfPoints){
		color = col;
		points = new Point[numberOfPoints];
		for (int i = 0; i < numberOfPoints; ++i){
			points[i].x = thePoints[i].x;
			points[i].y = thePoints[i].y;
		}
	}
	virtual void draw() = 0;
	virtual void fill(int Color) = 0;
	virtual string toString() = 0;
	virtual bool contains(int x, int y) = 0;
	virtual void clean() = 0;
	~Shape(){
		if (points != NULL)
			delete[]points;
	}
};

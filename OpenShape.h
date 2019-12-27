#include "Shape.h"
#pragma once

class OpenShape : public Shape{
protected:
	bool style; // if true line is solid
public:
	OpenShape(Point *thePoints, int NumberOfPoints, int col, bool theStyle)
		:Shape(thePoints, NumberOfPoints, col){
		style = theStyle;
	}
};
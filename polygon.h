#include "Shape.h"
#pragma once
class polygon : public Shape{
protected:
	int fillColor;
	int minX, minY,maxX,maxY;
public:
	polygon(Point *thePoints, int NumberOfPoints, int col, int theFillColor = 0)
		:Shape(thePoints, NumberOfPoints,col){
		fillColor = theFillColor;
	}
	void draw(){
		for(int i = 0; i < numberOfPoints-1; ++i){
			draw_line(points[i].x,points[i].y,points[i+1].x,points[i+1].y,color);
			if(i == numberOfPoints-2)
				draw_line(points[0].x,points[0].y,points[i+1].x,points[i+1].y,color);
		}
	}
	void fill(int Color){
		fillColor = Color;
		minX = maxX = points[0].x;
		minY = maxY = points[0].y;
		for(int i = 0; i < numberOfPoints; ++i){
			minX = MinOfTwo(minX,points[i].x);
			maxX = MaxOfTwo(maxX,points[i].x);
			minY = MinOfTwo(minY,points[i].y);
			maxY = MaxOfTwo(maxY,points[i].y);
		}
		for(int i = maxY; i >= minY; --i)
			for(int j = minX; j <= maxX; ++j)
				if(contains(j,i))
					print_point(j-2,i-5,fillColor);
		draw();
	}
	bool contains(int x, int y){
		bool odd = false;
		for(int i = 0, j = numberOfPoints-1; i < numberOfPoints; i++){
				 if ( ((points[i].y>y) != (points[j].y>y)) &&
					(x < (points[j].x-points[i].x) * (y-points[i].y) / (points[j].y-points[i].y) +points[i].x) )
						odd = !odd;
			j = i;
		}
		return odd;
	}
	string toString(){
		ostringstream out;
		out << 4 << " " << numberOfPoints << " ";
		for(int i = 0; i < numberOfPoints; ++i)
			out << points[i].x << " " << points[i].y << " ";
		out << color << " " << fillColor << endl;
		return out.str();
	}
	void clean(){
		color = 0;
		fill(0);
	}
};
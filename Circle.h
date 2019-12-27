#include "Shape.h"

class Circle : public Shape{
	double radius;
	int fillColor;
public:
	Circle(Point *thePoints, int col, double theRadius, int thefillColor = 0)
		:Shape(thePoints, 1, col){
		radius = theRadius;
		fillColor = thefillColor;
	}
	void draw(){
		draw_circle(points[0].x, points[0].y, radius,color);
		draw_circle(points[0].x, points[0].y, radius-1,fillColor);
	}
	bool contains(int x, int y){
		return sqrt(pow((x-points[0].x),2) + pow((y-points[0].y),2)) <= radius;
	}
	void fill(int Color){
		fillColor = Color;
		draw();
	}
	string toString(){
		ostringstream out;
		out << 5 << " " << points[0].x << " " << points[0].y << " "
			<< radius << " " << color << " " << fillColor << endl;
		return out.str();
	}
	void clean(){
		color = 0;
		if(fillColor)
			fillColor = 0;
		draw();
	}
};
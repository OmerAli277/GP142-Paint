#include "OpenShape.h"

class Curve : public OpenShape{
public:
	Curve(Point *thePoints, int NumberOfPoints, int col, bool style)
		:OpenShape(thePoints, NumberOfPoints, col, style){}
	void fill(int col){
		color = col;
		if(!style)
			for(int i = 0; i < numberOfPoints - 1; ++i)
				draw_line(points[i].x,points[i].y,points[i+1].x,points[i+1].y,0,16);
		draw();
	}
	void draw(){
		if(style)
			for(int i = 0; i < numberOfPoints - 1; ++i)
				draw_line(points[i].x,points[i].y,points[i+1].x,points[i+1].y,color);
		else
			for(int i = 0; i < numberOfPoints - 1; ++i)
				draw_doted_line(points[i].x,points[i].y,points[i+1].x,points[i+1].y,color);
	}
	bool contains(int x, int y){
		for(int i = 0; i < numberOfPoints - 1; ++i)
			if(pointLiesOnLine(points[i].x,points[i].y,points[i+1].x,points[i+1].y,x,y))
				return true;
		return false;
	}
	string toString(){
		ostringstream out;
		out << 2 << " " << numberOfPoints << " ";
		for(int i = 0; i < numberOfPoints; ++i)
			out << points[i].x << " " << points[i].y << " ";
		out << color << " " << style << endl;
		return out.str();
	}
	void clean(){
		color = 0;
		if(!style)
			for(int i = 0; i < numberOfPoints - 1; ++i)
				draw_line(points[i].x,points[i].y,points[i+1].x,points[i+1].y,0,16);
		else
			draw();
	}
};
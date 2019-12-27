#include "polygon.h"

class rectangle : public polygon{
public:
	rectangle(Point *thePoints, int col, int theFillColor = 0)
		:polygon(thePoints, 2, col, theFillColor){}
	void draw(){
		draw_rectangle(points[0].x,points[0].y,points[1].x,points[1].y,color);
	}
	void fill(int Color){
		fillColor = Color;
		int minY = MinOfTwo(points[0].y,points[1].y);
		int maxY = MaxOfTwo(points[0].y,points[1].y);
		for(int i = maxY-1; i > minY; --i)
			if(points[0].x < points[1].x)
				draw_line(points[0].x+1,i,points[1].x-1,i,fillColor);
			else
				draw_line(points[0].x-1,i,points[1].x+1,i,fillColor);
		draw();
	}
	bool contains(int x, int y){
		return pointLiesOnRectangle(points[0].x,points[0].y,points[1].x,points[1].y,x,y);
	}
	string toString(){
		ostringstream out;
		out << 3 << " " << points[0].x << " " << points[0].y << " "
			<< points[1].x << " " << points[1].y << " " << color << " " << fillColor << endl;
		return out.str();
	}
	void clean(){
		color = 0;
		fill(0);
	}
};
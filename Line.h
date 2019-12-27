#include "OpenShape.h"

class Line : public OpenShape{
public:
	Line(Point *thePoints, int col, bool style)
		:OpenShape(thePoints, 2, col, style){}
	void fill(int col){
		color = col;
		if(!style)
			draw_line(points[0].x,points[0].y,points[1].x,points[1].y,0,16);
		draw();
	}
	void draw(){
		if(style)
			draw_line(points[0].x,points[0].y,points[1].x,points[1].y,color);
		else
			draw_doted_line(points[0].x,points[0].y,points[1].x,points[1].y,color);
	}
	bool contains(int x, int y){
		return pointLiesOnLine(points[0].x,points[0].y,points[1].x,points[1].y,x,y);
	}
	string toString(){
		ostringstream out;
		out << 1 << " " << points[0].x << " " << points[0].y
			<< " " << points[1].x << " " << points[1].y << " " << color << " " << style << endl;
		return out.str();
	}
	void clean(){
		color = 0;
		if(!style){
			draw_line(points[0].x,points[0].y,points[1].x,points[1].y,0,18);
		}
		else
			draw();
	}
};
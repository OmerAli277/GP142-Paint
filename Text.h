#include "Shape.h";
class Text : public Shape{
	string text;
public:
	Text(Point *thePoints, int col, string theText)
		:Shape(thePoints, 1, col){
		text = theText;
	}
	void draw(){
		printStringXY(color,points[0].x,points[0].y,20,text);
	}
	bool contains(int x, int y){
		if(pointLiesOnRectangle(points[0].x,points[0].y+1,points[0].x + text.size()*11,points[0].y+21,x,y))
			return true;
		return false;
	}
	void fill(int Color){
		color = 0;
		for(int i = 0; i < 20; ++i)
			draw();
		color = Color;
		draw();
	}
	string toString(){
		ostringstream out;
		out << 6 << " " << points[0].x << " " << points[0].y << " "
			<< color << " " << text << endl;
		return out.str();
	}
	void clean(){
		color = 0;
		for(int i = 0; i < 20; ++i)
			draw();
	}
};
#include "GP142.h"
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
#define TEXT_SIZE 20

#pragma once

struct Point{
	int x;
	int y;
};

int MaxOfTwo(int a, int b){
	return a > b ? a : b;
}

int MinOfTwo(int a, int b){
	return a < b ? a : b;
}

bool pointLiesOnLine(int x1, int y1, int x2, int y2, int x, int y){
	int xMax = MaxOfTwo(x1,x2);
	int xMin = MinOfTwo(x1,x2);
	int yMax = MaxOfTwo(y1,y2);
	int yMin = MinOfTwo(y1,y2);
	if(x1 == x2)
		if(y <= yMax && y >= yMin)
			return true;
		else
			return false;
	double slope = (double)(y2-y1)/(x2-x1);
	int n = y-y1;
	int m = slope*(x-x1);
	if (x <= xMax && x >=  xMin && y <= yMax && y >= yMin && (m >= n-10 && m <= n+10))
		return true;
	return false;
}

bool pointLiesOnRectangle(int x1, int y1, int x2, int y2, int x, int y){
	int xMax = MaxOfTwo(x1,x2);
	int xMin = MinOfTwo(x1,x2);
	int yMax = MaxOfTwo(y1,y2);
	int yMin = MinOfTwo(y1,y2);
	if (x <= xMax && x >=  xMin && y <= yMax && y >= yMin)
		return true;
	return false;
}

void print_point(int x, int y, int color = WHITE){
	GP142_printfXY(color, x, y,   TEXT_SIZE, "%c", '.');
}

void draw_line(int x1, int y1, int x2, int y2, int color=WHITE, int width=2){
	GP142_lineXY (color,x1,y1,x2,y2,width);
}

int draw_doted_line(int x1, int y1, int x2, int y2, int color=WHITE, int width = 1){
	int xmid = (x1+x2)/2;
	int ymid = (y1+y2)/2;
	if((xmid == x1 || xmid == x2) && (ymid == y1 || ymid == y2))
		return 1;
	static int x = 0;
	if(x%3 == 0)
		print_point(xmid,ymid,color);
	x++;
	draw_doted_line(x1,y1,xmid,ymid,color);
	draw_doted_line(xmid,ymid,x2,y2,color);
	return 1;
}
void draw_rectangle(int x1, int y1, int x2, int y2, int color=WHITE, int width = 1){
	draw_line(x1,y1,x2,y1,color,width);
	draw_line(x1,y1,x1,y2,color,width);
	draw_line(x2,y2,x2,y1,color,width);
	draw_line(x2,y2,x1,y2,color,width);
}

void draw_circle(int x, int y, int radius, int color=WHITE){
	 GP142_circleXY(color, x, y, radius);
}

void printCharXY(char c, int x, int y, int text_size = 20,int color = WHITE){
	GP142_printfXY(color, x, y, text_size, "%c", c);
}

void printStringXY(int color, int x, int y, int text_size, string str){
	GP142_printfXY(color,x,y,text_size,str.c_str());
}
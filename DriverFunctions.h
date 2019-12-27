#include "Shape.h"
#include "rectangle.h"
#include "Line.h"
#include "Circle.h"
#include "Text.h"
#include "Curve.h"
#pragma once

Shape **doubleTheShapesArray(Shape **allShapes, int &capacity){
	Shape **temp = new Shape*[capacity*2];
	for(int i = 0; i < capacity; ++i)
		temp[i] = allShapes[i];
	delete[]allShapes;
	capacity *= 2;
	return temp;
}

Shape **deleteAt(Shape **allShapes, int at, int &count, int &capacity){
	if(capacity == 1){
		Shape **temp = new Shape*[1];
		count--;
		delete allShapes[0];
		delete[]allShapes;
		return temp;
	}else{
		Shape **temp;
		if(capacity > (count-1)*2){
			temp = new Shape*[capacity/2];
			capacity /= 2;
		}else
			temp = new Shape*[capacity];
		for(int i = 0, j = 0; i < count; ++i)
			if(i != at)
				temp[j++] = allShapes[i];
			else
				delete allShapes[i];
		count--;
		delete[]allShapes;
		return temp;
	}
}

Point *doubleThePointsArray(Point *points, int &pcapacity){
	Point *temp = new Point[pcapacity*2];
	for(int i = 0; i < pcapacity; ++i){
		temp[i].x = points[i].x;
		temp[i].y = points[i].y;
	}
	pcapacity *= 2;
	delete[]points;
	return temp;
}

void drawLoadNewButtons(){
	Point p1[2];
	Point p2[2];
	p1[0].x = -82; p1[0].y = 20;
	p1[1].x = 0; p1[1].y = -20;
	p2[0].x = 0; p2[0].y = 20;
	p2[1].x = 82; p2[1].y = -20;
	rectangle r1(p1,5);
	rectangle r2(p2,5);
	r1.fill(9);
	r2.fill(14);
	printStringXY(5,-68,-10,20,"NEW");
	printStringXY(5,8,-10,20,"LOAD");
}

void saveAllShapes(Shape **allShape, string filepath, int count){
	ofstream outFile(filepath);
	outFile << count << endl;
	for(int i = 0; i < count; ++i)
		outFile << allShape[i]->toString();
	outFile.close();
}

Shape **loadAllShapes(string filepath, int &count, int &capacity){
	ifstream inFile(filepath);
	inFile >> capacity;
	capacity++;
	Shape **allShape = new Shape*[capacity];
	int shape;
	int color;
	int fillColor;
	int numberOfPoints;
	bool style;
	double radius;
	string text;
	Point p[2];
	Point *points;
	while(!inFile.eof()){
		inFile >> shape;
		switch(shape){
		case 1: { inFile >> p[0].x >> p[0].y >> p[1].x >> p[1].y >> color >> style;
				allShape[count] = new Line(p,color,style);
				allShape[count++]->draw();
				break;
			}
		case 2: { inFile >> numberOfPoints;
				points = new Point[numberOfPoints];
				for(int i = 0; i < numberOfPoints; ++i)
					inFile >> points[i].x >> points[i].y;
				inFile >> color >> style;
				allShape[count] = new Curve(points,numberOfPoints,color,style);
				allShape[count++]->draw();
				delete[]points;
				break;
			}
		case 3: { inFile >> p[0].x >> p[0].y >> p[1].x >> p[1].y >> color >> fillColor;
				allShape[count] = new rectangle(p,color,fillColor);
				allShape[count++]->fill(fillColor);
				break;
			}
		case 4: { inFile >> numberOfPoints;
				points = new Point[numberOfPoints];
				for(int i = 0; i < numberOfPoints; ++i)
					inFile >> points[i].x >> points[i].y;
				inFile >> color >> fillColor;
				allShape[count] = new polygon(points,numberOfPoints,color,fillColor);
				allShape[count++]->draw();
				delete[]points;
				break;
			}
		case 5: { inFile >> p[0].x >> p[0].y >> radius >> color  >> fillColor;
				allShape[count] = new Circle(p,color,radius,fillColor);
				allShape[count++]-> draw();
				break;
			}
		case 6: { inFile >> p[0].x >> p[0].y >> color;
				getline(inFile,text);
				allShape[count] = new Text(p,color,text);
				allShape[count++]->draw();
				break;
			}
		}
	}
	count--;
	return allShape;
}

void drawToolBox(){
	Point Rec[2];
	Rec[0].x = -683; Rec[0].y = 360;
	Rec[1].x = -640; Rec[1].y = -330;
	rectangle toolBoxBackground(Rec,1);
	toolBoxBackground.fill(22);
	int color = 0;
	for(int i = 360; i >= -300; i -= 30){
		draw_rectangle(-683,i,-640,i-30,1);
		if(i <= 60 && i >= -270){
			Point P[2];
			P[0].x = -683; P[0].y = i;
			P[1].x = -640; P[1].y = i-30;
			rectangle box(P,1);
			box.fill(color++);
		}
	}

	draw_line(-678,354,-645,334,7,2);

	draw_doted_line(-678,323,-645,304,7,2);

	Point pts[14];
	pts[0].x = -682;   pts[0].y = 257;
	pts[1].x = -679;   pts[1].y = 260;
	pts[2].x = -676;   pts[2].y = 263;
	pts[3].x = -673;   pts[3].y = 266;
	pts[4].x = -670;   pts[4].y = 266;
	pts[5].x = -667;   pts[5].y = 263;
	pts[6].x = -664;   pts[6].y = 260;
	pts[7].x = -661;   pts[7].y = 256;
	pts[8].x = -658;   pts[8].y = 251;
	pts[9].x = -655;   pts[9].y = 248;
	pts[10].x = -652;   pts[10].y = 251;
	pts[11].x = -649;   pts[11].y = 256;
	pts[12].x = -646;   pts[12].y = 257;
	pts[13].x = -643;   pts[13].y = 257;

	for(int i = 0; i < 13; ++i)
			draw_doted_line(pts[i].x,pts[i].y+25,pts[i+1].x,pts[i+1].y+25,7,2);

	for(int i = 0; i < 13; ++i)
			draw_line(pts[i].x,pts[i].y,pts[i+1].x,pts[i+1].y,7,2);

	draw_rectangle(-678,234,-645,214,7,2);

	Point pts1[11];
	pts1[0].x = -679;   pts1[0].y = 198;
	pts1[1].x = -676;   pts1[1].y = 201;
	pts1[2].x = -673;   pts1[2].y = 204;
	pts1[3].x = -667;   pts1[3].y = 207;
	pts1[4].x = -655;   pts1[4].y = 207;
	pts1[5].x = -646;   pts1[5].y = 201;
	pts1[6].x = -652;   pts1[6].y = 186;
	pts1[7].x = -664;   pts1[7].y = 198;
	pts1[8].x = -664;   pts1[8].y = 186;
	pts1[9].x = -673;   pts1[9].y = 192;
	pts1[10].x = -679;   pts1[10].y = 186;
	for(int i = 0; i < 10; ++i){
		draw_line(pts1[i].x,pts1[i].y,pts1[i+1].x,pts1[i+1].y,7,2);
		if(i == 9)
			draw_line(pts1[0].x,pts1[0].y,pts1[i+1].x,pts1[i+1].y,7,2);
	}

	draw_circle(-661,164,13,7);
	draw_circle(-661,164,11,22);

	printCharXY('T',-670,120,26,7);

	printCharXY('x',-670,90,30,7);

	printStringXY(7,-679,65,20,"FILL");

	Point save_p[2];
	save_p[0].x = -676; save_p[0].y = -302;
	save_p[1].x = -649; save_p[1].y = -327;
	rectangle save1(save_p,0);
	save1.fill(0);

	save_p[0].x = -673; save_p[0].y = -304;
	save_p[1].x = -655; save_p[1].y = -309;
	rectangle save2(save_p,1);
	save2.fill(1);

	save_p[0].x = -673; save_p[0].y = -315;
	save_p[1].x = -655; save_p[1].y = -325;
	rectangle save3(save_p,1);
	save3.fill(1);

	save_p[0].x = -670; save_p[0].y = -318;
	save_p[1].x = -664; save_p[1].y = -325;
	rectangle save4(save_p,0);
	save4.fill(0);
}

int ToolBox(int y){
	int mouse_y = 360;
	for(int i = 1; i <= 23; i++)
		if(y > mouse_y-30*i)
			return i;
	return -1;
}
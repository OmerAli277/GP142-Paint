#include "DriverFunctions.h"

int main(void){
	Shape **allShapes = new Shape*[1];
	int capacity = 1;
	int count = 0;
	Point *points = new Point[1];
	int pcapacity = 1;
	int pcount = 0;
	Point pts[2];
	int p_count = 0;
	int tool = 0;
	bool style;
	int whatShape; //type of shape
	int color = 1;
	int quit = 0;
	int mouse_x, mouse_y;
	bool start = false;
	bool run_only_once = true;
	char key_pressed;
	string filepath = "";
	string text = "";
	Point p_text[1];
	GP142_open();          /* Open and initialize the GP142 Graphics Window    */
    while (!quit) {
	    if(start){
	    drawToolBox();
	    start = false;
	    }
	    if(!tool)
		    drawLoadNewButtons();
	    if(tool == 7 && run_only_once){
		    Point p[2];
		    p[0].x = -370; p[0].y = 23;
		    p[1].x = 370; p[1].y = -19;
		    rectangle r(p,1);
		    r.fill(9);
		    printStringXY(5,-365,-12,20,"Enter File Path & Name: ");
		    run_only_once = false;
	    }
	    if(tool == 6)
		    printStringXY(5,-679,-351,12,"Enter File Path & Name: ");
        switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
			case GP142_QUIT:
				quit = 1;   /* set flag to terminate loop                */
				break;
			case GP142_MOUSE:{
				if(mouse_x > -640){
					switch(tool){
						case 0:{
							Point p[2];
							p[0].x = -82; p[0].y = 20;
							p[1].x = 82; p[1].y = -20;
							if(mouse_x > -82 && mouse_x < 0 && mouse_y > -20 && mouse_y < 20){
								rectangle r(p,0);
								r.fill(0);
								tool = -1;
								start = true;
							}else if(mouse_x > 0 && mouse_x < 82 && mouse_y > -20 && mouse_y < 20){
								rectangle r(p,0);
								r.fill(0);
								tool = 7;
							}
							break;
						}
						case 1:{
							pts[p_count].x = mouse_x;
							pts[p_count].y = mouse_y;
							double radius = 0.0;
							double Lborder = abs(-640 - pts[0].x);
							int flag = 1;
							p_count++;
							if(p_count == 2){
								if(count == capacity)
									allShapes = doubleTheShapesArray(allShapes,capacity);
								switch(whatShape){
									case 0: allShapes[count++] = new Line(pts,color,style); break;
									case 1: allShapes[count++] = new rectangle(pts,color); break;
									case 2: {
											radius = sqrt(pow(pts[0].x - pts[1].x,2) + pow(pts[0].y - pts[1].y,2));
											if(radius > Lborder)
												flag = 0;
											else 
												allShapes[count++] = new Circle(pts,color,radius);
											break;
									}
								}
								if(flag)
									allShapes[count-1]->draw();
								p_count = 0;
							}
							break;
						}
						case 2:{
							if(pcount == pcapacity)
								points = doubleThePointsArray(points,pcapacity);
							points[pcount].x = mouse_x;
							points[pcount].y = mouse_y;
							pcount++;
							if(pcount > 1){
								if((points[pcount-1].x == points[pcount-2].x) &&
									(points[pcount-1].y == points[pcount-2].y))
									if(pcount < 3){
										delete[]points;
										points = new Point[1];
										pcapacity = 1;
										pcount = 0;
									}else{
										if(count == capacity)
											allShapes = doubleTheShapesArray(allShapes,capacity);
										if(!whatShape)
											allShapes[count++] = new Curve(points,pcount-1,color,style);
										else{
											if(pcount < 4){
												delete[]points;
												points = new Point[1];
												pcapacity = 1;
												pcount = 0;
											}else
												allShapes[count++] = new polygon(points,pcount-1,color);
										}
										if(pcount)
											allShapes[count-1]->draw();
										delete[]points;
										points = new Point[1];
										pcapacity = 1;
										pcount = 0;
									}
							}
							break;
						}
						case 3:{
							if(text != ""){
								if(count == capacity)
									allShapes = doubleTheShapesArray(allShapes,capacity);
								allShapes[count++] = new Text(p_text,color,text);
								text = "";
							}
							p_text[0].x = mouse_x;
							p_text[0].y = mouse_y;
							break;
						}
						case 4:{
							for(int i = 0; i < count; ++i)
								if(allShapes[i]->contains(mouse_x,mouse_y)){
									allShapes[i]->clean();
									allShapes = deleteAt(allShapes,i,count,capacity);
								}
							for(int i = 0; i < count; ++i)
								allShapes[i]->draw();
							break;
						}
						case 5:{
							for(int i = 0; i < count; ++i)
								if(allShapes[i]->contains(mouse_x,mouse_y))
									allShapes[i]->fill(color);
							break;
						}
					}
				}else{
					if(tool == 3 && text != ""){
						allShapes[count++] = new Text(p_text,color,text);
						text = "";
					}
					delete[]points;
					points = new Point[1];
					pcapacity = 1;
					pcount = 0;
					p_count = 0;
					int value = ToolBox(mouse_y);
					switch(value){
						case 1: {tool = 1; style = true; whatShape = 0; break;}
						case 2: {tool = 1; style = false; whatShape = 0; break;}
						case 3: {tool = 2; style = false; whatShape = 0; break;}
						case 4: {tool = 2; style = true; whatShape = 0; break;}
						case 5: {tool = 1; whatShape = 1; break;}
						case 6: {tool = 2; whatShape = 1; break;}
						case 7: {tool = 1; whatShape = 2; break;}
						case 8: {tool = 3; break;}
						case 9: {tool = 4; break;}
						case 10: {tool = 5; break;}
						case 11: {color = 0; break;}
						case 12: {color = 1; break;}
						case 13: {color = 2; break;}
						case 14: {color = 3; break;}
						case 15: {color = 4; break;}
						case 16: {color = 5; break;}
						case 17: {color = 6; break;}
						case 18: {color = 7; break;}
						case 19: {color = 8; break;}
						case 20: {color = 9; break;}
						case 21: {color = 10; break;}
						case 22: {color = 11; break;}
						case 23: {tool = 6; break;}
						default: break;
					}
				}
                break;
			}
            case GP142_KBD:{
			  switch(tool){
				case 3:{
					if(key_pressed == '\b'){
						if(text != ""){
							printStringXY(0,p_text[0].x,p_text[0].y,20,text);
							string cpy = text;
							text = "";
							for(int i = 0; i < cpy.length()-1; ++i)
								text += cpy.at(i);
						}
					}
					else if(key_pressed != '\r'){
						text += key_pressed;
					}
					printStringXY(color,p_text[0].x,p_text[0].y,20,text);
					if(key_pressed == '\r'){
						allShapes[count++] = new Text(p_text,color,text);
						text = "";
					}
					break;
				}
				case 6:{
					if(key_pressed == '\b'){
						if(filepath != ""){
							printStringXY(0,-541,-351,12,filepath);
							string cpy = filepath;
							filepath = "";
							for(int i = 0; i < cpy.length()-1; ++i)
								filepath += cpy.at(i);
						}
					}
					else if(key_pressed != '\r'){
						filepath += key_pressed;
					}
					printStringXY(5,-541,-351,12,filepath);
					if(key_pressed == '\r'){
						filepath += ".pb";
						saveAllShapes(allShapes,filepath,count);
						filepath = "";
						Point p[2];
						p[0].x = -682; p[0].y = -333;
						p[1].x = 5; p[1].y = -354;
						rectangle remove_filename(p,0);
						remove_filename.fill(0);
						tool = -1;
					}
					break;
				}
				case 7:{
					if(key_pressed == '\b'){
						if(filepath != ""){
							printStringXY(0,-148,-12,20,filepath);
							string cpy = filepath;
							filepath = "";
							for(int i = 0; i < cpy.length()-1; ++i)
								filepath += cpy.at(i);
						}
					}
					else if(key_pressed != '\r'){
						filepath += key_pressed;
					}
					printStringXY(5,-148,-12,20,filepath);
					if(key_pressed == '\r'){
						Point p[2];
						p[0].x = -370; p[0].y = 23;
						p[1].x = 370; p[1].y = -19;
						rectangle remove_filename(p,0);
						remove_filename.fill(0);
						delete[]allShapes;
						filepath += ".pb";
						ifstream ifile(filepath);
						if(ifile)
							allShapes = loadAllShapes(filepath,count,capacity);
						tool = -1;
						start = true;
						filepath = "";
					}
					break;
				}
			  }
                break;
		}
            default:
                break;
        }
    }
    GP142_close();          /* Clean up and close graphics window           */
    for(int i = 0; i < count; ++i)
	    delete allShapes[i];
    delete[]allShapes;
    delete[]points;
    return 0;
}
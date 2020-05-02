#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
#include <map>
#include <SDL_image.h>
#include <SDL_image.h>
using namespace std;
#ifndef COMMON FUNCTION_H_INCLUDED
#define COMMON FUNCTION_H_INCLUDED
bool checkout(int x, int y) {
	if ( y >=520  || y<=0 ) {
		return false;
	}
	return true;
}
int crash(double x1, double y1 , double x2 , double y2) {
	if ((x2 < x1 + 20 &&  x2 >= x1 )|| (x2 + 20  > x1 && x1 > 200) ){
		if (y2 > y1 && y2 <= y1 + 20) {
			return 1;
		}
		else if (y2 > y1 + 20 && y2 <= y1 + 40) {
			return 2;
		}
		else if (y2 > y1 + 40 && y2 <= y1 + 60) {
			return 3;
		}
		else if (y2 > y1 + 60 && y2 < y1 + 80) {
			return 4;
		}
		else return 5;
	}
	return 6;
}
bool step(double &step1, double &step2 , double a , double b , double x , double y) {
	if (step1 < 0 && step2 < 0 &&  y <=0 ) {
		step1 = -a;
		step2 = b;
		return true;
	}
	else if (step1 < 0 && step2 < 0) {
		step1 = a;
		step2 = -b;
		return true;
	}
    if (step1 > 0 && step2 < 0 && y<=0 ) {
		step1 = a;
		step2 = b;
		return true;
	} 
	else if (step1 > 0 && step2 < 0) {
		step1 = -a;
		step2 = -b;
		return true;
	}
	if (step1 < 0 && step2 > 0 && y+20 >=600) {
		step1 = -a;
		step2 = -b;
		return true;
	}
	else if (step1 < 0 && step2 > 0) {
		step1 = a;
		step2 = b;
		return true;
	}
	if (step1 > 0 && step2 > 0 && y+20>=600) {
		step1 = a;
		step2 = -b;
		return true;
	} 
	else if (step1 > 0 && step2 > 0) {
		step1 = -a;
		step2 = b;
		return true;
	}
}
bool checkcrash(double x1, double y1, double x2, double y2  ) {
	if (crash(x1,y1,x2,y2)!=6 && crash(x1,y1,x2,y2)!=5) {
	
		return true;
	}
	else if (crash(x1,y1,x2,y2)==6){
		
		return false;
	}
}
#endif
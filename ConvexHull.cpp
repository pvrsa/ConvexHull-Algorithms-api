#include <iostream>
#include "ConvexHull.h"
#include <vector>
#include <math.h>
using namespace std;
#define PI 3.14159265

ConvexHull::ConvexHull(vector<Node> v){
	this->points = v;

	cout << points.size() << endl;
}

void ConvexHull::grahamScan(){

	int min=0;
	for (vector<Node>::iterator i = points.begin(); i != points.end(); ++i)
	{
		if((*i).y < points[min].y){
			min = i - points.begin();
		}else if((*i).y == points[min].y){
			if((*i).x < points[min].x){
				min = i - points.begin();
			}
		}
	}

	

	double angles[points.size()][2];
	angles[min][0] = 0.0;
	angles[min][1] = min;

	for (int i = 0; i < points.size(); ++i)
	{
		if(i != min){
			double slope = (points[i].y-points[min].y) / (points[i].x-points[min].x);
			angles[i][0] =  atan (slope) * 180 / PI;
			angles[i][1] = i;
		}

		cout << angles[i][0] << "  " << angles[i][1] << endl;	
	}


}

void ConvexHull::jarvisMarch(){

}

void ConvexHull::ksAlgo(){

}

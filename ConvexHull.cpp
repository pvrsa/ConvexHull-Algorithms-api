#include "ConvexHull.h"
#include<bits/stdc++.h>
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

	vector< pair <double,int> > angles;
	angles.push_back(make_pair(0,min));

	for (int i = 0; i < points.size(); ++i)
	{
		if(i != min){
			double slope = (points[i].y-points[min].y) / (points[i].x-points[min].x);
			angles.push_back(make_pair(atan (slope) * 180 / PI,i));
		}

		cout << angles[i].first << "  " << angles[i].second << endl;	
	}

	sort(angles.begin(),angles.end());

	for (vector<pair <double,int>>::iterator i = angles.begin(); i != angles.end(); ++i)
	{
		cout << (*i).first << "  " << (*i).second << endl;
	}

}

void ConvexHull::jarvisMarch(){

}

void ConvexHull::ksAlgo(){

}

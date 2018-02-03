#include "ConvexHull.h"
#include<bits/stdc++.h>
using namespace std;
#define PI 3.14159265

ConvexHull::ConvexHull(vector<Node> v){
	this->points = v;
}

int ConvexHull::turn_check(int p, int q, int r){
	int val = (points[q].y - points[p].y) * (points[r].x - points[q].x) -
              (points[q].x - points[p].x) * (points[r].y - points[q].y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}



double ConvexHull::eudist(int a,int b)
{
	double x = points[a].x - points[b].x; //calculating number to square in next step
	double y = points[a].y - points[b].y;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);                  

	return dist;
}

vector< pair<int,int> > ConvexHull::grahamScan(){

	//Finding the bottom most point to take as origin
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

	//stores angles in a pair of (angle,index of the point)
	vector< pair <double,int> > angles;
	angles.push_back(make_pair(0,min));

	//Find the angles of every other point from the origin
	for (int i = 0; i < points.size(); ++i)
	{
		if(i != min){
			double slope = (points[i].y-points[min].y) / (points[i].x-points[min].x);
			angles.push_back(make_pair(atan (slope) * 180 / PI,i));
		}
	}

	//Angular sort the points
	sort(angles.begin(),angles.end());

	for (int i = 1; i < angles.size()-1; ++i)
	{
		if(angles[i].first == angles[i+1].first){
			if(eudist(i,min)>eudist(i+1,min)){
				angles.erase(angles.begin() + i + 1);
			}else{
				angles.erase(angles.begin() + i);
			}
		}
	}
	//List storing the points forming the Convex Hull
	deque<int> hull;
	hull.push_front(angles[0].second);
	hull.push_front(angles[1].second);

	for (int i = 2; i < angles.size(); ++i)
	{
		int now = angles[i].second;
		
		int ori = turn_check(hull[1],hull[0],now);
		//If left turn
		if(ori == 2){
			hull.push_front(now);
		}else{
			hull.pop_front();
			i--;
		}

	}


	vector< pair<int,int> > edges;
	for (int i = 0; i < hull.size()-1; ++i)
	{
		edges.push_back(make_pair(hull[i],hull[i+1]));
	}
	edges.push_back(make_pair(hull.back(),hull.front()));

	return edges;

}

void ConvexHull::jarvisMarch(){

}

void ConvexHull::ksAlgo(){

}

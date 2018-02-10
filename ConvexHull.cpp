#include<bits/stdc++.h>
#include "KSAlgo.h"
#include <unistd.h>
using namespace std;
#define PI 3.14159265

/**
 * Constructor to initialise points, find bottom most point
 */
ConvexHull::ConvexHull(vector<Node> v){
	this->points = v;

	min = 0;

	//Finding the bottom most point
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

}

/**
 * Check if point 'r' is to the left or right of Line segment 'pq'
 * @param  p [line segment start point]
 * @param  q [line segment end point]
 * @param  r [point to check]
 * @return   [2 = left turn , 1 = right turn , 0 = collinear]
 */
int ConvexHull::turn_check(int p, int q, int r){
	int val = (points[q].y - points[p].y) * (points[r].x - points[q].x) -
              (points[q].x - points[p].x) * (points[r].y - points[q].y);
 
    if (val == 0) return 0;  
    return (val > 0)? 1: 2;
}


/**
 * Calculate euclidian distance points
 * @param  a [index of first point]
 * @param  b [index of second point]
 * @return   [euclidian distance as a float value]
 */
double ConvexHull::eudist(int a,int b)
{
	double x = points[a].x - points[b].x; //calculating number to square in next step
	double y = points[a].y - points[b].y;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);                  

	return dist;
}

/**
 * Implementation of Graham's Scan Algorithm -  Time Complexity - O(n*log(n)) - n = number of vertices
 * @return [vector of edges represented as a pair of verices]
 */
vector< pair<int,int> > ConvexHull::grahamScan(){

	
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

		//If right turn
		if(ori == 1){
			hull.pop_front();
			i--;
		}else{
			hull.push_front(now);
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

/**
 * Implementation of Jarvis March Algorithm - Time Complexity - O(n*h) - n = number of vertices,
 * 																		 h = number of points in hull
 * @return [vector of edges represented as a pair of verices]
 */
vector< pair<int,int> > ConvexHull::jarvisMarch(){
	

	int now,next;
	deque<int> hull;
	
	now = min;
	do{
		hull.push_front(now);

		next=(now+1)%points.size();
		for (int i = 0; i < points.size(); ++i)
		{
			if (turn_check(now, i, next) == 2)
               next = i;
		}

		now = next;
		
	}while(now != min);

	vector< pair<int,int> > edges;
	for (int i = 0; i < hull.size()-1; ++i)
	{
		edges.push_back(make_pair(hull[i],hull[i+1]));
	}
	edges.push_back(make_pair(hull.back(),hull.front()));
	


	return edges;

}

/**
 * Implementation of Kirkpatrick-Seidel Algorithm - Time Complexity - O(n*log(h)) - n = number of vertices,
 * 															                        h = number of points in hull
 * @return [vector of edges represented as a pair of verices]
 */
vector< pair<int,int> > ConvexHull::ksAlgo(){
	
	//umin = point with least 'x' coordinate
	//umax = point with maximum 'x' coordinate
	int umin=0,umax=0;
	for (vector<Node>::iterator i = points.begin(); i != points.end(); ++i)
	{
		if((*i).x < points[umin].x){
			umin = i - points.begin();
		}else if((*i).x == points[umin].x){
			if((*i).y > points[umin].y){
				umin = i - points.begin();
			}
		}

		if((*i).x > points[umax].x){
			umax = i - points.begin();
		}else if((*i).x == points[umax].x){
			if((*i).y > points[umax].y){
				umax = i - points.begin();
			}
		}

	}

	//T = vector of points represented in pair of (X-coordinate,index) fashion
	vector< pair<double,int> > T;

	T.push_back(make_pair(points[umin].x,umin));
	for (int i = 0; i < points.size(); ++i)
	{
		if(points[i].x > points[umin].x && points[i].x < points[umax].x)
		{
			T.push_back(make_pair(points[i].x,i));	
		}
	}

	T.push_back(make_pair(points[umax].x,umax));

	//Get upperhull of the points
	vector<int> upperhull = UPPERHULL(umin,umax,T);
	


	for (int i = 0; i < points.size(); ++i)
	{
		points[i].y = -points[i].y;
	}	

	//Get lowerhull of the points
	vector<int> lowerhull = UPPERHULL(umin,umax,T);

	cout << "UPPERHULL POINTS \n\n" ;
	for (vector<int>::iterator i = upperhull.begin(); i != upperhull.end(); ++i)
	{
	 	cout << (*i) << endl;
	} 

	cout << "LOWERHULL POINTS \n\n" ;
	for (vector<int>::iterator i = lowerhull.begin(); i != lowerhull.end(); ++i)
	{
	 	cout << (*i) << endl;
	}

	for (int i = 0; i < points.size(); ++i)
	{
		points[i].y = -points[i].y;
	}	

	vector< pair<int,int> > edges;
	
	edges.push_back(make_pair(umin,upperhull[0]));
	
	for (int i = 0; i < upperhull.size()-1; ++i)
	{
		edges.push_back(make_pair(upperhull[i],upperhull[i+1]));
	}
	edges.push_back(make_pair(upperhull.back(),umax));

	edges.push_back(make_pair(umin,lowerhull[0]));
	for (int i = 0; i < lowerhull.size()-1; ++i)
	{
		edges.push_back(make_pair(lowerhull[i],lowerhull[i+1]));
	}
	edges.push_back(make_pair(lowerhull.back(),umax));

	


	return edges;

}













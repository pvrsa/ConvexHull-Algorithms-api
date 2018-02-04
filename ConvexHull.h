#include<bits/stdc++.h>
using namespace std;


class Node
{

public:
	float x;
	float y;
	vector<int> edges;
	bool valid;
	Node(float x,float y){
		this->x = x;
		this->y = y;
		valid = true;
	}
};


class ConvexHull
{
private:
	vector<Node> points;
public:
	ConvexHull(vector<Node> v);
	vector< pair<int,int> > grahamScan();
	vector< pair<int,int> > jarvisMarch();
	void ksAlgo();
	int turn_check(int p, int q, int r);
	double eudist(int a,int b);
};


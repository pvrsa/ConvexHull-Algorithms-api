#include <iostream>
#include "ConvexHull.cpp"
#include <vector>
using namespace std;


int main(int argc, char const *argv[])
{
	int n;
	cin >> n;

	vector<Node> points;

	float x,y;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		Node baby(x,y);
		points.push_back(baby);
	}

	ConvexHull ch(points);

	
	ch.grahamScan();
	return 0;
}
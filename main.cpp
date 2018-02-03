#include <iostream>
#include "ConvexHull.cpp"
#include <vector>
using namespace std;


int main(int argc, char const *argv[])
{
	ifstream input ("coords1.txt");

	int n;
	input >> n;

	vector<Node> points;

	float x,y;
	for (int i = 0; i < n; ++i)
	{
		input >> x >> y;
		Node baby(x,y);
		points.push_back(baby);
	}

	input.close();

	ConvexHull ch(points);
	vector< pair<int,int> > edges = ch.grahamScan();

	ofstream out ("ans1.txt");

	for (vector<pair<int,int>>::iterator i = edges.begin(); i != edges.end(); ++i)
	{
		out << (*i).first << " " << (*i).second << endl;
	}

	cout << "BUBYEE \n" ;
	return 0;
}
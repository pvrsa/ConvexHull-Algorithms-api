#include <iostream>
#include "ConvexHull.cpp"
#include <vector>
using namespace std;


int main(int argc, char const *argv[])
{
	ifstream input (argv[1]);

	//No of points input
	int n;
	input >> n;

	vector<Node> points;

	float x,y;
	for (int i = 0; i < n; ++i)
	{
		input >> x >> y;
		Node point(x,y);
		points.push_back(point);
	}
	input.close();

	ConvexHull ch(points);
	vector< pair<int,int> > edges = ch.ksAlgo();

	

	ofstream out ("ans1.txt");
	for (vector<pair<int,int>>::iterator i = edges.begin(); i != edges.end(); ++i)
	{
		out << (*i).first << " " << (*i).second << endl;
	}
	out.close();


	cout << "BUBYEE \n" ;
	return 0;
}
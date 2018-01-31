#include <vector>
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
	void grahamScan();
	void jarvisMarch();
	void ksAlgo();
};


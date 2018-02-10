#include<bits/stdc++.h>
#include "ConvexHull.h"
using namespace std;


vector<int> ConvexHull::UPPERHULL(int umin,int umax,vector< pair<double,int> > T)
{
	
	vector<int> list;
	if(T.size() == 1)
	{
		list.push_back((T.front()).second);
		return list;
	}

	int N = T.size();
	

	vector< pair<double,int> > T2(T);
	nth_element(T2.begin(),T2.begin()+N/2 , T2.end());
	int median = T2[N/2].second;


	vector<int> Tleft,Tright;

	for (int i = 0; i < N; ++i)
	{
		if(points[median].x >= T[i].first)
		{
			Tleft.push_back(T[i].second);
		}
		if(points[median].x <= T[i].first)
		{
			Tright.push_back(T[i].second);
		}
	}

	
	pair<int,int> plpr = (UPPERBRIDGE(T,median));

	vector< pair <double,int> > Tleft2,Tright2;

	for (int i = 0; i < Tleft.size(); ++i)
	{
		if(turn_check(umin,plpr.first,Tleft[i]) == 2)
		{
			Tleft2.push_back(make_pair(points[Tleft[i]].x,Tleft[i]));
		}
	}

	Tleft2.push_back(make_pair(points[plpr.first].x,plpr.first));

	for (int i = 0; i < Tright.size(); ++i)
	{
		if(turn_check(umax,plpr.second,Tright[i]) == 1)
		{
			Tright2.push_back(make_pair(points[Tright[i]].x,Tright[i]));
		}
	}

	Tright2.push_back(make_pair(points[plpr.second].x,plpr.second));

	vector<int> vector1 = UPPERHULL(umin,plpr.first,Tleft2);
	vector<int> vector2 = UPPERHULL(umax,plpr.second,Tright2);


	vector1.insert( vector1.end(), vector2.begin(), vector2.end() );
	return vector1;


}


pair<int,int> ConvexHull::UPPERBRIDGE(vector< pair<double,int> > T,int median)
{
	if(T.size() == 2){
		if(T[0].first < T[1].first)
			return make_pair(T[0].second,T[1].second);
		else
			return make_pair(T[1].second,T[0].second);
	}

	vector<pair <double,int>> CANDIDATES;
	vector< pair<int,int> > PAIRS;

	for (int i = 0; i < T.size()-1; i=i+2)
	{
		pair<int,int> x;
		if(T[i].first < T[i+1].first)
		{
			x.first = T[i].second;
			x.second = T[i+1].second;
			PAIRS.push_back(x);
		}
		else
		{
			x.first = T[i+1].second;
			x.second = T[i].second;
			PAIRS.push_back(x);
		}
	}
	if(T.size()%2)
	{
		CANDIDATES.push_back(T[T.size()-1]);
	}


	vector<double> k;

	for (int i = 0; i < PAIRS.size(); ++i)
	{
		if(points[PAIRS[i].first].x == points[PAIRS[i].second].x)
		{
			if(points[PAIRS[i].first].y > points[PAIRS[i].second].y)
			{
				pair<double,int> random;
				random.first = points[PAIRS[i].first].x;
				random.second = PAIRS[i].first;

				PAIRS.erase(PAIRS.begin() + i);
				CANDIDATES.push_back(random);
			}
			else
			{
				pair<double,int> random;
				random.first = points[PAIRS[i].second].x;
				random.second = PAIRS[i].second;
				PAIRS.erase(PAIRS.begin() + i);

				CANDIDATES.push_back(random);
			}
		}
		else
		{
			double tp = (double)(points[PAIRS[i].first].y - points[PAIRS[i].second].y)/(double)(points[PAIRS[i].first].x - points[PAIRS[i].second].x);
			k.push_back(tp);
		}
	}


	double K = 0;	
	if(k.size()){
		vector<double> k2(k);
		nth_element(k2.begin(),k2.begin()+k.size()/2,k2.end());
		K = k2[k2.size()/2];

	}

	

	vector<pair<int,int>> SMALL;
	vector<pair<int,int>> EQUAL;
	vector<pair<int,int>> LARGE;

	for (int i = 0; i < PAIRS.size(); ++i)
	{
		double tp = (double)(points[PAIRS[i].first].y - points[PAIRS[i].second].y)/(double)(points[PAIRS[i].first].x - points[PAIRS[i].second].x);
		if(tp < K)
		{
			SMALL.push_back(PAIRS[i]);
		}
		else if(tp > K)
		{
			LARGE.push_back(PAIRS[i]);
		}
		else
			EQUAL.push_back(PAIRS[i]);
	}

	
	vector<int> MAX;
	double maxval = points[T[0].second].y- K * T[0].first;

	for (int i = 0; i < T.size(); ++i)
	{
		if(maxval < points[T[i].second].y- K * T[i].first)
		{
			maxval = points[T[i].second].y- K * T[i].first;
		}
	}

	int pk, pm;

	for (int i = 0; i < T.size(); ++i)
	{
		if(maxval == points[T[i].second].y- K * T[i].first)
		{

			MAX.push_back(T[i].second);
			
		}
	}

	pk = MAX[0];
	pm = MAX[0];

	for (int i = 0; i < MAX.size(); ++i)
	{
		if(points[pk].x > points[MAX[i]].x)
			pk = MAX[i];
		if(points[pm].x < points[MAX[i]].x)
			pm = MAX[i];
	}

	

	pair<int,int> ans;
	if(points[pk].x <= points[median].x && points[pm].x > points[median].x)
	{
		ans.first = pk;
		ans.second = pm;
		return ans;
	}

	if(points[pm].x <= points[median].x)
	{
		for (int i = 0; i < LARGE.size(); ++i)
		{
			pair<double,int> random;
			random.first = points[LARGE[i].second].x;
			random.second = LARGE[i].second;
			CANDIDATES.push_back(random);
		}
		for (int i = 0; i < EQUAL.size(); ++i)
		{
			pair<double,int> random;
			random.first = points[EQUAL[i].second].x;
			random.second = EQUAL[i].second;
			CANDIDATES.push_back(random);
		}
		for (int i = 0; i < SMALL.size(); ++i)
		{
			pair<double,int> random;
			random.first = points[SMALL[i].second].x;
			random.second = SMALL[i].second;
			CANDIDATES.push_back(random);

			random.first = points[SMALL[i].first].x;
			random.second = SMALL[i].first;
			CANDIDATES.push_back(random);
		}


	}


	if(points[pk].x > points[median].x)
	{
		for (int i = 0; i < SMALL.size(); ++i)
		{

			pair<double,int> random;
			random.first = points[SMALL[i].first].x;
			random.second = SMALL[i].first;
			CANDIDATES.push_back(random);
		}
		for (int i = 0; i < EQUAL.size(); ++i)
		{
			pair<double,int> random;
			random.first = points[EQUAL[i].first].x;
			random.second = EQUAL[i].first;
			CANDIDATES.push_back(random);
		}
		for (int i = 0; i < LARGE.size(); ++i)
		{
			pair<double,int> random;
			random.first = points[LARGE[i].second].x;
			random.second = LARGE[i].second;
			CANDIDATES.push_back(random);

			random.first = points[LARGE[i].first].x;
			random.second = LARGE[i].first;
			CANDIDATES.push_back(random);
		}
	}

	
	return UPPERBRIDGE(CANDIDATES,median); 

}
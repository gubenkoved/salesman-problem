#pragma once
using namespace std;

class world
{
	vector < city > cities;
	vector< vector< int > > matrix;
	vector< size_t > sol;
public:
	enum DrawMode { WithRoad, WithoutRoad };
	void createMatrix( void );
	world( void ) { cities.clear(); matrix.clear(); sol.clear(); }
	void draw( Graphics^ g, DrawMode = WithRoad );
	void drawSolving( Graphics^ g, string s );
	void addCity( int _x, int _y );
	void delCity( city* c );
	city* under_mouse( int _x, int _y );
	int getDistance( size_t i, size_t j );
	vector< vector< int > >& getMatix( void ) { return matrix; }
	size_t N( void ) { return cities.size(); }
	string SolutionToString( void );
	void ToFile( void );
	friend class solver;
};
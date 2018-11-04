#pragma once

class solver
{
	vector< size_t > solution; // номера городов
	world* wrld;
	void Little_method( void );
public:
	enum method { direct, little_method };
	solver( world* _wrld ): wrld( _wrld ) { solution.clear(); }
	void solve( method m );
	void To( world& w ) 
		{ 
			w.sol.clear(); 
			w.sol = solution;
		}
};

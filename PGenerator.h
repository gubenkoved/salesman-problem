#pragma once
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class PGenerator
{
	size_t n;
	void swap( size_t& a, size_t& b);
	void reverse( size_t k );
	void reverseL( size_t k );
	void Antilex( size_t m );
	void Lex( size_t m );
	void init();
	vector< vector<size_t> > P;
	vector < size_t > PP;
public:
	enum Order { direct_order, reverse_order };
	PGenerator(size_t _n, Order ordr ): n( _n ) { P.clear(); init();  if ( ordr == direct_order ) Lex( 1 ); else Antilex(n); }
	vector< vector<size_t> >& get_p( void ) { return P; }
};

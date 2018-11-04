#include "StdAfx.h"
#include "PGenerator.h"

void PGenerator::init()
{
	//генерация самой первой перестановки
	for ( size_t i = 1; i <= n; i++ )
	{
		PP.push_back( i );
	}
}

void PGenerator::swap( size_t& a, size_t& b)
{
	size_t tmp = a;
	a = b;
	b = tmp;
}

void PGenerator::reverse( size_t k )
{
	size_t j = 1;
	while ( j < k )
		swap( PP[++j - 1], PP[--k - 1] );
}

void PGenerator::reverseL( size_t k )
{
	size_t q = PP.size() - k;
	//for reverse last k elements
	size_t j = PP.size() - 1;
	while ( q < j )
	{
		swap( PP[q], PP[j] );
		++q;
		--j;		
	}
}

void PGenerator::Antilex( size_t m )
{
	if ( m == 1 ) 
	{
		P.push_back( PP );
	} else
	{
		for ( size_t i = 1; i <= m; i++ )
		{
			Antilex( m - 1 );

			if ( i < m )
			{
				swap( PP[ i-1 ], PP[ m-1 ] );
				reverse( m - 1);
			}
		}
	}
}

void PGenerator::Lex( size_t m )
{
	
	if ( m == n ) 
	{
		P.push_back( PP );
	} else
	{
		for ( size_t i = n; i >= m; i--) 
		{
			Lex ( m + 1 );

			if ( i > m ) 
			{
				swap( PP[ m-1 ], PP[ i-1 ] );
				reverseL ( n - m );
			}
		}
	}
}

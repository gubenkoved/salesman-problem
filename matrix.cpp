#include "StdAfx.h"
#include "matrix.h"

int matrix::J( size_t cn)
{
	for ( size_t w = 0; w < HNum.size(); w++ )
	{
		if ( HNum[w] == cn )
			return w;
	}	
	return -1;
}

int matrix::I( size_t cn )
{
	for ( size_t w = 0; w < VNum.size(); w++ )
	{
		if ( VNum[w] == cn )
			return w;
	}	
	return -1;
}
matrix::matrix( vector< vector< int > > m )
{
	size_t n = m.size();
	mx = m;

	for ( size_t i = 1; i <= n; i++ ) //начальная нумерация 
	{
		HNum.push_back( i );
		VNum.push_back( i );
	}
}

void matrix::del( size_t i, size_t j ) // удаляет из матрицы m i строку и j столбец
{
	Set( j, i, -1 ); // устанавливает в матрице mx ребру (j,i) -1
	//востанавливаем нумерацию
	i = I( i );
	j = J( j );
	//теперь i и j истинные индексы в массиве mx
	
	VNum.erase( VNum.begin() + i );
	HNum.erase( HNum.begin() + j );

	if ( i >= mx.size() || j >= mx.size() )
		return;

	for ( size_t q = 0; q < mx.size(); q++  )
	{
		mx[q].erase( mx[q].begin() + j );
		nc[q].erase( nc[q].begin() + j );
	}

	mx.erase( mx.begin() + i );
	nc.erase( nc.begin() + i );
	
}

size_t matrix::min_in_col( size_t c )
{
	int min;
	bool first = true;
	for ( size_t i = 0; i < mx.size(); i++ )
	{
		if ( (mx[i][c] >= 0) && (first || ( mx[i][c] < min )) )
		{
			min = mx[i][c];
			first = false;
		}
	}
	return min;
}

size_t matrix::min_in_col( size_t c, size_t p )
{
	int min;
	bool first = true;
	for ( size_t i = 0; i < mx.size(); i++ )
	{
		if ( (mx[i][c] >= 0) &&( i != p ) && (first || ( mx[i][c] < min )) )
		{
			min = mx[i][c];
			first = false;
		}
	}
	return min;
}

size_t matrix::min_in_row( size_t r )
{
	int min;
	bool first = true;
	for ( size_t i = 0; i < mx.size(); i++ )
	{
		if ( (mx[r][i] >= 0) && (first || (mx[r][i] < min ) ))
		{
			min = mx[r][i];
			first = false;
		}
	}
	return min;
}

size_t matrix::min_in_row( size_t r, size_t p )
{
	int min;
	bool first = true;
	for ( size_t i = 0; i < mx.size(); i++ )
	{
		if ( (mx[r][i] >= 0) && (i != p ) && (first || (mx[r][i] < min )) )
		{
			min = mx[r][i];
			first = false;
		}
	}
	return min;
}
size_t matrix::bringing( ) //приведение
{
	size_t sum = 0;
	size_t n = mx.size();
	if ( !n )
		return 0;
	//приведение по строкам
	for ( size_t i = 0; i < n; i++ )
	{
		size_t br = min_in_row( i ); // находим минимум в строке
		sum += br; // увеличиваем сумму констант приведения
		for ( size_t j = 0; j < mx.size(); j++ ) // уменьшаем элементы в строке на мин эл. в строке
		{
			if ( mx[i][j] > 0 ) 
				 mx[i][j] -= br;
		}
		
	}
	//приведение по столбцам

	for ( size_t j = 0; j < n; j++ )
	{
		size_t br = min_in_col( j ); // находим минимум в строке
		sum += br; // увеличиваем сумму констант приведения
		for ( size_t i = 0; i < mx.size(); i++ ) // уменьшаем элементы в строке на мин эл. в строке
		{
			if ( mx[i][j] > 0 ) 
				 mx[i][j] -= br;
		}
		
	}
	return sum;
}

void matrix::costingNill( )
{
	nc.clear();
	vector< int > row;
	row.clear();
	size_t n = mx.size();

	for ( size_t q = 1; q <= n; q++ )
		row.push_back( -1 );

	for ( size_t q = 1; q <= n; q++ )
		nc.push_back( row );
	
	for ( size_t i = 0; i < n; i++ )
	{
		for ( size_t j = 0; j < n; j++ )
		{
			if ( mx[i][j] == 0 )
			{
				//оцениваем ноль в исходной матрице
				nc[i][j] = min_in_col( j, i ) + min_in_row( i, j );
			}
		}
	}

}
void matrix::findMaxNillCost( size_t &i, size_t &j )
{
	int maxCost;
	size_t mi = 0;
	size_t mj = 0;
	size_t n = nc.size();

	for ( size_t ii = 0; ii < n; ii++ )
		for ( size_t jj = 0; jj < n; jj++ )
		{
			if ( nc[ii][jj] > nc[mi][mj] )
			{
				mi = ii;
				mj = jj;
				goto end_of_for;
			}
		}

end_of_for:
	i = mi;
	j = mj;
}
void matrix::Set( size_t i, size_t j, int x )
{
	size_t ti = I( i );
	size_t tj = J( j );

	if ( ti == -1 || tj == -1 ) //такого ребра нету в mx
		return;

	mx[ti][tj] = x;
}

matrix::matrix( vector< vector< int > > m, SolutionTree* st )
{
	size_t n = m.size();
	mx = m;

	for ( size_t i = 1; i <= n; i++ ) //начальная нумерация 
	{
		HNum.push_back( i );
		VNum.push_back( i );
	}
	
	costingNill();
	while ( st->cnfg.begin != 0  )
	{
		if ( st->cnfg.on ) 
		{
			//вычеркиваем
			del( st->cnfg.begin, st->cnfg.end );
		} else
		{
			//ставим запрет
			Set( st->cnfg.begin, st->cnfg.end, -1 );
		}
		bringing();
		st = st->p;
	}
	/*costingNill();*/
}

bool matrix::bad( void )
{
	size_t n = mx.size();

	for ( size_t i = 0; i < n; i++ )
	{
		for ( size_t j = 0; j < n; j++ )
		{
			if ( mx[i][j] != -1 )
				return false;
		}
	}
	return true;
}
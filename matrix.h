#pragma once

class matrix
{
	vector< vector< int > > mx;
	vector< vector< int > > nc; //стоимости нулей
	vector< size_t > HNum; //горизонтальные подписи к матрице mx
	vector< size_t > VNum; //вертикальные
public:
	matrix( vector< vector< int > > m );
	matrix( vector< vector< int > > m, SolutionTree* st );
	size_t bringing( ); //приведение
	size_t min_in_col( size_t c );
	size_t min_in_col( size_t c, size_t p );
	size_t min_in_row( size_t r );
	size_t min_in_row( size_t r, size_t p );
	void findMaxNillCost( size_t &i, size_t &j );
	void del( size_t i, size_t j );
	void costingNill( );
	int J( size_t cn); //возвращает номер столбеца в соответствии с нумерацией HNum
	int I( size_t cn); //возвращает номер строки в соответствии с нумерацией VNum
	size_t HbyJ( size_t j ) { return HNum[j]; } //реальный номер города в jтом столбце
	size_t VbyI( size_t i ) { return VNum[i]; } //реальный номер города в iтой строке
	void Set( size_t i, size_t j, int x );
	bool bad( void );
	friend class solver;
};

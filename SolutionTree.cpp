#include "StdAfx.h"
#include "SolutionTree.h"

SolutionTree::PTST SolutionTree::active;
SolutionTree::SolutionTree( size_t RootCost )
{
	l = 0;
	r = 0;
	p = 0;
	cnfg = config( 0,0,0, RootCost);
	active = this;
}

void SolutionTree::branching( size_t begin, size_t end, size_t cost_with, size_t cost_without )
{
	active->r = new SolutionTree( 0,0, active, config( begin, end, 0, cost_without ) );
	active->l = new SolutionTree( 0,0, active, config( begin, end, 1, cost_with ) );

}

void SolutionTree::GoParent( void )
{
	if ( active->p )
		active = active->p;
}

void SolutionTree::GoLeft( void )
{
	if ( active->l )
		active = active->l;
}

void SolutionTree::GoRight( void )
{
	if ( active->r )
		active = active->r;
}

size_t SolutionTree::evaluteNumOfRib ( void )
{	
	size_t res = 0;
	PTST p = active;
	while ( active != this )
	{
		if ( active->cnfg.on )
			++res;
		GoParent();
	}
	active = p;

	return res;
}

size_t SolutionTree::GetCost ( void )
{
	return active->cnfg.cost;
}

vector< size_t > SolutionTree::CreateSolution( void )
{
	PTST p = active;
	vector< size_t > sol;
	vector< config > ribs;
	ribs.clear();
	sol.clear();
	
	while ( active != this )
	{
		if ( active->cnfg.on )
			ribs.push_back( active->cnfg );
		GoParent();
	}

	active = p;

	size_t pnt = 1;
	size_t count = 1;
	size_t n = ribs.size();
	sol.push_back( pnt );

	for ( size_t v = 0; v < ribs.size(); v++ )
	{
			if ( ribs[v].begin == pnt )
			{
				pnt = ribs[v].end;
				sol.push_back( pnt );
				ribs.erase( ribs.begin() + v );
				break;
			}
	}

	do
	{
		for ( size_t y = 0; y < ribs.size(); y++ )
			if ( ribs[y].begin == pnt )
			{
				pnt = ribs[y].end;
				ribs.erase( ribs.begin() + y );
				sol.push_back( pnt );
				break;
			}
		++count;
	} while ( ribs.size() && count <= n);

	return sol;
}

bool SolutionTree::isCycle( size_t len )
{
	PTST p = active;
	vector< config > ribs;
	ribs.clear();

	while ( active != this )
	{
		if ( active->cnfg.on )
			ribs.push_back( active->cnfg );
		GoParent();
	}	
	active = p;
	
	if ( ribs.size() < len )
		return false;

	size_t l = 0;
	size_t now = 1;
	bool finded;
	//идем из 1-го города
	while ( 1 )
	{
		finded = false;
		for ( size_t i = 0; i < ribs.size(); i++ )
		{
			if ( ribs[i].begin == now )
			{
				now = ribs[i].end;
				ribs.erase( ribs.begin() + i );
				++l;
				finded = true;
				continue;
			}
		}
		if ( !finded )
			break;
	}

	return l == len;

}

bool SolutionTree::isBadSolution( size_t len ) //есть ли циклы длины меньше len
{
	PTST p = active;
	vector< config > ribs;
	ribs.clear();

	while ( active != this )
	{
		if ( active->cnfg.on )
			ribs.push_back( active->cnfg );
		GoParent();
	}	
	active = p;

	//идем из k-го города
	vector< config > ribs_cpy = ribs;
	for ( size_t k = 0; k < ribs.size() ; k++ )
	{	
		size_t now = ribs[k].end;
		size_t needed = ribs[k].begin;
		size_t length = 1;
		ribs.erase( ribs.begin() + k );
		while ( 1 )
		{
			bool finded = false;
			if ( ribs.size() == 0 ) break;
			for ( size_t i = 0; i < ribs.size(); i++ )
				if ( ribs[i].begin == now )
				{
					++length;
					now = ribs[i].end;
					ribs.erase( ribs.begin() + i );
					finded = true;
					break;
				}
			if ( now == needed && length < len)
				return true;
			if ( !finded )
				break;
		}
		ribs = ribs_cpy;
	}

	return false;
}
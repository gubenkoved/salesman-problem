#pragma once
#include <set>

class SolutionTree
{
	typedef SolutionTree* PTST; //pointer to SolutionTree
	PTST l;
	PTST r;
	PTST p;
	config cnfg;
	static PTST active; //активная конфигурация
	
public:
	SolutionTree( size_t RootCost );
	SolutionTree( PTST _l, PTST _r, PTST _p, config _cnfg ) { l = _l; r = _r; p = _p; cnfg = _cnfg; }
	void branching( size_t begin, size_t end, size_t cost_with = 0, size_t cost_without = 0 ); //ветвление текущей конфигурации по ребру (begin,end); 

	void GoParent( void );
	void GoLeft( void );
	void GoRight( void );
	size_t evaluteNumOfRib ( void ); //возвращает кол-во ребер в активной частичной конфигурации
	size_t GetCost ( void ); 
	size_t GetThisCost ( void ) { return this->cnfg.cost; }
	vector< size_t > CreateSolution( void );
	bool isChecked( void ) { return active->cnfg.checked; }
	bool ThisChecked( void ) { return this->cnfg.checked; }
	void SetAsChecked( void ) { active->cnfg.checked = true; }
	void SetThisAsChecked( void ) { this->cnfg.checked = true; }
	bool isCycle( size_t len );
	bool isBadSolution( size_t len );
	friend class solver;
	friend class matrix;
};

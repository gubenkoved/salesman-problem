#include "StdAfx.h"
#include "solver.h"


void solver::solve( method m )
{
	solution.clear();
	if ( wrld->cities.size() == 0 ) return;

	switch ( m )
	{
		case direct:
			{
				size_t sum;
				size_t res = 0;
				size_t res_sum = 0;
				size_t j;
				vector <vector < size_t >> PP;
				PP.clear();
				PGenerator PGen( wrld->cities.size(), PGenerator::Order::direct_order );
				PP = PGen.get_p();
				
				for ( size_t i = 0; i < PP.size(); i++ )
				{
					sum = 0;
					for ( j = 1; j < PP[0].size(); j++ )
						sum += wrld->matrix[ PP[i][j-1] - 1 ][ PP[i][j] - 1 ]; 
					sum += wrld->matrix[ PP[i][PP[0].size()-1] - 1 ][ PP[i][0]-1 ];

					if ( sum < res_sum || i == 0 )
					{
						res_sum = sum;
						res = i;
					}
				}
				
				for ( size_t i = 0; i < PP[ res ].size(); i++ )
					solution.push_back( PP[ res ][ i ] );
				solution.push_back( PP[ res ][ 0 ] );
			}
			break;

		case little_method:
			 Little_method();
			 break;
	}
}
//<--block--> Little method

void solver::Little_method( void )
{
	const size_t TIME_LIMIT = 600000; //лимит выполнени€ 10 мин
	size_t TIME = GetTickCount();
	size_t NLM = 0;
	size_t n = wrld->matrix.size(); // n - кол-во ребер в полной конфигурации
	int low_bound = -1; //текуща€ нижн€€ граница полных конфигураций
	SolutionTree* best = 0;
	matrix m( wrld->matrix );
	//size_t rib = (m.mx.size() * (m.mx.size() - 1)) / 2; //кол-во ребер
	size_t brinding_sum = m.bringing(); // приведение. brinding_sum  -  нижн€€ оценка стоимости
	SolutionTree ST ( brinding_sum ); //дерево решений
	m.costingNill();
	//найдем любой локальный минимум

	size_t i; //строка с нулем максимальной оценки
	size_t j; //столбец -/-
	size_t WithoutCost;
	size_t WithCost;


	bool first = true;
	//ветвление влево, пока не дойдем до полной конфигурации
qwerty:
	do {
		if ( ST.isChecked() || m.bad() ) break;		
		
		m.costingNill();
		
		m.findMaxNillCost( i, j ); // ребро по которому пойдем ветвление дерева решени€. построим оценки...
		WithoutCost = ST.GetCost() + m.nc[i][j]; //оценка с поддеревом без ребра (i,j) возрастает на оценку нул€ (i,j)	
		i = m.VbyI( i ); //VbyI( i ) - реальный номер города в i - й строке
		j = m.HbyJ( j ); //HbyJ( j ) - реальный номер города в j - м столбце
		matrix buf = m;
		m.del( i, j );
		WithCost = ST.GetCost() + m.bringing();
		
		ST.branching( i, j, WithCost, WithoutCost );	
		
		if ( WithCost <= WithoutCost )
			ST.GoLeft();
		else
		{
			ST.GoRight();
			m = buf;
			m.Set( i, j, -1 );
			m.bringing();
		}

		if ( ST.isBadSolution( n ) ) //если преждевременное образование циклов
		{
			ST.SetAsChecked();
			ST.GoParent();
			ST.GoRight();
			m = buf;
			m.Set( i, j, -1 );
			m.bringing();
			
		}
	} while ( !m.bad() && (ST.evaluteNumOfRib() != n) && ( low_bound == -1 || ST.GetCost() < low_bound ) );
	
	if ( ST.isCycle( n ) &&  ((ST.GetCost() < low_bound)  || low_bound == -1) )  //если найдена полна€ конфигураци€ меньшей длинны
	{
			best = ST.active;
			low_bound = ST.GetCost();
			++NLM;
	}
	//р-т одного прохода
	//best = ST.active;
	//goto ext;
	if ( GetTickCount() - TIME > TIME_LIMIT )
		goto ext;

	ST.SetAsChecked();
	if ( ST.active->r )
		ST.active->r->SetThisAsChecked();
	if ( ST.active->l )
		ST.active->l->SetThisAsChecked();

	//есть полна€ конфигураци€, можно начать обратный проход, с вычеркиванием
	//поднимаемс€, если есть куда ветвитс€ ещЄ, то ветвимс€, потом также доходим в низ, и начинаем обратный проход
	//процесс продолжаетс€ когда ветвитс€ будет некуда
	
	while ( !ST.ThisChecked() )
	{
		if ( ST.l->ThisChecked() && ST.r->ThisChecked() ) break;
			ST.GoParent();

		if ( ST.active->l && ST.active->l->GetThisCost() >= low_bound )
			ST.active->l->SetThisAsChecked();
		if ( ST.active->r && ST.active->r->GetThisCost() >= low_bound )
			ST.active->r->SetThisAsChecked();

		if ( ST.active->l && ST.active->r && ST.active->l->ThisChecked() && ST.active->r->ThisChecked() )
			ST.SetAsChecked();
		else
		{
			if ( !ST.active->r->ThisChecked() )
				ST.GoRight();
			else if ( !ST.active->l->ThisChecked() )
				ST.GoLeft();
			else continue;
			matrix tmp ( wrld->matrix, ST.active );
			m = tmp;
			goto qwerty;
		}
	}

ext:	
	ST.active = best;
	if ( best )
		solution = ST.CreateSolution();
}
//<--end block--> 
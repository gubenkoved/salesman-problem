#pragma once

class config
{
	size_t begin; //начальна€ вершина
	size_t end; //конечна€ вершина
	bool on; //признак включаетс€ или исключаетс€ ребро (begin, end) из конфигурации
	size_t cost; //нижн€€ оценка текущей конфигурации, т.е. меньше этой оценки полные конфигурации ( маршруты ) стоить не могут
	bool checked;
public:
	config( size_t _begin, size_t _end, bool _on, size_t _cost );
	config( void ) { begin = 0; end = 0; on = 0; cost = 0; checked = 0;  }
	
	void check( void ) { checked = true; } // вычеркивание конфигурации, из дерева решений
	friend class SolutionTree;
	friend class matrix;
};

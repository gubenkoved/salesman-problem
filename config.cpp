#include "StdAfx.h"
#include "config.h"

config::config( size_t _begin, size_t _end, bool _on, size_t _cost )
{
	begin = _begin;
	end = _end;
	cost = _cost;
	on = _on;
	checked = false;
}
#include "StdAfx.h"
#include "city.h"

city::city( int _x, int _y, int _num)
{
	x = _x;
	y = _y;
	num = _num;
}

city::~city(void)
{
}


void city::draw( Graphics^ g )
{
	Drawing::Pen^ p = gcnew Drawing::Pen( Color::Black, 2 );
	g->FillEllipse( Brushes::Red, (float) x - r , (float) y - r, (float) 2*r, (float) 2*r );
	g->DrawEllipse( p, (float) x - r , (float) y - r, (float) 2*r, (float) 2*r );

	Drawing::StringFormat ^sf = gcnew Drawing::StringFormat;
	sf->Alignment = Drawing::StringAlignment::Center; 
	sf->LineAlignment = Drawing::StringAlignment::Center; // выравнивание
	Drawing::Font^ f = gcnew Drawing::Font( "Arial", 10 ); // создаем шрифт

	g->DrawString( num.ToString() , f, Brushes::White, (float) x, (float) y, sf );
}
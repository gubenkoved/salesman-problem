#include "StdAfx.h"
#include "world.h"


void world::draw( Graphics^ g, DrawMode dm )
{
	Bitmap ^bmp = gcnew Bitmap( 1280,1024 );
	Graphics^ buf = Graphics::FromImage( bmp );
	buf->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
	buf->Clear( Color::White );
	
	if ( cities.size() )
	{
		if ( dm == DrawMode::WithRoad )
		{
			for ( size_t i = 0; i < cities.size() - 1 ; i++ )
				 for ( size_t j = i + 1; j < cities.size(); j++ )
				 {
					 buf->DrawLine( Pens::Gray, cities[i].x, cities[i].y, cities[j].x, cities[j].y );
					 buf->DrawString( getDistance( i, j ).ToString() , gcnew Font( "Arial", 7 ), Brushes::Blue, (double) (cities[i].x + cities[j].x) /2., (double) (cities[i].y + cities[j].y) /2. );
				 }
		}

		for ( size_t i = 1; i < sol.size(); i++ )
		{
			buf->DrawLine( gcnew Pen( Color::Green, 2 ), cities[ sol[i-1] - 1].x, cities[sol[i-1] - 1].y, cities[sol[i] - 1].x, cities[sol[i] - 1].y );
		}
		
		for ( size_t i = 0; i < cities.size(); i++ )
			cities[i].draw( buf );

	}

	g->DrawImage( bmp, 0, 0 );
}

void world::drawSolving( Graphics^ g, string s )
{
	Bitmap ^bmp = gcnew Bitmap( 1280,1024 );
	Graphics^ buf = Graphics::FromImage( bmp );
	buf->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;	
	buf->Clear( Color::White );
	draw( buf );

	Drawing::StringFormat ^sf = gcnew Drawing::StringFormat;
	sf->Alignment = Drawing::StringAlignment::Center; 
	sf->LineAlignment = Drawing::StringAlignment::Center; // выравнивание
	Drawing::Font^ f = gcnew Drawing::Font( "Arial", 36 ); // создаем шрифт

	//buf->DrawString( gcnew System::String( s.c_str() ) , f, Brushes::Black, 1280/2, 1024/2, sf );
	buf->DrawString( gcnew System::String( s.c_str() ) , gcnew Font( "Calibri", 30 ), Brushes::Black, 1280/2, 1024/2, sf );
	g->DrawImage( bmp,0,0 );
	//h->DrawString(;
}

string world::SolutionToString( void )
{
	string res;
	char *buf = new char [100];
	int r = 0;
	
	for ( size_t i = 0; i < sol.size(); i++ )
	{
		res += string( itoa( sol[i], buf, 10 ) );
		if ( i != sol.size() - 1)
			res += "->";
		if ( i + 1 < sol.size() )
			r += matrix[ sol[ i ] - 1 ][ sol[ i + 1 ] - 1 ];
	}

	delete[] buf;
	char* rs = new char[ 10 ];
	itoa( r, rs, 10 );
	string rss ( rs );
	delete[] rs;
	return res + " [" + rss + "]";
}

void world::addCity( int _x, int _y )
{
	cities.push_back( city( _x, _y, cities.size() + 1 ) );
	createMatrix();
}

void world::delCity( city* c )
{
	sol.clear();
	for ( size_t i = 0; i < cities.size(); i++ )
	{
		if ( &cities[i] == c )
			cities.erase( cities.begin() + i );
	}

	for ( size_t i = 0; i < cities.size(); i++ )
	{
		cities[i].num = i + 1;
	}
	createMatrix();
}

city* world::under_mouse( int _x, int _y )
{
	for ( size_t i = 0; i < cities.size(); i++ )
	{
		 size_t rs = (cities[i].x - _x)*(cities[i].x - _x) + (cities[i].y - _y)*(cities[i].y - _y);
		 if ( rs <= 4*city::r * city::r )
			return &cities[i];
	} 
	return 0;
}

int world::getDistance( size_t i, size_t j )
{
	if ( i >= cities.size() || j >= cities.size() || i == j )
		return -1;

	return sqrt( (double)(cities[i].x - cities[j].x) * (cities[i].x - cities[j].x) + (cities[i].y - cities[j].y) * (cities[i].y - cities[j].y) );
}

void world::createMatrix( void )
{
	matrix.clear();
	vector< int > row;
	row.clear();
	for ( size_t q = 1; q <= cities.size(); q++)
		row.push_back( -1 );
	for ( size_t q = 1; q <= cities.size(); q++)
		matrix.push_back( row );

	for ( size_t i = 1; i <= cities.size(); i++ ) 
		for ( size_t j = 1; j <= cities.size(); j++ ) 
		{
			matrix[i-1][j-1] = getDistance( i-1, j-1 );
		}
}
void world::ToFile( void )
{
	ofstream ofs( "out.txt" );
	for ( size_t i = 0; i < matrix.size(); i++ )
	{
		for ( size_t j = 0; j < matrix.size(); j++ )
			if ( j !=  matrix.size() - 1 ) ofs << matrix[i][j] << "\t";
			else ofs << matrix[i][j];
		if ( i != matrix.size() - 1 ) 
			ofs << endl;
	}
	ofs.close();
}
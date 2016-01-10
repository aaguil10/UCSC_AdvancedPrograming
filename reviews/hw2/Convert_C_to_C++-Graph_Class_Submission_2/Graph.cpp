#include "Graph.h"


inline double Graph::probability()
{
	return 1.0*rand() / RAND_MAX;
}

Graph::Graph(int size, double density)
{
	_size = size;
	_g1 = new bool*[_size];
	for (int i = 0; i < _size; ++i)
	{
		_g1[i] = new bool[_size];
	}

	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			if (probability() < density) _g1[i][j] = true;
			else _g1[i][j] = false;
		}
	}
}

Graph::Graph(const Graph& obj)
{
	_size = obj._size;
	_g1 = new bool*[_size];
	for (int i = 0; i < _size; ++i)
	{
		_g1[i] = new bool[_size];
	}

	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			_g1[i][j] = obj._g1[i][j];
		}
	}
}


Graph::~Graph()
{
	// deletion of array
	for (int i = 0; i < _size; ++i)
	{
		delete[] _g1[i];
	}
	delete[] _g1;
}

ostream& operator<<(ostream& os, const Graph& graph)
{
	os << "Graph size: " << graph._size << endl;
	for (int i = 0; i < graph._size; ++i)
	{
		os << endl;
		for (int j = 0; j < graph._size; ++j)
		{
			os << graph._g1[i][j] << "\t";
		}
		os << endl;
	}

	return os;
}

void Graph::print()
{
	cout << "Graph size: " << _size << endl;
	for (int i = 0; i < _size; ++i)
	{
		cout << endl;
		for (int j = 0; j < _size; ++j)
		{
			cout << _g1[i][j] << "\t";
		}
		cout << endl;
	}
}

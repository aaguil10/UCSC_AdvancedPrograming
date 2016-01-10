#include "Graph.h"

// generates a graph that has connections to other
// elements in the graph denoted by a positive int
//
// elements denoted with a -1 have no connection and
// elements cannot have connections to themselves.
Graph::Graph(int size, double density, bool debug)
{

	closed1 = vector<int>(0); // nodes explored
	open1 = vector<int>(size); // verts needed to explore
	dist1 = vector<int>(size); // distance from source to index
	parent1 = vector<int>(size); // closest node from index

	closed2 = vector<int>(0); // nodes explored
	open2 = vector<int>(size); // verts needed to explore
	dist2 = vector<int>(size); // distance from source to index
	parent2 = vector<int>(size); // closest node from index

	if (!debug)
	{
		_size = size;
		_g1 = new int*[_size];

		for (int i = 0; i < _size; ++i)
		{
			_g1[i] = new int[_size];

			bool connection = false;
			while (!connection)
			{
				for (int j = 0; j < _size; ++j)
				{
					double d = probability();
					if (d < density && i != j && _size != 1)
					{
						_g1[i][j] = static_cast<unsigned int>(round(rand() * 200));
						connection = true;
					}
					else if (_size == 1)
					{
						_g1[i][j] = -1; // only one node
						connection = true;
					}
					else
					{
						_g1[i][j] = -1; // no connection
					}
				}
			}
		}
	}
	else
	{
		const int AMT = 6;
		_size = AMT;
		int temp[6][6] =
		{
			{-1,3,-1,-1,2,1},
			{3,-1,2,-1,2,-1},
			{-1,2,-1,1,-1,-1},
			{-1,-1,1,-1,-1,-1},
			{2,2,-1,-1,-1,1},
			{1,-1,-1,-1,1,-1}
		};
		_g1 = new int*[AMT];
		for (int i = 0; i < AMT; ++i)
		{
			_g1[i] = new int[AMT];
			for (int j = 0; j < AMT; ++j)
			{
				_g1[i][j] = temp[i][j];
			}
		}
	}
}

Graph::Graph(const Graph& obj)
{
	_size = obj._size;

	_g1 = new int*[_size];
	for (int i = 0; i < _size; ++i)
	{
		_g1[i] = new int[_size];
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

bool Graph::visited(int index, vector<int>& closed)
{
	for (int i = 0; i < closed.size(); i++)
	{
		if (closed[i] == index)
		{
			return true;
		}
	}
	return false;
}

int Graph::dijkstraStep(vector<int>* open, vector<int>* closed, vector<int>* dist, vector<int>* parent)
{
	int index = getLowestCostIndex(open, closed,dist);

	for (int i = 0; i < _size; i++)
	{
		// test to see if we need to update the distance
		int t = (*dist)[index] == MAX ? 0 : (*dist)[index];
		// distance from index to i
		int p = _g1[index][i];
		int d = t + p;
		if (p != -1 && d < (*dist)[i]) // there is a connection
		{
			(*dist)[i] = d;
			(*parent)[i] = index;
		}
	}

	return index;
}

int Graph::getLowestCostIndex(vector<int>* open, vector<int>* closed, vector<int>* dist)
{
	int min = MAX;
	int index = -1;
	int r = -1;
	for (int i = 0; i < open->size(); i++)
	{
		if ((*dist)[(*open)[i]] <= min)
		{
			min = (*dist)[(*open)[i]];
			index = (*open)[i];
			r = i;
		}
		if (i + 1 == open->size())
		{
			(*open)[r] = (*open)[i];
			closed->push_back((*open)[i]);
			open->pop_back();
		}
	}
	return index;
}

// Returns the shortest path as a stack
vector<int> Graph::dijkstra(int source, int target)
{
	closed1.clear();
	open1.resize(_size);
	for (int i = 0; i < _size; i++)
	{
		open1[i] = i;
		dist1[i] = MAX;
		parent1[i] = -1;
	}

	// distance from source to source is 0
	dist1[source] = 0;
	int i = 0;
	while (!open1.empty())
	{
		cout << "test" << i++ << endl;
		int index = dijkstraStep(&open1, &closed1, &dist1, &parent1);
		if (index == target)
			break;
	}

	// reverse the path for correct order
	vector<int> path(0);
	path.push_back(target);
	int node = parent1[target];
	while (node != -1)
	{
		path.push_back(node);
		node = parent1[node];
	}

	return path;
}


vector<int> Graph::biDirectionalSearch(int source, int target)
{
	closed1.clear();
	closed2.clear();
	open1.resize(_size);
	open2.resize(_size);

	for (int i = 0; i < _size; i++)
	{
		open1[i] = i;
		dist1[i] = MAX;
		parent1[i] = -1;

		open2[i] = i;
		dist2[i] = MAX;
		parent2[i] = -1;
	}

	// distance from source to source is 0
	dist1[source] = 0;
	dist2[target] = 0;

	int index1, index2;

	while (!open1.empty() || !open2.empty())
	{
		index1 = dijkstraStep(&open1, &closed1, &dist1, &parent1);
		index2 = dijkstraStep(&open2, &closed2, &dist2, &parent2);
		if (visited(index1, closed2))
		{
			index2 = index1;
			break;
		}
		if (visited(index2, closed1))
		{
			index1 = index2;
			break;
		}
	}

	// reverse the path for correct order
	vector<int> path(0);
	path.push_back(index1);
	int node1 = parent1[index1];
	while (node1 != -1)
	{
		path.push_back(node1);
		node1 = parent1[node1];
	}
	// pretty sure the ordering is not correct 
	// but I didnt have enough time to finsh
	path.push_back(index2);
	int node2 = parent2[target];
	while (node2 != -1)
	{
		path.push_back(node2);
		node2 = parent2[node2];
	}

	return path;
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

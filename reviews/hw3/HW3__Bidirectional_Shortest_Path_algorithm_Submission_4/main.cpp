
// Dijkstra's by Tyler Gatta - tgatta@ucsc.edu && Logan McGhee - LMcGhee@ucsc.edu
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>
#include <vector>
#include <climits>
#include <random>

typedef std::mt19937 MyRNG; //Random number generator merssane twister
uint32_t seed_val = time(0); // Seed rand
MyRNG rng;
int infinity = INT_MAX;
inline double probability()
{
    return 1.0*rand()/RAND_MAX;
}

class Graph
{
public:
    Graph(int s, double density)  //Constructor
    {
        std::uniform_int_distribution<uint32_t> uint_dist10(1,200);
        rng.seed(seed_val);
        this->size = s;
        std::vector<int> emptyVec(size, infinity); //Create a vector of size s initialized to false     eg: s = 3    [0,0,0]
        for (int i = 0; i < s; i++)  //Set s vectors in the matrix to the false vectors          eg: s = 3    [(0,0,0),(0,0,0),(0,0,0)]
        {
            this->matrix.push_back(emptyVec);
        }
        for (int i = 0; i < this->size; i++)  //For each vector in 1D
        {
            for(int j = 0; j< this->size; j++)  //For each vector in 2D
            {
                if(probability()<density && i<j)this->matrix[i][j] = uint_dist10(rng);  //Set element to 5 probability is less than density
                if(i == j) this->matrix[i][j] = infinity;
                if(i>j) this->matrix[i][j] = this->matrix[j][i];
            }
        }
    }

    std::vector<std::vector<int>> getMatrix()
    {
        return this->matrix;   //Getter function for matrix
    }
    int getSize()
    {
        return this->size;
    }; //Getter function for size
    void print_graph(); //Prints contents of the graph
    bool is_connected(); //Returns true if the graph is connected
    std::vector<std::vector<int>> matrix; //matrix is a 2 dimensional vector of ints representing distances

private:
    int size;

};

void Graph::print_graph()
{
    std::cout<<"Graph size: "<<this->size<<"\n";
    for (auto& element:this->matrix)   //For each vector in 1D
    {
        for(auto element2: element) //For each vector in 2D
        {
            std::cout<<element2<<" ";  //Print element
        }
        std::cout<<"\n";
    }
}

std::ostream &operator << (std::ostream &out, Graph &g)   //Bit shift operator overload
{
    out<<"Graph size: "<<g.getSize()<<"\n\n";
    for (auto& element:g.getMatrix())   //For each vector in 1D
    {
        for(auto element2: element) //For each vector in 2D
        {
            std::cout<<element2<<" ";  //Print element
        }
        std::cout<<"\n";
    }
    return out;
}


int Dijkstra(Graph g)
{
    time_t startTime; // For measuring time it takes for a function
    time(&startTime);
    int s = g.getSize();

    std::uniform_int_distribution<uint32_t> uint_distGraph(0,s-1); //Random number between 0 and size for picking target nodes
    int target = uint_distGraph(rng);
    int start = uint_distGraph(rng);
    while(start== target) start = uint_distGraph(rng); // If target and start are the same, we pick a new random
    std::cout<<"Start Node: "<< start << " Target node: "<< target<< " \n";

    int x;
    std::vector<std::vector<int>> m = g.getMatrix();

    std::vector<int> distFromSource(s, infinity); //Distances initialized to infinity (INT_MAX)
    std::vector<int> previous(s, infinity);


    distFromSource[start] = 0; //Set distance from start node to 0

    std::list<int> Q;
    for(int i=0; i < s; i++)
    {
        Q.push_back(i);  //Builds a set of every node
    }
    while(!Q.empty()) //While there are unvisited nodes
    {
        int shortestDist = infinity; // Shortest will be the node closest to the source
        int shortest = 0;
        for(int i=0; i < s; i ++)   //For each node, find the one with the smallest dist and make it shortest
        {
            for(auto element:Q)     //That has not yet been removed from Q
            {
                if(element == i)
                {
                    if(distFromSource[i]<= shortestDist) //Finding smallest node
                    {
                        shortestDist = distFromSource[i];
                        shortest = i;
                        break;
                    }
                }
            }
        }
        if (distFromSource[shortest] == infinity) break; //This happens when there is no possible path

        if(target == shortest) //If the target node is found
        {
            std::cout<<"Target node found!\n";
            break;
        }
        Q.remove(shortest); // Remove node from Q

        for(int i=0; i<s; i++) //For each node
        {
            if (g.matrix[shortest][i]>0 && g.matrix[shortest][i]!=infinity && shortest!=i)   // For each neighbor
            {
                for(auto element:Q)
                {
                    if(element == i) //That has not yet been removed from Q
                    {
                        int alt = distFromSource[shortest] + m[shortest][i]; //Adding dist from start to the dist from neighbor
                        if (alt < distFromSource[i]) //Update if smaller distance
                        {
                            distFromSource[i] = alt;
                            previous[i]= shortest;
                        }
                    }
                }
            }
        }
        //std::cout <<"End loop\n";
        x = shortest;
    }
    int diameter=1; //Diameter represents the number of nodes in the shortest path
    while(x !=start) //Work backwards through the list of shortest path nodes and add one to diameter for each
    {
        diameter++;
        x = previous[x];
    }
    time_t endTime;
    time(&endTime);
    double seconds = difftime( endTime, startTime); //Set seconds to how long the function took
    std::cout << "Runtime = " << seconds << " seconds.\n";
    return diameter;
}


int biDirectionalDjkstra(Graph g)
{
    time_t startTime; // For measuring time it takes for a function
    time(&startTime);
    int s = g.getSize();
    std::uniform_int_distribution<uint32_t> uint_distGraph(0,s-1); //Random number between 0 and size for picking target nodes
    int biStart = uint_distGraph(rng);
    int start = uint_distGraph(rng);
    while(start== biStart) start = uint_distGraph(rng); // If target and start are the same, we pick a new random
    std::cout<<"First Start Node: "<< start << " Second Start Node: "<< biStart<< " \n";

    int x, x2;
    std::vector<std::vector<int>> m = g.getMatrix();

    std::vector<int> distFromSource(s, infinity);   //Distances initialized to infinity (INT_MAX)
    std::vector<int> previous(s, infinity);
    std::vector<int> biDistFromSource(s, infinity); //Distances initialized to infinity (INT_MAX)
    std::vector<int> biPrevious(s, infinity);
    std::vector<int> fringe;
    std::vector<int> biFringe;

    distFromSource[start] = 0; //Set distance from start node to 0
    biDistFromSource[biStart] = 0; //Set distance from start node to 0

    std::list<int> Q;
    for(int i=0; i < s; i++)
    {
        Q.push_back(i);
    }
    while(!Q.empty())
    {
        int shortestDist = infinity; // Shortest will be the node closest to the source
        int shortest = 0;
        int biShortestDist = infinity;
        int biShortest = 0;
        fringe.clear();
        biFringe.clear();


        for(int i=0; i < s; i ++)   //For each node, find the one with the smallest dist and make it shortest
        {
            for(auto element:Q)     //That has not yet been removed from Q
            {
                if(element == i)
                {
                    if(distFromSource[i]<= shortestDist)
                    {
                        shortestDist = distFromSource[i];       // finding next shortest neighbor
                        shortest = i;
                    }
                }
            }
            for(auto element:Q)     //That has not yet been removed from Q
            {
                if(element == i)
                {
                    if(biDistFromSource[i]<= biShortestDist)
                    {
                        biShortestDist = biDistFromSource[i];
                        biShortest = i;
                    }
                }
            }
        }

        for(int i=0; i<s; i++)      //add fringe nodes to respective fringe vectors and then compare.
        {
            if (g.matrix[shortest][i]>0 && g.matrix[shortest][i]!=infinity && shortest!=i)      // FOR EACH NEIGHBOR OF SHORTEST
            {
                for(auto element:Q)     //That has not yet been removed from Q
                {
                    if(element == i)
                    {
                        fringe.push_back(i);
                    }
                }
            }
            if (g.matrix[biShortest][i]>0 && g.matrix[biShortest][i]!=infinity && biShortest!=i)
            {
                for(auto element:Q)
                {
                    if(element == i)
                    {
                        biFringe.push_back(i);
                    }
                }
            }
        }

        for(auto& element:fringe)
        {
            int done = 0;
            for(auto element2:biFringe)
            {
                if(element2==element)   //If the fringes touch one another.
                {
                    //std::cout << "Fringe connection found!" << std::endl;
                    done=1;
                    int temp = shortest;
                    int temp2 = biShortest;
                    break;
                }
            }
            if(done == 1) break;
        }


        if (distFromSource[shortest] == infinity) break; //This happens when there is no possible path
        if (biDistFromSource[biShortest] == infinity) break; //This happens when there is no possible path

        Q.remove(shortest); // Remove node from Q

        for(int i=0; i<s; i++)
        {
            if (g.matrix[shortest][i]>0 && g.matrix[shortest][i]!=infinity && shortest!=i)      // FOR EACH NEIGHBOR OF SHORTEST
            {
                for(auto element:Q)     //That has not yet been removed from Q
                {
                    if(element == i)
                    {
                        int alt = distFromSource[shortest] + m[shortest][i];
                        if (alt < distFromSource[i])
                        {
                            distFromSource[i] = alt;
                            previous[i]= shortest;
                        }
                    }
                }
            }
            if (g.matrix[biShortest][i]>0 && g.matrix[biShortest][i]!=infinity && biShortest!=i)      // FOR EACH NEIGHBOR OF SHORTEST
            {
                for(auto element:Q)     //That has not yet been removed from Q
                {
                    if(element == i)
                    {
                        int alt = biDistFromSource[biShortest] + m[biShortest][i];
                        if (alt < biDistFromSource[i])
                        {
                            biDistFromSource[i] = alt;
                            biPrevious[i]= biShortest;
                        }
                    }
                }
            }
        }
        //std::cout <<"End loop\n";
        x = shortest;
        x2 = biShortest;

    } //End while

    // Increase diameter based on previous array to return how long the link was.
    int diameter=0   ;
    while(x != start)
    {
        diameter++;
        x = previous[x];
    }
    while(x2 != biStart)
    {
        diameter++;
        x2 = biPrevious[x2];
    }
    time_t endTime;
    time(&endTime);     // counts the total time since start of run by comparing system time.
    double seconds = difftime( endTime, startTime);
    std::cout << "Runtime = " << seconds << " seconds.\n";
    return diameter;
}


int main()
{
    Graph test1(1000,0.1); //Create a graph of size 10 with density 0.7
    Graph test2(1000,0.01); //Create a graph of size 8 with density 0.5
    std::cout<<("Test simple graph generation\n\n");
    //std::cout<<test1;   //Overloaded <<
    std::cout<<("\nEND of TEST 1\n\n");
    //std::cout<<test2;
    //std::cout<<("\nEND of TEST 2\n\n");
    for(int i = 0; i < 10; i ++) //Sparse Dijkstra
    {
        std::cout<<"Diameter: "<< Dijkstra(test1)<<"\n\n";
    }
    for(int i = 0; i < 10; i ++) //Sparse BiDijkstra
    {
        std::cout<<"Diameter: "<< biDirectionalDjkstra(test1)<<"\n\n";
    }
     for(int i = 0; i < 10; i ++) //Dense Dijkstra
    {
        std::cout<<"Diameter: "<< Dijkstra(test2)<<"\n\n";
    }
    for(int i = 0; i < 10; i ++) //Dense BiDijkstra
    {
        std::cout<<"Diameter: "<< biDirectionalDjkstra(test2)<<"\n\n";
    }

    return 1;
}

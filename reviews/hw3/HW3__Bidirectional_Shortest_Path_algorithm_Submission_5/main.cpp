//Tyler Marshik
//Rashad Kayed
//February 6, 2014

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>

using namespace std;
int MAX = 1000;

//Probability initialization made into an inline function
inline double probability(){
    return 1.0*rand()/RAND_MAX;
}


//This defines the class graph
class graph {
public:
    graph (int s, double density);
    void random(double edge, int max_distance);
	void print_edges();
    void print();
    void djik(int source, int destination);
    void bidirectional(int source, int destination);
    
    //These values are hidden from the user
private:
    int size; double density;
    vector<list<pair<int, int>>> G;
};


//This is the constructor for a graph
graph::graph(int s, double density):
size(s), density(density){
	G=vector<list<pair<int, int>>> (MAX);
    //Iterating through the vector
    for ( int i = 0; i < s; i++ ) {
        for ( int j = i+1; j < s; j++ ){
            if(probability()< density){
                //make an edge
				//first pair represents length, and second represents edge
                int tmp = (rand() % 10) + 1;
                G[i].push_front(make_pair(tmp, j));
                G[j].push_front(make_pair(tmp, i));
            }
        }
    }
	for ( int i = 0; i < this->size; i++ ) {
		G[i].sort();
	}
}

//prints the adjacency list
void graph::print_edges(){
	for ( int i = 0; i < this->size; i++ ) {
		cout << i << ": ";
		for ( auto it = G[i].begin(); it!=G[i].end(); ++it) {
			cout << it->second << " at " << it->first << ", ";
			//*it.pop_front();
		}
		cout << "\n";
	}
}

//get smallest unvisited sorted
int get_min(vector<pair<int, int>> sorted, vector<int> done){
	int min=-1;
	int p=0;
	for(auto it=sorted.begin(); it!=sorted.end();++it){
		if(it->first==-1 || it->first==0){
			//unvisited or source
		}else if(done[p]==1){
			//already completed
		}else{
			if(min==-1) {
				min=p;
			}else if(sorted[min].first > it->first){
				min=p;
			}
		}
		p++;
	}
	return min;
}

//performs the unidirectional djiksta's
void graph::djik(int source, int destination){
    int curr;
    cout << "Unidirectional Djikstra's: \n";
    vector<int> done (this->size);
	vector<pair<int, int>> sorted(this->size);
	for(int i=0; i<this->size; i++){
        //initialize vector values
		sorted[i].first=sorted[i].second=-1;
        done[i]=0;
    }
    curr=source;
    sorted[curr].first=0;
    while(curr!=-1){
        //marks curr as visited
        done[curr]=1;
        if(curr==destination) break;
        for ( auto it = G[curr].begin(); it!=G[curr].end(); ++it) {
			if(done[it->second]==1){
               //do nothing since already visited
            }else if(sorted[it->second].first==-1){
                //first connection
                sorted[it->second].first=sorted[curr].first + it->first;
                sorted[it->second].second=curr;
            }else{
                //not first connection
                if(sorted[it->second].first > (sorted[curr].first + it->first)){
                    sorted[it->second].first=sorted[curr].first + it->first;
                    sorted[it->second].second=curr;
                }
            }
		}
        curr=get_min(sorted, done);
    }
    if(curr==-1){
        cout << "A path could not be determined\n";
    }else{
        cout << "path is: " << destination << " <- ";
        curr=destination;
        for(;;){
            cout << sorted[curr].second << " <- ";
            curr=sorted[curr].second;
            if(curr==source) break;
        }
        cout << "\nDistance is " << sorted[destination].first << endl;
    }
}

//gets the path and distance from source to destination
void interpret_bidirectional(int curr1, int curr2, vector<int> done1, vector<int> done2, vector<pair<int, int>> sorted1, vector<pair<int, int>> sorted2){
    if(curr1==-1 || curr2==-1){
        cout << "A path could not be determined\n";
    }else{
		list<int> final, final2;
		for(int q=0; q<done1.size(); q++){
			if(sorted1[q].first!=-1){
				final.push_back(q);
			}
			if(sorted2[q].first!=-1){
				final2.push_back(q);
			}
		}
		list<int> matches;
		while(!final.empty() && !final2.empty()){
			if(final.front()==final2.front()){
				matches.push_back(final.front());
				final2.pop_front();
				final.pop_front();
			}else{
				if(final.front()<final2.front()) final.pop_front();
				else final2.pop_front();
			}
		}
		int least=100, num=100;
		for(auto it = matches.begin(); it!=matches.end(); ++it){
			if(least>sorted1[*it].first+sorted2[*it].first){
				least=sorted1[*it].first+sorted2[*it].first;
				num=*it;
			}
		}
		curr1=curr2=num;
        cout << "Distance is " << sorted1[curr1].first + sorted2[curr2].first << endl;
    }
}

//performs the bidirectional Djiksta's
void graph::bidirectional(int source, int destination){
    int curr1, curr2;
    cout << "Bidirectional Djikstra's: \n";
    vector<int> done1 (this->size);
    vector<int> done2 (this->size);
	vector<pair<int, int>> sorted1(this->size);
    vector<pair<int, int>> sorted2(this->size);
	for(int i=0; i<this->size; i++){
        //initialize vector values
		sorted1[i].first=sorted1[i].second=-1;
        done1[i]=0;
        sorted2[i].first=sorted2[i].second=-1;
        done2[i]=0;
    }
    curr1=source;
    curr2=destination;
    sorted1[curr1].first=sorted2[curr2].first=0;
    while(curr1!=-1 || curr2==-1){
        if(curr1==destination) break;
        for ( auto it = G[curr1].begin(); it!=G[curr1].end(); ++it) {
			if(done1[it->second]==1){
                //do nothing since already visited
            }else if(sorted1[it->second].first==-1){
                //first connection
                sorted1[it->second].first=sorted1[curr1].first + it->first;
                sorted1[it->second].second=curr1;
            }else{
                //not first connection
                if(sorted1[it->second].first > (sorted1[curr1].first + it->first)){
                    sorted1[it->second].first=sorted1[curr1].first + it->first;
                    sorted1[it->second].second=curr1;
                }
            }
		}
        curr1=get_min(sorted1, done1);
		for(int q = 0; q<done1.size(); q++){
			if((done1[q]==1 && done2[q]==1) || (done1[q]==1 && q==destination)){
				curr1=curr2=q;
			}
		}
		if(curr1==curr2) break;
		done1[curr1]=1;
        
        //run from reverse
        if(curr2==source) break;
        for ( auto it = G[curr2].begin(); it!=G[curr2].end(); ++it) {
			if(done2[it->second]==1){
                //do nothing since already visited
            }else if(sorted2[it->second].first==-1){
                //first connection
                sorted2[it->second].first=sorted2[curr2].first + it->first;
                sorted2[it->second].second=curr2;
            }else{
                if(sorted2[it->second].first > (sorted2[curr2].first + it->first)){
                    sorted2[it->second].first=sorted2[curr2].first + it->first;
                    sorted2[it->second].second=curr2;
                }
            }
		}
        curr2=get_min(sorted2, done2);
		for(int q = 0; q<done1.size(); q++){
			if((done1[q]==1 && done2[q]==1) || (done2[q]==1 && q==source)){
				curr1=curr2=q;
			}
		}
		if(curr1==curr2){
			break;
		}
		done2[curr2]=1;
    }
	interpret_bidirectional(curr1, curr2, done1, done2, sorted1, sorted2);
}

//gets a destination not equal to the source
int get_destination(int source){
	int destination = rand() % MAX;
	while(source==destination){
        destination = rand() % MAX;
    }
	cout << "Path from " << source << " to " << destination << endl;
	return destination;
}

//builds the graphs and performs unidirectional and bidirectional djikstra's
int main(int argc, const char * argv[])
{
	clock_t one, two, three, four;
	one=two=three=four=0;
	//run algorithms 100 times
	for(int i=0; i<100; i++){
		srand((int)time(0));
		graph test1(MAX,.1);
		graph test2(MAX,.01);
		cout << "Graph of " << MAX << " nodes with a density of .1\n";
		int source = rand() % MAX;
		int destination= get_destination(source);
		clock_t t=clock();
		test1.djik(source, destination);
		one+=clock()-t;
		cout << "took " << (float)(clock() - t)/CLOCKS_PER_SEC << " seconds\n";
		t=clock();
		test1.bidirectional(source, destination);
		two+=clock()-t;
		cout << "took " << (float)(clock() - t)/CLOCKS_PER_SEC << " seconds\n";
		cout << "Graph of " << MAX << " nodes with a density of .01\n";
		source = rand() % MAX;
		destination= get_destination(source);
		t=clock();
		test2.djik(source, destination);
		three+=clock()-t;
		cout << "took " << (float)(clock() - t)/CLOCKS_PER_SEC << " seconds\n";
		t=clock();
		test2.bidirectional(source, destination);
		four+=clock()-t;
		cout << "took " << (float)(clock() - t)/CLOCKS_PER_SEC << " seconds\n\n";
	}
	//take average
	one=one/100;
	two=two/100;
	three=three/100;
	four=four/100;
	cout << "unidirectional djikstra's for .1 density took about  " << (float)one/CLOCKS_PER_SEC << " seconds\n";
	cout << "bidirectional djikstra's for .1 density took about   " << (float)two/CLOCKS_PER_SEC << " seconds\n";
	cout << "unidirectional djikstra's for .01 density took about " << (float)three/CLOCKS_PER_SEC << " seconds\n";
	cout << "bidirectional djikstra's for .01 density took about  " << (float)four/CLOCKS_PER_SEC << " seconds\n";
    return 0;
}

 /*
This program creates an 11x11 hex board with the pieces randomly chosen between red and blue, or 1 and 2
*/
 
 
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <new>
#include <list>
#include <random>
 
using namespace std;

class node{
	
  public:
    int weight;
    int connected;

  	bool operator<(const node &n){ return weight<n.weight;}
};

class graph{

  public:
	friend ostream& operator<< (ostream &out, const graph &graph);
	graph(int); //the constructor we use
//ACCESSOR FUNCTIONS
	int getsize(){
		return size;
	};
	node element(int row, int column){
		return matrix[row][column];
	}
//ALTERING FUNCTION
	void changec(int row, int column, int newvalue){
		matrix[row][column].connected=newvalue;	
	}

  private:
    int size;
    vector<vector<node>> matrix;
};



graph::graph(int s):
   size(s)
   {
   matrix.resize(s,vector<node>(s,{0,0}));
   //This will give each node a random value from 1 to 2.
   for(int i=0;i<s;i++){ 
   	 random_device random;
   	 int rn = (random()%2)+1;
   	 for(int j=0;j<s;j++){
   	   matrix[i][j].weight=rn;
   	 }
   }
   //This goes through each node that has a special case (corners and edges) then goes onto the rest
   for(int i =0; i < s; ++i){
        if(i==0){
           matrix[1][i].connected = 1;
           matrix[i][1].connected = 1;
           matrix[11][i].connected = 1;
           matrix[i][11].connected = 1;
        }else if(i==120){
           matrix[119][i].connected = 1;
           matrix[i][119].connected = 1;
           matrix[i][109].connected = 1;
           matrix[109][i].connected = 1;
        }else if(i==10){
           matrix[i][9].connected=1;
           matrix[9][i].connected=1;
           matrix[i][21].connected=1;
           matrix[21][i].connected=1;
           matrix[20][i].connected=1;
           matrix[i][20].connected=1;
        }else if(i==110){
           matrix[i][99].connected=1;
           matrix[99][i].connected=1;
           matrix[i][111].connected=1;
           matrix[111][i].connected=1;
           matrix[100][i].connected=1;
           matrix[i][100].connected=1;           
        }else if(i%11==0){
           matrix[i-11][i].connected=1;
           matrix[i][i-11].connected=1;
           matrix[i][i+11].connected=1;
           matrix[i+11][i].connected=1;
           matrix[i-10][i].connected=1;
           matrix[i][i-10].connected=1;
           matrix[i+1][i].connected=1;
           matrix[i][i+1].connected=1;
        }else if((i+1)%11==0){
           matrix[i-11][i].connected=1;
           matrix[i][i-11].connected=1;
           matrix[i][i+11].connected=1;
           matrix[i+11][i].connected=1;
           matrix[i+10][i].connected=1;
           matrix[i][i+10].connected=1;
           matrix[i-1][i].connected=1;
           matrix[i][i-1].connected=1;           
        }else if(i>0&&i<10){
           matrix[i-1][i].connected=1;
           matrix[i][i-1].connected=1;
           matrix[i+1][i].connected=1;
           matrix[i][i+1].connected=1;
           matrix[i][i+11].connected=1;
           matrix[i+11][i].connected=1;
           matrix[i+10][i].connected=1;
           matrix[i][i+10].connected=1;
        }else if(i>110&&i<120){
           matrix[i-1][i].connected=1;
           matrix[i][i-1].connected=1;
           matrix[i+1][i].connected=1;
           matrix[i][i+1].connected=1;
           matrix[i][i-11].connected=1;
           matrix[i-11][i].connected=1;
           matrix[i-10][i].connected=1;
           matrix[i][i-10].connected=1;         
        }else {
           matrix[i-1][i].connected=1;
           matrix[i][i-1].connected=1;
           matrix[i+1][i].connected=1;
           matrix[i][i+1].connected=1;
           matrix[i][i-11].connected=1;
           matrix[i-11][i].connected=1;
           matrix[i-10][i].connected=1;
           matrix[i][i-10].connected=1;           
           matrix[i][i+11].connected=1;
           matrix[i+11][i].connected=1;
           matrix[i+10][i].connected=1;
           matrix[i][i+10].connected=1;         
         }
	}
}

ostream& operator<< (ostream &out, const node &node){
	
	out<< "Weight: "<<node.weight << " Value: "<<node.connected<<endl;
	
	return out;
}

//This prints out our board as best as possible
ostream& operator<< (ostream &out, const graph &graph){
	int space_count=0;
	int row = 0;
	int column = 0;
	while(row<121){
	    for(int k=0;k<space_count;k++){
			out<<" ";
		}	
		for(int i=0;i<11;i++){		
			out << "|";
			//
			if(graph.matrix[row][column].weight==1){
				out << "R";
			}else{
				out << "B";
			}
			row++;					
		}
		out <<"|"<< endl;
		for(int k=0;k<space_count;k++){
			out<<" ";
		}
		cout<<" ";			
		for(int e=0;e<11;e++){
			cout << "\\/";
		}
		cout<<"\\";
		cout<<endl;
		space_count++;
	}
	return out;
}

//I didn't have enough time to work on this and get it working
/*int doDFS(const graph &graph){
	int winner=0;
	vector<int> bluelist(graph.getsize(),0);
	//vector<int> redlist(graph.getsize(),0);
	for(int i= 0;i<graph.getsize();i++){
		if(graph.element(i,0).weight==2) continue;
		for(int j=0;j<graph.getsize();i++){
			if(graph.element(i,j).connected==1&&graph.element(i,j).weight==1){
				bluelist.push_back(j);	
			}
						
		}
	}	
}*/

 

int main()
{
   graph test1(121);
   cout << test1 <<endl;
   return 0;
}
 

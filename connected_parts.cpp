#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;


void print(vector<int> A) {
   cout <<endl<< "The vector elements are : ";

   for(int i=0; i < A.size(); i++){
    cout << A[i] << ' ';
   }
   cout<<endl;
};


class SCC{

    public:

    int num_nodes=875714;
    vector<int> edge_pointer ={1};
    vector<vector<int>> Adj;
    vector<vector<int>> Adj_reverse;
    vector<int> visited;
    vector<int> visited_scc;
    vector<int> visit_time;
    vector<int> Ans;
    vector<int> scc;
    int counter = 0;

    string file_address;

    SCC(string f_address){
        visited.resize(num_nodes,0);
        visited_scc.resize(num_nodes,0);
        visit_time.resize(num_nodes,0);
        Adj.resize(num_nodes,edge_pointer);
        Adj_reverse.resize(num_nodes,edge_pointer);
        file_address=f_address;
        set_adj();
    }


    void set_adj(){
        ifstream infile;
        string row;
        int node;
        int tail=-1;
        int head=-1;
        infile.open(file_address);

        while(!infile.eof()){
            getline(infile,row);
            stringstream iss(row);
            
            iss>>tail>>head;
            tail--;
            head--;

            Adj[tail].push_back(head);
            Adj_reverse[head].push_back(tail);
        }
        

        infile.close();
    }

    void set_visit_times(){
        for (int node=0; node<num_nodes; node++){
            if (visited[node]==0){
                DFS(node);
            }
        }
    }

    void DFS(int node){
        visited[node]=1;
        int len_edge = Adj_reverse[node].size();
        for(int j= 1; j<len_edge; j++){
            if(visited[Adj_reverse[node][j]]==0){
                DFS(Adj_reverse[node][j]);
            }
        }
        visit_time[counter] = node;
        counter++;
    }


    void find_scc(){
        for (int i=visit_time.size()-1; i>-1; i--){
            if (visited_scc[visit_time[i]]==0){
                scc={};
                reverse_DFS(visit_time[i]);
                Ans.push_back(scc.size());
            }
        }
    }

    void reverse_DFS(int node){
        visited_scc[node]=1;
        scc.push_back(node);
        for(int j=1; j<Adj[node].size(); j++){
            if(visited_scc[Adj[node][j]]==0){
                reverse_DFS(Adj[node][j]);
            }
        }
    }


    void find_Ans(){
        set_visit_times();
        // find_scc();
        // sort(Ans.begin(),Ans.end(),greater<int>());

        // for (int i=0; i<5;i++){
        //     cout<<Ans[i]<<endl;
        // }
    }

};




int main(){
    string File_address = "G:\\My Drive\\course\\Algorithm\\SCC\\SCC.txt";

    SCC connected(File_address);
    connected.find_Ans();
    return 0;
}
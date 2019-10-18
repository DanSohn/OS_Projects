/**
 * Program that examines multiple system states consisting of several processes and resources.
 * Will state whether or not any processes are in deadlock or not.
 */


#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
#include<vector>
#include<sstream>
#include<stdlib.h>
#include<algorithm>
#include<string>
#include<unordered_map>
using namespace std;


unordered_map<int, int> outgoing;
unordered_map<int, list<int>> incoming;

struct Edge{
    int src, dest;

};

void sort(){
    /*
    L ← Full list that will contain the deadlocked elements
    S ← Set of all nodes with no outgoing edge
    while S is non-empty do
        remove a node n from S
        remove n from L
        for each node m with an edge e from m to n do
        . in other words, for all nodes that are incoming to n
            remove edge e from the graph
            if m has no other outgoing edges then
                insert m into S
    if graph has edges then
        return error   (graph has at least one cycle)
    else
        return L   (a topologically sorted order)
    */
    list<int> myList;
    list<int> zeroOut;
    unordered_map<int, int>:: iterator it;
    for (it = outgoing.begin(); it != outgoing.end(); it++)
    {
        myList.push_back(it->first);

        if(it->second == 0){
            zeroOut.push_back(it->first);
        }
    }
    /*
    cout << "ELEMENTS IN MYLIST"<<endl;
    for (auto v : myList)
        cout << v << "\n";
    cout<< "ELEMENTS IN ZEROOUT"<<endl;
    for(auto w : zeroOut)
        cout << w << "\n";
*/
    while(zeroOut.size() != 0){
        //find first node in S, then remove n from S
        int n = zeroOut.front();
        zeroOut.pop_front();
        //remove n from L
        myList.remove(n);

        //find all nodes m with edges e from m to n
        unordered_map<int, list<int> >:: iterator it;
        for (it = incoming.begin(); it != incoming.end(); it++)
        {
            if(it->first == n){
                list<int>::iterator ite = it->second.begin();
                //remove incoming key node, the whole thing
                myList.remove(n);
                for(int i = 0; i < it->second.size();i++){
                    //list all incoming nodes
                    //cout << it->first << "  " << *ite << endl;
                    //*ite contains the value of the node -> our node
                    outgoing[*ite]--;
                    if(outgoing[*ite] == 0){
                        zeroOut.push_back(*ite);
                    }
                    //remove edge e from the graph
                    //if m has no other outgoing edges then insert m into S
                    advance(ite, 1);
                }
            }
        }
    }//end of while
    //cout <<"size of list: " << myList.size()<<endl;
    cout<<"Deadlocked processes: ";
    if(myList.size() == 0){
        cout <<"none"<<endl;
    }else{

        myList.sort();
        //cout<<"hello";
        for (auto el : myList){
            if(el > 1000000){
                cout << el - 1000000 << " ";
            }
            //cout << el << " " ;
        }
        cout<<"\n";
    }

}

// Driver program to test above functions
int main(int argc, char ** argv)
{
    vector<int> to;
    vector<int> from;
    vector<Edge> edges;

    ifstream config; //configuration file
    string conffile; //config file name

    if( argc < 2){
        cout << "Usage: deadlock <config file>\n";
        return 0;
    }else{
        conffile = argv[1];
    }
    //open the file
    config.open(conffile.c_str());
    //get the graph edges
    string line, equal, pro, res; //strings for parsing a line in the config file

    while(1){
        incoming.clear();
        outgoing.clear();
        int numVertices = 0;
        int next = 0;
        vector<int> L;
        while(1){
            getline(config, line);
            istringstream iss(line);
            if(line.rfind("#", 0) == 0 || config.eof()){
                //end of graph, computer now
                //    iterating over all value of umap
                //cout << "\nAll Elements IN INCOMING: \n";
                unordered_map<int, list<int> >:: iterator it = incoming.begin();

                for (it = incoming.begin(); it != incoming.end(); it++)
                {
                    // Create iterator pointing to second element
                    list<int>::iterator ite = it->second.begin();

                    // Advance the iterator by 2 positions,

                    // itr works as a pointer to pair<string, double>
                    // type itr->first stores the key part  and
                    // itr->second stroes the value part
                    for(int i = 0; i < it->second.size();i++){
                        //cout << it->first << "  " << *ite << endl;
                        advance(ite, 1);

                    }
                }

                unordered_map<int, int>:: iterator itr;
                //cout << "\nAll Elements in outgoing: \n";
                for (itr = outgoing.begin(); itr != outgoing.end(); itr++)
                {
                    // itr works as a pointer to pair<string, double>
                    // type itr->first stores the key part  and
                    // itr->second stroes the value part
                    //cout << itr->first << "  " << itr->second << endl;
                }
                sort();
                break;
            }else{
                iss.str(line);
                iss >> pro >> equal >> res; //get the process and resource
                iss.clear();
                if(outgoing.find(stoi(res)) == outgoing.end()){
                    outgoing[stoi(res)] = 0;
                }
                if(outgoing.find(stoi(pro) + 1000000) == outgoing.end()){
                    outgoing[stoi(pro) + 1000000] = 0;
                }
                if(!equal.compare("->")){

                    //cout << "Storing key "<< stoi(pro) + 1000000<< "with value of" << stoi(res)<<endl;
                    //cout << "out, process key _ has value _"<<stoi(pro) + 1000000<<outgoing[stoi(pro) + 1000000] <<endl;
                    if(outgoing.find(stoi(pro) + 1000000) == outgoing.end()){
                        outgoing[stoi(pro) + 1000000] = 0;
                    }else{
                        outgoing[stoi(pro) + 1000000]++;
                    }

                    incoming[stoi(res)].push_back(stoi(pro)+1000000);
                }else{
                    // process <- resource
                    //cout << "Storing key "<<stoi(res)<< "with value of" <<  stoi(pro) + 1000000<<endl;
                    //cout << "out, resource key _ has value _"<<stoi(res)<<outgoing[stoi(res)] << endl;

                    if(outgoing.find(stoi(res)) == outgoing.end()){
                        outgoing[stoi(res)] = 0;
                    }else{
                        outgoing[stoi(res)] ++;
                    }

                    incoming[stoi(pro) + 1000000].push_back(stoi(res));
                }
            }
        }
        if(config.eof()){
            break;
        }
    }
	return 0;
}

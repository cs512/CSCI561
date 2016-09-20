// 561HW1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Node
{
	public:
		void setNode(int s, Node *p, int c, int h, int timestamp);
		void setParent(Node A);
		Node *getParent();
		void setCost(int c);
		int getCost();

	public:
		int state;
		int cost;
		int heuristic;
		Node *parent;
		int time;

		friend bool operator<(Node n1,Node n2)  
		{  
			if((n1.cost+n1.heuristic)!=(n2.cost+n2.heuristic)) {
				return (n1.cost+n1.heuristic)>(n2.cost+n2.heuristic);
			}else if(n1.cost!=n2.cost){
				return n1.cost>n2.cost;
			}else {
				return n1.time>n2.time;
			}
		}
};

void Node::setNode(int s, Node *p, int c, int h, int timestamp)
{
	state = s;
	parent = p;
	cost = c;
	heuristic = h;
	time = timestamp;
}

void Node::setParent(Node A)
{
	parent = &A;
}

Node *Node::getParent()
{
	return parent;
}

void Node::setCost(int c)
{
	cost = c;
}

int Node::getCost()
{
	return cost;
}

typedef list<Node> LISTNODE;

//judge whether a state had appeared
int isGotState(string s, vector<string> v, int number)
{
	for(int i=0;i<number;i++){
		if (v[i]==s) return 1;
	}
	return 0;
}

int getStateIndex(string s, vector<string> v, int number)
{
	for(int i=0;i<number;i++){
		if (v[i]==s) return i;
	}
}

string showPath(Node a, vector<string> state)
{
	string temp1, temp2;
	stringstream ss;
	if (a.parent == NULL){  
		cout << state[a.state] << " " << a.cost << "\n";
		ss<<a.cost;
		ss>>temp2;
		temp1 = state[a.state]+" "+temp2+"\n";
		return temp1;
	}else{
		temp1 = showPath(*(a.parent), state);
		cout << state[a.state] << " " << a.cost << "\n";
		ss<<a.cost;
		ss>>temp2;
		temp1 = temp1+state[a.state]+" "+temp2+"\n";
		return temp1;
	}
}

void BFSearch(int st, int go, vector<vector<vector<int> > > G, int staten, vector<string> state)
{
	Node start, goal, rightn, tempnode;
	Node an;
	LISTNODE openL, expandL, tempL;
	LISTNODE::iterator j;
	priority_queue<Node> qn; 
	int i;
	int alreadyhave = 0;

	start.setNode(st, NULL, 0, 0, 0);
	goal.setNode(go, NULL, 0, 0, 0);
	openL.push_front(start);
	while(!openL.empty()){
		rightn = openL.back();
		openL.pop_back();
		expandL.push_front(rightn);
		cout << "expanding: " << rightn.state << " parent: " << rightn.parent << endl;
		if(rightn.state == goal.state) break;
		for(i=0;i<staten;i++){
			if (G[rightn.state][i][0] > 0){
				for(j=openL.begin();j!=openL.end();j++){
					tempnode = *j;
					if (tempnode.state == i) alreadyhave = 1;
				}
				for(j=expandL.begin();j!=expandL.end();j++){
					tempnode = *j;
					if (tempnode.state == i) alreadyhave = 1;
				}
				if(alreadyhave == 0){
					an.setNode(i, &expandL.front(), rightn.cost+1, 0, G[rightn.state][i][1]);
					cout << "an: "<< an.state << " ";
					qn.push(an);
				}
				alreadyhave = 0;
			}
		}
		cout << "EndExpand" << endl;
		while(!qn.empty()){
			openL.push_front(qn.top());
			cout << "pushing " << qn.top().state << endl;
			qn.pop();
		}
	}
	cout << "----------" << endl;
	string path;
	ofstream fout("E:\\16FALL\\561\\HW1\\output.txt");
	if (!fout.is_open())  {
		cout << "Error opening file"; 
		exit (1); 
	}
	path = showPath(rightn, state);
	path = path.substr(0, path.size()-1);
	fout << path;
	fout.close();
}

void DFSearch(int st, int go, vector<vector<vector<int> > > G, int staten, vector<string> state)
{
	cout << "Using DFS..." << endl;
	Node start, goal, rightn, tempnode;
	Node an;
	LISTNODE openL, expandL, tempL;
	LISTNODE::iterator j;
	priority_queue<Node> qn; 
	int i;
	int alreadyhave = 0;

	start.setNode(st, NULL, 0, 0, 0);
	goal.setNode(go, NULL, 0, 0, 0);
	openL.push_front(start);
	while(!openL.empty()){
		rightn = openL.front();
		openL.pop_front();
		expandL.push_front(rightn);
		cout << "expanding: " << rightn.state << " parent: " << rightn.parent << endl;
		if(rightn.state == goal.state) break;
		for(i=0;i<staten;i++){
			if (G[rightn.state][i][0] > 0){
				for(j=openL.begin();j!=openL.end();j++){
					tempnode = *j;
					if (tempnode.state == i) alreadyhave = 1;
				}
				for(j=expandL.begin();j!=expandL.end();j++){
					tempnode = *j;
					if (tempnode.state == i) alreadyhave = 1;
				}
				if(alreadyhave == 0){
					an.setNode(i, &expandL.front(), rightn.cost+1, 0, G[rightn.state][i][1]);
					cout << "an: "<< an.state << " ";
					qn.push(an);
				}
				alreadyhave = 0;
			}
		}
		cout << "EndExpand" << endl;
		while(!qn.empty()){
			tempL.push_front(qn.top());
			qn.pop();
		}
		while(!tempL.empty()){
			openL.push_front(tempL.front());
			tempL.pop_front();
			cout << "pushing " << openL.front().state << endl;
		}
	}
	cout << "----------" << endl;
	string path;
	ofstream fout("E:\\16FALL\\561\\HW1\\output.txt");
	if (!fout.is_open())  {
		cout << "Error opening file"; 
		exit (1); 
	}
	path = showPath(rightn, state);
	path = path.substr(0, path.size()-1);
	fout << path;
	fout.close();
}

void UCSearch(int st, int go, vector<vector<vector<int> > > G, int staten, vector<string> state)
{
	Node start, goal, rightn, tempnode;
	Node an;
	LISTNODE openL, expandL, tempL;
	LISTNODE::iterator j;
	priority_queue<Node> openpq; 
	int i;
	int alreadyhave = 0;
	int inlist=0;

	cout << "Using UCS" << endl;
	start.setNode(st, NULL, 0, 0, 0);
	goal.setNode(go, NULL, 0, 0, 0);
	openL.push_front(start);
	openpq.push(start);
	while(!openpq.empty()){
		while(inlist==0){
			rightn = openpq.top();
			openpq.pop();
			cout << rightn.state << " in pq, testing if in list..." << endl;
			for(j=openL.begin();j!=openL.end();j++){
				tempnode = *j;
				if(tempnode.state == rightn.state) {
					if(tempnode.cost == rightn.cost) inlist = 1;
					cout << "find " << (*j).state << " inlist = " << inlist << endl;
					openL.erase(j);
					break;
				}
			}
			if(rightn.state == 3) cout << "YEAH " << inlist << endl;
		}
		inlist = 0;
		expandL.push_front(rightn);
		cout << "expanding: " << rightn.state << " parent: " << rightn.parent << endl;
		if(rightn.state == goal.state) break;
		for(i=0;i<staten;i++){
			if (G[rightn.state][i][0] > 0){
				for(j=expandL.begin();j!=expandL.end();j++){
					tempnode = *j;
					if (tempnode.state == i) alreadyhave = 1;
				}
				for(j=openL.begin();j!=openL.end();j++){
					tempnode = *j;
					if ((tempnode.state == i)&&(alreadyhave == 0)) {
						alreadyhave = 1;
						if (tempnode.cost>rightn.cost+G[rightn.state][i][0]){
							(*j).parent = &rightn;
							(*j).cost = rightn.cost+G[rightn.state][i][0];
						}
					}
				}
				if(alreadyhave == 0){
					an.setNode(i, &expandL.front(), rightn.cost+G[rightn.state][i][0], 0, G[rightn.state][i][1]);
					cout << "an: "<< an.state << " ";
					openpq.push(an);
					openL.push_front(an);
				}
				alreadyhave = 0;
			}
		}
		cout << "EndExpand" << endl;
	}
	cout << "----------" << endl;
	string path;
	ofstream fout("E:\\16FALL\\561\\HW1\\output.txt");
	if (!fout.is_open())  {
		cout << "Error opening file"; 
		exit (1); 
	}
	path = showPath(rightn, state);
	path = path.substr(0, path.size()-1);
	fout << path;
	fout.close();
}

void AStarSearch(int st, int go, vector<vector<vector<int> > > G, int staten, vector<string> state, vector<int> hn)
{
	Node start, goal, rightn, tempnode;
	Node an;
	LISTNODE openL, expandL, tempL;
	LISTNODE::iterator j;
	priority_queue<Node> openpq; 
	int i;
	int alreadyhave = 0;
	int inlist=0;

	cout << "Using A*..." << endl;
	start.setNode(st, NULL, 0, hn[st], 0);
	goal.setNode(go, NULL, 0, hn[go], 0);
	openL.push_front(start);
	openpq.push(start);
	while(!openpq.empty()){
		while(inlist==0){
			rightn = openpq.top();
			openpq.pop();
			cout << rightn.state << " in pq, testing if in list..." << endl;
			for(j=openL.begin();j!=openL.end();j++){
				tempnode = *j;
				if(tempnode.state == rightn.state) {
					if(tempnode.cost == rightn.cost) inlist = 1;
					cout << "find " << (*j).state << " inlist = " << inlist << endl;
					openL.erase(j);
					break;
				}
			}
			if(rightn.state == 3) cout << "YEAH " << inlist << endl;
		}
		inlist = 0;
		expandL.push_front(rightn);
		cout << "expanding: " << rightn.state << " parent: " << rightn.parent << endl;
		if(rightn.state == goal.state) break;
		for(i=0;i<staten;i++){
			if (G[rightn.state][i][0] > 0){
				for(j=expandL.begin();j!=expandL.end();j++){
					tempnode = *j;
					if (tempnode.state == i) alreadyhave = 1;
				}
				for(j=openL.begin();j!=openL.end();j++){
					tempnode = *j;
					if ((tempnode.state == i)&&(alreadyhave == 0)) {
						alreadyhave = 1;
						if (tempnode.cost>rightn.cost+G[rightn.state][i][0]){
							(*j).parent = &rightn;
							(*j).cost = rightn.cost+G[rightn.state][i][0];
						}
					}
				}
				if(alreadyhave == 0){
					an.setNode(i, &expandL.front(), rightn.cost+G[rightn.state][i][0], hn[i], G[rightn.state][i][1]);
					cout << "an: "<< an.state << " cost: " << an.cost << " h: " << an.heuristic <<endl;
					openpq.push(an);
					openL.push_front(an);
				}
				alreadyhave = 0;
			}
		}
		cout << "EndExpand" << endl;
	}
	cout << "----------" << endl;
	string path;
	ofstream fout("E:\\16FALL\\561\\HW1\\output.txt");
	if (!fout.is_open())  {
		cout << "Error opening file"; 
		exit (1); 
	}
	path = showPath(rightn, state);
	path = path.substr(0, path.size()-1);
	fout << path;
	fout.close();
}

int main()
{
	string mode, start, goal, vhead, vtail, point;
	int i, j, nmode=0, n1, n2, weight, h, statenumber=0, vheadindex=0, vtailindex=0, pointindex=0, timestamp=1, startindex=0, goalindex=0;
	ifstream fin("E:\\16FALL\\561\\HW1\\input.txt");  
	if (!fin.is_open())  {
		cout << "Error opening file"; 
		exit (1); 
	}

	//search strategy
	fin >> mode;
	cout << "Mode: " << mode << endl;
	if (mode == "BFS"){
		nmode = 1;
	}else if(mode == "DFS"){
		nmode = 2;
	}else if(mode == "UCS"){
		nmode = 3;
	}else{
		nmode = 4;
	}

	//start & goal
	fin >> start >> goal;
	cout << "Start: " << start << " Goal: " << goal << endl;

	//number of live traffic lines
	fin >> n1;
	cout << "n1: " << n1 << endl;


	vector<string> state(2*n1);
	vector<vector<vector<int> > > graph;
	graph.resize(2*n1);
	for (i=0;i<2*n1;i++){
		graph[i].resize(2*n1);
	}
	for (i=0;i<2*n1;i++){
		for (j=0;j<2*n1;j++){
			graph[i][j].resize(2);
		}
	}
	//live traffic lines
	for (i=0;i<n1;i++){
		fin >> vhead >> vtail >> weight;
		cout << "from " << vhead << " to " << vtail << " Time: " << weight << endl;

		if (!isGotState(vhead, state, statenumber)){
			state[statenumber] = vhead;
			statenumber++;
		}
		vheadindex = getStateIndex(vhead, state, statenumber);
		if (!isGotState(vtail, state, statenumber)){
			state[statenumber] = vtail;
			statenumber++;
		}
		vtailindex = getStateIndex(vtail, state, statenumber);

		graph[vheadindex][vtailindex][0] = weight;
		graph[vheadindex][vtailindex][1] = timestamp;
		//graph[vtailindex][vheadindex][0] = weight;
		//graph[vtailindex][vheadindex][1] = timestamp;
		timestamp++;

		for( j=0;j<2*n1;j++){
			for(int k=0;k<2*n1;k++){
				cout << graph[j][k][0] << " ";
			}
			cout << endl;
		}
	}

	//number of sunday traffic lines
	fin >> n2;
	cout << "n2: " << n2 << endl;

	vector<int> hn(2*n1);
	//sunday traffic lines
	for(i=0;i<n2;i++){
		fin >> point >> h;
		pointindex = getStateIndex(point, state, statenumber);
		hn[pointindex] = h;
	}

	for(i=0;i<statenumber;i++){
		if (state[i]==start) startindex = i;
		if (state[i]==goal) goalindex = i;
	}

	switch(nmode){
		case 1:
			BFSearch(startindex, goalindex, graph, statenumber, state);
			break;
		case 2:
			DFSearch(startindex, goalindex, graph, statenumber, state);
			break;
		case 3:
			UCSearch(startindex, goalindex, graph, statenumber, state);
			break;
		case 4:
			AStarSearch(startindex, goalindex, graph, statenumber, state, hn);
			break;
		default:
			BFSearch(startindex, goalindex, graph, statenumber, state);
	}
	fin.close();
	system("pause");
	return 0;
}


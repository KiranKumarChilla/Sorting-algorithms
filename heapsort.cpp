#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include<time.h>
using namespace std;
ofstream output;

// Quick Sort Function Declarations 
void VectorQuickSort(vector<int> &nodeElements, int nodeStart, int nodeEnd);
int VectorPartition(int start, int end, int pivot, vector<int> &nodeElements);
void swap(int &a, int &b);



//Quick Sort Algorithm 
void VectorQuickSort(vector<int> &nodeElements, int nodeStart, int nodeEnd) {
	int pivot = nodeElements[nodeStart];
	int pivotElement;

	if (nodeEnd > nodeStart) {
		pivotElement = VectorPartition(nodeStart, nodeEnd, pivot, nodeElements);
		nodeElements[pivotElement] = pivot;
		VectorQuickSort(nodeElements, nodeStart, pivotElement - 1);
		VectorQuickSort(nodeElements, pivotElement + 1, nodeEnd);
	}
}

// Vector Partitioning 
int VectorPartition(int start, int end, int pivot, vector<int> &nodeElements) {
	int leftElem = start;
	int rightElem = end;

	while (leftElem < rightElem) {
		while(pivot < nodeElements[rightElem] && rightElem > leftElem) {
			rightElem--;
		}
		swap(nodeElements[leftElem], nodeElements[rightElem]);

		while(pivot >= nodeElements[leftElem] && leftElem < rightElem) {
			leftElem++;
		}
		swap(nodeElements[rightElem], nodeElements[leftElem]);
	}

	return leftElem;
}

// Swap function
void swap(int &a, int&b) {
	int temp = a;
	a = b;
	b = temp;
}


// Function to Print Data in each Node
void printDataInNodes(vector< vector<int> >V) {
	output<<endl<<"Data in each Node: "<<endl;
	for (unsigned int i = 0; i < V.size() ;i++) {
		output<<endl<< "Node " << i<<": ";
		for (unsigned int j=0; j < V[i].size(); j++)
    		output << V[i][j] << '\t';
	}
}
clock_t x1,x2,t;


int main() {
x1=clock();
	unsigned int N, noOfHeapNodes; // N -> No of Data Values, HeapN -> No.of Heap Nodes

	printf("Enter number of data elements to be sorted: ");
	scanf("%u",&N); // Input No. of Elements to take

	printf("Enter number of heap nodes: ");
	scanf("%u", &noOfHeapNodes); // Input no of Heap Nodes

	// open data file in read mode.
    ifstream inFile;
    inFile.open("data.txt"); 
    output.open("result.txt");
    int dataValue; 
    vector < vector <int> > V(noOfHeapNodes);
    // cout<<V.size();
    
    for(int i = 0; i < N && !inFile.eof(); i++) {
  		inFile >> dataValue; // Taking each data Values
    	V[i % noOfHeapNodes].push_back(dataValue); // Using Round Robin methodology to randomize the data intake
    	//output<<"inputvalues are"<<dataValue<<"\n"; 	
    }

    // Printing Nodes after Data Intake 
    printDataInNodes(V);
x1=clock();
    // Performing Quick Sort on the given data set
    for(int i = 0;i<noOfHeapNodes; i++) {
    	VectorQuickSort( V[i], 0 , V[i].size() - 1);
    }

    // Printing Nodes after Data Quick Sorting all Individual Nodea (First step) 
    printDataInNodes(V);

    vector <int> finalNode;
    int temp = noOfHeapNodes;
    vector <int> nodeX;


    while(temp) {

	    output<< endl << "Elements of Central Node: " << endl;
	    for(int i = 0; i< noOfHeapNodes; i++) {
	    	if(V[i].size()) {
		    	nodeX.push_back(V[i].back());
		    	V[i].pop_back();
		    	output<<nodeX[i]<<endl;
	    	}
	    }

	    make_heap(nodeX.begin(), nodeX.end());
	    sort_heap (nodeX.begin(),nodeX.end());

	    for( int i=0;i<nodeX.size();i++)
	    	output<<endl<<"Maximum of node "<<i<<": "<<nodeX[i]<<endl;

	    bool flag = true;
	    while(flag) {
	    	flag = false;
		    for(int i = 0; i < V.size(); i++) {
		    	
		    	if(!V[i].size()) { break; flag = true;}

		    	if( V[i].back() > nodeX[0] ) {
		    		output<< "swapping "<< V[i].back()<<" with "<< nodeX[0]<<endl;
		    		flag = true;
		    		//Swapping code
		    		int tmp = nodeX[0];
		    		nodeX[0] = (V[i].back());

		    		V[i].pop_back();
		    		V[i].push_back(tmp);
		    		// Re sort
		    		make_heap(nodeX.begin(), nodeX.end());
		    		sort_heap (nodeX.begin(),nodeX.end());
		    		VectorQuickSort( V[i], 0 , V[i].size() - 1);

		    		// Printing Nodes after Data Quick Sorting all Individual Nodea (First step) 
   					printDataInNodes(V);

		    	}
		    }
		}

		for(int i = nodeX.size() - 1; i >= 0;i--) {
			finalNode.insert(finalNode.begin(), nodeX[i]);
			output<<nodeX.back()<<endl;
			nodeX.pop_back();
		}

		temp--;
	}
x2=clock();
float t((float)x2-(float)x1);
float sec = t / CLOCKS_PER_SEC;
output<<"timetaken is"<<sec<<endl;




	//Printing the Final Result of Sorted Elements in Central Node
	output<<endl<< "Final Sorted Data is: "<<endl;
	for( int i =0; i< finalNode.size(); i++)
		output<<finalNode[i]<<"\t";

	return 0;
}

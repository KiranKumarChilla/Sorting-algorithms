#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <time.h>
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
// Algorithm for Merge Sort
vector<int> merge(const vector<int>& vec_left, const vector<int>& vec_right)
{
    vector<int> res;
    unsigned left = 0, right = 0;

    while(left < vec_left.size() && right < vec_right.size())
    {
        // If the left value is smaller than the right it goes next
        // into the resultant vector
        if(vec_left[left] < vec_right[right])
        {
            res.push_back(vec_left[left]);
            left++;
        }
        else
        {
            res.push_back(vec_right[right]);
            right++;
        }
    }
 // Push the remaining data from both vectors onto the resultant
    while(left < vec_left.size())
    {
        res.push_back(vec_left[left]);
        left++;
    }

    while(right < vec_right.size())
    {
        res.push_back(vec_right[right]);
        right++;
    }

    return res;
}
// Algorithm for Merge Sort
vector<int> merge_sort(vector<int>& V)  {

    if(V.size() == 1)
        return V;

    std::vector<int>::iterator middleVal = V.begin() + (V.size() / 2);

    vector <int> vec_left(V.begin(), middleVal);
    vector <int> vec_right(middleVal, V.end());

    vec_left = merge_sort(vec_left);
    vec_right = merge_sort(vec_right);

    return merge(vec_left, vec_right);
}


// Function to Print Data in each Node
void printDataInNodes(vector< vector<int> >V) {
	for (unsigned int i = 0; i < V.size() ;i++) {
	output<<endl<< "Node " << i<<": ";
		for (unsigned int j=0; j < V[i].size(); j++)
    		output << V[i][j] << '\t';
	}
}


int main() {
clock_t x1,x2;
x1=clock();
	unsigned int N, noOfHeapNodes; // N -> No of Data Values,N -> No.of Heap Nodes

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
    	//output<<dataValue<<"\n"; 	
    }

    // Printing Nodes after Data Intake
output<<endl<<"elements in each node are"; 
    printDataInNodes(V);

    // Performing Quick Sort on the given data set
output<<endl<<"elements after initial sorting";
    for(int i = 0;i<noOfHeapNodes; i++) {
    	VectorQuickSort( V[i], 0 , V[i].size() - 1);
    }

    // Printing Nodes after Data Quick Sorting all Individual Nodea (First step) 
    printDataInNodes(V);

    //Creating Central Node (Node X)
    vector <int> nodeX;
    output<<endl<< "Maximum Elements in  Central Node: " <<endl;
    for(int i = 0; i< noOfHeapNodes; i++) {
    	nodeX.push_back(V[i].back());
V[i].pop_back();
    	output<<nodeX[i]<<endl;
    }


    // Performing Sort based on Central Node values by Taking each Node into Central Heap Node
   std::vector<int>mode;
std::vector<int>temp;
  for (unsigned int i = 0; i < V.size() ;i++) {
for(unsigned int j =0;j<nodeX.size();j++)
{	temp.push_back(nodeX.back());
nodeX.pop_back();}
std::merge(temp.begin(),temp.end(),V[i].begin(),V[i].end(),std::back_inserter(nodeX));
//merge_sort(nodeX);
sort(nodeX.begin(),nodeX.end());
temp.erase(temp.begin(),temp.end());
	
}

//float sec = t / CLOCKS_PER_SEC;
//out<<"time taken is :"<<sec;
	// Printing the Final Result of Sorted Elements in Central Node
	output<<endl<< "Final sorted data is ";
	for(int i =0; i< nodeX.size(); i++)
	output<<nodeX[i]<<"\n";
x2=clock();
float t((float)x2 - (float)x1);
float sec = t / CLOCKS_PER_SEC;
output<<"time taken is :"<<sec;


	return 0;
}

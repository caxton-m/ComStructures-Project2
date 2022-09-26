// Computing Structures Fall 2022
// DSA 5005
// Project 2
// Original editor - Aditya Narasimhan
// Modified by Caxton Muchono

#include <iostream>
#include <string>

using namespace std;

// class node to store one node's details
template <class DT>
class Node
{
    friend ostream& operator<< (ostream& s, const Node<DT>& N);
protected:
    int nodeNumber;  // field to store node's number
    string nodeInfo; // field to store node's information
    DT yearCreated;  // field to store the year of the node created
    string location; // field to store the location

public:
    Node() {  // default constructor
        nodeNumber = 0;
        nodeInfo = "";
        yearCreated = NULL;
        location = "";
    } 

    // getters
    string getNodeInfo() {
        return nodeInfo;
    }
    int getNodeNumber() {
        return nodeNumber;
    }
    DT getYearCreated() {
        return yearCreated;
    }
    string getLocation() {
        return location;
    }

    // setters
    void setNodeInfo(string newInfo, DT newYearCreated, string newLoc) {

        nodeInfo = newInfo;
        setYearCreated(newYearCreated);
        setLocation(newLoc);

        //yearCreated = newYearCreated;
        //location = newLoc;

    } // V2: updated
    void setNodeNumber(int newNum) {
        nodeNumber = newNum;
    }
    void setYearCreated(DT newYearCreated) {
        yearCreated = newYearCreated;
    }
    void setLocation(string newLocation) {
        location = newLocation;
    }

    void display() {
        cout << getNodeNumber() << ": " << getNodeInfo() << ", " << getYearCreated() <<
            ", " << getLocation() << endl;
    } // display node details

    ~Node() {} // destructor
};

template <class DT>
ostream& operator<<(ostream& s, const Node<DT>& N)
{
    
    s << *(N.nodeNumber) << ": " << *(N.nodeInfo) << ", " << *(N.yearCreated) <<
        ", " << *(N.location) << endl;
    return s;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store one edge's details
template <class DT>
class Edge
{
protected:
    Node<DT>* u;     // field to store source node pointer
    Node<DT>* v;     // field to store destination node pointer
    string edgeInfo; // field to store edge information
    DT yearsKnown;   // u and v - years known

public:
    Edge() { // default constructor
        u = NULL;
        v = NULL;
        edgeInfo = "";
        yearsKnown = NULL;
    }
    // getters
    Node<DT>* getu() {
        return u;
    }
    Node<DT>* getv() {
        return v;
    }
    string getEdgeInfo() {
        return edgeInfo;
    }
    DT getYearsKnown() {
        return yearsKnown;
    }

    // setters
    void setu(Node<DT>* newu) {
        u = newu;
    }
    void setv(Node<DT>* newv) {
        v = newv;
    }
    void setEdgeInfo(string newInfo, DT newYearsKnown) {
        edgeInfo = newInfo;
        setYearsKnown(newYearsKnown);
    } // V2: updated
    void setYearsKnown(DT newYear) {
        yearsKnown = newYear;
    }                     // V2: updated

    void display(){ // display edge details
        cout << u->getNodeInfo() << " - " << v->getNodeInfo() << " " << 
            getEdgeInfo() << ", " << getYearsKnown() << endl;
    }

    ~Edge() {} // destructor
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store the graph
template <class DT>
class GraphDB
{
    // TODO: ostream operator for displaying myNodes and myEdges
protected:
    Node<DT>* myNodes; // array of nodes
    Edge<DT>* myEdges; // array of edges
    int numNodes;      // number of nodes
    int numEdges;      // number of edges
    int maxEdges;      // store the max number of edges (array size)

public:
    GraphDB(int nNodes, int nEdges){ // non-default constructor
        numNodes = nNodes;
        numEdges = 0;  // start numEdge at 0 and increase index as edges increase 
        maxEdges = nEdges;
        myNodes = new Node<DT>[nNodes]();
        myEdges = new Edge<DT>[nEdges]();
    }

    // setters
    void setNode(Node<DT>& newNode) {
        // find the node number of newNode and store in nodeNum
        int nodeNum = newNode.getNodeNumber();

        // set GraphDB node at NodeNum index with the node info
        myNodes[nodeNum].setNodeNumber(newNode.getNodeNumber());
        myNodes[nodeNum].setNodeInfo(newNode.getNodeInfo(), newNode.getYearCreated(), newNode.getLocation());
        
    }
    void setEdge(Edge<DT>& newEdge) {

        // increase the numEdge index to go to the next one
        numEdges++;


    }
    void setNodeInfo(int u, string newInfo) {

    }
    void setEdgeInfo(int u, int v, string newInfo) {

    }

    // getters
    Node<DT>* getNode(int nodeNum) {
        return &myNodes[nodeNum];
    }
    string getNodeInfo(int nodeNum) {
    }
    Edge<DT>* getEdgeInfo(int u, int v) {
    }

    // operations
    bool isAnEdge(int u, int v){     // is this edge existent

    }
    void addEdge(Edge<DT>& newEdge){ // add an edge

    }
    void deleteEdge(int u, int v){   // delete the edge

    }
    void display(){                  // display the contents of the two arrays

    }
    int* findNeighbours(int u){      // returns an integer array of neighbours' nodeNum

    }

    bool isANode(int nodex) {

        for (int i = 0; i < numNodes; i++) {
            if (myNodes[i].getNodeNumber() == nodex) {
                return true;
            }
        }

        return false;
    }

    ~GraphDB() {} // destructor
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{

    // you can start with the same main function from project 1
    int numNodes, maxEdges;
    int nodeNum;
    int nodeYear;
    int nodeU, nodeV;
    int yearsKnown;

    string nodeInfo;
    string nodeLocation;
    string edgeInfo;

    char input; // command to do something

    Node<int> tempNode; // temp node for node insertion 
    Edge<int> tempEdge; // temp edge for edge insertion

    cin >> numNodes >> maxEdges;

    // display the values read in
    cout << "numNodes: " << numNodes << endl;
    cout << "maxEdges: " << maxEdges << endl << endl;

    GraphDB<int>* mastergraph;
    mastergraph = new GraphDB<int>(numNodes, maxEdges);

    for (int i = 0; i < numNodes; i++) {

        cin >> nodeNum >> nodeInfo >> nodeYear >> nodeLocation;

        tempNode.setNodeNumber(nodeNum);
        tempNode.setNodeInfo(nodeInfo, nodeYear, nodeLocation);

        mastergraph->setNode(tempNode);
    }

    cin >> input;  // read the next command from input

    // while input is not end of file get next command 
    while (!cin.eof()) {
        // use switch cases to see the different commands to do next
        switch (input) {

            case 'I': { // insert edge

                // read the node numbers and edge info
                cin >> nodeU >> nodeV >> edgeInfo >> yearsKnown;
                cout << "Inserting " << nodeU << " " << nodeV << ": " <<
                    edgeInfo << ", " << yearsKnown << endl;

                // check if NodeU and nodeV are a part of graphDB nodes
                if ((mastergraph->isANode(nodeU) && mastergraph->isANode(nodeV)) == false) {

                    // if node does not exist 
                    cout << "Node not a part of the graph" << endl << endl;
                    break;
                }

                // Set the tempEdge nodes to the GraphDB nodes with the same node numbers  
                tempEdge.setu(mastergraph->getNode(nodeU));
                tempEdge.setv(mastergraph->getNode(nodeV));

                // Set the tempEdge info 
                tempEdge.setEdgeInfo(edgeInfo, yearsKnown);

                // store the address of this tempEdge to the GraphDB edges
                mastergraph->setEdge(tempEdge);

                cout << endl;
                break;
            }
            case 'R': { // remove edge 
                break;
            }
            case 'D': { // display the nodes and edges 

                // loop through GraphDB nodes and display them
                cout << "Displaying myNodes:" << endl;
                for (int i = 0; i < numNodes; i++) {
                    //cout << mastergraph->getNode(i);
                    mastergraph->getNode(i)->display();
                }

                break;
            }
            case 'E': { // check existence of edges 
                break;
            }
            case 'N': { // check existence of edges 
                break;
            }

            default: cout << "No commands found";   // if no command found
        }

        cin >> input; // read the next command from input 
    }

    return 0;
}
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
protected:
    int nodeNumber;  // field to store node's number
    string nodeInfo; // field to store node's information
    DT yearCreated;  // field to store the year of the node created
    string location; // field to store the location

public:
    Node() {  // default constructor
        nodeNumber = 0;
        nodeInfo = "";
        yearCreated = -1;
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

    // display node details
    void display() { 
        cout << getNodeNumber() << ": " << getNodeInfo() << ", " << getYearCreated() <<
            ", " << getLocation() << endl;
    } 

    // destructor
    ~Node() {
        //cout << "Node Destructor" << endl;
    }
};

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
        yearsKnown = -1;
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
    } // V2: updated

    // display edge details
    void display(){ 
        cout << u->getNodeInfo() << " - " << v->getNodeInfo() << " " << 
            getEdgeInfo() << ", " << getYearsKnown() << endl;
    }

    // destructor
    ~Edge() {
        //if (u != NULL) delete [] u;
        //if (v != NULL) delete [] v;
        //cout << "Edge Destructor" << endl;
    }
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store the graph
template <class DT>
class GraphDB
{
    // ostream operator for displaying myNodes and myEdges
    friend ostream& operator<< (ostream& s, GraphDB<int>& G) {

        // loop through GraphDB nodes and display them
        s << "Displaying myNodes:" << endl;
        for (int i = 0; i < G.getnumNodes(); i++) {
            G.getNode(i)->display();
            //(G.myNodes[i].display());
        }

        // loop through GraphDB edges and display them
        s << "Displaying myEdges:" << endl;
        for (int i = 0; i < G.getnumEdges(); i++) {
            G.getEdge(i)->display();
            //(G.myEdges[i].display());
        }

        return s;
    }
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

        if (numEdges >= maxEdges) {

            // create a new temp array
            Edge<DT>* temp = new Edge<DT>[maxEdges + (maxEdges / 2)]();

            // copy old values - deep copy
            for (int i = 0; i < maxEdges; i++) {
                temp[i] = myEdges[i];
            }

            delete[] myEdges;  // delete the pointer to the old values
            myEdges = temp;    // re point the pointer to the new memory location

            maxEdges = maxEdges + (maxEdges / 2);  // update the value of maxEdges

        }

        // set GraphDB edge at numEdge index with node u, v and edge info
        myEdges[numEdges - 1].setu(newEdge.getu());
        myEdges[numEdges - 1].setv(newEdge.getv());
        myEdges[numEdges - 1].setEdgeInfo(newEdge.getEdgeInfo(), newEdge.getYearsKnown());
    }
    void setNodeInfo(int u, string newInfo) {

        // loop through the GraphDB nodes
        for (int i = 0; i < numNodes; i++) {

            // if the GraphDB node number is equal to u set new node info
            if (myNodes[i].getNodeNumber() == u) {
                myNodes[i].setNodeInfo(newInfo, myNodes[i].getYearCreated(), myNodes[i].getLocation());
            }
        }

    }
    void setEdgeInfo(int u, int v, string newInfo) {

        // loop through the GraphDB edges
        for (int i = 0; i < numEdges; i++) {

            // If the edge u node number is equal to u and 
            //    if the edge v node number is equal to v set new info with years known
            if (myEdges[i].getu()->getNodeNumber() == u && myEdges[i].getv()->getNodeNumber() == v) {
                myEdges[i].setEdgeInfo(newInfo, myEdges[i].getYearsKnown());
            }
        }
    }

    // getters
    Node<DT>* getNode(int nodeNum) {
        return &myNodes[nodeNum];
    }
    string getNodeInfo(int nodeNum) {
        return myNodes[nodeNum].getNodeInfo();
    }
    Edge<DT>* getEdgeInfo(int u, int v) {

        // loop through the GraphDB edges 
        for (int i = 0; i < numEdges; i++) {

            // If the edge u node number is equal to u and 
            //    if the edge v node number is equal to v return the edge.
            if (myEdges[i].getu()->getNodeNumber() == u && myEdges[i].getv()->getNodeNumber() == v) {
                return &myEdges[i];
            }
        }

        // If edge is not found 
        return NULL;
    }
    Edge<DT>* getEdge(int edgeIndex) {
        return &myEdges[edgeIndex];
    }
    int getnumNodes() {
        return numNodes;
    }
    int getnumEdges() {
        return numEdges;
    }

    // operations
    bool isAnEdge(int u, int v){     // is this edge existent

        // loop through the GraphDB edges
        for (int i = 0; i < numEdges; i++) {

            // If the edge u node number is equal to u and 
            //    if the edge v node number is equal to v then edge exists
            if (myEdges[i].getu()->getNodeNumber() == u && myEdges[i].getv()->getNodeNumber() == v) {

                return true;  // return true when edge is found
            }
        }

        return false;         // return false when edge not found
    }
    void addEdge(Edge<DT>& newEdge){ // add an edge

        // increase the numEdge index to go to the next one
        numEdges++;

        if (numEdges >= maxEdges) {

            // create a new temp array
            Edge<DT>* temp = new Edge<DT>[maxEdges + (maxEdges / 2)]();

            // copy old values - deep copy
            for (int i = 0; i < maxEdges; i++) {
                temp[i] = myEdges[i];
            }

            delete[] myEdges;  // delete the pointer to the old values
            myEdges = temp;    // re point the pointer to the new memory location

            maxEdges = maxEdges + (maxEdges / 2);  // update the value of maxEdges

        }

        // set GraphDB edge at numEdge index with node u, v and edge info
        myEdges[numEdges - 1].setu(newEdge.getu());
        myEdges[numEdges - 1].setv(newEdge.getv());
        myEdges[numEdges - 1].setEdgeInfo(newEdge.getEdgeInfo(), newEdge.getYearsKnown());
        
    }
    void deleteEdge(int u, int v){   // delete the edge

        // check if the edge is existent
        if (isAnEdge(u, v)){

            int ind = -1; // temp index to store where index of edge is in the GraphDB

            // loop through the GraphDB edges
            for (int i = 0; i < numEdges; i++) {

                // break loop when index with deleted edge is found and store index in ind
                if (myEdges[i].getu()->getNodeNumber() == u && myEdges[i].getv()->getNodeNumber() == v) {
                    ind = i;
                    break;
                }
            }

            // loop through the GraphDB edges starting from deleted edge index
            for (int j = ind; j < numEdges - 1; j++)
            {
                myEdges[j] = myEdges[j + 1]; // make the current index edge the next edge from GraphDB edges
            }

            // remove the last index of GraphDB edges by setting to constructor values
            myEdges[numEdges - 1].setu(NULL);
            myEdges[numEdges - 1].setv(NULL);
            myEdges[numEdges - 1].setEdgeInfo("", -1);

            // decrease the numEdge index since the number of Edges is one less
            numEdges--;

            // ----- deallocating memory -------
            // if the numEdges is less than the half the maxEdges array
            if (numEdges < (maxEdges / 2)) {

                // create a new temp array
                Edge<DT>* temp = new Edge<DT>[maxEdges / 2]();

                // copy old values - deep copy
                for (int i = 0; i < (maxEdges / 2); i++) {
                    temp[i] = myEdges[i];
                }

                delete[] myEdges;  // delete the pointer to the old values
                myEdges = temp;    // re point the pointer to the new memory location

                maxEdges = maxEdges / 2;  // update the value of maxEdges to half the size
            }
        }

        else{
            cout << "Edge does not exist to be deleted" << endl; // this could be an exception
        }
    }
    void display(){ // display the contents of the two arrays

        // loop through the GraphDB edges and display them
        for (int i = 0; i < numEdges; i++) {
            myEdges[i].display();
        }
    }
    int* findNeighbours(int u){      // returns an integer array of neighbours' nodeNum

        int* neighbours = new int[numNodes - 1]();  // make array to store neighbours
        int index = 0;                              // variable for index of neighbour array

        // initialize all the elements in neighbours array to -1
        for (int i = 0; i < (numNodes - 1); i++) {
            neighbours[i] = -1;
        }

        // loop the DB nodes 
        for (int i = 0; i < numNodes; i++) {
           
            // if there exists an edge between the nodeNum and another node in grapgDB nodes add 
            //    as a neighbour to nodeNum
            if (isAnEdge(myNodes[i].getNodeNumber(), u) || isAnEdge(u, myNodes[i].getNodeNumber())) {

                // add index of node as neighbour 
                neighbours[index] = myNodes[i].getNodeNumber();
                index++;        // go to the next index
                
            }
        }

        return neighbours;      // return the array of neighbours
    }

    bool isANode(int nodex) {  // return true or false value if node exists

        // loop the the graph DB nodes
        for (int i = 0; i < numNodes; i++) {

            // if node is found return a true value 
            if (myNodes[i].getNodeNumber() == nodex) {
                return true;
            }
        }

        return false;  // if node not found
    }

    // destructor
    ~GraphDB() {   
        //if (myNodes != NULL) delete [] myNodes;
        //if (myEdges != NULL) delete [] myEdges;
        //cout << "GraphDB Destructor" << endl;
    }
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    int numNodes, maxEdges;    // temp variable to store numNodes and maxEdges from input
    int nodeNum;               // index of node
    int nodeYear;              // node year created
    int nodeU, nodeV;          // temp variable to store 1st and 2nd node index
    int yearsKnown;            // variable to store years known 
    int nodeNeighbour;         // node to check neighbours 
    int* neighbours;           // array to store neighbour of nodeNeighbours

    string nodeInfo;           // names or infomation of nodes
    string nodeLocation;       // location of nodes
    string edgeInfo;           // temp variable to store edge information

    char input;                // command to do something
    bool edgeExistence;        // variable to store edge existent 
    bool nodeExistence;        // variable to store node existent 

    Node<int> tempNode;        // temp node for node insertion 
    Edge<int> tempEdge;        // temp edge for edge insertion
    GraphDB<int>* mastergraph; // pointer object of GraphDB class

    cin >> numNodes >> maxEdges;  // read the numNodes and maxEdges from redirected input

    // display the values read in
    cout << "numNodes: " << numNodes << endl;
    cout << "maxEdges: " << maxEdges << endl << endl;

    // allocate memory by calling non-default constructor
    mastergraph = new GraphDB<int>(numNodes, maxEdges);

    // input nodes
    for (int i = 0; i < numNodes; i++) {

        cin >> nodeNum >> nodeInfo >> nodeYear >> nodeLocation; // read in the node info

        // Set the node number and info to temp node
        tempNode.setNodeNumber(nodeNum);
        tempNode.setNodeInfo(nodeInfo, nodeYear, nodeLocation);

        // store the address of this node to the GraphDB nodes
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
                nodeExistence = (mastergraph->isANode(nodeU) && mastergraph->isANode(nodeV));

                try {
                    // if nodes not part of graphDB throw error message
                    if (nodeExistence == false) throw nodeExistence;

                }
                catch (bool nodeExistence) {
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

                // read the node numbers to be removed
                cin >> nodeU >> nodeV;
                cout << "Removing " << nodeU << " " << nodeV << endl;

                // remove the edge from the GraphDB byy calling function
                mastergraph->deleteEdge(nodeU, nodeV);

                cout << endl;
                break;
            }
            case 'D': { // display the nodes and edges 

                // loop through GraphDB nodes and edges and display them
                cout << (*mastergraph);
                cout << endl;

                break;
            }
            case 'E': { // check existence of edges 

                // read the node numbers to be checked for edge existence
                cin >> nodeU >> nodeV;

                edgeExistence = mastergraph->isAnEdge(nodeU, nodeV);

                if (edgeExistence == true)
                    // print out message 
                    cout << "Edge exists between " << mastergraph->getNode(nodeU)->getNodeInfo()
                        << " and " << mastergraph->getNode(nodeV)->getNodeInfo() << endl;
                else
                    // if edge is not in GraphDB edges it does not exist so print out message
                    cout << "No edge exists between " << mastergraph->getNode(nodeU)->getNodeInfo()
                    << " and " << mastergraph->getNode(nodeV)->getNodeInfo() << endl;

                cout << endl;
                break;
            }
            case 'N': { // check existence of edges 
                
                // read the node number to be checked for neighbours
                cin >> nodeNeighbour; 

                // check the neighbours of the nodeNum
                neighbours = mastergraph->findNeighbours(nodeNeighbour);

                cout << "Neighbours of " << nodeNeighbour << ": ";

                // print of the neighbours of the nodeNum
                for (int i = 0; i < numNodes - 1; i++) {
                    if (neighbours[i] == -1) break;
                    cout << neighbours[i] << " ";
                }

                cout << endl << endl;
                break;
            }

            default: cout << "No commands found";   // if no command found
        }

        cin >> input; // read the next command from input 
    }

     return 0;
}
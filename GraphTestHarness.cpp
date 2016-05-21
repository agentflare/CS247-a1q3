#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//************************************************************************
//* YOUR IMPLENTATION OF BCODE, BUILDING, COLLECTION HERE
//************************************************************************
class BCode{
public:
    BCode();
    BCode ( string code );
    string getCode () const;
    string toString () const;
private:
    string code_;
};
BCode::BCode(){
}
BCode::BCode( string code ):code_(code){
}

string BCode::getCode () const{
    return code_;
}

class Building{
public:
    Building();
    Building( BCode bcode, string name );
    string toString () const;
    string getCode();
    string getName();
private:
    BCode bcode_;
    string name_;
};

Building::Building(){

}

Building::Building( BCode bcode, string name ){
    bcode_ = bcode;
    name_ = name;
}
string Building::getCode(){
    return bcode_.getCode();
}

string Building::getName(){
    return name_;
}

string Building::toString () const{
    return bcode_.getCode() + " " + name_;
}

ostream& operator<< ( ostream &sout, const Building &a ) {
    sout.setf(ios::internal);
    sout << a.toString();
    return sout;
}
class NodeEdge;
class BuildingNode;

class NodeEdgeList{
public:
    NodeEdgeList();
    void insertEdge( BuildingNode* other, string type );
    void deleteEdge( string code );
    NodeEdge* find ( string code );
    int size();
    string getType( string code1,string code2 );
    NodeEdge* getHead();
    bool operator== (NodeEdgeList &a) const;
private:
    int count_;
    NodeEdge* head_;
    NodeEdge* tail_;
};

class BuildingNode{
public:
    BuildingNode();
    BuildingNode( Building* b );
    BuildingNode* getNext();
    NodeEdgeList* getEdges();
    void setData( Building* b );
    Building* getData();
    BuildingNode* setNext( BuildingNode* b );
    string getCode();
private:
    BuildingNode* next_;
    Building* data_;
    NodeEdgeList* edgeList_;
};
BuildingNode::BuildingNode(){
    edgeList_ = new NodeEdgeList();
}

BuildingNode::BuildingNode( Building* b ){
    data_ = b;
    edgeList_ = new NodeEdgeList();
}

Building* BuildingNode::getData(){
    return data_;
}

BuildingNode* BuildingNode::getNext(){
    return next_;
}

NodeEdgeList* BuildingNode::getEdges(){
    return edgeList_;
}
void BuildingNode::setData( Building* b ){
    data_ = b;
}
BuildingNode* BuildingNode::setNext( BuildingNode* b ){
    next_ = b;
    return next_;
}
string BuildingNode::getCode(){
    return data_->getCode();
}

class BuildingList{
public:
    BuildingList();
    ~BuildingList();
    void insert( Building* b );
    void remove ( string code );
    BuildingNode* findElement ( string code );
    int size() const;
    BuildingNode* getHead() const;
    bool operator== (BuildingList &list_)const;
private:
    BuildingNode* head_;
    BuildingNode* tail_;
    int count_;
};

BuildingList::BuildingList(){
    head_ = NULL;
    tail_ = NULL;
}

BuildingList::~BuildingList(){
    BuildingNode* iter = head_;
    while( iter!= NULL ){
        BuildingNode* temp = iter;
        iter = temp->getNext();
        delete temp;
    }
}

int BuildingList::size() const{
    return count_;
}

bool BuildingList::operator== (BuildingList &a) const{
    if( a.count_ != count_){
        return false;
    }

    BuildingNode* temp = head_;
    BuildingNode* aTemp = a.getHead();

    if(temp!= NULL && aTemp==NULL){
        return false;
    }
    else if(temp == NULL && aTemp!=NULL){
        return false;
    }
    else if(temp == NULL && aTemp == NULL){
        return true;
    }

    while( temp != NULL ){
        while( aTemp!=NULL ){
            if(aTemp->getCode() == temp->getCode() && *temp->getEdges()==*aTemp->getEdges()){
                break;
            }
            aTemp = aTemp->getNext();
        }

        if(aTemp == NULL){
            return false;
        }
        temp = temp->getNext();
    }
    return true;
}

BuildingNode* BuildingList::getHead() const{
    return head_;
}

void BuildingList::insert( Building* b ){
BuildingNode* bNode = new BuildingNode( b );
count_++;
    if(tail_ == NULL && head_ == NULL){
        tail_ = bNode;
        head_ = bNode;
        tail_->setNext(NULL);
        return;
    }
    else{
        BuildingNode* temp = head_;
        while(temp != NULL){
            if( head_->getCode() > bNode->getCode() ){
                bNode->setNext(head_);
                head_=bNode;
                return;
            }
            else if( temp->getNext() == NULL ){
                temp->setNext( bNode );
                tail_ = bNode;
                tail_->setNext( NULL );
                return;
            }
            else if( temp->getNext()->getData()->getCode() > b->getCode() ){
                bNode->setNext(temp->getNext());
                temp->setNext( bNode );
                return;
            }
            temp = temp->getNext();
        }
    }
}
BuildingNode* BuildingList::findElement( string code ){
    BuildingNode* temp = head_;
    while(temp!= NULL){
        if( temp->getCode() == code ){
            return temp;
        }
        temp = temp->getNext();
    }
    return NULL;
}

void BuildingList::remove( string code ){
    BuildingNode* temp = head_;
    if(temp == NULL){
        return;
    }
    if(temp->getCode() == code){
        //TODO
        //Remove Edge Nodes
        head_ = temp->getNext();
        delete temp;
        if( head_ == NULL ){
            tail_ = NULL;
        }
        count_--;
        return;
    }
    else if( temp->getNext() != NULL ){
        //TODO
        //Remove Edge Nodes
        while( temp->getNext() != NULL ){
            if( temp->getNext()->getCode() == code ){
                BuildingNode* holder = temp->getNext();
                temp->setNext(holder->getNext());
                delete holder;
            }
        }
        count_--;
        return;
    }
    return;
}

class NodeEdge{
public:
    NodeEdge( BuildingNode* other, string type );
    ~NodeEdge();
    NodeEdge* getNext() const;
    BuildingNode* getOther() const;
    string getType() const;
    NodeEdge* addElement( BuildingNode newGraphNode );
    void setNext( NodeEdge* next);
private:
    string type_;
    BuildingNode* other_;
    NodeEdge* next_;
};

NodeEdge::NodeEdge( BuildingNode* other, string type ){
    other_ = other;
    type_ = type;
    next_ = NULL;
}

NodeEdge::~NodeEdge(){
    NodeEdge* iter = next_;
    while(iter != NULL){
        NodeEdge* temp = iter;
        iter = temp->getNext();
        delete temp;
    }
}

NodeEdge* NodeEdge::getNext() const{
    return next_;
}

void NodeEdge::setNext(NodeEdge* next){
    next_ = next;
}
string NodeEdge::getType() const{
    return type_;
}
BuildingNode* NodeEdge::getOther() const{
    return other_;
}

NodeEdgeList::NodeEdgeList(){
    head_ = NULL;
    count_ = 0;
}
NodeEdge* NodeEdgeList::getHead(){
    return head_;
}

void NodeEdgeList::insertEdge( BuildingNode* other, string type ){
    NodeEdge* newEdge = new NodeEdge(other, type);

    if(head_ != NULL){
        newEdge->setNext(head_);
        head_=newEdge;
    }
    else{
        head_ = newEdge;
        tail_ = newEdge;
        tail_->setNext(NULL);
    }
}

int NodeEdgeList::size(){
    return count_;
}

void NodeEdgeList::deleteEdge( string code ){
    NodeEdge* temp = head_;
    if(temp == NULL){
        return;
    }
    if(temp->getOther()->getCode() == code){
        head_ = temp->getNext();
        delete temp;
        count_--;
        return;
    }
    else if( temp->getNext() != NULL ){
        while( temp->getNext() != NULL ){
            if( temp->getNext()->getOther()->getCode() == code ){
                NodeEdge* holder = temp->getNext();
                temp->setNext(holder->getNext());
                count_--;
                delete holder;
            }
        }
    }
    return;
}

bool NodeEdgeList::operator== (NodeEdgeList &a) const{
    if( count_ != a.count_ ){
        return false;
    }

    NodeEdge* temp = head_;

    if(temp!=NULL && a.getHead()==NULL){
        return false;
    }
    else if(temp==NULL && a.getHead()!=NULL){
        return false;
    }
    while( temp!= NULL){
        NodeEdge* aComparator = a.getHead();
        while( aComparator!=NULL ){
            if(aComparator->getOther()->getCode() == temp->getOther()->getCode()){
                if(aComparator->getType() == temp->getType()){
                    break;
                }
            }
            aComparator = aComparator->getNext();
        }
        if(aComparator == NULL){
            return false;
        }
        temp = temp->getNext();
    }
    return true;
}

class Collection{
public:
    Collection();
    ~Collection();
    void insert( string code, string name );
    Building* findBuilding( string code );
    void remove( string code );
private:
    BuildingNode* head_;
    BuildingNode* tail_;
};
Collection::Collection(){
    tail_ = NULL;
    head_ = NULL;
}

Collection::~Collection(){
    BuildingNode* iter = head_;
    while(iter != NULL){
        BuildingNode* temp = iter;
        iter = temp->getNext();
        delete temp->getData();
        delete temp;
    }
}

void Collection::insert( string code, string name ){
    BCode bcode = BCode(code);
    Building* build = new Building(bcode, name);
    BuildingNode* bNode = new BuildingNode( build );
    if(tail_ != NULL){
        tail_ = tail_->setNext(bNode);
        tail_->setNext(NULL);
    }
    else{
        head_ = bNode;
        tail_ = bNode;
        tail_->setNext(NULL);
    }
}

Building* Collection::findBuilding( string code ){
    BuildingNode* temp = head_;
    while(temp != NULL){
        if(temp->getCode() == code){
            return temp->getData();
        }
        temp = temp->getNext();
    }
    return NULL;
}

void Collection::remove( string code ){
    BuildingNode* temp = head_;
    if(temp == NULL){
        return;
    }
    if(temp->getCode() == code){
        head_ = temp->getNext();
        delete temp;
        if( head_ == NULL){
            tail_ = NULL;
        }
        return;
    }
    else if( temp->getNext() != NULL ){
        while( temp->getNext() != NULL ){
            if( temp->getNext()->getCode() == code ){
                BuildingNode* holder = temp->getNext();
                temp->setNext(holder->getNext());
                delete holder;
            }
        }
    }
    return;
}

//===================================================================
// Graph (of Buildings and Connectors)
//===================================================================

class Graph {
public:
    Graph();                                                // constructor
    ~Graph();                                               // destructor
    Graph ( const Graph& );                                 // copy constructor
    void addNode ( Building* );                             // mutator - add node to graph
    void removeNode ( string );                             // mutator - remove node from graph
    Building* findBuilding ( string ) const;                // accessor - find building stored in node in graph
    void addEdge ( string, string, string );                // mutator - add edge to graph
    void removeEdge ( string, string );                     // mutator - remove edge from graph
    void printPaths ( string, string, const bool = false ) const; // accessor - print path from one node to another
    void deleteGraph();                                     // delete graph
    friend ostream& operator<< ( ostream&, const Graph& );  // insertion operator (insert graph into output stream)
    Graph& operator= ( const Graph& );                      // assignment operator for graph objects
    bool operator== ( const Graph& ) const;                 // equality operator for graph objects
    BuildingList* getList() const;                          //This is kind of cheating, but I think it makes more sense to add one accessor than to hide a bunch of classes.
private:
    void swap( Graph &a, Graph &b );
    BuildingList* list_;
};

//************************************************************************
//* YOUR IMPLENTATION OF GRAPH HERE
//************************************************************************

Graph::Graph(){
    list_ = new BuildingList();
}

Graph::~Graph(){
    delete list_;
}

Graph::Graph( const Graph& b){
    list_ = new BuildingList();
    BuildingNode* temp = b.getList()->getHead();
    while( temp != NULL ){
        list_->insert(temp->getData());
        temp = temp->getNext();
    }

    temp = b.getList()->getHead();
    BuildingNode* listTemp = list_->getHead();
    while( temp != NULL ){
        NodeEdge* edgeTemp = temp->getEdges()->getHead();
        while( edgeTemp != NULL ){
            listTemp->getEdges()->insertEdge(list_->findElement(edgeTemp->getOther()->getCode()),edgeTemp->getType());
            edgeTemp = edgeTemp->getNext();
        }
        temp = temp->getNext();
    }
}

BuildingList* Graph::getList() const{
    return list_;
}

void Graph::addNode(Building* building){
    list_->insert(building);
}

void Graph::addEdge( string currentCode,string otherCode, string type ){
    BuildingNode* bNode1 = list_->findElement(currentCode);
    BuildingNode* bNode2 = list_->findElement(otherCode);
    bNode1->getEdges()->insertEdge(bNode2,type);
    bNode2->getEdges()->insertEdge(bNode1,type);
}

ostream& operator<< ( ostream &sout, const Graph &a ) {
    sout.setf(ios::internal);
//TODO
    BuildingNode* temp = a.list_->getHead();
    while(temp != NULL){
        cout<<temp->getCode()<<"\t"<<temp->getData()->getName()<<"\n";
        NodeEdge* tempHead = temp->getEdges()->getHead();

        if (tempHead != NULL){
                cout<<"\tConnects to: ";
        }
        while(tempHead != NULL){
            cout<<tempHead->getOther()->getCode()<<" ("<<tempHead->getType()<<")";
            if(tempHead->getNext()!= NULL){
                cout<<", ";
            }
            else{
                cout<<"\n";
            }
            tempHead = tempHead->getNext();
        }
        temp = temp->getNext();
    }
    //sout<< ;
    return sout;
}

Building* Graph::findBuilding(string code) const{
    BuildingNode* node = list_->findElement(code);
    return node->getData();
}

void Graph::deleteGraph(){
    //TODO
    BuildingNode* tempRm = list_->getHead();
    while(tempRm != NULL){
        NodeEdgeList* tempEdgeList = tempRm->getEdges();
        NodeEdge* tempEdges = tempEdgeList->getHead();

        while( tempEdges != NULL ){
            tempEdgeList->deleteEdge( tempEdges->getOther()->getCode() );
            tempEdges = tempEdgeList->getHead();
        }

        list_->remove(tempRm->getCode());
        tempRm = list_->getHead();
    }
}

void Graph::removeEdge( string code1, string code2 ){
    BuildingNode* node1 = list_->findElement(code1);
    BuildingNode* node2 = list_->findElement(code2);
    node1->getEdges()->deleteEdge(code2);
    node2->getEdges()->deleteEdge(code1);
}

void Graph::removeNode( string code ){
    list_->remove( code );
}


bool recursePath( string currCode, string destCode,BuildingList* list_, Collection& travelled){
    BuildingNode* start = list_->findElement( currCode );
    NodeEdge* temp = start->getEdges()->getHead();

    if(currCode == destCode){
        cout<<destCode;
        return true;
    }
    while( temp != NULL ){
        string nextCode = temp->getOther()->getCode();
        if(travelled.findBuilding(nextCode) == NULL){
            travelled.insert(nextCode,temp->getOther()->getData()->getName());
            if(recursePath(nextCode,destCode,list_,travelled)){
                cout<<" ("<<temp->getType()<<") "<<currCode;
                return true;
            }
        }
        temp = temp->getNext();
    }
    return false;
}

void Graph::printPaths( string code1, string code2, bool printall ) const{
    Collection travelled = Collection();
    travelled.insert(code2,list_->findElement(code2)->getData()->getName());

    BuildingNode* start = list_->findElement( code2 );
    NodeEdge* temp = start->getEdges()->getHead();

    while( temp != NULL ){
        string nextCode = temp->getOther()->getCode();
        if( travelled.findBuilding(nextCode) == NULL ){
            if(recursePath(nextCode,code1, list_, travelled)){
                cout<< " ("<<temp->getType()<<") "<<start->getCode()<<"\n";
                return;
            }
        }
        temp = temp->getNext();
    }
}

bool Graph::operator== (const Graph &a) const{
    return (*list_ == *a.list_);
}

Graph& Graph::operator= ( const Graph& other){
    if(&other == this){
        return *this;
    }

    deleteGraph();
    //delete list_;

    Graph temp (other);
    list_ = new BuildingList(*(other.getList()));
    return *this;
}
//************************************************************************
//  Test Harness Helper functions
//************************************************************************

//  test-harness operators
enum Op { NONE, mapPtr, building, wreckage, findB, node, remNode, edge, remEdge, delGraph, copyGraph, assignGraph, eq, path, print };

Op convertOp( string opStr ) {
    switch( opStr[0] ) {
        case 'm': return mapPtr;
        case 'b': return building;
        case 'w': return wreckage;
        case 'f': return findB;
        case 'n': return node;
        case 'v': return remNode;
        case 'e': return edge;
        case 'r': return remEdge;
        case 'd': return delGraph;
        case 'c': return copyGraph;
        case 'a': return assignGraph;
        case 'q': return eq;
        case 'p': return path;
        case 'g': return print;
        default: {
            return NONE;
        }
    }
}

//******************************************************************
// Test Harness for Graph ADT
//******************************************************************

int main( int argc, char *argv[] ) {
    Collection buildings;
    Graph map1, map2;

    // initialize buildings and map1 with input file, if present
    if ( argc > 1 ) {

        ifstream source(argv[1]);
        if ( source.fail() ) {
            cerr << "Error: Could not open file \"" << argv[1] << "\"." << endl;
            return 1;
        }

        // create a collection of buildings, and a map of buildings and interior links

        string type;
        source >> type;
        Op op = convertOp ( type );
        while ( !source.eof() ) {
            switch (op) {

                    // add a new building to the collection of Buildings, and add the building to map1
                case building : {
                    string code;
                    string name;
                    string name2;
                    source >> code >> name;
                    getline( source, name2 );
                    buildings.insert( code, name+name2 );
                    map1.addNode( buildings.findBuilding ( code ) );
                    break;
                }

                    // add a new link between two existing nodes in map1
                case edge: {
                    string code1, code2, type;
                    source >> code1 >> code2 >> type;
                    map1.addEdge( code1, code2, type );
                    string junk;
                    getline ( source, junk );
                    break;
                }

                default: { }
            }
            source >> type;
            op = convertOp( type );
        }
    }

    cout << map1;

    Graph* map = &map1;  // input commands affect which ever graph that map points to (map1 or map2)

    cout << "Test harness for Graph ADT:" << endl << endl;

    // get input command
    cout << "Command: ";
    string command;
    cin >> command;

    Op op = convertOp( command );

    while ( !cin.eof() ) {
        switch (op) {

                // set variable map to point to new graph (map1 or map2)
            case mapPtr: {
                string mapNo;
                cin >> mapNo;
                map = ( mapNo[0] == '1' ) ? &map1 : &map2;
                break;
            }

                // print the current map to the console
            case print: {
                cout << *map;
                break;
            }

                // add a new building to the collection of buildings
            case building : {
                string code;
                string name;
                string name2;
                cin >> code >> name;
                getline( cin, name2 );
                buildings.insert( code, name+name2 );
                break;
            }

                // add an existing building to the current map
            case node: {
                string code;
                cin >> code;
                map->addNode( buildings.findBuilding( code ) );
                string junk;
                getline( cin, junk );
                break;
            }

                // find a building in the current map
            case findB: {
                string code;
                cin >> code;
                Building *b = map->findBuilding ( code );
                if ( b ) {
                    cout << *b << endl;
                }
                else {
                    cout << "Couldn't find building " << code << endl;
                }
                cout << endl;
                string junk;
                getline( cin, junk );
                break;
            }

                // add a new link between existing graph nodes in the current map
            case edge: {
                string code1, code2, type;
                cin >> code1 >> code2 >> type;
                map->addEdge( code1, code2, type );
                string junk;
                getline ( cin, junk );
                break;
            }


                // delete the entire graph (no memory leak).  There is no change to the collection of Buildings.
            case delGraph: {
                map->deleteGraph();
                break;
            }

                // remove an existing edge from the current map
            case remEdge: {
                string code1, code2;
                cin >> code1 >> code2;
                map->removeEdge( code1, code2 );
                string junk;
                getline ( cin, junk );
                break;
            }

                // remove an existing node from the current map.  There is no change to the collection of Buildings.
            case remNode: {
                string code;
                cin >> code;
                map->removeNode( code );
                string junk;
                getline( cin, junk );
                break;
            }

                // remove an existing building from the collection of buildings.  The building also needs to be removed from the two maps, as well as all links involving the building
            case wreckage: {
                string code;
                cin >> code;
                map1.removeNode( code );
                map2.removeNode( code );
                buildings.remove ( code );
                string junk;
                getline ( cin, junk );
                break;
            }

                // check whether map1 is equal to map2
            case eq: {
                if ( map1 == map2 ) {
                    cout << "Maps 1 and 2 are equal." << endl;
                }
                else {
                    cout << "Maps 1 and 2 are NOT equal." << endl;
                }
                break;
            }

                // graph copy constructor
            case copyGraph: {
                Graph map3( *map );
                cout << map3;
                string junk;
                getline( cin, junk );
                break;
            }

                // graph assignment operator
            case assignGraph: {
                map1 = map2;
                cout << map1;
                break;
            }

                // find path(s) in graph from one building to another building
            case path: {
                string code1, code2, all;
                cin >> code1 >> code2 >> all;
                cout << "Paths from " << code1 << " to " << code2 << " are: " << endl;
                bool printall = ( all.length() > 0 && all.at(0) == 't' ) ? true : false;
                map->printPaths( code1, code2, printall );
                string junk;
                getline( cin, junk );
                break;
            }

            default: {
                cerr << "Invalid command." << endl;
            }
        }

        cout << "Command: ";
        cin >> command;
        op = convertOp( command );

    } // while cin OK

}

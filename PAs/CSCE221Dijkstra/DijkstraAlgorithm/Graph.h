#ifndef GRAPH_H
#define GRAPH_H

#include "LocatorHeap.h"

#include <vector>
using std::vector;


class Edge;

class Vertex
{
public:
    int label;
    vector<Edge*> edges;

    // helpers stored inside a vertex to help with path finding
    // you can use different auxilliary structures if desired
    bool visited;
    float distanceTo;
    vector<Vertex*> pathTo;
    Heap<Vertex*>::Locator locator;
    bool operator < ( const Vertex &v ) const 
    { 
        // TODO for locator heap implementation
        if(this->distanceTo < v.distanceTo )
        {
            return true;
        }
        return false;
    }

    Vertex ( int l ) : label (l) { }
};

class Edge
{
public:
    Vertex *v1, *v2;
    float weight;

    Edge ( Vertex *nv1, Vertex *nv2, float newWeight ) : v1 ( nv1 ), v2 ( nv2 ), weight ( newWeight ) { }
};


class Graph
{
protected:
    vector<Vertex*> v;
    vector<Edge*> e;

public:
    Graph () {}

    ~Graph ()
    {
        // TODO
        for(int i = 0; i < v.size(); i++)
        {
            for(int j = 0; j < v.at(i)->edges.size(); j++)
            {
                delete v.at(i)->edges.at(j);
            }
            delete v.at(i)->locator;
            delete v.at(i);
        }
        for(int i = 0; i < e.size(); i++)
        {
            delete e.at(i);
        }

    }
    Graph (const Graph& rhs)
    {
        *this = rhs;
    }
    const Graph & operator=( const Graph & rhs )
    {
       if(this != &rhs)
       {
            delete this;
            
            for(int i = 0; i < rhs.v.size(); i++)
            {
                this->v.push_back(v.at(i));
            }
            for(int i = 0; i < rhs.e.size(); i++)
            {
                this->e.push_back(e.at(i));
            }
       }
       return *this;
    }

    // TODO: complete rule of 3

    void insertVertex ( int label )
    {
        // TODO
        bool skipInsertion = false;
        for(int i = 0; i < v.size(); i++)
        {
            if(v.at(i)->label == label)
            {
                skipInsertion = true;
            }
            
        }
        if(!skipInsertion)
        {
            Vertex* newVertex = new Vertex(label);
            v.push_back(newVertex);
        }
        

    }

    void insertEdge ( int l1, int l2, float weight )
    {
        // TODO
        this->insertVertex(l1);
        this->insertVertex(l2);
        Vertex* v1 = nullptr;
        Vertex* v2 = nullptr;
        for(int i = 0; i < v.size(); i ++)
        {
            
            if(v.at(i)->label == l1)
            {
                v1 = v.at(i);
            }
            else if (v.at(i)->label == l2)
            {
                v2 = v.at(i);
            }
            
        }

        Edge* newEdge = new Edge(v1, v2, weight);
        e.push_back(newEdge);
        v1->edges.push_back(newEdge);

    }
    void print()
    {
        for(int i = 0; i < v.size(); i++)
        {
            cout << v.at(i)->label << " ";
            cout << endl;
            for(int j = 0; j < v.at(i)->edges.size(); j++)
            {
                cout << " Edges: " << v.at(i)->edges.at(j)->v2->label;
                cout << endl;
            }
        }
        cout << endl;
    }

    vector<Vertex*> shortestPath ( int start, int end )
    {
        // TODO: Dijkstra's algorithm
        vector <Vertex*> output;
        vector <Vertex*> d;
        vector <float> p(v.size());
        vector <bool> booleans(v.size());
        

        int s = 0; // s is start index
        
        Vertex* current; //not really using
        Vertex* endNode;
        for(int i = 0; i < v.size(); i++)
        {
            d.push_back(v.at(i));
            if(v.at(i)->label == start)
            {
                current = v.at(i);
                s = i;
            }
            if(v.at(i)->label == end)
            {
                endNode = v.at(i);
            }
        }

        //create an empty min-priority queue q
        Heap <Vertex*> q;

        d[s]->distanceTo = 0; p[s] = -1;
        booleans[s] = true;
        output.push_back(d[s]);
        //q.enqueue((d[s],s));
         q.insertElement(d[s]);

        //for each vertex u in V that is not s
        for (int i = 0; i < v.size(); i++) {
            if(v.at(i)->label != start)
            {
                p[i] = -1;
                d[i]->distanceTo = __FLT_MAX__;
                booleans[i] = false;
                q.insertElement(d[i]);
                
            }
        }
        while(!q.isEmpty()) 
        {
            Vertex* min = q.removeMin();
            
            
            //for each edge (u,v) in E
            for (int i = 0; i < min->edges.size(); i++) 
            {
                //find index of v in d
                int v = indexOf(min->edges.at(i)->v2, d);
                
                if (d[s]->distanceTo + min->edges.at(i)->weight < d[v]->distanceTo) //pretend s is u
                {
                    d[v]->distanceTo = d[s]->distanceTo + min->edges.at(i)->weight;
                    p[v] = d[s]->distanceTo;
                    //update (d[v], v) in the queue q
                    //q.update(d[v]->locator); //Getting a seg fault when trying to call this
                    s = v;
                    
                    d[s]->visited = true;
                    output.push_back(d[s]);
                    if(d[s]->label == end)
                    {
                        endNode->visited = true;
                        return output;
                    }  
                   
                            
                }
            }
            
            
            
            
            

        }   
        return output;
        
    }
    int indexOf(Vertex* v2, vector <Vertex*> d)
    {
        for(int i = 0; i < d.size(); i++)
        {
            if(d.at(i)->label == v2->label)
            {
                return i;
            }
        }
    }  
};

#endif

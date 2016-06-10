#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <sstream>
#include <functional>
#include <iomanip>
#include <cstdio>


using namespace std;

struct edge{
    unsigned int destination;
    double distance;
};


struct vertex{
    double distance = INFINITY;
    bool visited = false;
    unsigned int parent = 0;
    bool in_path = false;
    vector<edge> neighbors;
};

typedef vector<vertex> Graph;


double dijkstra(Graph &graph, unsigned int source, unsigned int destination)
{
    auto cmp = [](pair<unsigned int, double> left, pair<unsigned int, double> right) { return (left.second > right.second);};

    priority_queue<pair<unsigned int, double>, vector<pair<unsigned int, double>>, decltype(cmp)> q(cmp);
    graph.at(source).distance=0;
    q.push(make_pair(source, graph.at(source).distance));
    unsigned int current;
    while(!q.empty())
    {
        current = q.top().first;
        graph.at(current).visited = true;
        q.pop();
        if (current == destination)
        {
            return graph.at(current).distance;
        }
        for(const edge& e : graph.at(current).neighbors)
        {

            if(!(graph.at(e.destination).visited))
            {
                if(graph.at(e.destination).distance > graph.at(current).distance+e.distance)
                {
                    graph.at(e.destination).distance = graph.at(current).distance+e.distance;
                    graph.at(e.destination).parent = current;
                    q.push(make_pair(e.destination, graph.at(e.destination).distance));
                }

            }
        }
    }
    return INFINITY;
}



int main(int argc, char* argv[])
{
    if (argc<2)
    {
        cerr<<"dijkstra 0 123 <drukuj>< data.txt"<<endl;
        cerr<<"<drukuj> = 0 lub 1, 1: drukuj ścieżkę (dla kwadratowych grafów o sqrt(n)<200)"<<endl;
        return -1;

    }
    istringstream arg_source(argv[1]);
    unsigned int source;
    if (!(arg_source >> source))
        cerr << "Invalid number " << argv[1] << '\n';

    unsigned int destination;
    istringstream arg_destination(argv[2]);
    if (!(arg_destination >> destination))
        cerr << "Invalid number " << argv[2] << '\n';
    unsigned int print;
    istringstream arg_print(argv[3]);
    if (!(arg_print >> print))
        cerr << "Invalid number " << argv[3] << '\n';

    string line;
    getline(cin, line);
    stringstream ss(line);
    int graph_size;
    ss>>graph_size;
    Graph graph(graph_size);
    /*
        wczytanie danych o krawędziach
    */
    while(getline(cin, line))
    {
        stringstream ss(line);
        unsigned int a, b;
        double d;
        ss>>a;
        ss>>b;
        ss>>d;
        edge edge_a;
        edge_a.destination=b;
        edge_a.distance=d;
        graph.at(a).neighbors.push_back(edge_a);
        edge edge_b;
        edge_b.destination=a;
        edge_b.distance=d;
        graph.at(b).neighbors.push_back(edge_b);

    }
    cout<<"Wczytałem."<<endl;
    double dist = dijkstra(graph, source, destination);
    cout<<"Odległość między #"<<source<<" a #"<<destination<<" wynosi "<<dist<<endl;
    int dimension = round(sqrt(graph_size));
    cout << setfill(' ') << setw(5);

    unsigned int temp = destination;
    do {
        graph.at(temp).in_path = true;
        temp = graph.at(temp).parent;
    }while(graph.at(temp).parent != 0);
    graph.at(temp).in_path = true;
    if (!print)
    {
        return 0;
    }
    for (int j=0; j< dimension; j++)
    {
        for (int i=0; i< dimension; i++)
        {
            if(graph.at(i+j*dimension).in_path)
            {
                printf("\033[31m");
            }
            cout << setfill(' ') << setw(5)<<i+j*dimension;
            printf("\033[0m");

        }
        cout<<endl;
    }
    return 0;
}

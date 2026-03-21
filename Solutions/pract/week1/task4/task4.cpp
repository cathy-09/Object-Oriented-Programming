#include <iostream>
#include <cstring>

const int MAX_LABEL = 11;

struct Edge
{
    char from[MAX_LABEL];
    char to[MAX_LABEL];
};

struct Graph
{
    int verticesCount;
    int edgesCount;
    int capacity;
    Edge* edges;
};

void initGraph(Graph& g, int m)
{
    g.edgesCount = 0;
    g.capacity = m;
    g.verticesCount = 0;
    g.edges = new Edge[m];
}

bool edgeExists(const Graph& g, const char* from, const char* to)
{
    for (int i = 0; i < g.edgesCount; i++)
    {
        if (strcmp(g.edges[i].from, from) == 0 &&
            strcmp(g.edges[i].to, to) == 0)
            return true;
    }
    return false;
}

void addEdge(Graph& g, const char* from, const char* to)
{
    if (g.edgesCount >= g.capacity)
        return;

    strcpy(g.edges[g.edgesCount].from, from);
    strcpy(g.edges[g.edgesCount].to, to);
    g.edgesCount++;
}

void createGraph(Graph& g, int m)
{
    initGraph(g, m);

    char from[MAX_LABEL];
    char to[MAX_LABEL];

    for (int i = 0; i < m; i++)
    {
        std::cin >> from >> to;
        addEdge(g, from, to);
    }
}

int degree(const Graph& g, const char* vertex)
{
    int count = 0;

    for (int i = 0; i < g.edgesCount; i++)
    {
        if (strcmp(g.edges[i].from, vertex) == 0)
            count++;
    }

    return count;
}

bool isComplete(const Graph& g)
{
    for (int i = 0; i < g.edgesCount; i++)
    {
        for (int j = 0; j < g.edgesCount; j++)
        {
            if (strcmp(g.edges[i].from, g.edges[j].to) != 0 &&
                !edgeExists(g, g.edges[i].from, g.edges[j].to))
                return false;
        }
    }
    return true;
}

void removeEdge(Graph& g, const char* from, const char* to)
{
    for (int i = 0; i < g.edgesCount; i++)
    {
        if (strcmp(g.edges[i].from, from) == 0 &&
            strcmp(g.edges[i].to, to) == 0)
        {
            for (int j = i; j < g.edgesCount - 1; j++)
            {
                g.edges[j] = g.edges[j + 1];
            }
            g.edgesCount--;
            std::cout << "Edge removed.\n";
            return;
        }
    }

    std::cout << "Edge does not exist.\n";
}

int main()
{
    int m;
    std::cout << "Enter number of edges: ";
    std::cin >> m;

    Graph g;
    createGraph(g, m);

    char vertex[MAX_LABEL];
    std::cout << "Enter vertex to check degree: ";
    std::cin >> vertex;

    std::cout << "Degree: " << degree(g, vertex) << std::endl;

    std::cout << "Is complete: "
        << (isComplete(g) ? "Yes" : "No")
        << std::endl;

    char from[MAX_LABEL], to[MAX_LABEL];
    std::cout << "Enter edge to remove (from to): ";
    std::cin >> from >> to;

    removeEdge(g, from, to);

    delete[] g.edges;

    return 0;
}
#include <fstream>
#include <vector>
#include <queue>

std::ifstream is("dijkstra.in");
std::ofstream os("dijkstra.out");

#define INF 0x3f3f3f3f

std::vector<int> dist;
std::vector<std::vector<std::pair<int,int>>> graph;

int N, M;

struct CMP{
    bool operator() (int A, int B)
    {
        return dist[A] > dist[B];
    }
};

std::priority_queue<int, std::vector<int>, CMP> nodes;

void Dijkstra( int vertex );

int main()
{
    is >> N >> M;

    dist.resize(N+1, INF);
    graph.resize(N+1);

    int x, y, cost;
    for( int i = 0; i < M; i++ )
    {
        is >> x >> y >> cost;
        graph[x].push_back(std::make_pair(y, cost));
    }

    Dijkstra(1);

    for( int i = 2; i <= N; i++ )
        if( dist[i] == INF )
            os << "0 ";
        else
            os << dist[i] << ' ';

    return 0;
}

void Dijkstra( int vertex )
{
    dist[vertex] = 0;
    nodes.push(vertex);

    while( ! nodes.empty() )
    {
        vertex = nodes.top();
        nodes.pop();

        for( const auto& i : graph[vertex] )
            if( dist[i.first] > dist[vertex] + i.second )
            {
                dist[i.first] = dist[vertex] + i.second;
                nodes.push(i.first);
            }
    }
}

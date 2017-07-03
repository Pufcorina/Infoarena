#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream is("bfs.in");
ofstream os("bfs.out");

#define INF 0x3f3f3f3f

vector<int> dist;
vector<bool> visited;
vector<vector<int>> graph;
queue<int> nodes;

int S, N, M;

void Bfs(int vertex);

int main()
{
    is >> N >> M >> S;

    dist.resize(N+1, INF);
    visited.resize(N+1,false);
    graph.resize(N+1);

    int x, y;
    for(int i = 0; i < M; i++)
    {
        is >> x >> y;
        graph[x].push_back(y);
    }

    Bfs(S);

    for(int i = 1; i <= N; i++)
        if(dist[i] == INF)
            os << "-1 ";
        else
            os << dist[i] << " ";

    is.close();
    os.close();
    return 0;
}


void Bfs( int vertex )
{
    dist[vertex] = 0;
    nodes.push(vertex);
    visited[vertex] = true;

    while ( ! nodes.empty() )
    {
        vertex = nodes.front();
        nodes.pop();

        for( const auto& i : graph[vertex] )
            if( dist[i] > dist[vertex] + 1 && visited[i] == false )
            {
                dist[i] = dist[vertex] + 1;
                visited[i] = true;
                nodes.push(i);
            }
    }
}

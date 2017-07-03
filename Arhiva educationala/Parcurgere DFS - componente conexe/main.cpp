#include <fstream>
#include <vector>
#include <queue>

std::ifstream is("dfs.in");
std::ofstream os("dfs.out");

int N, M;

std::vector<std::vector<int>> graph;
std::vector<bool> visited;

void DFS( int vertex );

int main()
{
    is >> N >> M;

    graph.resize(N+1);
    visited.resize(N+1, false);

    int x, y;
    for( int i = 0; i < M; i++)
    {
        is >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int conex_components = 0;

    for( int i = 1; i <= N; i++ )
        if( visited[i] == false )
        {
            conex_components++;
            DFS(i);
        }

    os << conex_components;

    return 0;
}

void DFS( int vertex )
{
    visited[vertex] = true;

    for( const auto& i : graph[vertex] )
        if( visited[i] == false )
            DFS(i);
}

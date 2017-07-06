#include <fstream>
#include <vector>
#include <deque>

std::ifstream is("sortaret.in");
std::ofstream os("sortaret.out");

#define alb 0
#define gri 1
#define negru 2

std::vector<std::vector<int>> graph;
std::vector<int> color;
std::deque<int> nodes;

int N, M;

void DFS(int vertex);

int main()
{
    is >> N >> M;

    graph.resize(N + 1);
    color.resize(N + 1, alb);

    int x, y;
    for (int i = 0; i < M; i++)
    {
        is >> x >> y;
        graph[x].push_back(y);
    }

    for (int i = 1; i <= N; i++)
        if (color[i] == alb)
            DFS(i);

    for (const auto& i : nodes)
        os << i << ' ';

    is.close();
    os.close();
    return 0;
}

void DFS(int vertex)
{
    color[vertex] = gri;
    for (const auto& i : graph[vertex])
        if(color[i] == alb)
            DFS(i);
    color[vertex] = negru;
    nodes.push_front(vertex);
}

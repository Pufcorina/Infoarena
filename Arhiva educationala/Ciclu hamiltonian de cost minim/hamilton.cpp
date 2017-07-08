#include <fstream>
#include <vector>

#define INF 0x3f3f3f3f

std::ifstream is("hamilton.in");
std::ofstream os("hamilton.out");

std::vector<std::vector<int>> graph;
int cost[19][19], din_cost[270000][19];

int N, M;

int main()
{
    is >> N >> M;

    graph.resize(N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cost[i][j] = INF;

    int x, y, c;
    for (int i = 0; i < M; i++)
    {
        is >> x >> y >> c;
        graph[y].push_back(x);
        cost[x][y] = c;
    }

    int lung = (1 << N);
    for (int i = 0; i < lung; i++)
        for (int j = 0; j < N; j++)
            din_cost[i][j] = INF;

    din_cost[1][0] = 0;
    for (int i = 1; i < lung; i++)
        for (int j = 0; j < N; j++)
            if ((i & (1 << j)) == 0)
                for (const auto& vertex : graph[j])
                    if (i & (1 << vertex))
                        din_cost[(i | (1 << j))][j] = std::min(din_cost[(i | (1 << j))][j], din_cost[i][vertex] + cost[vertex][j]);
    int sol = INF;

    for (int i = 0; i < N; i++)
        sol = std::min(sol, din_cost[lung-1][i] + cost[i][0]);
    if (sol == INF)
        os << "Nu exista solutie";
    else
        os << sol;

    is.close();
    os.close();
    return 0;
}

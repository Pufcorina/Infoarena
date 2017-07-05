#include <fstream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

std::ifstream is("bellmanford.in");
std::ofstream os("bellmanford.out");

std::vector<std::vector<std::pair<int, int>>> graph;
std::queue<int> nodes;
std::vector<bool> visited;
std::vector<int> nb_visits;
std::vector<int> dist;

int N, M;
int cicle;

void BFS_BellmanFord();

int main()
{
    is >> N >> M;

    graph.resize(N + 1);
    visited.resize(N + 1, false);
    nb_visits.resize(N + 1, 0);
    dist.resize(N + 1, INF);

    int x, y, cost;
    for (int i = 0; i < M; i++)
    {
        is >> x >> y >> cost;
        graph[x].push_back({y, cost});
    }

    BFS_BellmanFord();

    if (cicle == 1)
        os << "Ciclu negativ!";
    else
        for (int i = 2; i <= N; i++)
            os << dist[i] << " ";

    is.close();
    os.close();
    return 0;
}

void BFS_BellmanFord()
{
    nodes.push(1);
    visited[1] = true;
    dist[1] = 0;
    int vertex;

    while (! nodes.empty())
    {
        vertex = nodes.front();
        visited[vertex] = false;
        nodes.pop();

        for (const auto& i : graph[vertex])
            if(dist[i.first] > dist[vertex] + i.second)
            {
                dist[i.first] = dist[vertex] + i.second;
                if (visited[i.first] == false)
                {
                    nb_visits[i.first]++;
                    if (nb_visits[i.first] == N)
                    {
                        cicle = 1;
                        return;
                    }
                    visited[i.first] = true;
                    nodes.push(i.first);
                }
            }
    }
}

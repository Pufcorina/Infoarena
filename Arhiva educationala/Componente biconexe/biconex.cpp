#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

std::ifstream is("biconex.in");
std::ofstream os("biconex.out");

std::vector<std::vector<int>> graph;
std::stack<std::pair<int, int>> nodes;

std::vector<int> low_time;
std::vector<int> visited_time;
std::vector<std::vector<int>> result;
std::vector<int> component;
std::vector<int> parent;

int N, M;
int time_visit;

void DFS(int vertex);

int main()
{
    is >> N >> M;

    graph.resize(N + 1);
    low_time.resize(N + 1);
    visited_time.resize(N + 1, -1);
    parent.resize(N + 1, 0);

    int x, y;
    for (int i = 0; i < M; i++)
    {
        is >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    DFS(1);

    os << result.size() << "\n";
    for (auto& i : result)
    {
        sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()), i.end());
        for (const auto& j : i)
            os << j << " ";
        os << "\n";
    }

    is.close();
    os.close();
    return 0;
}

inline void DFS(int vertex)
{
    visited_time[vertex] = low_time[vertex] = time_visit++;
    for (const auto& i : graph[vertex])
    {
        if (i == parent[vertex])
            continue;
        if (visited_time[i] == -1)
        {
            parent[i] = vertex;
            nodes.push({vertex, i});
            DFS(i);
            low_time[vertex] = std::min(low_time[i], low_time[vertex]);
            if (visited_time[vertex] <= low_time[i])
            {
                component.clear();
                int x, y;
                do
                {
                    x = nodes.top().first;
                    y = nodes.top().second;
                    nodes.pop();
                    component.push_back(x);
                    component.push_back(y);
                } while (x != vertex && y != i);
                result.push_back(component);
            }
        }
        else
            low_time[vertex] = std::min(low_time[i], low_time[vertex]);
    }
}

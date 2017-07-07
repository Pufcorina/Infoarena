#include <fstream>
#include <vector>
#include <algorithm>

#define INF 0x3f3f3f3f

std::ifstream is("apm.in");
std::ofstream os("apm.out");

std::vector<std::vector<std::pair<int, int>>> graph;
std::vector<std::pair<int, int>> result;
std::vector<int> min_dist;
std::vector<int> edge;
std::vector<int> heap, poz;

int N, M;
int position;
int min_cost;

void insert_in_apm(int vertex);
void insert_in_heap(int vertex);
void bubble_up(int pos);
void bubble_down(int pos);
int extractMin();

int main()
{
    is >> N >> M;

    graph.resize(N + 1);
    min_dist.resize(N + 1, INF);
    edge.resize(N + 1);
    heap.resize(N + 1);
    poz.resize(N + 1);

    int x, y, cost;
    for (int i = 0; i < M; i++)
    {
        is >> x >> y >> cost;
        graph[x].push_back({y, cost});
        graph[y].push_back({x, cost});
    }

    min_dist[1] = 0;
    insert_in_apm(1);

    for (int i = 2; i <= N; i++)
        insert_in_heap(i);

    int vertex;
    for (int i = 1; i < N; i++)
    {
        vertex = extractMin();
        insert_in_apm(vertex);
        min_cost += min_dist[vertex];
        result.push_back({vertex, edge[vertex]});
        for (const auto& i : graph[vertex])
        {
            if (poz[i.first])
                bubble_up(poz[i.first]);
        }
    }

    os << min_cost << "\n";
    os << N - 1 << "\n";
    for (const auto& i : result)
        os << i.first << " " << i.second << "\n";
    is.close();
    os.close();
    return 0;
}

void insert_in_apm(int vertex)
{
    for (const auto& i : graph[vertex])
    {
        min_dist[i.first] = std::min(min_dist[i.first], i.second);
        if (min_dist[i.first] == i.second)
            edge[i.first] = vertex;
    }
}

void insert_in_heap(int vertex)
{
    heap[++position] = vertex;
    poz[vertex] = position;
    bubble_up(position);
}

void bubble_up(int pos)
{
    while (pos > 1 && min_dist[heap[pos]] < min_dist[heap[pos/2]])
    {
        std::swap(heap[pos], heap[pos/2]);
        std::swap(poz[heap[pos]], poz[heap[pos/2]]);
        pos /= 2;
    }
}

void bubble_down(int pos)
{
    while ((pos*2 <= position && min_dist[heap[pos]] > min_dist[heap[2*pos]]) || (pos*2 + 1 <= position && min_dist[heap[pos]] > min_dist[heap[2*pos + 1]]))
    {
        if (min_dist[heap[2*pos]] < min_dist[heap[2*pos + 1]] || 2*pos + 1 > position)
        {
            std::swap(heap[pos], heap[pos*2]);
            std::swap(poz[heap[pos]], poz[heap[pos*2]]);
            pos *= 2;
        }
        else
        {
            std::swap(heap[pos], heap[pos*2 + 1]);
            std::swap(poz[heap[pos]], poz[heap[pos*2 + 1]]);
            pos = pos*2 + 1;
        }
    }
}

int extractMin()
{
    int vertex = heap[1];
    std::swap(heap[1], heap[position]);
    std::swap(poz[heap[1]], poz[heap[position]]);
    position--;
    bubble_down(1);
    poz[vertex] = 0;
    return vertex;
}

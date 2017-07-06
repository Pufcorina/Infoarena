#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream is("apm.in");
std::ofstream os("apm.out");

class Edge{
public:
    int x, y, cost;
    Edge(int a, int b, int c) : x(a), y(b), cost(c) {}
    bool operator<(const Edge& e) const
    {
        return this->cost < e.cost;
    }
};

std::vector<Edge> edges;
std::vector<Edge> apm;
std::vector<int> disj_set;
std::vector<int> h;

int N, M;
int min_cost, apm_edges;

void Kruskal();
void Union(int A, int B);
int Find(int A);

int main()
{
    is >> N >> M;

    int x, y, cost;
    for (int i = 0; i < M; i++)
    {
        is >> x >> y >> cost;
        edges.push_back(Edge(x, y, cost));
    }

    Kruskal();

    os << min_cost << "\n";
    os << apm_edges << "\n";
    for(const auto& i : apm)
        os << i.x << ' ' << i.y << '\n';

    is.close();
    os.close();
    return 0;
}

void Kruskal()
{
    disj_set.resize(N + 1);
    h.resize(N + 1, 1);
    for (int i = 1; i <= N; i++)
        disj_set[i] = i;
    sort(edges.begin(), edges.end());
    int A, B;
    for (const auto& i : edges)
    {
        A = Find(i.x);
        B = Find(i.y);
        if (A == B)
            continue;
        min_cost += i.cost;
        apm_edges++;
        apm.push_back(i);
        Union(A, B);
        if (apm_edges == N - 1)
            return;
    }
}

int Find(int A)
{
    if (disj_set[A] == A)
        return A;
    return disj_set[A] = Find(disj_set[A]);
}

void Union(int A, int B)
{
    if (h[A] < h[B])
        disj_set[A] = B;
    else
    {
        disj_set[B] = A;
        if (h[A] == h[B])
            h[A]++;
    }
}

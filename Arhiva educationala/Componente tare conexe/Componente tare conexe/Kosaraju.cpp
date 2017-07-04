#include <fstream>
#include <vector>
#include <stack>

std::ifstream is("ctc.in");
std::ofstream os("ctc.out");

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> reversed_graph;
std::vector<std::vector<int>> result;
std::vector<int> auxiliary;

std::stack<int> nodes;

std::vector<bool> visited;

int N, M;

void DFS_traversal(int vertex);
void DFS_component(int vertex);


int main()
{
	is >> N >> M;

	visited.resize(N + 1, false);
	graph.resize(N + 1);
	reversed_graph.resize(N + 1);

	int x, y;
	for (int i = 0; i < M; i++)
	{
		is >> x >> y;
		graph[x].push_back(y);
		reversed_graph[y].push_back(x);
	}

	for (int i = 1; i <= N; i++)
		if (visited[i] == false)
			DFS_traversal(i);

	visited.clear();
	visited.resize(N + 1, false);

	int vertex;
	while (!nodes.empty())
	{
		vertex = nodes.top();
		nodes.pop();
		if (visited[vertex] == false)
		{
			auxiliary.clear();
			DFS_component(vertex);
			result.push_back(auxiliary);
		}
	}

	os << result.size() << "\n";
	for (const auto& i : result)
	{
		for (const auto& j : i)
			os << j << " ";
		os << "\n";
	}

	is.close();
	os.close();
	return 0;
}

void DFS_traversal(int vertex)
{
	visited[vertex] = true;
	for (const auto& i : graph[vertex])
		if (visited[i] == false)
			DFS_traversal(i);
	nodes.push(vertex);
}

void DFS_component(int vertex)
{
	visited[vertex] = true;
	auxiliary.push_back(vertex);
	for (const auto& i : reversed_graph[vertex])
		if (visited[i] == false)
			DFS_component(i);
}
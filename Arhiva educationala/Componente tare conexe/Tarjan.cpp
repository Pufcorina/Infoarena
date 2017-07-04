#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

std::ifstream is("ctc.in");
std::ofstream os("ctc.out");

std::vector<std::vector<int>> graph;
std::vector<bool> in_stack;
std::vector<int> visited_time;
std::vector<int> low_time;
int time_visit;
int node;

int N, M;

std::stack<int> nodes;
std::vector<std::vector<int>> result;
std::vector<int> component;

void Tarjan(int vertex);

int main()
{
	is >> N >> M;

	graph.resize(N + 1);
	visited_time.resize(N + 1);
	visited_time.assign(N+1, -1);
	low_time.resize(N + 1);
	in_stack.resize(N + 1, false);

	int x, y;
	for (int i = 0; i < M; i++)
	{
		is >> x >> y;
		graph[x].push_back(y);
	}

	for (int i = 1; i <= N; i++)
		if (visited_time[i] == -1)
			Tarjan(i);

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

void Tarjan(int vertex)
{
	visited_time[vertex] = low_time[vertex] = time_visit++;
	nodes.push(vertex);
	in_stack[vertex] = true;

	for(const auto& i : graph[vertex])
		if (visited_time[i] == -1)
		{
			Tarjan(i);
			low_time[vertex] = std::min(low_time[vertex], low_time[i]);
		}
		else if(in_stack[i])
			low_time[vertex] = std::min(low_time[vertex], low_time[i]);
	if (visited_time[vertex] == low_time[vertex])
	{
		component.clear();
		do
		{
			node = nodes.top();
			nodes.pop();
			component.push_back(node);
			in_stack[node] = false;
		} while (node != vertex);
		result.push_back(component);
	}
}
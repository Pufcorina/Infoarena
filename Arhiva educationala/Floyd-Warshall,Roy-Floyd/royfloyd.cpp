#include <fstream>

std::ifstream is("royfloyd.in");
std::ofstream os("royfloyd.out");

int graph_distance[101][101];
int N;

void RoyFloyd();

int main()
{
	is >> N;

	int x;
	for(int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			is >> x;
			graph_distance[i][j] = x;
		}

	RoyFloyd();

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
            os << graph_distance[i][j] << ' ';
		os << '\n';
	}

	is.close();
	os.close();
	return 0;
}

void RoyFloyd()
{
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if ( i!= j && graph_distance[i][k] && graph_distance[k][j] && (graph_distance[i][j] > graph_distance[i][k] + graph_distance[k][j] || !graph_distance[i][j]))
					graph_distance[i][j] = graph_distance[i][k] + graph_distance[k][j];
}

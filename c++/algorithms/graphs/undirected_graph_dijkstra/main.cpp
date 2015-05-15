#include "undirected_graph.h"

int main(int /*argc*/, char */*argv*/[])
{
  std::vector<std::pair<std::pair<int, int>, std::pair<double, double> > > graph_data;

  graph_data.push_back(std::make_pair(std::make_pair(12, 10), std::make_pair(DBL_MAX, 1.2)));
  graph_data.push_back(std::make_pair(std::make_pair(12, 9), std::make_pair(DBL_MAX, 1.2)));
  graph_data.push_back(std::make_pair(std::make_pair(12, 2), std::make_pair(DBL_MAX, 1.2)));
  graph_data.push_back(std::make_pair(std::make_pair(1, 2), std::make_pair(DBL_MAX, 1.2)));
  graph_data.push_back(std::make_pair(std::make_pair(9, 12), std::make_pair(DBL_MAX, 1.2)));
  graph_data.push_back(std::make_pair(std::make_pair(4, 4), std::make_pair(DBL_MAX, 1.2)));
  graph_data.push_back(std::make_pair(std::make_pair(1, 4), std::make_pair(DBL_MAX, 1.2)));

  GraphComponents::undirected_graph<int, double, double> ug(graph_data);
  ug.print_graph();
  ug.dijkstras_algorithm(12);
}

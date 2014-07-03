#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <utility>
#include <cfloat>
#include <algorithm>

namespace GraphComponents
{
  template <typename vertex_key, typename vertex_data, typename edge_data>
  class vertex
  {
  public:
    /*!
     * \br Edge class which has a weight and a traversed variable
     * managed by a vertex
     */
    template <typename edge_data_internal>
    class edge
    {
    public:
      /*!
       * \br ctor -- construct a edge with a weight, and an adjacent vertex
       */
      edge(edge_data weight, vertex<vertex_key, vertex_data, edge_data> *&adjacent) :
        _weight(weight),
        _adjacent(adjacent),
        _traversed(false)
      {}

      /* Geters */
      edge_data weight() const { return _weight; }
      vertex<vertex_key, vertex_data, edge_data> *adjacent() const { return _adjacent; }
      bool traversed() const { return _traversed; }

      /* Setters */
      void set_weight(edge_data weight) { _weight = weight; }
      void set_traversed(bool traversed) { _traversed = traversed; }

      bool operator() (edge<edge_data_internal> &e) { return e.adjacent()->key() == _adjacent->key(); }
    private:
      edge_data _weight;
      vertex<vertex_key, vertex_data, edge_data> *_adjacent;
      bool _traversed;
    };
    /* END EDGE CLASS*/

    /*!
     * \br ctor -- construct a vertex with a key, and a distance object
     */
    vertex() :
      _visited(false)
    {}
    vertex(vertex_key key, vertex_data distance) :
      _key(key),
      _distance(distance),
      _visited(false)
    {}
    /* Getters */
    vertex_key key() const { return _key; }
    vertex_data distance() const { return _distance; }
    const std::list<edge<edge_data> > *edges() const { return &_edges; }
    bool visited() const { return visited; }

    /* Setters */
    void set_key(vertex_key &key) { _key = key; }
    void set_distance(vertex_data &distance) { _distance = distance; }
    bool operator() (vertex<vertex_key, vertex_data, edge_data> &v) { return v.key() == _key; }

    /* Public Methods */
    void insert_edge(vertex<vertex_key, vertex_data, edge_data> *adjacent, edge_data weight);

    typedef typename std::list<edge<edge_data> >::iterator edge_iterator;
    typedef typename std::list<edge<edge_data> >::const_iterator const_edge_iterator;

  private:
    vertex_key _key;
    vertex_data _distance;
    std::list<edge<edge_data> > _edges;
    bool _visited;
  };

  /*!
   * \br Undirected graph template class which allows you to specify the type of edge weight
   * vertex key and vertex data
   */
  template <typename vertex_key_type, typename vertex_data_type, typename edge_data_type>
  class undirected_graph
  {
  public:
    /*!
     * \br ctor -- construct a graph with a key type, and a distance type and a edge weight
     * type
     */
    undirected_graph(std::vector<std::pair<std::pair<vertex_key_type, vertex_key_type>,
                                           std::pair<vertex_data_type, edge_data_type> > > adjacency_list);

    void insert_vertex_by_key_pair(vertex_key_type key1, vertex_key_type key2, vertex_data_type distance, edge_data_type weight);
    void print_graph();
    void dijkstras_algorithm(vertex_key_type key);


    /*!
     * \br Typedefs
     */
    typedef typename std::vector<
      typename std::pair<
      typename std::pair<vertex_key_type, vertex_key_type>,
      typename std::pair<vertex_data_type, edge_data_type> > >::iterator graph_data_iter;

    typedef typename std::list<vertex<vertex_key_type, vertex_data_type, edge_data_type> >::iterator vertex_iterator;

  private:
    std::list<vertex<vertex_key_type, vertex_data_type, edge_data_type> > _vertices;
  };

  /*!
   * Predicate for comparing vertices
   */
  template <typename vertex_key_type, typename vertex_data_type, typename edge_data_type>
  bool compare_vertices(vertex<vertex_key_type, vertex_data_type, edge_data_type> *v1,
    vertex<vertex_key_type, vertex_data_type, edge_data_type> *v2) {
    if (v1 && v2) {
      return v1->distance() > v2->distance();
    } else {
      return false;
    }
  }
}

template <typename vertex_key_type, typename vertex_data_type, typename edge_data_type>
GraphComponents::undirected_graph<vertex_key_type, vertex_data_type, edge_data_type>::undirected_graph
  (std::vector<std::pair<std::pair<vertex_key_type, vertex_key_type>, std::pair<vertex_data_type, edge_data_type> > > adjacency_list)
{
  for (graph_data_iter data_iter = adjacency_list.begin(); data_iter != adjacency_list.end(); ++data_iter) {
      insert_vertex_by_key_pair(data_iter->first.first, data_iter->first.second, data_iter->second.first,data_iter->second.second);
  }
}

template <typename vertex_key_type, typename vertex_data_type, typename edge_data_type>
void GraphComponents::undirected_graph<vertex_key_type, vertex_data_type, edge_data_type>::insert_vertex_by_key_pair
  (vertex_key_type key1, vertex_key_type key2, vertex_data_type distance, edge_data_type weight)
{
  vertex_iterator key1_vertex =
      std::find_if(_vertices.begin(), _vertices.end(), GraphComponents::vertex<vertex_key_type, vertex_data_type, edge_data_type>(key1, distance));
  if (key1_vertex == _vertices.end()) {
    _vertices.push_back(GraphComponents::vertex<vertex_key_type, vertex_data_type, edge_data_type>(key1, distance));
    key1_vertex =
        std::find_if(_vertices.begin(), _vertices.end(), GraphComponents::vertex<vertex_key_type, vertex_data_type, edge_data_type>(key1, distance));
  }

  vertex_iterator key2_vertex =
      std::find_if(_vertices.begin(), _vertices.end(), GraphComponents::vertex<vertex_key_type, vertex_data_type, edge_data_type>(key2, distance));
  if (key2_vertex == _vertices.end()) {
    _vertices.push_back(GraphComponents::vertex<vertex_key_type, vertex_data_type, edge_data_type>(key2, distance));
    key2_vertex =
        std::find_if(_vertices.begin(), _vertices.end(), GraphComponents::vertex<vertex_key_type, vertex_data_type, edge_data_type>(key2, distance));
  }

  key1_vertex->insert_edge(&(*key2_vertex), weight);
  key2_vertex->insert_edge(&(*key1_vertex), weight);
}

template <typename vertex_key_type, typename vertex_data_type, typename edge_data_type>
void GraphComponents::undirected_graph<vertex_key_type, vertex_data_type, edge_data_type>::print_graph()
{
  vertex_iterator print_vertex_iter = _vertices.begin();
  while (print_vertex_iter != _vertices.end()) {
    std::cerr << print_vertex_iter->key() << "[" << print_vertex_iter->distance() << "] --:";
    typename GraphComponents::vertex<vertex_key_type, vertex_data_type, edge_data_type>::const_edge_iterator print_edges =
      print_vertex_iter->edges()->begin();
    while (print_edges != print_vertex_iter->edges()->end()) {
      std::cerr << print_edges->adjacent()->key() << "(" << print_edges->weight() << ") --> ";
      ++print_edges;
    }
    std::cout << std::endl;
    ++print_vertex_iter;
  }
}

template <typename vertex_key_type, typename vertex_data_type, typename edge_data_type>
void GraphComponents::undirected_graph<vertex_key_type, vertex_data_type, edge_data_type>::dijkstras_algorithm(vertex_key_type key)
{
  /*
   * Copy all vertices into a heap
   */
  typename std::vector<vertex<vertex_key_type, vertex_data_type, edge_data_type> *> heap;
  vertex_iterator copy_vertex_iter = _vertices.begin();
  while (copy_vertex_iter != _vertices.end()) {
    heap.push_back(&(*copy_vertex_iter));
    ++copy_vertex_iter;
  }

  vertex_data_type d = 0;
  (*heap.begin())->set_distance(d);

  std::make_heap(heap.begin(), heap.end(), GraphComponents::compare_vertices<vertex_key_type, vertex_data_type, edge_data_type>);

  typedef typename std::vector<GraphComponents::vertex<vertex_key_type, vertex_data_type, edge_data_type> *>::iterator heap_iter;
  heap_iter print_heap_iter = heap.begin();
  while(print_heap_iter != heap.end()) {
    std::cout << (*print_heap_iter)->key() << " -- " << (*print_heap_iter)->distance() << std::endl;
    ++print_heap_iter;
  }

  print_graph();
}

template <typename vertex_key, typename vertex_data, typename edge_data>
void GraphComponents::vertex<vertex_key, vertex_data, edge_data>::insert_edge
  (vertex<vertex_key, vertex_data, edge_data> *adjacent, edge_data weight)
{
  edge_iterator edge_finder =
      std::find_if(_edges.begin(), _edges.end(), GraphComponents::vertex<vertex_key, vertex_data, edge_data>::edge<edge_data>(weight, adjacent));
  if(edge_finder == _edges.end()) {
    _edges.push_back(GraphComponents::vertex<vertex_key, vertex_data, edge_data>::edge<edge_data>(weight, *&adjacent));
  }
}

#endif // UNDIRECTED_GRAPH_H

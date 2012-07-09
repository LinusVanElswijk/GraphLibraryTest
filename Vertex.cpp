#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE GraphLibTest
#endif
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <list>
#include <Graph.hpp>
using namespace graphs;


BOOST_AUTO_TEST_SUITE(vertex)

typedef boost::mpl::list<float,double> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(addingOutgoingEdges, T, test_types)
{
	Graph<T> graph(100);

	Vertex<T> &vertexA = graph.getVertex(0);

	for(unsigned int i = 1; i < 10; i++)
	{
		Vertex<T> &vertexI = graph.getVertex(i);

		vertexA.addEdgeTo(vertexI, (T)1.0);
		BOOST_CHECK_EQUAL(vertexA.getOutgoingEdges().size(), i);
		BOOST_CHECK_EQUAL(vertexI.getIncomingEdges().size(), 1);
	}

	for(unsigned int i = 1; i < 10; i++)
	{
		Vertex<T> &vertexI = graph.getVertex(i);

		vertexA.addEdgeTo(vertexI, (T)1.0);
		BOOST_CHECK_EQUAL(vertexA.getOutgoingEdges().size(), 9);
		BOOST_CHECK_EQUAL(vertexI.getIncomingEdges().size(), 1);
	}
}

BOOST_AUTO_TEST_CASE_TEMPLATE(gettingOutgoingEdges, T, test_types)
{
	Graph<T> graph(10);

	Vertex<T> &vertexA = graph.getVertex(7),
			  &vertexB = graph.getVertex(4);

	vertexA.addEdgeTo(vertexB, 1.0f);

	std::list<Edge<T> > edges = vertexA.getOutgoingEdges();
	BOOST_CHECK_EQUAL(edges.size(), 1);
	BOOST_CHECK_EQUAL(edges.front().fromIndex, vertexA.getIndex());
	BOOST_CHECK_EQUAL(edges.front().toIndex, vertexB.getIndex());
	BOOST_CHECK_EQUAL(edges.front().cost, 1.0f);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(gettingIncomingEdges, T, test_types)
{
	Graph<T> graph(10);

	Vertex<T> &vertexA = graph.getVertex(7),
			  &vertexB = graph.getVertex(4);

	vertexA.addEdgeTo(vertexB, 1.0f);

	std::list<Edge<T> > edges = vertexB.getIncomingEdges();
	BOOST_CHECK_EQUAL(edges.size(), 1);
	BOOST_CHECK_EQUAL(edges.front().fromIndex, vertexA.getIndex());
	BOOST_CHECK_EQUAL(edges.front().toIndex, vertexB.getIndex());
	BOOST_CHECK_EQUAL(edges.front().cost, 1.0f);
}

BOOST_AUTO_TEST_SUITE_END()

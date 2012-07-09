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

BOOST_AUTO_TEST_CASE_TEMPLATE(addEdgeToTest, T, test_types)
{
	Graph<T> graph(10);

	Vertex<T> &vertexA = graph.getVertex(7),
			  &vertexB = graph.getVertex(4);

	vertexA.addEdgeTo(vertexB, 1.23f);

	std::list<Edge<T> > outEdges = vertexA.getOutgoingEdges();
	BOOST_CHECK_EQUAL(outEdges.size(), 1);
	BOOST_CHECK_EQUAL(outEdges.front().fromIndex, vertexA.getIndex());
	BOOST_CHECK_EQUAL(outEdges.front().toIndex, vertexB.getIndex());
	BOOST_CHECK_EQUAL(outEdges.front().cost, 1.0f);

	std::list<Edge<T> > inEdges = vertexB.getIncomingEdges();
	BOOST_CHECK_EQUAL(inEdges.size(), 1);
	//BOOST_CHECK_EQUAL(outEdges.front(), inEdges.front());
}

BOOST_AUTO_TEST_SUITE_END()

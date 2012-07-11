#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE GraphLibTest
#endif
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <Graph.hpp>
using namespace graphs;

BOOST_AUTO_TEST_SUITE(GraphTest)

typedef boost::mpl::list<float,double> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(constructorTest, T, test_types)
{
	/*
	for(unsigned int i = 0; i <= 1000000; i+= 200000)
    {
		Graph<T> graph(i);
    	BOOST_REQUIRE_EQUAL(graph.getNrOfVertices(), i);

    	for(unsigned int j = 0; j < i; j++)
    	{
    		Vertex<T> &vertex  = graph.getVertex(j);
    		BOOST_CHECK_EQUAL(vertex.getIndex(), j);
    		BOOST_CHECK_EQUAL(vertex.getIncomingEdges().size(), 0);
    		BOOST_CHECK_EQUAL(vertex.getOutgoingEdges().size(), 0);
    		BOOST_CHECK_EQUAL(&vertex.getGraph(), &graph);
    	}
    }*/
}

BOOST_AUTO_TEST_CASE_TEMPLATE(addingEdgesTest, T, test_types)
{
	Graph<T> graph(100);

    Vertex<T> &vertexA = graph.getVertex(0),
    		  &vertexB = graph.getVertex(99);

    graph.addEdge(vertexA, vertexB, (T)1.0);
    BOOST_CHECK_EQUAL(vertexA.getOutgoingEdges().size(), 1);
    BOOST_CHECK_EQUAL(vertexA.getIncomingEdges().size(), 0);
    BOOST_CHECK_EQUAL(vertexB.getOutgoingEdges().size(), 0);
    BOOST_CHECK_EQUAL(vertexB.getIncomingEdges().size(), 1);

    graph.addEdge(vertexA, vertexB, 2.0);

    BOOST_CHECK_EQUAL(vertexA.getOutgoingEdges().size(), 1);
    BOOST_CHECK_EQUAL(vertexA.getIncomingEdges().size(), 0);
    BOOST_CHECK_EQUAL(vertexB.getOutgoingEdges().size(), 0);
    BOOST_CHECK_EQUAL(vertexB.getIncomingEdges().size(), 1);
}


BOOST_AUTO_TEST_SUITE_END()

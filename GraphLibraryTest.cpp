#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE const_string GraphTest
#include <boost/test/unit_test.hpp>

#include <Graph.hpp>

using namespace graphs;

BOOST_AUTO_TEST_CASE(contructorTest)
{
	for(unsigned int i = 0; i < 1000000; i+= 200000)
    {
		Graph<float> fGraph(i);
    	BOOST_CHECK(fGraph.getNrOfVertices() == i);

    	Graph<double> dGraph(i);
    	BOOST_CHECK(dGraph.getNrOfVertices() == i);

    	for(unsigned int j = 0; j < i; j++)
    	{
    		Vertex<float> &fVertex  = fGraph.getVertex(j);
    		BOOST_CHECK(fVertex.getIndex() == j);
    		BOOST_CHECK(fVertex.getIncomingEdges().size() == 0);
    		BOOST_CHECK(fVertex.getOutgoingEdges().size() == 0);

    		Vertex<double> &dVertex = dGraph.getVertex(j);
    		BOOST_CHECK(dVertex.getIndex() == j);
    		BOOST_CHECK(dVertex.getIncomingEdges().size() == 0);
    		BOOST_CHECK(dVertex.getOutgoingEdges().size() == 0);
    	}
    }
}

BOOST_AUTO_TEST_CASE(addingEdges)
{
	Graph<float> fGraph(100);

    Graph<double> dGraph(100);

    Vertex<float> &fVertexA = fGraph.getVertex(0),
    		      &fVertexB = fGraph.getVertex(99);

    fGraph.addEdge(fVertexA, fVertexB, 1.0);
    BOOST_CHECK(fVertexA.getOutgoingEdges().size() == 1);

    Vertex<double> &dVertexA = dGraph.getVertex(0),
       		       &dVertexB = dGraph.getVertex(99);

    dGraph.addEdge(dVertexA, dVertexB, 1.0);
    BOOST_CHECK(dVertexA.getOutgoingEdges().size() == 1);
    //dGraph.addEdge(dVertexA, dVertexB, 2.0);
    //BOOST_CHECK(dVertexA.getOutgoingEdges().size() == 1);
}

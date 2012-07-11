#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE GraphLibTest
#endif
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <GridGraph.hpp>
using namespace graphs;

BOOST_AUTO_TEST_SUITE(GridGraphTest)

typedef boost::mpl::list<float,double> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(constructorTest, T, test_types)
{
	const unsigned int width = 5,
			           height = 5;

	GridGraph<T> graph(width, height);
    BOOST_REQUIRE_EQUAL(graph.getNrOfVertices(), width * height);
    BOOST_REQUIRE_EQUAL(graph.getWidth(), width);
    BOOST_REQUIRE_EQUAL(graph.getHeight(), height);

    unsigned int expectedIndex = 0;

    for(unsigned int y = 0; y < width; y++)
    {
    	for(unsigned int x = 0; x < height; x++, expectedIndex++)
    	{
    		GridVertex<T> &vertex  = graph.getVertex(x, y);
        	BOOST_CHECK_EQUAL(vertex.getIndex(), expectedIndex);
        	BOOST_CHECK_EQUAL(vertex.getX(), x);
        	BOOST_CHECK_EQUAL(vertex.getY(), y);
        	//BOOST_CHECK_EQUAL(vertex.getIncomingEdges().size(), 0);
        	//BOOST_CHECK_EQUAL(vertex.getOutgoingEdges().size(), 0);
        	BOOST_CHECK_EQUAL(&vertex.getGraph(), &graph);
    	}
    }
}

BOOST_AUTO_TEST_SUITE_END()

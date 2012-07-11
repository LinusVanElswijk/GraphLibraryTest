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

template <typename T>
struct Fixture
{
	Fixture()
	:graph(10),
	 vertexA(graph.getVertex(7)),
	 vertexB(graph.getVertex(4)),
	 vertexC(graph.getVertex(0)),
	 COST_A((T)1.23),
	 COST_B((T)2.55),
	 COST_C((T)0.45),
	 EPSILON((T)0.0001)
	{

	}

	void addEdgesToAll(Vertex<T>& vertex, const T& cost)
	{
		for(unsigned int i = 0; i < graph.getNrOfVertices(); i++)
		{
			vertex.addEdgeTo(graph.getVertex(i), cost);
		}
	}

	void addEdgesFromAll(Vertex<T>& vertex, const T& cost)
	{
		for(unsigned int i = 0; i < graph.getNrOfVertices(); i++)
		{
			vertex.addEdgeFrom(graph.getVertex(i), cost);
		}
	}

	Graph<T>  graph;

	Vertex<T> &vertexA,
			  &vertexB,
			  &vertexC;

	const T COST_A,
			COST_B,
			COST_C;

	const T EPSILON;
};

template <typename T>
void checkListContainsEdge(std::list<Edge<T> > &list,
						   Vertex<T> &from, Vertex<T> &to, const T &cost,
						   const T &epsilon
						  )
{
	typedef typename std::list<Edge<T> >::iterator iterator;

	unsigned int count = 0;

	for(iterator i = list.begin(); i != list.end(); i++)
	{
		if(i->fromIndex == from.getIndex() && i->toIndex == to.getIndex())
		{
			count++;
			if(count == 1)
			{
				BOOST_CHECK_CLOSE(i->cost, cost, epsilon);
			}
		}
	}

	BOOST_CHECK_EQUAL(count, 1);
}

template <typename T>
void checkListNotContainsEdge(std::list<Edge<T> > &list,
						      Vertex<T> &from, Vertex<T> &to
						     )
{
	typedef typename std::list<Edge<T> >::iterator iterator;

	unsigned int count = 0;

	for(iterator i = list.begin(); i != list.end(); i++)
	{
		if(i->fromIndex == from.getIndex() && i->toIndex == to.getIndex())
		{
			count++;
		}
	}

	BOOST_CHECK_EQUAL(count, 0);
}

template <typename T>
void checkEdgeWithGetEdgeTo(Vertex<T> &from, Vertex<T> &to, const T &cost, const T &epsilon)
{
	typedef typename Vertex<T>::EdgePtr EdgePtr;

	EdgePtr edgeTo = from.getEdgeTo(to);
	BOOST_CHECK_EQUAL(edgeTo->fromIndex, from.getIndex());
	BOOST_CHECK_EQUAL(edgeTo->toIndex, to.getIndex());
	BOOST_CHECK_CLOSE(edgeTo->cost, cost, epsilon);
}

template <typename T>
void checkNoEdgeWithGetEdgeTo(Vertex<T> &from, Vertex<T> &to)
{
	typedef typename Vertex<T>::EdgePtr EdgePtr;

	EdgePtr edgeTo = from.getEdgeTo(to);
	BOOST_CHECK_EQUAL(edgeTo, EdgePtr());
}

template <typename T>
void checkEdgeWithGetEdgeFrom(Vertex<T> &from, Vertex<T> &to, const T &cost, const T &epsilon)
{
	typedef typename Vertex<T>::EdgePtr EdgePtr;

	EdgePtr edgeFrom = to.getEdgeFrom(from);
	BOOST_CHECK_EQUAL(edgeFrom->fromIndex, from.getIndex());
	BOOST_CHECK_EQUAL(edgeFrom->toIndex, to.getIndex());
	BOOST_CHECK_CLOSE(edgeFrom->cost, cost, epsilon);
}

template <typename T>
void checkNoEdgeWithGetEdgeFrom(Vertex<T> &from, Vertex<T> &to)
{
	typedef typename Vertex<T>::EdgePtr EdgePtr;

	EdgePtr edgeFrom = to.getEdgeTo(from);
	BOOST_CHECK_EQUAL(edgeFrom, EdgePtr());
}

template <typename T>
void checkEdgeSuccessfullyAdded(std::list<Edge<T> > &outEdges, const unsigned int &expectedOutEdgesListSize,
							    std::list<Edge<T> > &inEdges, const unsigned int &expectedInEdgesListSize,
						   	    Vertex<T> &from, Vertex<T> &to, const T &cost,
						   	    const T &epsilon
						  	   )
{
	BOOST_CHECK_EQUAL(outEdges.size(), expectedOutEdgesListSize);
	BOOST_CHECK_EQUAL(inEdges.size(), expectedInEdgesListSize);
	checkListContainsEdge(outEdges, from, to, cost, epsilon);
	checkListContainsEdge(inEdges, from, to, cost, epsilon);
	checkEdgeWithGetEdgeTo(from, to, cost, epsilon);
	checkEdgeWithGetEdgeFrom(from, to, cost, epsilon);
}

template <typename T>
void checkEdgeSuccessfullyRemoved(std::list<Edge<T> > &outEdges, const unsigned int &expectedOutEdgesListSize,
							      std::list<Edge<T> > &inEdges, const unsigned int &expectedInEdgesListSize,
						   	      Vertex<T> &from, Vertex<T> &to
						  	     )
{
	BOOST_CHECK_EQUAL(outEdges.size(), expectedOutEdgesListSize);
	BOOST_CHECK_EQUAL(inEdges.size(), expectedInEdgesListSize);
	checkListNotContainsEdge(outEdges, from, to);
	checkListNotContainsEdge(inEdges, from, to);
	checkNoEdgeWithGetEdgeTo(from, to);
	checkNoEdgeWithGetEdgeFrom(from, to);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(addEdgeToTest, T, test_types)
{
	Fixture<T> f;
	typedef typename Vertex<T>::EdgePtr EdgePtr;


	// Adding first edge to vertex

	f.vertexA.addEdgeTo(f.vertexB, f.COST_A);
	std::list<Edge<T> > outEdges = f.vertexA.getOutgoingEdges(),
					    inEdges  = f.vertexB.getIncomingEdges();

	checkEdgeSuccessfullyAdded(outEdges, 1, inEdges, 1, f.vertexA, f.vertexB, f.COST_A, f.EPSILON);

	// Adding second edge to vertex
	f.vertexA.addEdgeTo(f.vertexC, f.COST_B);

	outEdges = f.vertexA.getOutgoingEdges();
	inEdges  = f.vertexC.getIncomingEdges();

	checkEdgeSuccessfullyAdded(outEdges, 2, inEdges, 1, f.vertexA, f.vertexC, f.COST_B, f.EPSILON);

	// Updating existing edge to vertex
	f.vertexA.addEdgeTo(f.vertexB, f.COST_C);

	outEdges = f.vertexA.getOutgoingEdges();
	inEdges  = f.vertexB.getIncomingEdges();

	checkEdgeSuccessfullyAdded(outEdges, 2, inEdges, 1, f.vertexA, f.vertexB, f.COST_C, f.EPSILON);


	// Adding reflexive edge to vertex
	f.vertexA.addEdgeTo(f.vertexA, f.COST_B);
	outEdges = f.vertexA.getOutgoingEdges();
	inEdges = f.vertexA.getIncomingEdges();

	checkEdgeSuccessfullyAdded(outEdges, 3, inEdges, 1, f.vertexA, f.vertexA, f.COST_B, f.EPSILON);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(addEdgeFromTest, T, test_types)
{
	Fixture<T> f;
	typedef typename Vertex<T>::EdgePtr EdgePtr;


	// Adding first edge from vertex

	f.vertexA.addEdgeFrom(f.vertexB, f.COST_A);
	std::list<Edge<T> > outEdges = f.vertexB.getOutgoingEdges(),
					    inEdges  = f.vertexA.getIncomingEdges();

	checkEdgeSuccessfullyAdded(outEdges, 1, inEdges, 1, f.vertexB, f.vertexA, f.COST_A, f.EPSILON);


	// Adding second edge from vertex
	f.vertexA.addEdgeFrom(f.vertexC, f.COST_B);

	outEdges = f.vertexC.getOutgoingEdges();
	inEdges  = f.vertexA.getIncomingEdges();

	checkEdgeSuccessfullyAdded(outEdges, 1, inEdges, 2, f.vertexC, f.vertexA, f.COST_B, f.EPSILON);

	// Updating existing edge from vertex
	f.vertexA.addEdgeFrom(f.vertexB, f.COST_C);

	outEdges = f.vertexB.getOutgoingEdges();
	inEdges  = f.vertexA.getIncomingEdges();

	checkEdgeSuccessfullyAdded(outEdges, 1, inEdges, 2, f.vertexB, f.vertexA, f.COST_C, f.EPSILON);

	// Adding reflexive edge to vertex
	f.vertexA.addEdgeTo(f.vertexA, f.COST_B);

	outEdges = f.vertexA.getOutgoingEdges();
	inEdges = f.vertexA.getIncomingEdges();

	checkEdgeSuccessfullyAdded(outEdges, 1, inEdges, 3, f.vertexA, f.vertexA, f.COST_B, f.EPSILON);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(removeEdgeToTest, T, test_types)
{
	Fixture<T> f;
	typedef typename Vertex<T>::EdgePtr EdgePtr;

	f.addEdgesToAll(f.vertexA, (T)1.0);
	std::list<Edge<T> > outEdges = f.vertexA.getOutgoingEdges();
	unsigned int expectedOutEdgesListSize = outEdges.size();

	// Removing edge to first vertex
	f.vertexA.removeEdgeTo(f.vertexB);
	expectedOutEdgesListSize--;

	outEdges = f.vertexA.getOutgoingEdges();
	std::list<Edge<T> > inEdges  = f.vertexB.getIncomingEdges();
	unsigned int expectedInEdgesListSize = 0;

	checkEdgeSuccessfullyRemoved(outEdges, expectedOutEdgesListSize, inEdges, expectedInEdgesListSize, f.vertexA, f.vertexB);

	// Removing edge to second vertex
	f.vertexA.removeEdgeTo(f.vertexC);
	expectedOutEdgesListSize--;

	outEdges = f.vertexA.getOutgoingEdges(),
	inEdges  = f.vertexC.getIncomingEdges();
	expectedInEdgesListSize = 0;

	checkEdgeSuccessfullyRemoved(outEdges, expectedOutEdgesListSize, inEdges, expectedInEdgesListSize, f.vertexA, f.vertexC);

	// Removing edge to second vertex again
	f.vertexA.removeEdgeTo(f.vertexC);

	outEdges = f.vertexA.getOutgoingEdges(),
	inEdges  = f.vertexC.getIncomingEdges();

	checkEdgeSuccessfullyRemoved(outEdges, expectedOutEdgesListSize, inEdges, expectedInEdgesListSize, f.vertexA, f.vertexC);

	// Removing reflexive edge
	f.vertexA.removeEdgeTo(f.vertexA);
	expectedOutEdgesListSize--;

	outEdges = f.vertexA.getOutgoingEdges();
	inEdges = f.vertexA.getIncomingEdges();
	expectedInEdgesListSize = 0;

	checkEdgeSuccessfullyRemoved(outEdges, expectedOutEdgesListSize, inEdges, expectedInEdgesListSize, f.vertexA, f.vertexA);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(removeEdgeFromTest, T, test_types)
{
	Fixture<T> f;
	typedef typename Vertex<T>::EdgePtr EdgePtr;

	f.addEdgesFromAll(f.vertexA, (T)1.0);
	std::list<Edge<T> > inEdges = f.vertexA.getIncomingEdges();
	unsigned int expectedInEdgesListSize = inEdges.size();

	// Removing edge from first vertex
	f.vertexA.removeEdgeFrom(f.vertexB);
	expectedInEdgesListSize--;

	inEdges = f.vertexA.getIncomingEdges();
	std::list<Edge<T> > outEdges  = f.vertexB.getOutgoingEdges();
	unsigned int expectedOutEdgesListSize = 0;

	checkEdgeSuccessfullyRemoved(outEdges, expectedOutEdgesListSize, inEdges, expectedInEdgesListSize, f.vertexA, f.vertexB);

	// Removing edge to second vertex
	f.vertexA.removeEdgeFrom(f.vertexC);
	expectedInEdgesListSize--;

	outEdges = f.vertexC.getOutgoingEdges(),
	inEdges  = f.vertexA.getIncomingEdges();
	expectedOutEdgesListSize = 0;

	checkEdgeSuccessfullyRemoved(outEdges, expectedOutEdgesListSize, inEdges, expectedInEdgesListSize, f.vertexA, f.vertexC);

	// Removing edge to second vertex again
	f.vertexA.removeEdgeTo(f.vertexC);

	outEdges = f.vertexC.getOutgoingEdges(),
	inEdges  = f.vertexA.getIncomingEdges();

	checkEdgeSuccessfullyRemoved(outEdges, expectedOutEdgesListSize, inEdges, expectedInEdgesListSize, f.vertexA, f.vertexC);

	// Removing reflexive edge
	f.vertexA.removeEdgeTo(f.vertexA);
	expectedInEdgesListSize--;

	outEdges = f.vertexA.getOutgoingEdges();
	inEdges = f.vertexA.getIncomingEdges();
	expectedOutEdgesListSize = 0;

	checkEdgeSuccessfullyRemoved(outEdges, expectedOutEdgesListSize, inEdges, expectedInEdgesListSize, f.vertexA, f.vertexA);
}

BOOST_AUTO_TEST_SUITE_END()

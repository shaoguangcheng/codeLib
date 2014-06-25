#include <iostream>
#include <lemon/lp.h>
#include <lemon/list_graph.h>

#include "../src/sys/timeProcess.h"

using namespace lemon;

void testLP()
{
    // Create an instance of the default LP solver class
    // (it will represent an "empty" problem at first)
    Lp lp;
    // Add two columns (variables) to the problem
    Lp::Col x1 = lp.addCol();
    Lp::Col x2 = lp.addCol();
    // Add rows (constraints) to the problem
    lp.addRow(x1 - 5 <= x2);
    lp.addRow(0 <= 2 * x1 + x2 <= 25);
    // Set lower and upper bounds for the columns (variables)
    lp.colLowerBound(x1, 0);
    lp.colUpperBound(x2, 10);
    // Specify the objective function
    lp.max();
    lp.obj(5 * x1 + 3 * x2);
    // Solve the problem using the underlying LP solver
    lp.solve();
    // Print the results
    if (lp.primalType() == Lp::OPTIMAL) {
    std::cout << "Objective function value: " << lp.primal() << std::endl;
    std::cout << "x1 = " << lp.primal(x1) << std::endl;
    std::cout << "x2 = " << lp.primal(x2) << std::endl;
    } else {
    std::cout << "Optimal solution not found." << std::endl;
    }
}

void testGraph()
{
  ListDigraph g;
  ListDigraph::Node u = g.addNode();
  ListDigraph::Node v = g.addNode();
  ListDigraph::Arc  a = g.addArc(u, v);
  std::cout << "Hello World! This is LEMON library here." << std::endl;
  std::cout << "We have a directed graph with " << countNodes(g) << " nodes "
       << "and " << countArcs(g) << " arc." << std::endl;
}

int main()
{
    LOG_TIME("lemon");
    testGraph();
    return 0;
}

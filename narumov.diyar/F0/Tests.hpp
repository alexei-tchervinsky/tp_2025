#ifndef TESTS_HPP
#define TESTS_HPP

#include <cstddef>
#include <string>

namespace narumov {
    void testDefaultConstructor();
    void testAddRemoveVertex();
    void testAddRemoveEdge();
    void testExceptions();
    void testCopyMoveAssign();
    void testGetEdgesAndWeight();
    void testKruskalMST();
    void testPrintGraph();
    void testCompleteGraph(std::size_t, std::size_t);
    void testDisconnectedGraph(std::size_t);
    void testLargeRandomGraph(std::size_t, std::size_t);
    void testStressRandomOperations(std::size_t);
    void testStressKruskal(std::size_t, std::size_t);
    void testCustom(const std::string &);
    void testFull();
}

#endif

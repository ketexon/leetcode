# https://leetcode.com/problems/clone-graph/
class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

from typing import Optional
class Solution:
    def cloneGraph(self, root: Optional['Node']) -> Optional['Node']:
        if root is None: return None
        node_map = {
            root: Node(),
        }
        to_search = [root]
        while len(to_search) > 0:
            node = to_search.pop()
            cloned = node_map[node]
            cloned.val = node.val
            for neighbor in node.neighbors:
                if neighbor in node_map:
                    neighbor_cloned = node_map[neighbor]
                else:
                    neighbor_cloned = Node()
                    node_map[neighbor] = neighbor_cloned
                    to_search.append(neighbor)
                cloned.neighbors.append(neighbor_cloned)
        return node_map[root]

import unittest
class Test133(unittest.TestCase):
    cases = [
        [[2,4],[1,3],[2,4],[1,3]],
        [[]],
        [],
    ]

    def build_graph(self, case) -> Optional['Node']:
        if len(case) == 0: return None
        nodes = [Node(i + 1) for i in range(len(case))]
        for i, neighbors in enumerate(case):
            nodes[i].neighbors = [nodes[j - 1] for j in neighbors]
        return nodes[0]

    def compare_graphs(
        self,
        node1: Optional['Node'],
        node2: Optional['Node'],
        visited1: set = set(),
        visited2: set = set(),
    ) -> bool:
        if node1 is None and node2 is None: return True
        if node1 is None or node2 is None: return False
        if node1 is node2: return False

        if node1 in visited1 and node2 in visited2: return True
        if node1 in visited1 or node2 in visited2: return False

        if node1.val != node2.val: return False

        visited1.add(node1)
        visited2.add(node2)

        for n1, n2 in zip(node1.neighbors, node2.neighbors):
            if not self.compare_graphs(n1, n2, visited1, visited2):
                return False

        return True

    def test_cases(self):
        for case in self.cases:
            with self.subTest(case=case):
                root = self.build_graph(case)
                cloned = Solution().cloneGraph(root)
                self.assertTrue(self.compare_graphs(root, cloned))

if __name__ == '__main__':
    unittest.main()

// https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/description/

#include <vector>
#include <algorithm>
#include <optional>
#include <tuple>
#include <iostream>

static_assert(__cplusplus >= 202300L, "C++23 or higher is required");

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // col, depth, value
        // if we sort ascending,
        // this is the right order for the nodes
        vector<tuple<int, int, int>> nodes;
        auto impl = [&nodes](this const auto &self, TreeNode* node, int col, int depth) {
            if(!node) return;
            nodes.emplace_back(col, depth, node->val);
            self(node->left, col - 1, depth + 1);
            self(node->right, col + 1, depth + 1);
        };
        impl(root, 0, 0);

        sort(nodes.begin(), nodes.end());

        vector<vector<int>> out;
        int last_col = -1001;
        for(auto [col, _, value] : nodes) {
            if (col != last_col) {
                out.emplace_back();
            }
            last_col = col;
            out.back().push_back(value);
        }

        return out;
    }
};

vector<tuple<
	vector<optional<int>>,
	vector<vector<int>>
>> test_cases {
	{
		{3,9,20,nullopt,nullopt,15,7},
		{{9},{3,15},{20},{7}},
	},
	{
		{1,2,3,4,5,6,7},
		{{4},{2},{1,5,6},{3},{7}},
	},
	{
		{1,2,3,4,6,5,7},
		{{4},{2},{1,5,6},{3},{7}},
	},
};

TreeNode* tree_from_vector(const vector<optional<int>>& vec) {
	if (vec.empty() || !vec[0].has_value()) {
		return nullptr;
	}
	vector<TreeNode*> nodes;
	nodes.reserve(vec.size());
	for (auto v : vec) {
		if (v.has_value()) {
			nodes.push_back(new TreeNode(v.value()));
		} else {
			nodes.push_back(nullptr);
		}
	}
	for (int i = 0; i < vec.size(); ++i) {
		if (!nodes[i]) continue;
		int left_index = 2 * i + 1;
		int right_index = 2 * i + 2;
		if (left_index < vec.size()) {
			nodes[i]->left = nodes[left_index];
		}
		if (right_index < vec.size()) {
			nodes[i]->right = nodes[right_index];
		}
	}
	return nodes[0];
}

void free_tree(TreeNode* root) {
	if (!root) return;
	free_tree(root->left);
	free_tree(root->right);
	delete root;
}

int main() {
	Solution solution;
	int test_num = 1;
	for (auto [tree_vec, expected] : test_cases) {
		TreeNode* tree = tree_from_vector(tree_vec);
		auto result = solution.verticalTraversal(tree);
		cout << "Test Case " << test_num++ << ": ";
		if (result == expected) {
			cout << "Passed";
		} else {
			cout << "Failed";
		}
		cout << endl;
		free_tree(tree);
	}
	return 0;
}
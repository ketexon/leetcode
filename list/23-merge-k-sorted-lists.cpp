// https://leetcode.com/problems/merge-k-sorted-lists/description/

#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<tuple<int, ListNode*>> heap;
        auto cmp = std::greater<decltype(heap[0])>{};

        ListNode dummy { 0, nullptr };
        ListNode* cur = &dummy;
        for (auto node : lists) {
            if (!node) continue;
            heap.push_back(make_tuple(node->val, node));
            push_heap(heap.begin(), heap.end(), cmp);
        }

        while(!heap.empty()) {
            pop_heap(heap.begin(), heap.end(), cmp);
            auto [_, node] = heap.back();
            cur->next = node;
            cur = cur->next;
            if (cur->next) {
                heap.back() = { cur->next->val, cur->next };
                push_heap(heap.begin(), heap.end(), cmp);
                cur->next = nullptr;
            } else {
                heap.pop_back();
            }
        }
        return dummy.next;
    }
};

#include <iostream>

ListNode* make_list(const vector<int>& vals) {
	ListNode dummy { 0, nullptr };
	ListNode* cur = &dummy;
	for (auto v : vals) {
		cur->next = new ListNode(v);
		cur = cur->next;
	}
	return dummy.next;
}

vector<tuple<vector<vector<int>>, vector<int>>> test_cases {
	{
		{
			{1,4,5},
			{1,3,4},
			{2,6}
		},
		{1,1,2,3,4,4,5,6},
	},

	{
		{},
		{},
	},
	{
		{{}},
		{},
	},
};

int main() {
	Solution s;
	int test_case_number = 1;
	for (auto [lists, expected] : test_cases) {
		vector<ListNode*> llists;
		for (auto l : lists) {
			llists.push_back(make_list(l));
		}
		auto result = s.mergeKLists(llists);

		cout << "Test case " << test_case_number++ << ": ";
		bool ok = true;
		for (auto v : expected) {
			if (!result || result->val != v) {
				ok = false;
				break;
			}
			result = result->next;
		}
		if (result) ok = false;

		if (ok) {
			cout << "PASS";
		} else {
			cout << "FAIL";
		}
		cout << endl;
	}
	return 0;
}

#include<iostream>
#include<algorithm>
#include<random>
using namespace std;


class Treap {
	static minstd_rand generator;
	struct Node {
		int key, priority;//В кожному узлі є не тільки ключ а й пріорітет
		Node* l = nullptr, * r = nullptr;
		Node(int key) : key(key), priority(generator()) {}
	} *root = nullptr;

	static Node *merge(Node* a, Node* b) {
		if (!a || !b)
			return a ? a : b;
		if (a->priority > b->priority) {
			a->r = merge(a->r, b);
			return a;

		}else{
			b->l = merge(a, b->l);
			return b;
		}
	}

	static void split(Node* n, int key, Node*& a, Node*& b) {
		if (!n) {
			a = b = nullptr;
			return;
		}
		if (n->key, key) {
			split(n->r, key, n->r, b);
			a = n;
		}
		else {
			split(n->l, key, a, n->l);
				b = n;
		}
	}

	int min(Node* n) const {
		if (!n)
			return -1;
		while (n->l)
			n = n->l;
		return n->key;
	}
public:
	bool contains(int key) {
		Node* less, * equal , * greater;
		split(root, key, less, greater);
		split(greater, key + 1, equal, greater);
		bool result = equal;
		root = merge(merge(less, equal), greater);
		return result;
	}


	void insert(int key) {
		Node* less, * greater;
		split(root, key, less, greater);
		less = merge(less, new Node(key));
		root = merge(less, greater);
	}

	void erase(int key) {
		Node* less, * equal, * greater;
		split(root, key, less, greater);
		split(greater, key + 1, equal, greater);
		root = merge(less, greater);
	}

	int next(int key) {
		Node* less, * greater;
		split(root, key , less, greater);
		int result = min(greater);
		root = merge(less, greater);
		return result;
	}
};

minstd_rand Treap::generator;

int main() {

	Treap t;

	int n;
	cin >> n;

	int prevRes = 0;
	for (int i = 0; i < n; i++) {
		string command;
		int x;
		cin >> command >> x;

		if (command == "+") {
			x = (x + prevRes) % (int)1e9;
			if (!t.contains(x)) {
				t.insert(x);
			}
			prevRes = 0;

		}
		else {
			prevRes = t.next(x);
			cout << prevRes << endl;
		}
	}
}
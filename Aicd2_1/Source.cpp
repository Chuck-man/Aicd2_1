#include <iostream>
#include <vector>
#include <time.h>

#pragma once

using namespace std;

class Tree {
	struct TreeNode {
		int  data;
		TreeNode* left;
		TreeNode* right;

		TreeNode(int data, TreeNode* left, TreeNode* right) : data(data), left(left), right(right) {}
	};

	TreeNode* _root;

	void _delete_tree(TreeNode* root) {
		if (root) {
			_delete_tree(root->left);
			_delete_tree(root->right);
			delete root;
		}
		root = nullptr;
	}

	void _print(const TreeNode* root) {
		if (!root) return;
		_print(root->left);
		cout << root->data << "  ";
		_print(root->right);
	}

	bool _contains(const TreeNode* root, const int key) {
		if (!root) return false;
		if (key == root->data) return true;
		if (key > root->data) return _contains(root->right, key);
		return _contains(root->left, key);
	}

	TreeNode* _copy(const TreeNode* temp) {
		if (!temp) return nullptr;
		TreeNode* root_copy = new TreeNode(temp->data, nullptr, nullptr);
		root_copy->left = _copy(temp->left);
		root_copy->right = _copy(temp->right);
		return root_copy;
	}

	TreeNode* _insert(const int key, TreeNode* temp) {
		if (!temp) return new TreeNode(key, nullptr, nullptr);
		if (key < temp->data) temp->left = _insert(key, temp->left);
		else  temp->right = _insert(key, temp->right);
		return temp;
	}

	TreeNode* _min(TreeNode* temp) {
		if (!temp->left) return temp;
		return _min(temp->left);
	}
	TreeNode* _erase(TreeNode* temp, const int key) {
		//if (!temp) return temp;
		if (key < temp->data)  temp->left = _erase(temp->left, key);
		else if ((key > temp->data)) temp->right = _erase(temp->right, key);
		else {
			if (!temp->left) return temp->right;
			if (!temp->right) return temp->left;
			temp->data = _min(temp->right)->data;
			temp->right = _erase(temp->right, temp->data);
		}
		return temp;
	}

public:
	TreeNode* get_root() {
		return _root;
	}

	Tree() {
		_root = nullptr;
	}

	~Tree() {
		_delete_tree(_root);
	}

	Tree(const Tree& obj) {
		if (!obj._root) {
			_delete_tree(_root);
		}
		else {
			if (!_root) {
				_root = _copy(obj._root);
			}
			else {
				_delete_tree(_root);
				_root = _copy(obj._root);
			}
		}
	}

	Tree& operator=(const Tree& obj) {
		if (!obj._root) {
			_delete_tree(_root);
			return *this;
		}
		else {
			if (!_root) {
				_root = _copy(obj._root);
			}
			else {
				_delete_tree(_root);
				_root = _copy(obj._root);
				return *this;
			}
		}
	}

	bool contains(const int key) { return _contains(_root, key); }

	void print() { _print(_root); }

	bool insert(const int key) {
		if (!contains(key)) {
			_root = _insert(key, _root);
			return true;
		}
		return false;
	}

	bool erase(const int key) {
		if (contains(key)) {
			_root = _erase(_root, key);
			return true;
		}
		return false;
	}

	void creating_container(const TreeNode* temp, vector<int>& values) {
		if (!temp) return;
		creating_container(temp->left, values);
		creating_container(temp->right, values);
		values.push_back(temp->data);
	}

};

Tree intersection(Tree& a, Tree& b) {
	Tree temp;
	vector<int> v1, v2;
	a.creating_container(a.get_root(), v1);
	b.creating_container(b.get_root(), v2);
	for (auto i : v1) {
		for (auto j : v2) {
			if (i == j) {
				temp.insert(i);
			}
		}
	}
	return temp;
}

Tree difference(Tree& a, Tree& b) {
	Tree temp = a;
	vector<int> v;
	b.creating_container(b.get_root(), v);
	for (auto i : v) {
		if (temp.contains(i)) {
			temp.erase(i);
		}
	}
	return temp;
}
size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}
double avg100(const double* arr) {
	double sum = 0;
	for (size_t i = 0; i < 100; ++i) {
		sum += arr[i];
	}
	return sum / 100;
}

double avg1000(const double* arr) {
	double sum = 0;
	for (size_t i = 0; i < 1000; ++i) {
		sum += arr[i];
	}
	return sum / 1000;
}
void insert_tree(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		Tree tree;
		clock_t begin = clock();
		for (size_t j = 0; j < count; ++j) {
			tree.insert(static_cast<int>(lcg()));
		}
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << count << avg100(time) << endl;
}

void insert_vector(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		vector<size_t> vector;
		clock_t begin = clock();
		for (size_t j = 0; j < count; ++j) {
			vector.push_back(lcg());
		}
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << count << avg100(time) << endl;
}

void search_tree(size_t count) {
	double time[1000]{};
	Tree tree;
	for (size_t j = 0; j < count; ++j) {
		tree.insert(static_cast<int>(lcg()));
	}
	for (size_t i = 0; i < 1000; ++i) {
		clock_t begin = clock();
		tree.contains(static_cast<int>(lcg()));
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << count << avg1000(time) << endl;
}
void add_tree(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		Tree tree;
		for (size_t j = 0; j < count; ++j) {
			tree.insert(static_cast<int>(lcg()));
		}
		clock_t begin = clock();
		tree.insert(static_cast<int>(lcg()));
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << count << avg1000(time) << endl;
}
void erase_tree(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		Tree tree;
		for (size_t j = 0; j < count; ++j) {
			tree.insert(static_cast<int>(lcg()));
		}
		clock_t begin = clock();
		tree.erase(static_cast<int>(lcg()));
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << count << avg1000(time) << endl;
}

void search_vector(size_t count) {
	double time[1000]{};
	vector<size_t> vector;
	for (size_t j = 0; j < count; ++j) {
		vector.push_back(static_cast<int>(lcg()));
	}
	for (size_t i = 0; i < 1000; ++i) {
		size_t elem = lcg();
		clock_t begin = clock();
		for (auto i = vector.begin(); i != vector.end(); ++i) {
			if (*i == elem) {
				break;
			}
		}
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << count << avg1000(time) << endl;
}
void add_vector(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		vector<size_t> vector;
		for (size_t j = 0; j < count; ++j) {
			vector.push_back(static_cast<int>(lcg()));
		}
		clock_t begin = clock();
		vector.push_back(lcg());
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << count << avg1000(time) << endl;
}
void erase_vector(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		vector<size_t> vector;
		for (size_t j = 0; j < count; ++j) {
			vector.push_back(static_cast<int>(lcg()));
		}
		size_t elem = lcg();
		clock_t begin = clock();
		for (auto i = vector.begin(); i != vector.end(); ++i) {
			if (*i == elem) {
				vector.emplace(i);
				break;
			}

		}
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << count << avg1000(time) << endl;
}

void menu() {
	cout << "1. Inserting a number" << endl;
	cout << "2. Deleting a number" << endl;
	cout << "3. Checking for the presence of a number" << endl;
	cout << "4. Output" << endl;
	cout << "5. Equating trees" << endl;
	cout << "6. Crossing containers" << endl;
	cout << "7. Checking for time" << endl;
	cout << "8. Difference of containers" << endl;
	cout << "0. Exit" << endl;
}

int main() {
	Tree wood;
	while (true) {
		system("cls");
		menu();
		int sw;
		cin >> sw;
		switch (sw)
		{
		case 1:
		{
			system("cls");
			int number;
			cout << "Enter a number: ";
			cin >> number;
			if (wood.insert(number)) cout << "Number inserted" << endl;
			else cout << "The number is not inserted" << endl;
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			int number;
			cout << "";
			cin >> number;
			if (wood.erase(number))cout << "Number deleted" << endl;
			else cout << "The number has not been deleted" << endl;
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			int number;
			cout << "";
			cin >> number;
			if (wood.contains(number))cout << "The number is contained in the tree" << endl;
			else cout << "The number is not contained in the tree" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			wood.print();
			cout << endl;
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			Tree temp;
			wood.print();
			cout << endl;
			temp = wood;
			temp.print();
			cout << endl;
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			Tree a, b, result;
			size_t count;
			cout << "Enter the quantity: ";
			cin >> count;
			for (size_t i = 0; i < count; i++) {
				int number;
				cout << "Enter a number: ";
				cin >> number;
				if (a.insert(number))cout << "" << endl;
				else cout << "" << endl;
			}
			system("cls");
			cout << "Enter the quantity: ";
			cin >> count;
			for (size_t i = 0; i < count; i++) {
				int number;
				cout << "Enter a number: ";
				cin >> number;
				if (b.insert(number)) cout << "" << endl;
				else cout << "" << endl;
			}
			system("cls");
			cout << "Container A: ";
			a.print();
			cout << endl;
			cout << "Container B: ";
			b.print();
			cout << endl;
			result = intersection(a, b);
			cout << "Intersection of containers: ";
			result.print();
			cout << endl;
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			insert_tree(1000);
			insert_tree(10000);
			insert_tree(100000);
			cout << "-------------------------------------------------------------------" << endl;
			insert_vector(1000);
			insert_vector(10000);
			insert_vector(100000);
			cout << "-------------------------------------------------------------------" << endl;
			search_tree(1000);
			search_tree(10000);
			search_tree(100000);
			cout << "-------------------------------------------------------------------" << endl;
			search_vector(1000);
			search_vector(10000);
			search_vector(100000);
			cout << "-------------------------------------------------------------------" << endl;
			add_tree(1000);
			add_tree(10000);
			add_tree(100000);
			cout << "-------------------------------------------------------------------" << endl;
			add_vector(1000);
			add_vector(10000);
			add_vector(100000);
			cout << "-------------------------------------------------------------------" << endl;
			erase_tree(1000);
			erase_tree(10000);
			erase_tree(100000);
			cout << "-------------------------------------------------------------------" << endl;
			erase_vector(1000);
			erase_vector(10000);
			erase_vector(100000);
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			Tree a, b, result;
			size_t count;
			cout << "Enter the quantity: ";
			cin >> count;
			for (size_t i = 0; i < count; i++) {
				int number;
				cout << "Enter a number: ";
				cin >> number;
				if (a.insert(number))cout << "" << endl;
				else cout << "" << endl;
			}
			system("cls");
			cout << "Enter the quantity: ";
			cin >> count;
			for (size_t i = 0; i < count; i++) {
				int number;
				cout << "Enter a number: ";
				cin >> number;
				if (b.insert(number)) cout << "" << endl;
				else cout << "" << endl;
			}
			system("cls");
			cout << "Container A: ";
			a.print();
			cout << endl;
			cout << "Container B: ";
			b.print();
			cout << endl;
			result = difference(a, b);
			cout << " a/b: ";
			result.print();
			cout << endl;
			result = difference(b, a);
			cout << " b/a: ";
			result.print();
			cout << endl;

			cout << endl;
			system("pause");
			break;
		}
		case 0:
		{
			return 0;
		}
		}
	}
}

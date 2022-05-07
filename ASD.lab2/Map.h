#pragma once

#include <iostream>
#include <stdexcept>
using namespace std;

template<typename TKey, typename TValue>

class Map {
public:
	class Node {
	public:
		Node* parent;
		Node* left;
		Node* right;
		TKey key;
		TValue value;
		bool color;

		Node(Node* parent, Node* left, bool color, Node* right, TKey key, TValue value) : parent(parent), color(color), key(key), value(value) {}
	};
	Node* root;
	Node* NIL;
	void leftRotate(Node* current) {
		Node* noduleRight = current->right;
		current->right = noduleRight->left;
		if (noduleRight->left != NIL) {
			noduleRight->left->parent = current;
		}
		noduleRight->parent = current->parent;
		if (current->parent == nullptr) {
			this->root = noduleRight;
		}
		else
			if (current != current->parent->left) {
				current->parent->right = noduleRight;
			}
			else {
				current->parent->left = noduleRight;
			}
		noduleRight->left = current;
		current->parent = noduleRight;
	}

	void rightRotate(Node* current) {
		Node* noduleLeft = current->left;
		current->left = noduleLeft->right;
		if (noduleLeft->right != NIL) {
			noduleLeft->right->parent = current;
		}
		noduleLeft->parent = current->parent;
		if (current->parent == nullptr) {
			this->root = noduleLeft;
		}
		else
			if (current == current->parent->right) {
				current->parent->right = noduleLeft;
			}
			else {
				current->parent->left = noduleLeft;
			}
		noduleLeft->right = current;
		current->parent = noduleLeft;
	}

	void subClear(Node* node) {
		if (node != NIL) {
			if (node->right != nullptr && node->right != NIL)
				subClear(node->right);
			if (node->left != nullptr && node->left != NIL)
				subClear(node->left);
			delete node;
		}
	}

	void rbChanger(Node* ourNode, Node* newNode) {
		if (ourNode->parent == nullptr) {
			root = newNode;
		}
		else if (ourNode == ourNode->parent->left) {
			ourNode->parent->left = newNode;
		}
		else {
			ourNode->parent->right = newNode;
		}
		newNode->parent = ourNode->parent;
	}

	List<TKey> subKeyFinder(Node* node, List<TKey>& list) {
		if (node != NIL) {
			if (node->right != nullptr && node->right != NIL)
				list = subKeyFinder(node->right, list);
			if (node->left != nullptr && node->left != NIL)
				list = subKeyFinder(node->left, list);
			list.pushBack(node->key);
			return list;
		}
	}
	List<TValue> subValueFinder(Node* node, List<TValue>& list) {
		if (node != NIL) {
			if (node->right != nullptr && node->right != NIL)
				list = subValueFinder(node->right, list);
			if (node->left != nullptr && node->left != NIL)
				list = subValueFinder(node->left, list);
			list.pushBack(node->value);
			return list;
		}
	}

	void subPrinter(Node* node) {
		if (node != NIL) {
			if (node->right != nullptr && node->right != NIL)
				subPrinter(node->right);
			if (node->left != nullptr && node->left != NIL)
				subPrinter(node->left);
			cout << "[key " << node->key << " : " << node->value << " value]" << " ";
		}
	}
	Map() {
		NIL = new Node(NULL, NULL, 0, NULL, NULL, NULL);
		NIL->color = 0;
		NIL->left = nullptr;
		NIL->right = nullptr;
		root = NIL;
	}
	~Map() {
		clear();
	}
	void clear() {
		subClear(this->root);
		this->root = NIL;
	}
	List <TKey> getKeys() {
		List<TKey> list;
		return subKeyFinder(this->root, list);
	}
	List <TValue> getValues() {
		List <TValue> list;
		return subValueFinder(this->root, list);
	}
	void print() {
		if (this->root == NIL) {
			cout << "[Empty map]" << endl;
		}
		else {
			subPrinter(this->root);
		}
	}
	Node* find(TKey key) {
		Node* find = nullptr;
		Node* current = this->root;

		while (current != NIL) {
			if (current->key == key) {
				find = current;
				break;
			}
			if (current->key <= key)
				current = current->right;
			else
				current = current->left;
		}
		return find;
	}

	// Fix the RBTree
	void fixInsert(Node* current) {
		Node* uncle;
		while (current->parent->color == 1) {
			if (current->parent == current->parent->parent->right) {
				uncle = current->parent->parent->left;
				if (uncle->color == 1) {
					uncle->color = 0;
					current->parent->color = 0;
					current->parent->parent->color = 1;
					current = current->parent->parent;
				}
				else {
					if (current == current->parent->left) {
						current = current->parent;
						rightRotate(current);
					}
					current->parent->color = 0; // Parent becomes black
					current->parent->parent->color = 1;
					leftRotate(current->parent->parent);
				}
			}
			else {
				uncle = current->parent->parent->right;

				if (uncle->color == 1) {
					uncle->color = 0;
					current->parent->color = 0;
					current->parent->parent->color = 1;
					current = current->parent->parent;
				}
				else {
					if (current == current->parent->right) {
						current = current->parent;
						leftRotate(current);
					}

					current->parent->color = 0;
					current->parent->parent->color = 1;
					rightRotate(current->parent->parent);
				}
			}
			if (current == root) {
				break;
			}
		}
		root->color = 0; // Root must be black
	}

	void nodeRearrange(Node* ourNode, Node* newNode) {
		if (ourNode->parent == nullptr) {
			root = newNode;
		}
		else if (ourNode == ourNode->parent->left) {
			ourNode->parent->left = newNode;
		}
		else {
			ourNode->parent->right = newNode;
		}
		newNode->parent = ourNode->parent;
	}

	void insert(TKey key, TValue value) {

		Node* newNode = new Node(NULL, NULL, 0, NULL, NULL, NULL);
		newNode->parent = nullptr;
		newNode->key = key;
		newNode->value = value;
		newNode->left = NIL;
		newNode->right = NIL;
		newNode->color = 1; // New node must be red

		Node* y = nullptr;
		Node* x = root;

		while (x != NIL) {
			y = x;
			if (newNode->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		newNode->parent = y;
		if (y == nullptr) {
			root = newNode;
		}
		else if (newNode->key < y->key) {
			y->left = newNode;
		}
		else {
			y->right = newNode;
		}

		if (newNode->parent == nullptr) {
			newNode->color = 0;
			return;
		}

		if (newNode->parent->parent == nullptr) {
			return;
		}

		fixInsert(newNode); //Fix the Map after insert
	}

	void remove(TKey key) {
		Node* nodeToBeDeleted = NIL;
		Node* x;
		Node* y;

		// Finding the node for key
		nodeToBeDeleted = find(key);

		y = nodeToBeDeleted;
		int OriginalColorOfY = y->color;
		if (nodeToBeDeleted->left == NIL) {
			x = nodeToBeDeleted->right;
			nodeRearrange(nodeToBeDeleted, nodeToBeDeleted->right);
		}
		else if (nodeToBeDeleted->right == NIL) {
			x = nodeToBeDeleted->left;
			nodeRearrange(nodeToBeDeleted, nodeToBeDeleted->left);
		}
		else {
			y = nodeToBeDeleted->right;
			while (y->left != NIL) {
				y = y->left;
			}
			OriginalColorOfY = y->color;
			x = y->right;
			if (y->parent == nodeToBeDeleted) {
				x->parent = y;
			}
			else {
				nodeRearrange(y, y->right);
				y->right = nodeToBeDeleted->right;
				y->right->parent = y;
			}

			nodeRearrange(nodeToBeDeleted, y);
			y->left = nodeToBeDeleted->left;
			y->left->parent = y;
			y->color = nodeToBeDeleted->color;
		}
		delete nodeToBeDeleted;


		if (OriginalColorOfY == 0) { //Fix after remove
			Node* brother;
			while (x != root && x->color == 0) {
				if (x == x->parent->left) {
					brother = x->parent->right;
					if (brother->color == 1) {
						brother->color = 0;
						x->parent->color = 1;
						leftRotate(x->parent);
						brother = x->parent->right;
					}

					if (brother->left->color == 0 && brother->right->color == 0) {
						brother->color = 1;
						x = x->parent;
					}
					else {
						if (brother->right->color == 0) {
							brother->left->color = 0;
							brother->color = 1;
							rightRotate(brother);
							brother = x->parent->right;
						}

						brother->color = x->parent->color;
						x->parent->color = 0;
						brother->right->color = 0;
						leftRotate(x->parent);
						x = root;
					}
				}
				else {
					brother = x->parent->left;
					if (brother->color == 1) {
						brother->color = 0;
						x->parent->color = 1;
						rightRotate(x->parent);
						brother = x->parent->left;
					}

					if (brother->right->color == 0 && brother->left->color == 0) {
						brother->color = 1;
						x = x->parent;
					}
					else {
						if (brother->left->color == 0) {
							brother->right->color = 0;
							brother->color = 1;
							leftRotate(brother);
							brother = x->parent->left;
						}
						brother->color = x->parent->color;
						x->parent->color = 0;
						brother->left->color = 0;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
			x->color = 0;
		}
	}
	bool containsAlgorithm(Node* current, TKey key) { 
		if (key == current->key) {
			return true;
		}

		if (current == NIL) {
			return false;
		}

		if (key < current->key) {
			return containsAlgorithm(current->left, key);
		}
		return containsAlgorithm(current->right, key);
	}

	bool contains(TKey key) {
		return containsAlgorithm(root, key);
	}
};
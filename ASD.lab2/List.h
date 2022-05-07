#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>

class List {
private:
	class Elem { //Element of list
	public:
		T data;
		Elem* prev;		//Previous
		Elem* next; // Next
		Elem(T data, Elem* prev = nullptr, Elem* next = nullptr) {
			this->data = data;
			this->prev = prev;
			this->next = next;
		};
	};
	Elem* head; //Pointer to the beginning of the list
	Elem* tail; //Pointer to the end of the list
	size_t size;

	Elem* getElem(size_t index) {
		if (index < getSize() && index >= 0) {
			Elem* elem = head;
			elem = head;
			for (int i = 0; i < (int)index; i++) {
				elem = elem->next;
			}
			return elem;
			elem = 0;
		}
	}
public:
	List() : head(nullptr), tail(nullptr) {}

	List(const size_t size, T* arr) : head(nullptr), tail(nullptr)
	{
		for (size_t i = 0; i < size; i++) this->PushBack(arr[i]);
	}

	~List() {		//Eraser
		clear();
	}
	void clear() {
		head = tail = nullptr;
		size = 0;
	}
	// Add item to the front
	void pushFront(T data) {
		Elem* elem = new Elem(data);
		if (isEmpty()) {
			head = tail = elem;
		}
		else {
			tail = elem;
			head = tail;
		}
		size++;

	}
	// Add item to the end
	void pushBack(T data) {
		Elem* elem = new Elem(data);
		if (head == nullptr) {
			head = tail = elem;
		}
		else {
			tail->next = elem;
			tail = tail->next;
		}
		size++;
	}
	// Delete front element
	void popFront() {
		if (head == nullptr) throw logic_error("List is empty");
		if (head->next == nullptr)
		{
			delete head;
			head = tail = nullptr;
			size--;
		}
		else
		{
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
			size--;
		}
	}
	// Delete last element
	void popBack() {
		if (tail == nullptr) throw logic_error("List is empty");
		if (tail->prev == nullptr)
		{
			delete tail;
			head = tail = nullptr;
			size--;
		}
		else
		{
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
			size--;
		}
	}
	//Inserting an item by index
	void insert(T data, size_t index) {
		if (index > getSize() && index < 0) throw invalid_argument("Index out of range");
		if (index < getSize() && index >= 0) {
			if (index == 0) pushFront(data);
			else if (index == getSize()) pushBack(data);
			else {
				Elem* next_elem = getElem(index);
				Elem* elem = new Elem(next_elem->data, next_elem, next_elem->next);
				next_elem->data = data;
				next_elem->next = elem;
				if (tail == next_elem) tail = elem;
				size++;
			}
		}
	}
	//Point an index and print it
	int indexPointer(size_t index) {
		if (index < getSize() && index >= 0) {
			return getElem(index)->data;
		}
		else throw invalid_argument("Index is out of range");
	}
	//Deleting an element by it index
	void remove(size_t index) {
		if (index < getSize() && index >= 0) {
			Elem* elem = getElem(index);
			if (getSize() == 1) {
				delete elem;
				head = tail = nullptr;
			}
			else {
				if (index == getSize() - 1) {
					elem->prev->next = nullptr;
					tail = getElem(index);
				}
				else if (index == 0) {
					elem->next->prev = nullptr;
					head = elem;
				}
				else {

					elem->next->prev = elem->prev;
					elem->prev->next = elem->next;
				}
				delete elem;
			}
			size--;
		}
		else throw invalid_argument("Index is out of range");
	}

	size_t getSize()
	{
		int size = 0;
		Elem* elem = head;
		while (elem != nullptr)
		{
			size++;
			elem = elem->next;
		}
		return size;
	}
	//Replacing an element by index
	void indexReplacer(size_t index, T data) {
		if (index < getSize() && index >= 0) {
			getElem(index)->data = data;
		}
		else throw invalid_argument("Index is out of range");
	}

	bool isEmpty() {
		return getSize() == false;
	}

	T getHead() {
		if (size != 0)
			return head->data;
	}

	void setNext() {
		if (head != NULL)
			head = head->next;
		else
			throw out_of_range("There is not next element");
	}
	friend ostream& operator<< (ostream& out, const List& list);
};

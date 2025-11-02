#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		Node* current = head;
		while (current) {
			cout << current->data << endl;
			current = current->next;
		}
	}

	void printReverse() const {
		Node* current = tail;
		while (current) {
			cout << current->data << endl;
			current = current->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}

	Node* getHead() {
		return head;
	}

	const Node* getHead() const {
		return head;
	}

	Node* getTail() {
		return tail;
	}

	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node* newHead = new Node;
		newHead->data = data;
		newHead->prev = nullptr;
		newHead->next = head;
		head->prev = newHead;
		head = newHead;
		count++;
	}

	void addTail(const T& data) {
		Node* newTail = new Node;
		newTail->data = data;
		newTail->prev = tail;
		newTail->next = nullptr;
		tail->next = newTail;
		tail = newTail;
		count++;
	}

	// Removal
	bool removeHead() {
		Node* temp = head->next;
		delete head;
		head = temp;
		count--;
	}

	bool removeTail() {
		Node* temp = tail->prev;
		delete tail;
		tail = temp;
		count--;
	}

	void Clear() {
		Node* current = head;
		while (current) {
			delete current;
			current = current->next;
		}
		count = 0;
		head = nullptr;
		tail = nullptr;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if(this == &rhs) return *this;
		
		Clear();

		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;

	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if(this == &rhs) return *this;

		Clear();

		Node* current = rhs.head;

		if (current) {
			Node* startingNode = new Node;

			startingNode->data = list.head;
			startingNode->next = nullptr;
			startingNode->prev = nullptr;
			current = current->next;

			head = startingNode;
			tail = startingNode;
		}

		while (current) {
			Node* newNode = new Node;
			newNode->data = current->data;
			newNode->prev = tail;
			newNode->next = nullptr;
			tail = newNode;
			current = current->next;
		}

		count = rhs.count;

		return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}

	LinkedList(const LinkedList<T>& list) : count(list.count) {
		Node* current = list.head;

		if (current) {
			Node* startingNode = new Node;

			startingNode->data = list.head;
			startingNode->next = nullptr;
			startingNode->prev = nullptr;
			current = current->next;

			head = startingNode;
			tail = startingNode;
		}

		while (current) {
			Node* newNode = new Node;
			newNode->data = current->data;
			newNode->prev = tail;
			newNode->next = nullptr;
			tail = newNode;
			current = current->next;
		}
	}

	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}

	~LinkedList() {
		Clear()
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};
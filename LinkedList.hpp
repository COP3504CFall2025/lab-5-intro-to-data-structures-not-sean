#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		Node<T>* current = head;
		while (current) {
			cout << current->data << endl;
			current = current->next;
		}
	}

	void printReverse() const {
		Node<T>* current = tail;
		while (current) {
			cout << current->data << endl;
			current = current->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}

	Node<T>* getHead() {
		return head;
	}

	const Node<T>* getHead() const {
		return head;
	}

	Node<T>* getTail() {
		return tail;
	}

	const Node<T>* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node<T>* newHead = new Node{data, nullptr, head};
		//newHead->data = data;
		//newHead->prev = nullptr;
		//newHead->next = head;
		head->prev = newHead;
		head = newHead;
		count++;
	}

	void addTail(const T& data) {
		Node<T>* newTail = new Node{data, tail, nullptr};
		//newTail->data = data;
		//newTail->prev = tail;
		//newTail->next = nullptr;
		tail->next = newTail;
		tail = newTail;
		count++;
	}

	// Removal
	bool removeHead() {
		if (count == 0) return false;

		Node<T>* temp = head->next;
		delete head;
		head = temp;
		count--;

		return true;
	}

	bool removeTail() {
		if (count == 0) return false;

		Node<T>* temp = tail->prev;
		delete tail;
		tail = temp;
		count--;

		return true;
	}

	void clear() {
		Node<T>* current = head;

		while (current) {
			temp = current->next;
			delete current;
			current = temp;
		}

		count = 0;
		head = nullptr;
		tail = nullptr;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if(this == &rhs) return *this;
		
		clear();

		head = other.head; // TODO: May need to use getHead()
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;
	}
	
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if(this == &rhs) return *this;

		clear();

		Node<T>* current = rhs.head;

		if (current) {
			Node<T>* startingNode = new Node{rhs.head->data, nullptr, nullptr};
			
			head = startingNode;
			tail = startingNode;

			current = current->next;
		}

		while (current) {
			Node<T>* newNode = new Node{current->data, tail, nullptr};
			tail = newNode;
			current = current->next;
		}

		count = rhs.count;

		return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}

	LinkedList(const LinkedList<T>& list) : count(list.count) {
		Node<T>* current = list.head;

		if (current) {
			Node<T>* startingNode = new Node{list.head->data, nullptr, nullptr};
			
			head = startingNode;
			tail = startingNode;

			current = current->next;
		}

		while (current) {
			Node<T>* newNode = new Node{current->data, tail, nullptr};
			tail = newNode;
			current = current->next;
		}
	}

	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr; // TODO: CAN"T ACCESS THESE VARIABLES
		other.tail = nullptr;
		other.count = 0;
	}

	~LinkedList() {
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};
#include <iostream>
#include <string>
using namespace std;

template<typename T, int N = 10>
class Queue {
protected:
	T arrayT[N]; // pointer to an array of type T
	int length = 0; // number of elements in the queue
	const int capacity = N; // maximum number of elements that queue can store
	int front = 0; // this variable points the front element in the queue
	int rear = -1; // points the rear element in the queue
public:
	void enqueueFront(T element);
	void enqueueRear(T element);
	T getFrontElement();
	T getRearElement();
	void dequeueFront();
	void dequeueRear();
	int numberOfElements();
	void clearQueue();
	const T* getQueue();
};

template<typename T, int N>
void Queue<T, N>::enqueueFront(T element) {
	if (length < capacity) { // if length is smaller than N
		int next_index;
		// shift all values to the next index
		for (int i = rear; i >= front; i--) {
			next_index = (i + 1) % capacity;
			arrayT[next_index] = arrayT[i];
		}
		arrayT[front] = element; // append first element
		length++;
		rear = (rear + 1) % capacity; // calculate next rear index
	}
	else {
		cout << "Limit exceeded. Element " << element << " could not be inserted." << endl;
		throw length_error("Queue is full");
	}
}

template<typename T, int N>
void Queue<T, N>::enqueueRear(T element) {
	if (length < capacity) {
		rear = (rear + 1) % capacity; // calculate next rear index
		arrayT[rear] = element; // append element and increment number of elements
		length += 1;
	}
	else {
		cout << "Limit exceeded. Element " << element << " could not be inserted." << endl;
		throw length_error("Queue is full");
	}
}

template<typename T, int N>
void Queue<T, N>::dequeueRear() {
	/* Dequeue element from the end of an array */
	if (length > 0) {
		arrayT[rear] = T{}; // insert empty object
		length--; // reduce length of queue
		rear = (rear - 1) % capacity; // calculate next rear index
	}
	else {
		cout << "No elements to dequeue" << endl;
		throw invalid_argument("Queue is empty");
	}
}

template<typename T, int N>
void Queue<T, N>::dequeueFront() {
	/* Dequeue element from the front of an queue */
	if (length > 0) {
		arrayT[front] = T{}; // insert empty object
		front = (front + 1) % capacity; // calculate next front index
		length--;
	}
	else {
		cout << "No elements to dequeue" << endl;
		throw invalid_argument("Queue is empty");
	}
}

template<typename T, int N>
T Queue<T, N>::getFrontElement() {
	/* Returns element from the front of an array */
	if (length <= 0) {
		cout << "Queue does not have values" << endl;
		throw invalid_argument("Queue is empty");
	}
	else return arrayT[front]; // get the last element of an array | array.back() doesn't work
}

template<typename T, int N>
T Queue<T, N>::getRearElement() {
	/* Returns element from the end of an array */
	if (length <= 0){
		cout << "Queue does not have values" << endl;
		throw invalid_argument("Queue is empty");
	}
	else {
		return arrayT[rear];
	}
}

template<typename T, int N>
int Queue<T, N>::numberOfElements() {
	/* Returns number of elements currently stored in queue*/
	return length;
}

template<typename T, int N>
void Queue<T, N>::clearQueue() {
	/*
	Fills all queue elements with empty type T values.
	Set attribute length equal to 0,
	and reset position parameters
	*/
	if (length <= 0) {
		cout << "Queue does not have values" << endl;
		throw length_error("Queue is empty");
	}
	else {
		// fill array with empty values type T
		// could be replaced with std::fill
		for (int i = 0; i < capacity; ++i) { 
			arrayT[i] = T{};
		}
		length = 0;
		front = 0;
		rear = -1;
	}
}

template<typename T, int N>
const T* Queue<T, N>::getQueue() {
	/*
	This method returns a pointer to the first element of an array
	This approach has some flaws, but at the moment I cannot find
	more appropriate solution
	*/
	if (length <= 0) {
		cout << "Queue does not have values" << endl;
		throw length_error("Queue is empty");
	}
	else {
		return arrayT;
	}
}

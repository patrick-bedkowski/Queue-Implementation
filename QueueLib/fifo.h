template<typename T, int N>
class FIFO : public Queue<T, N>
{
public:
	FIFO() = default;

	T getFrontElement();
	void enqueueFront() = delete; // disable access to this method
	void dequeueRear() = delete;
private:
	using Queue<T, N>::dequeueFront; // this method is disabled from being used outside of class
};

template<typename T, int N>
T FIFO<T, N>::getFrontElement() {
	/* Returns element from the front of an array and dequeues it after */
	if (Queue<T, N>::length <= 0 || Queue<T, N>::length > Queue<T, N>::capacity) {
		cout << "Queue does not have values" << endl;
		throw length_error("Queue is empty");
	}
	else {
		T temp_value = Queue<T, N>::arrayT[Queue<T, N>::front]; // create temp value that will be returned 
		Queue<T, N>::dequeueFront(); // deque Front element from the Queue
		return temp_value; // return elemnent
	}
};
#include "../QueueLib/queue.h"
#include "../QueueLib/fifo.h"
#include "../QueueLib/person.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QueueTests
{
	TEST_CLASS(QueueTests)
	{
	public:
		/*
		============================================
		|		Class Queue INT type values		   |
		============================================
		*/
		TEST_METHOD(enqueueFrontElement)
		{
			Queue<int, 4> queue;
			queue.enqueueFront(5); // append first element
			// it is also acceptable to use enqueueRear method since no element has been inserted yet

			Assert::AreEqual(5, queue.getFrontElement());
			Assert::AreEqual(queue.getRearElement(), queue.getFrontElement());
		}

		TEST_METHOD(enqueueRearElement)
		{
			Queue<int, 4> queue;
			queue.enqueueFront(5); // append first element
			queue.enqueueRear(10); // append end element
			queue.enqueueRear(15); // append end element again

			Assert::AreEqual(15, queue.getRearElement());
		}

		TEST_METHOD(dequeueRear)
		{
			Queue<int, 3> queue;
			queue.enqueueRear(5); // append first element
			queue.enqueueRear(10); // append end element
			queue.enqueueRear(15); // append end element again

			Assert::AreEqual(15, queue.getRearElement()); // last element 15

			queue.dequeueRear(); // delete 15
			Assert::AreEqual(10, queue.getRearElement());

			queue.dequeueRear(); // delete 10
			Assert::AreEqual(5, queue.getRearElement()); //check last element which is now 5
			Assert::AreEqual(5, queue.getFrontElement()); // first should be the same as last
		}

		TEST_METHOD(dequeueFront)
		{
			Queue<int, 5> queue;
			queue.enqueueRear(5); // append first element
			queue.enqueueRear(10); // append end element
			queue.enqueueRear(15); // append end element again
			
			Assert::AreEqual(5, queue.getFrontElement()); // first element 5

			queue.dequeueFront(); // delete 5
			Assert::AreEqual(10, queue.getFrontElement());

			queue.dequeueFront(); // delete 10
			Assert::AreEqual(15, queue.getRearElement()); // check last element which is now 15
			Assert::AreEqual(15, queue.getFrontElement()); // first should be the same as last
		}
		TEST_METHOD(ReturnNumberOfElements)
		{
			Queue<int, 5> queue;
			queue.enqueueRear(5);
			queue.enqueueRear(10);
			queue.enqueueRear(15);

			Assert::AreEqual(3, queue.numberOfElements());
		}

		TEST_METHOD(enqueueFrontRearWhenFull)
		{
			Queue<int, 1> queue;
			queue.enqueueRear(5); // append first element

			// catch all thrown exceptions

			auto func1 = [&] {queue.enqueueFront(10); };
			Assert::ExpectException<std::length_error>(func1);

			auto func2 = [&] {queue.enqueueRear(15); };
			Assert::ExpectException<std::length_error>(func2);
		}

		TEST_METHOD(GetFrontRearWhenEmpty)
		{
			Queue<int, 5> queue;
			queue.enqueueRear(5); // append first element

			queue.clearQueue();

			// catch all thrown exceptions

			auto func1 = [&] {queue.getFrontElement(); };
			Assert::ExpectException<std::invalid_argument>(func1);

			auto func2 = [&] {queue.getRearElement(); };
			Assert::ExpectException<std::invalid_argument>(func2);
		}

		TEST_METHOD(DequeueFrontRearWhenEmpty)
		{
			Queue<int, 5> queue;
			queue.enqueueRear(5); // append first element

			queue.clearQueue();

			// catch all thrown exceptions

			auto func1 = [&] {queue.dequeueRear(); };
			Assert::ExpectException<std::invalid_argument>(func1);

			auto func2 = [&] {queue.dequeueFront(); };
			Assert::ExpectException<std::invalid_argument>(func2);
		}

		TEST_METHOD(GetNumberOfElementsWhenEmpty)
		{

			Queue<int, 5> queue;
			queue.enqueueRear(5); // append first element
			queue.enqueueRear(10); // append end element
			queue.enqueueRear(15); // append end element again
		
			queue.clearQueue();

			Assert::AreEqual(0, queue.numberOfElements());
		}

		TEST_METHOD(GetQueueWhenEmpty)
		{

			Queue<int, 5> queue;
			queue.enqueueRear(5); // append first element

			queue.clearQueue();

			auto func = [&] {queue.getQueue(); };
			Assert::ExpectException<std::length_error>(func);
		}

		TEST_METHOD(GetQueue)
		{
			Queue<int, 5> queue;
			queue.enqueueRear(5);
			queue.enqueueRear(10);
			queue.enqueueRear(15);

			const int* queue_objects = queue.getQueue();
			vector<int> result{5, 10, 15};

			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(result[i], queue_objects[i]);
			}
		}

		/*
		==============================================
		|		Class Queue PERSON type values		 |
		==============================================
		*/

		TEST_METHOD(enqueueFrontRearElementPerson)
		{
			Queue<Person, 4> queue;
			queue.enqueueRear(Person("Tommy")); // append first element
			queue.enqueueFront(Person("John")); // append front element

			Assert::AreEqual(string("John"), queue.getFrontElement().getName());
		}
		
		TEST_METHOD(dequeueRearPerson)
		{
			Queue<Person, 4> queue;
			queue.enqueueFront(Person("Tommy"));
			queue.enqueueRear(Person("John"));
			queue.enqueueRear(Person("Michael"));

			Assert::AreEqual(string("Michael"), queue.getRearElement().getName());

			queue.dequeueRear(); // delete Michael
			Assert::AreEqual(string("John"), queue.getRearElement().getName());

			queue.dequeueRear(); // delete John
			Assert::AreEqual(string("Tommy"), queue.getRearElement().getName());
			Assert::AreEqual(string("Tommy"), queue.getFrontElement().getName());
		}
		
		TEST_METHOD(dequeueFrontPerson)
		{
			Queue<Person, 4> queue;
			queue.enqueueFront(Person("Tommy"));
			queue.enqueueRear(Person("John"));
			queue.enqueueRear(Person("Michael"));

			Assert::AreEqual(string("Tommy"), queue.getFrontElement().getName());

			queue.dequeueFront(); // delete Tommy
			Assert::AreEqual(string("John"), queue.getFrontElement().getName());

			queue.dequeueFront(); // delete John
			
			// last element is a front and rear one at the same time
			Assert::AreEqual(string("Michael"), queue.getRearElement().getName());
			Assert::AreEqual(string("Michael"), queue.getFrontElement().getName());
		}
	
		TEST_METHOD(ReturnNumberOfElementsPerson)
		{
			Queue<Person, 4> queue;
			queue.enqueueFront(Person("Tommy"));
			queue.enqueueRear(Person("John"));
			queue.enqueueRear(Person("Michael"));

			Assert::AreEqual(3, queue.numberOfElements());
		}
		
		TEST_METHOD(enqueueFrontRearWhenFullPerson)
		{
			Queue<Person, 1> queue;
			queue.enqueueFront(Person("Tommy"));

			// catch all thrown exceptions

			// cannot enqueue another object
			auto func1 = [&] {queue.enqueueFront(Person("Michael")); };
			Assert::ExpectException<std::length_error>(func1);

			// cannot enqueue another object
			auto func2 = [&] {queue.enqueueRear(Person("Michael")); };
			Assert::ExpectException<std::length_error>(func2);
		}
		
		TEST_METHOD(GetFrontRearWhenEmptyPerson)
		{
			Queue<Person, 1> queue;
			queue.enqueueFront(Person("Tommy"));

			queue.clearQueue();

			// catch all thrown exceptions

			auto func1 = [&] {queue.getFrontElement(); };
			Assert::ExpectException<std::invalid_argument>(func1);

			auto func2 = [&] {queue.getRearElement(); };
			Assert::ExpectException<std::invalid_argument>(func2);
		}
		
		TEST_METHOD(DequeueFrontRearWhenEmptyPerson)
		{
			Queue<Person, 1> queue;
			queue.enqueueFront(Person("Tommy"));

			queue.clearQueue();

			// catch all thrown exceptions

			auto func1 = [&] {queue.dequeueRear(); };
			Assert::ExpectException<std::invalid_argument>(func1);

			auto func2 = [&] {queue.dequeueFront(); };
			Assert::ExpectException<std::invalid_argument>(func2);
		}
		
		TEST_METHOD(GetNumberOfElementsWhenEmptyPerson)
		{
			Queue<Person, 4> queue;
			queue.enqueueFront(Person("Tommy"));
			queue.enqueueRear(Person("John"));

			queue.clearQueue();

			Assert::AreEqual(0, queue.numberOfElements());
		}

		TEST_METHOD(GetQueueWhenEmptyPerson)
		{

			Queue<Person, 4> queue;
			queue.enqueueFront(Person("Tommy"));
			queue.enqueueRear(Person("John"));

			queue.clearQueue();

			auto func = [&] {queue.getQueue();};
			Assert::ExpectException<std::length_error>(func);
		}

		TEST_METHOD(GetQueuePerson)
		{
			Queue<Person, 3> queue;
			queue.enqueueFront(Person("Tommy"));
			queue.enqueueRear(Person("John"));
			queue.enqueueRear(Person("Michael"));

			const Person* queue_objects = queue.getQueue();
			vector<string> result{ "Tommy", "John", "Michael" };

			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(result[i], queue_objects[i].getName());
			}
		}
	};
}

namespace FIFOTests
{
	TEST_CLASS(FIFOTests)
	{
	public:

		/*
		============================================
		|		Class FIFO INT type values		   |
		============================================
		*/
		TEST_METHOD(EnqueElement)
		{
			FIFO<int, 5> fifo;

			fifo.enqueueRear(5);
			Assert::AreEqual(5, fifo.getFrontElement());

			fifo.enqueueRear(10);
			Assert::AreEqual(10, fifo.getRearElement());

			fifo.enqueueRear(15);
			Assert::AreEqual(15, fifo.getRearElement());
		}

		TEST_METHOD(GetFrontElementDequeueAfter)
		{
			FIFO<int, 5> fifo;

			fifo.enqueueRear(5);
			fifo.enqueueRear(10);
			fifo.enqueueRear(15);

			Assert::AreEqual(3, fifo.numberOfElements());
			Assert::AreEqual(5, fifo.getFrontElement()); // 5 will be dequeue
			Assert::AreEqual(2, fifo.numberOfElements()); // number of elements will decrease
		}

		TEST_METHOD(getFrontElementWhenEmpty)
		{
			FIFO<int, 5> fifo;

			auto func = [&] {fifo.getQueue(); };
			Assert::ExpectException<std::length_error>(func);
		}

		/*
		=====================================
		|	Class FIFO Person type values	|
		=====================================
		*/

		TEST_METHOD(EnqueElementPerson)
		{
			FIFO<Person, 5> fifo;
			fifo.enqueueRear(Person("John"));
			fifo.enqueueRear(Person("Michael"));
			fifo.enqueueRear(Person("Tommy"));

			Assert::AreEqual(3, fifo.numberOfElements());

			Assert::AreEqual(string("John"), fifo.getFrontElement().getName()); // John will be dequeued
			Assert::AreEqual(2, fifo.numberOfElements()); // number of elements will decrease

			Assert::AreEqual(string("Tommy"), fifo.getRearElement().getName()); // last element will not be dequeued after peek
			Assert::AreEqual(2, fifo.numberOfElements()); // thus number of elements will not decrease

			Assert::AreEqual(string("Michael"), fifo.getFrontElement().getName()); // front element will be dequeued 
			Assert::AreEqual(1, fifo.numberOfElements()); // number of elements will decrease

			fifo.clearQueue(); // clear last element - "Tommy"
			Assert::AreEqual(0, fifo.numberOfElements());

			// catch an exception, queue is empty thus no element can be accessed
			auto func = [&] {fifo.getQueue();};
			Assert::ExpectException<std::length_error>(func);
		}
	};
}


namespace Personests
{
	TEST_CLASS(PersonTests)
	{
	public:

		/*
		=================================
		|		Class Person tests		|
		=================================
		*/
		TEST_METHOD(getName)
		{
			Person person1("Tommy");
			Assert::AreEqual(string("Tommy"), person1.getName());
		}

		TEST_METHOD(streamOperator)
		{
			Person person1("Tommy"); // create object
			stringstream ss;
			ss << person1;
			Assert::AreEqual(string("Tommy"), ss.str());
		}
	};
}

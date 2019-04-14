#include <vector>
#include <tsvector.h>

#include <iostream>
#include <string>

// Test with std::vector
void unsafeTest(const int size)
{
	std::vector<int> nums(size);

	auto popNum = [&nums, size]()
	{
		for (auto i = 0; i < size / 2; i++)
		{
			nums.pop_back();
		}
	};

	std::thread t1 = std::thread(popNum);
	std::thread t2 = std::thread(popNum);
	t1.join();
	t2.join();

	if (!nums.empty())
	{
		std::cout << "RACE CONDITION! List must be empty, but is of size " << nums.size() << std::endl;
	}
	else
	{
		std::cout << "ALL IS GOOD IN THIS REALM..." << std::endl;
	}
}


// Test with tsVector
void threadSafeTest(const int size)
{
    tsVector<int> nums(size);

	auto popNum = [&nums, size]()
	{
		for (auto i = 0; i < size / 2; i++)
		{
			nums.pop_back();
		}
	};

	std::thread t1 = std::thread(popNum);
	std::thread t2 = std::thread(popNum);
	t1.join();
	t2.join();

	if (!nums.empty())
	{
		std::cout << "RACE CONDITION! List must be empty, but is of size " << nums.size() << std::endl;
	}
	else
	{
		std::cout << "ALL IS GOOD IN THIS REALM..." << std::endl;
	}
}

int main()
{ 
	// TESTS
	// --IDEAL SCENARIO: Each thread should delete a different half of the list, resulting in an empty list
	const auto numTransactions = 10000;

	std::cout << "THREAD-UNSAFE (STD::VECTOR) TEST:" << std::endl;
	unsafeTest(numTransactions);

	std::cout << "\nTHREAD-SAFE (TSVECTOR) TEST:" << std::endl;
	threadSafeTest(numTransactions);

	return 0;
}

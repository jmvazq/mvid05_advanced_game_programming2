#include<iostream>
#include <vector>
#include <thread>
#include <mutex>

class Wallet
{
	private:
		uint32_t money_ = 0;
		std::mutex mutex_;
	public:
		Wallet() {}
		const uint32_t getMoney() const { return money_; }

		void addMoney(const uint32_t amount)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			for (uint32_t i = 0; i < amount; ++i)
			{
				money_++;
			}
		}
};

uint32_t testWallet()
{
	Wallet wallet;

	std::vector<std::thread> threads;
	for (uint32_t i = 0; i < 20; ++i)
	{
		threads.push_back(std::thread(&Wallet::addMoney, &wallet, 5000));
	}
	for (uint32_t i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	return wallet.getMoney();
}

int main() {
	std::cout << "Starting" << std::endl;

	uint32_t val = 0;
	for (uint32_t k = 0; k < 1000; ++k)
	{
		val = testWallet();
		if (val != 100000)
		{
			std::cout << "Error in Simulation: " << k << " Money in Wallet is " << val << std::endl;
		}
	}

	std::cout << "Ended" << std::endl;

	getchar();
	return 0;
}
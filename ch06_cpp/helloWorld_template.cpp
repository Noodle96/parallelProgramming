#include <iostream>
#include <cstdint> // uint64_t
#include <vector> // std::vector
#include <thread> // std::thread
// this function will be called by the threads (should be void)
using namespace std;
template<typename T>
void say_hello(T id);

// this runs in the master thread
int main(int argc, char * argv[]) {
	const uint64_t num_threads = 4;
	std::vector<thread> threads;
	// for all threads
	for (uint64_t id = 0; id < num_threads; id++){
		thread t(say_hello<uint64_t>, id);
		threads.push_back(t);
	}
	// join each thread at the end
	for (auto& thread: threads) thread.join();
}

void say_hello(uint64_t id) {
	std::cout << "Hello from thread: " << id << std::endl;
}
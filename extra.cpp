#include <cstdio>
#include <thread>

int main()
{
	printf("%u\n", std::jthread::hardware_concurrency());
	return 0;
}

#include "public.h"

int TestTimer()
{
	timer t;
	cout << "max timespac:" << t.elapsed_max()/3600/24/30 << "m" << endl;
	cout << "min timespac:" << t.elapsed_min() << "s" << endl;
	cout << "now timespac:" << t.elapsed() << "s" << endl;


	return 0;
}

int main()
{
	return 0;
}

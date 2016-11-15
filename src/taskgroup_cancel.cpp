//! @file tests wheter taskgroup cancel construct canel child tasks 
#include <omp.h>
#include <iostream>
#include <unistd.h>

using namespace std;

void f(char c){
	
	while(1){
		cout << c;
	}
}

int timeout(int seconds){
	sleep(seconds);
	return seconds;
}
int main(){
	int rv;
	#pragma omp parallel
	#pragma omp single
	#pragma omp taskgroup
	{
		#pragma omp task
		f('a');
		#pragma omp task
		f('b');
		#pragma omp task
		f('c');
		#pragma omp task
		{
			rv = timeout(1);
			#pragma omp cancel taskgroup if(rv==1)
		}
	}
	return 0;
}
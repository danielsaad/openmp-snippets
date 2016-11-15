//! @file tests wheter taskgroup cancel construct canel child tasks 
#include <omp.h>
#include <iostream>
#include <unistd.h>

using namespace std;

void f(char c){
	
	while(1){
		cout << c;
		usleep(1000);
	}
}

int timeout(int ms){
	cout << "Die.\n";
	return 1;
	return 0;
}
int main(){
	int rv;
	int rv2;
	if(omp_get_cancellation()){
		cout << "Cancelation Enabled\n";
	} 
	else{
		cout << "Cancelation Disabled\n";
	}
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
		#pragma omp task\
			private(rv2)
		{
			rv2 = timeout(400);
			#pragma omp critical
				rv = rv2;
				cout << "Rv = " << rv << endl;
			#pragma omp cancel taskgroup if(rv==1)
		}
	}
	return 0;
}
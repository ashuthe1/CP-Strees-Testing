// C program to illustrate 
// size of struct 
#include <stdio.h> 

int main() 
{ 

	struct A { 

		// sizeof(int) = 4 
		int x; 
		// Padding of 4 bytes 

		// sizeof(double) = 8 
		char z; 

		// sizeof(short int) = 2 
		float y; 
		// Padding of 6 bytes 
	}; 

	printf("Size of struct: %ld", sizeof(struct A)); 

	return 0; 
} 

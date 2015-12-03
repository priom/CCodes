//Authon: Priom

#include <stdio.h>

int main(void) {
	int i, j, k[10], m;
	// Inpuut number
	for (i = 0; i < 10; i++) {
		printf("Enter a number: ");
		scanf("%d", &k[i]);
	}
	//Return number if duplicate
	for (i= 0; i < 10; i++) {
		m = k[i];
		for(j=i+1; j<10; j++) {
			if (m == k[j]) {
				printf("%d is duplicate\n", m);
			}
		}
	}
	return 0;

}

#include <stdio.h>

void print_menu() {
	//Print the menu of the program.
	printf("1.Read a vector\n");
	printf("2.Find the value of x^n. \n");
	printf("3.Find the longest subsequence with consecutive numbers of different signs. \n");
	printf("4.Exit the program\n\n");
}

int determine_value(int x, int n){
	/*Determine the value of x^n.
	-input: x - the base
			n - the exponent
	-output: x1 - the value of x^n
	*/
	int x1 = 1;
	while (n > 0) {
		x1 = x1 * x;
		n--;
	}
	return x1;
}

void find_longest_subseq(int vector[], int* start, int* finish, int n) {
	/*Find the longest subsequence with consecutive numbers of different signs.
	-input: vector - the vector of numbers
			start - the start of the longest subsequence
			finish - the finish of the longest subsequence
			n - the length of the vector
	-output: start - the start of the longest subsequence
			finish - the finish of the longest subsequence
	*/

	int length = 1, length_maxim = 1;
	int start_current = 0, finish_current = 0;
	for (int i = 0; i < n-1; i++) {
		if ((vector[i] < 0 && vector[i + 1] >= 0) || (vector[i] >= 0 && vector[i + 1] < 0)) {
			length++;
			finish_current = i + 1;
		}
		if (length_maxim < length) {
			length_maxim = length;
			*start = start_current;
			*finish = finish_current;
		}
		if ((vector[i] < 0 && vector[i + 1] < 0) || (vector[i] >= 0 && vector[i + 1] >= 0)) {
			length = 1;
			start_current = i + 1;
		}

			
		
	}
}


void read_vector(int vector[], int n) {
	/*Read the vector of numbers.
	-input: vector - the vector of numbers
			n - the length of the vector
	-output: vector - the vector of numbers
	*/
	int number = 0;
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &number);
		vector[i] = number;
	}
}


int main() {
	print_menu();
	int option;
	int vector[1000] = { 0 };
	int n = 0;
	while (1) {
		printf("\nEnter the option: ");
		scanf_s("%d", &option);

		switch (option) {
		case 1: {
			printf("\nGive the length of vector: ");
			scanf_s("%d", &n);
			printf("\nGive the vector of numbers: ");
			read_vector(vector, n);
			break;
		}
		case 2: {
			int x, n, x_n;
			printf("\nPlease give the values for x: ");
			scanf_s("%d", &x);
			printf("\nPlease give the values for n: ");
			scanf_s("%d",&n);
			x_n = determine_value(x, n);
			printf("\nThe value of x^n is: %d\n", x_n);
			break;
		}

		case 3: {
			if (n==0)
				printf("\nRead the vector first!!\n");
			else
			{
				int start=0, finish=0;
				find_longest_subseq(vector, &start, &finish, n);
				for (int i = start; i <= finish; i++)
					printf("%d ", vector[i]);
				printf("\n");
			}
			break;
		}

		case 4: 
			printf("\nExiting the program...\n");
			return 0;

		default:
			printf("\nInvalid option!");
			break;
		}
	}
	return 0;
}

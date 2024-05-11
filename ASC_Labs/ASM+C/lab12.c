#include <stdio.h>

//Read a string of unsigned numbers in base 10 from keyboard.
//Determine the maximum value of the string and write it in the file max.txt (it will be created) in 16  base.
int compare(int maxim, int number);

int main() {
    int number;
    int maxim = 0;
    printf("Give the numbers: ");
    FILE *file;
    do {
        scanf("%d", &number);
        if (number == -1) {
            break;
        }
        maxim = compare(maxim, number);
    } while (1);
    file = fopen("max.txt", "w");
    if (file != NULL) {
        fprintf(file, "%x", maxim);
        fclose(file);
    }

    return 0;
}

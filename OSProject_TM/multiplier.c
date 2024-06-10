#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int multiplier_pipe = open("multiplier_pipe", O_RDONLY);

    double numbers[2];
    double result;

    read(multiplier_pipe, numbers, 2 * sizeof(double));
    close(multiplier_pipe);

    result = numbers[0] * numbers[1];
    char toplam[80];
    sprintf(toplam, "%lf", result);  

    multiplier_pipe = open("multiplier_pipe", O_WRONLY);
    write(multiplier_pipe, &toplam, sizeof(toplam));
    close(multiplier_pipe);

    return 0;
}

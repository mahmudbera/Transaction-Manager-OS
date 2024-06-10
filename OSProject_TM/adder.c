#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int adder_pipe = open("adder_pipe", O_RDONLY);

    double numbers[2];
    double result;

    read(adder_pipe, numbers, 2 * sizeof(double));
    close(adder_pipe);

    result = numbers[0] + numbers[1];
    char toplam[80];
    sprintf(toplam, "%lf", result);  

    adder_pipe = open("adder_pipe", O_WRONLY);
    write(adder_pipe, &toplam, sizeof(toplam));
    close(adder_pipe);

    return 0;
}

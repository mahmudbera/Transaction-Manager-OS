#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int subtractor_pipe = open("subtractor_pipe", O_RDONLY);

    double numbers[2];
    double result;

    read(subtractor_pipe, numbers, 2 * sizeof(double));
    close(subtractor_pipe);

    result = numbers[0] - numbers[1];
    char toplam[80];
    sprintf(toplam, "%lf", result);  

    subtractor_pipe = open("subtractor_pipe", O_WRONLY);
    write(subtractor_pipe, &toplam, sizeof(toplam));
    close(subtractor_pipe);

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int divider_pipe = open("divider_pipe", O_RDONLY);

    double numbers[2];
    double result;

    read(divider_pipe, numbers, 2 * sizeof(double));
    close(divider_pipe);

    result = numbers[0] / numbers[1];
    char toplam[80];
    sprintf(toplam, "%lf", result);  

    divider_pipe = open("divider_pipe", O_WRONLY);
    write(divider_pipe, &toplam, sizeof(toplam));
    close(divider_pipe);

    return 0;
}

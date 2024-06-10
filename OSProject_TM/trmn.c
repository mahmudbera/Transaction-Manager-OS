#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ADDER_PIPE "adder_pipe"
#define SUBTRACTOR_PIPE "subtractor_pipe"
#define MULTIPLIER_PIPE "multiplier_pipe"
#define DIVIDER_PIPE "divider_pipe"

int main() {

    mkfifo(ADDER_PIPE, 0666);
    mkfifo(SUBTRACTOR_PIPE, 0666);
    mkfifo(MULTIPLIER_PIPE, 0666);
    mkfifo(DIVIDER_PIPE, 0666);

    int adder_pipe_fd;
    int subtractor_pipe_fd;
    int multiplier_pipe_fd;
    int divider_pipe_fd;
    
    int pid1 = fork();
    if (pid1 == 0) {
        execl("./adder", "adder", NULL);
    }

    int pid2 = fork();
    if (pid2 == 0) { 
        execl("./subtractor", "subtractor", NULL);
    }

    int pid3 = fork();
    if (pid3 == 0) {
        execl("./multiplier", "multiplier", NULL);
    }

    int pid4 = fork();
    if (pid4 == 0) {
        execl("./divider", "divider", NULL);
    }

  while (1) {
    printf("1 - Addition\n2 - Subtraction\n3 - Multiplication\n4 - Division\n5 - Exit\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
      case 1: {
                double numbers[2];
                char result[80];	
                printf("Enter two numbers: ");
                scanf("%lf %lf", &numbers[0], &numbers[1]);
		
		adder_pipe_fd = open(ADDER_PIPE, O_WRONLY);
                write(adder_pipe_fd, numbers, sizeof(numbers));
		close(adder_pipe_fd);

		adder_pipe_fd = open(ADDER_PIPE, O_RDONLY);
                read(adder_pipe_fd, &result, sizeof(result));
		printf("Result: %s\n", result);
		close(adder_pipe_fd);	

                break;
            }
      case 2: {
        	double numbers[2];
                char result[80];	
                printf("Enter two numbers: ");
                scanf("%lf %lf", &numbers[0], &numbers[1]);

		subtractor_pipe_fd = open(SUBTRACTOR_PIPE, O_WRONLY);
                write(subtractor_pipe_fd, numbers, sizeof(numbers));
		close(subtractor_pipe_fd);

		subtractor_pipe_fd = open(SUBTRACTOR_PIPE, O_RDONLY);
                read(subtractor_pipe_fd, &result, sizeof(result));
		close(subtractor_pipe_fd);		

                printf("Result: %s\n", result);
                break;
      	}
      case 3: {
        	double numbers[2];
                char result[80];	
                printf("Enter two numbers: ");
                scanf("%lf %lf", &numbers[0], &numbers[1]);
		
		multiplier_pipe_fd = open(MULTIPLIER_PIPE, O_WRONLY);
                write(multiplier_pipe_fd, numbers, sizeof(numbers));
		close(multiplier_pipe_fd);

		multiplier_pipe_fd = open(MULTIPLIER_PIPE, O_RDONLY);
                read(multiplier_pipe_fd, &result, sizeof(result));
		close(multiplier_pipe_fd);		

                printf("Result: %s\n", result);
                break;
      }      
      case 4: {
        	double numbers[2];
                char result[80];	
                printf("Enter two numbers: ");
                scanf("%lf %lf", &numbers[0], &numbers[1]);
		if(numbers[1] != 0){
			divider_pipe_fd = open(DIVIDER_PIPE, O_WRONLY);                	
			write(divider_pipe_fd, numbers, sizeof(numbers));
			close(divider_pipe_fd);

			divider_pipe_fd = open(DIVIDER_PIPE, O_RDONLY);
                	read(divider_pipe_fd, &result, sizeof(result));
			close(divider_pipe_fd);		

                	printf("Result: %s\n", result);
                	break;
		}else{
			printf("ERROR: Division by zero!\n");
			break;
		}
      }
      case 5: {
                close(adder_pipe_fd);
                close(subtractor_pipe_fd);
                close(multiplier_pipe_fd);
                close(divider_pipe_fd);
		printf("Pipes closed. Program has been terminated.\n"); 
                return 0;
            }
      default: {
        printf("Geçersiz işlem seçimi\n");
        break;
      }
    }
  }

    close(adder_pipe_fd);
    close(subtractor_pipe_fd);
    close(multiplier_pipe_fd);
    close(divider_pipe_fd);

  return 0;
}
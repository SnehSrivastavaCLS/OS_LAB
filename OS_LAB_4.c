#include<stdio.h>
#include<unistd.h>

int main()
{
	int pipe1[2];
	int status1;
	int pid;
	char message1[50]={"Hello Parent, this is child process."};
	char message2[50]={"This is parent process"};

	char read_message[50];

	status1 = pipe(pipe1);
	if (status1 == -1)
	{
		printf("Unable to create pipe 1\n");
		return 1;
	}

	//Creating two processes
	pid = fork();

	if (pid==0)
		{
			//Child Process (first process)
			printf("Message sent in child process (pid = %d and ppid = %d): %s\n", getpid(), getppid(), message1);
			write(pipe1[1], message1, sizeof(message1));

		}
	else
		{
			//Parent Process (Second process)
			read( pipe1[0], read_message, sizeof(read_message));
			printf("%s (pid = %d and ppid = %d) and message received: %s\n", message2, getpid(), getppid(), read_message);
		}
	return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#define READ_END 0
#define WRITE_END 1

int main()
{
    pid_t pid;
    int fd[2];
    int randArray[5];
    int randNumW, childNum, parentNum, status;
    srand(time(NULL));
    printf("The game has launched\n");
    for (int i = 0; i < 5; i++)
    {
        randArray[i] = rand() % 99 + 1;
    }
    printf("Computer Choses [%d, %d, %d, %d, %d] randomly\n", randArray[0], randArray[1], randArray[2], randArray[3], randArray[4]);
    printf("Child process is created\n");
    printf("The game starts\n--\n");

    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }
    pid = fork();

    if (pid == 0)
    {
        wait(NULL);
        srand(time(NULL) ^ getpid());
        for (int i = 0; i < 5; i++)
        {
            randNumW = (rand() % 99) + 1;
            write(fd[WRITE_END], &randNumW, sizeof(randNumW));
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        srand(time(NULL) ^ getpid());
        int homeScore = 0, awayScore = 0;
        for (int i = 0; i < 5; i++)
        {
            wait(NULL);
            parentNum = rand() % 99 + 1;

            read(fd[READ_END], &childNum, sizeof(childNum));

            printf("Turn %d, Parent guess: %d, Child guess: %d\n", i + 1, parentNum, childNum);
            if (abs(randArray[i] - childNum) < abs(randArray[i] - parentNum))
            {
                awayScore++;
                printf("Child win, Score: %d – %d, %d is closer to %d than %d\n–\n", homeScore, awayScore, childNum, randArray[i], parentNum);
            }
            else if (abs(randArray[i] - childNum) > abs(randArray[i] - parentNum))
            {
                homeScore++;
                printf("Parent win, Score: %d – %d, %d is closer to %d than %d\n--\n", homeScore, awayScore, parentNum, randArray[i], childNum);
            }
            else
            {
                homeScore++;
                awayScore++;
                printf("Draw, Score: %d – %d, %d is equal to %d\n--\n", homeScore, awayScore, childNum, parentNum);
            }
        }
        if (homeScore > awayScore)
            printf("--\nParent has won the game with score: %d – %d .\n--\n", homeScore, awayScore);
        else
            printf("--\nChild has won the game with score: %d – %d .\n--\n", homeScore, awayScore);

        printf("Child has terminated\n");
        printf("Parent waits child with wait()\n");
        printf("Parent has terminated\n");
    }

    return 0;
}
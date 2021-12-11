#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static char guessArr[15][5];
static int count = 0;
pthread_mutex_t lock;
void *myThread(void *arg)
{
    int argInt = *(int *)arg;
    pthread_mutex_lock(&lock);
    for (int i = 0; i < 5; i++)
    {
        guessArr[argInt][i] = (rand() % 99) + 1;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}
void *myThread2(void *arg)
{
    int argInt = *(int *)arg;
    pthread_mutex_lock(&lock);
    if (argInt != 2 || count != 4)
        printf("%d_%d, ", argInt + 1, guessArr[argInt][count]);
    else
        printf("%d_%d", argInt + 1, guessArr[argInt][count]);
    if (argInt == 2)
        count++;
    if (count == 5)
        count = 0;
    pthread_mutex_unlock(&lock);

    return NULL;
}
int main()
{
    pthread_t tid[3], tid2[3];
    int randArray[5];
    int randNumW, childNum, parentNum, status, thr1Score = 0, thr2Score = 0, thr3Score = 0;
    int index[3];

    srand(time(NULL));
    printf("The game has launched\n");
    for (int i = 0; i < 5; i++)
    {
        randArray[i] = rand() % 100;
    }
    printf("Computer Choses [%d, %d, %d, %d, %d] randomly\n", randArray[0], randArray[1], randArray[2], randArray[3], randArray[4]);
    printf("3 threads will be created\n");
    printf("The game starts\n--\n");
    for (int i = 0; i < 3; i++)
    {
        index[i] = i;
        pthread_create(&tid[i], NULL, myThread, &index[i]);
    }
    for (int i = 0; i < 3; i++)
        pthread_join(tid[i], NULL);

    for (int i = 0; i < 5; i++)
    {

        int thr1 = guessArr[0][i];
        int thr2 = guessArr[1][i];
        int thr3 = guessArr[2][i];
        int thr1Abs = abs(randArray[i] - thr1);
        int thr2Abs = abs(randArray[i] - thr2);
        int thr3Abs = abs(randArray[i] - thr3);

        printf("Turn %d, Guesses: 1.Thread: %d, 2.Thread: %d, 3.Thread: %d, \n–-\n", i + 1, thr1, thr2, thr3);
        if (thr1Abs < thr2Abs && thr1Abs < thr3Abs)
        {
            thr1Score++;
            printf("1.thread win, Score: %d – %d - %d, %d is closest to %d, \n–-\n", thr1Score, thr2Score, thr3Score, thr1, randArray[i]);
        }
        else if (thr2Abs < thr1Abs && thr2Abs < thr3Abs)
        {
            thr2Score++;
            printf("2.thread win, Score: %d – %d - %d, %d is closest to %d, \n-–\n", thr1Score, thr2Score, thr3Score, thr2, randArray[i]);
        }
        else if (thr3Abs < thr1Abs && thr3Abs < thr2Abs)
        {
            thr3Score++;
            printf("3.thread win, Score: %d – %d - %d, %d is closest to %d, \n-–\n", thr1Score, thr2Score, thr3Score, thr3, randArray[i]);
        }
        else if (thr1Abs == thr2Abs && thr1Abs == thr3Abs)
        {
            thr1Score++;
            thr2Score++;
            thr3Score++;
            printf("1.thread and 2.thread and 3.thread win, Score: %d – %d - %d, %d is closest to %d, \n–-\n", thr1Score, thr2Score, thr3Score, thr1, randArray[i]);
        }
        else if (thr1Abs == thr2Abs && thr1Abs < thr3Abs)
        {
            thr1Score++;
            thr2Score++;
            printf("1.thread and 2.thread win, Score: %d – %d - %d, %d is closest to %d, \n–-\n", thr1Score, thr2Score, thr3Score, thr1, randArray[i]);
        }
        else if (thr2Abs == thr3Abs && thr2Abs < thr1Abs)
        {
            thr2Score++;
            thr3Score++;
            printf("2.thread and 3.thread win, Score: %d – %d - %d, %d is closest to %d, \n-–\n", thr1Score, thr2Score, thr3Score, thr2, randArray[i]);
        }
        else if (thr1Abs == thr3Abs && thr1Abs < thr2Abs)
        {
            thr1Score++;
            thr3Score++;
            printf("1.thread and 3.thread win, Score: %d – %d - %d, %d is closest to %d, \n–-\n", thr1Score, thr2Score, thr3Score, thr1, randArray[i]);
        }
    }
    if (thr1Score == thr2Score && thr1Score == thr3Score)
        printf("–-\n1.Thread and 2.Thread and 3. Thread won the game with score: Score: %d – %d – %d.\n–-\n-–\n", thr1Score, thr2Score, thr3Score);
    else if (thr1Score == thr2Score && thr1Score > thr3Score)
        printf("–-\n1.Thread and 2.Thread won the game with score: Score: %d – %d – %d.\n–-\n-–\n", thr1Score, thr2Score, thr3Score);
    else if (thr1Score == thr3Score && thr1Score > thr2Score)
        printf("-–\n1.Thread and 3.Thread won the game with score: Score: %d – %d – %d.\n–-\n–-\n", thr1Score, thr2Score, thr3Score);
    else if (thr2Score == thr3Score && thr2Score > thr1Score)
        printf("–-\n2.Thread and 3.Thread won the game with score: Score: %d – %d – %d.\n–-\n-–\n", thr1Score, thr2Score, thr3Score);
    else if (thr1Score > thr3Score && thr1Score > thr2Score)
        printf("-–\n1.Thread won the game with score: Score: %d – %d – %d.\n-–\n–-\n", thr1Score, thr2Score, thr3Score);
    else if (thr2Score > thr1Score && thr2Score > thr3Score)
        printf("-–\n2.Thread won the game with score: Score: %d – %d – %d.\n-–\n–-\n", thr1Score, thr2Score, thr3Score);
    else if (thr3Score > thr1Score && thr3Score > thr2Score)
        printf("–-\n3.Thread won the game with score: Score: %d – %d – %d.\n-–\n–-\n", thr1Score, thr2Score, thr3Score);
    else
        printf("something forgotten!");
    printf("Guesses made by threads: [");
    for (int i = 0; i < 5; i++)
    {
        for (int i = 0; i < 3; i++)
        {
            index[i] = i;
            pthread_create(&tid2[i], NULL, myThread2, &index[i]);
        }
        for (int i = 0; i < 3; i++)
            pthread_join(tid[i], NULL);
    }

    printf("]\n-–\n-–\n");
    printf("1.Thread terminated\n2.Thread terminated\n3.Thread terminated\nThreads are joined by main process\nGame finished\n");
    pthread_exit(NULL);
    return 0;
}
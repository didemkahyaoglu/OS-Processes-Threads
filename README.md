# OS-Processes-Threads

Subject: Playing a guess game with processes and threads. Processes and threads will try to guess the number that is chosen by computer from the interval from 1 to 99. The closest guess gets the point. The possible numbers include from [1,99].

You will implement two programs.

a)	guess_process.c ; Game with 2 processes

b)	guess_threads.c ; Game with 3 threads

Pseudocode for (a):
1.	Main process fills an array of size 5 with random numbers from 1 to 99.
2.	Main process creates a new child process with fork() 
3.	Child process selects a number randomly
4.	Parent process will select a number randomly
5.	Then they will compare their numbers with the first element of the filled array (in the second iteration of the loop, they will compare with second elements, in the third iteration compare with third element of the array, and so forth)
6.	Score of the winning process to be increased
7.	Game will end after 5 guesses.

Pseudocode for (b):
1.	Main process fills an array of size 5 with random numbers from 1 to 99.
2.	Main process creates 3 threads with pthread_create()
3.	Threads selects a number randomly
4.	Then they will compare their numbers with the first element of the filled array (in the second iteration of the loop, they will compare with second elements, in the third iteration compare with third element of the array, and so forth)
5.	Score of the winning threads will be increased 
6.	Game will end after 5 guesses.

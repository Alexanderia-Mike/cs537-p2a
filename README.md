This is a course project based on XV6 Operating System that implements lottery scheduling. 

### Brief Introduction 
One of the jobs of operating systems is to schedule different processes properly so that the processes could proceed together fairly and appropriately according to their priorities.
In XV6 Operating system, the default scheduling strategy is round-robin scheduling, which simply give each process the same amount of time to execute. Without taking the priorities of processes into consideration, round-robin scheduling could be problematic since urgent requests cannot be addresed timely.
In this project, the lottery scheduling is implemented to improve the scheduling strategy. In lottery scheduling, each process is assigned with a certain amount of lotteries, and the more the lotteries there are, the higher the priority that process is given. Specifically speaking, during the context switching process, a random number is generated, ranging from 0 to the total number of lotteries `num_lotteries`, and each process `p_i` will be mapped to a certain interval `[start_i, end_i]`, and the length of the interval is the number of lotteries held by that process. Therefore, the larger the interval is, the higher the probability of that process being picked as the next running process is, thus giving that process a higher priority.

### Codes
the main modification of codes are shown in the files `proc.c`

# philosophers

42 Cursus - philosophers: this project is a training to multi-threads/multi-process programming.

## Table of contents 📑
- [Status](#status)
- [About the project](#about-the-project)
    * [The philosophers problem](#the-philosophers-problem)
    * [Threading theory](#threading-theory)
    * [Project boundaries](#project-boundaries)
- [How to use](#how-to-use)

## Status ✔️
- Status: finished
- Score: 100%
- Observations: learned about threads

## About the project 👩‍💻

I never thought philosophy would be so deadly
In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes.

### The philosophers problem 🥢

This problem states that *n* philosophers are seated at a round table with one chopstick between each pair of philosophers (same number of pholosophers and chopsticks) and there is a large bowl of noodles in the middle of the table. 

A philosopher may eat if they can pick up the two chopsticks adjacent to them. Each chopstick may be picked up my and one of its adjacent philosophers, but not at the same time. 

When a philosopher has finished eating, they drop the chopstick back on the table and start sleeping. Philosophers, alternatively, eat, think, or sleep. They can only do one thing at a time. After sleeping, they will start thinking and waiting to eat again. 

Simulation stops when a philosopher dies of starvation. 

Every philosopher needs to eat, and should never starve.

Philosophers don't speak with each other.

Philosophers don't know if another philosopher is about to die. 

Philosophers, of course, should avoid dying.


### Threading theory 🧵

Multithreading is a form of multitasking, of running two or more programs concurrently.

- Process-based multitasking handles the concurrent execution of programs.
- Thread-based multitasking dials with the concurrent execution of pieces of the same program. 

A multithreaded program contains two or more parts that can run concurrently. Each part of such a program is called a thread, and each thread defines a separate path of execution.

Threads are not independent from each other unlike processes. As a result, threads shares with other threads their code section, data section and OS resources like open files and signals.

C does not contain any built-in support for multithreaded applications. Instead, it relies entirely upon the operating system to provide this feature.

For more information:

```
man pthread
```

### Project boundaries 🔧

- The program takes the following arguments:
    * number_of_philosophers (and also the number of chopsticks)
    * time_to_die -> (in milliseconds) margin of time they have to start eating before they die, since the begining of the simulation or since the last time they ate.
    * time_to_eat -> (in milliseconds) time it takes to eat.
    * time_to_sleep -> (in milliseconds) time it takes to sleep.
    * number_of_times_each_philosopher_must_eat -> (optional)
- The philosophers are seated in order.
- Any state change of a philosopher must be stated.
- There must not be any data races.

- Each philosopher should be a thread.
- You should protect the chopsticks state with a mutex for each of them.

## How to use

Run `make`

```sh
./philo [n_philos] [die_time] [eat_time] [sleep_time] (n_eating_times)
```
*Last argument is optional*

Example:

```sh
./philo 4 800 400 400
```

```sh
./philo 8 800 200 200 5
```

##

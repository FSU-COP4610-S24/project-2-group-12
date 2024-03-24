# Kernel Module

This project is an implementation of a elevator kernel module

## Group Number
12

## Group Name
Group 12

## Group Members
- **Ryan Baker**: rb20i@fsu.edu
- **Alexander Kajda**: ak21v@fsu.edu
- **Ian O'Neill**: ico19@fsu.edu
## Division of Labor

### Part 1: System call tracing
- **Assigned to**: Ryan Baker

### Part 2: Timer Kernel Module
- **Assigned to**: Alexander Kajda

### Part 3a: Adding System Calls
- **Assigned to**: Ryan Baker

### Part 3b: Kernel Compilatiomn
- **Assigned to**: Ryan Baker

### Part 3c: Threads
- **Assigned to**: Ryan Baker, Ian O'Neill

### Part 3d: Linked List
- **Assigned to**: Ryan Baker

### Part 3e: Mutexes
- **Assigned to**: Ian O'Neill

### Part 3f: Scheduling 
- **Assigned to**: Ryan Baker

### Part 3f: Write to Proc file
- **Assigned to**: Alexander Kajda, Ian O'Neill

  


## File Listing
```
shell/
│
├── part1/
│ └──empty.c
│ └──empty.trace
| └──part1.c
| └──part1.trace
| └──Makefile
├── part2/
│ ├───── src/
│ | └───── my_timer.c
│ └── Makefile
├── part3/
│ ├── 
│ └── 
├── README.md
└── Makefile
```
## How to Compile & Execute

### Requirements
- **Compiler**: `gcc' and install linux-6.7.9 kernel with added modifications

### Compilation

#### For the Timer Module:

In the part 2 folder run 
```bash
make
```
to create my_timer.ko, and

```
sudo insmod my_timer.ko
```
to insert the timer module into the linux kernel.

#### For the Elevator Module
Now navigate to the part 3 folder
```
cd ../part3
```

Run make again and this time insert the elevator.ko module that was created.

```
sudo insmod elevator.ko
```
### Execution
Use the --start flag on a consumer program that will begin running the elevator.
Use a separate producer file and specify the number of entries (passengers) on the command line.
View the proc file using:
```
cat /proc/elevator
```

Or:

```
watch -n1 cat /proc/elevator
```
To stop the elevator run the same consumer program with a --stop flag.

Unload the modules with:
```
sudo rmmod my_timer.ko
sudo rmmod elevator.ko
```

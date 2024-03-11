#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/syscalls.h>

#define IDLE 0
#define ACTIVE 1
#define OFFLINE 2

#define __NR_START_ELEVATOR 548
#define __NR_ISSUE_REQUEST 549
#define __NR_STOP_ELEVATOR 550
#define MIN_FLOOR 1
#define MAX_FLOOR 5
#define MAX_PASSENGER_TYPE 3
#define MIN_PASSENGER_TYPE 0

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ryan Baker");
MODULE_DESCRIPTION("Module to implement a scheduling algorithm for an elevator system");

struct elevator{
    int state;
    int current_floor;
    int current_load;    
}

static struct elevator *elevator_system;
extern int (*STUB_start_elevator)(void);
extern int (*STUB_issue_request)(int, int, int);
extern int (*STUB_stop_elevator)(void);

int start_elevator(void){
    
    if (elevator_system.state == 1){
        return 1;
    }

    if (!elevator_system){
        elevator_system = kmalloc(sizeof(struct elevator), GFP_KERNEL);
        if (!elevator_system){
            return -ENOMEM;
        }
    }
    
    elevator_system.state = 0;
    elevator_system.current_floor = 1;
    elevator_system.current_load = 0;

    if (elevator_system.state != 0 && elevator_system.current_floor != 1 && elevator_system.current_load !=0){
        return -ERRORNUM;
    }

    return 0;
}

int issue_request(int start_floor, int destination_floor, int type){
	if (start_floor < MIN_FLOOR || start_floor > MAX_FLOOR || destination_floor < MIN_FLOOR || destination_floor > MAX_FLOOR || type < MIN_PASSENGER_TYPE || type > MAX_PASSENGER_TYPE){
        return 1;
    }
    //need to service the request
    return 0;

}

static int __init elevator_init(void){
    printk(KERN_INFO "ELEVATOR MODULE LOADED");
    STUB_start_elevator = start_elevator;
    STUB_issue_request = issue_request;
    return 0;
}

static int __exit elevator_exit(void){
    if(elevator_system){
        kfree(elevator_system);
    }
    printk(KERN_INFO "ELEVATOR MODULE CLOSED");
}


module_init(elevator_init);
module_exit(elevator_exit);


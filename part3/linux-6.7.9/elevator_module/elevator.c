#include<linux/init.h>
#include<linux/module.h>
#include<linux/syscalls.h>

#define IDLE 0
#define ACTIVE 1
#define OFFLINE 2

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ryan Baker");
MODULE_DESCRIPTION("Module to implement a scheduling algorithm for an elevator system");

struct elevator{
    int state;
    int current_floor;
    int current_load;    
}

static struct elevator *elevator_system;

static int __init elevator_init(void){
    printk(KERN_INFO "ELEVATOR MODULE LOADED");
    return 0;
}

static int __exit elevator_exit(void){
    printk(KERN_INFO "ELEVATOR MODULE CLOSED");
}

asmlinkage long sys_start_elevator(void){
    
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
module_init(elevator_init);
module_exit(elevator_exit);


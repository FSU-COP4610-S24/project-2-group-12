#include<linux/init.h>
#include<linux/module.h>

#define IDLE 0
#define ACTIVE 1
#define OFFLINE 2

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ryan Baker");
MODULE_DESCRIPTION("Module to implement a scheduling algorithm for an elevator system");

struct elevator{
    int state;
    int current_floor;
    int state;    
}

static int __init elevator_init(void){
    printk(KERN_INFO "ELEVATOR MODULE LOADED");
    struct elevator elevator_system;
    return 0;
}

static int __exit elevator_exit(void){
    printk(KERN_INFO "ELEVATOR MODULE CLOSED");
}

module_init(elevator_init);
module_exit(elevator_exit);


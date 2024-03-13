#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

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
MODULE_AUTHOR("RYAN BAKER");
MODULE_DESCRIPTION("simple");
MODULE_VERSION("1.0");

struct elevator{
    int state;
    int current_floor;
    int current_load;
};

static struct elevator *elevator_system;
extern int (*STUB_start_elevator)(void);
extern int (*STUB_issue_request)(int, int, int);
extern int (*STUB_stop_elevator)(void);

int start_elevator(void){

    if (elevator_system->state == 1){
        return 1;
    }

    if (!elevator_system){
        elevator_system = kmalloc(sizeof(struct elevator), GFP_KERNEL);
        if (!elevator_system){
            return -ENOMEM;
        }
    }

    elevator_system->state = 0;
    elevator_system->current_floor = 1;
    elevator_system->current_load = 0;

    if (elevator_system->state != 0 && elevator_system->current_floor != 1 && elevator_system->current_load !=0){
        return 1; // supposed to return ERRORNUM here need to update
    }

    return 0;
}
static int __init elevator_init(void){
    printk(KERN_INFO "module loaded");
    STUB_start_elevator = start_elevator;
    return 0;
}

static void __exit elevator_exit(void){
    if(elevator_system){
        kfree(elevator_system);
    }
    printk(KERN_INFO "ELEVATOR MODULE CLOSED");
}

module_init(elevator_init);
module_exit(elevator_exit);

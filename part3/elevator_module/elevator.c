#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>

#define __NR_START_ELEVATOR 548
#define __NR_ISSUE_REQUEST 549
#define __NR_STOP_ELEVATOR 550

#define MIN_FLOOR 1
#define MAX_FLOOR 5
#define MAX_PASSENGER_TYPE 3
#define MIN_PASSENGER_TYPE 0
#define MAX_PASSENGER_COUNT 5
#define MAX_ELEVATOR_WEIGHT 7
#define OFFLINE 0
#define IDLE 1
#define ACTIVE 2
#define UP 3
#define DOWN 4
#define PARTTIMER 0
#define LAWYER 1
#define BOSS 2
#define VISITOR 3


MODULE_LICENSE("GPL");
MODULE_AUTHOR("RYAN BAKER");
MODULE_DESCRIPTION("Kernel elevator system");
MODULE_VERSION("1.0");

struct passenger{
    int weight;
    int type;

    struct list_head list;
};

struct elevator{
    int state;
    int current_floor;
    int current_load;
    int current_weight;

    struct list_head passenger_list;
};

static struct elevator *elevator_system;
extern int (*STUB_start_elevator)(void);
extern int (*STUB_issue_request)(int, int, int);
extern int (*STUB_stop_elevator)(void);

int start_elevator(void){

    if (elevator_system->state == ACTIVE){
        return 1;
    }

    if (!elevator_system){
        elevator_system = kmalloc(sizeof(struct elevator), GFP_KERNEL);
        if (!elevator_system){
            return -ENOMEM;
        }
    }

    elevator_system->state = IDLE;
    elevator_system->current_floor = 1;
    elevator_system->current_load = 0;
    INIT_LIST_HEAD(&elevator_system->passenger_list);

    if (elevator_system->state != IDLE && elevator_system->current_floor != 1 && elevator_system->current_load !=0){
        return 1; // supposed to return ERRORNUM here need to update
    }

    return 0;
}

int issue_request(int start_floor, int destination_floor, int type){
    if (start_floor < MIN_FLOOR || start_floor > MAX_FLOOR || destination_floor < MIN_FLOOR || destination_floor > MAX_FLOOR || type < MIN_PASSENGER_TYPE || type > MAX_PASSENGER_TYPE){
        return 1;
    }

    struct passenger *person;
    person = kmalloc(sizeof(struct passenger), __GFP_RECLAIM);

    if (type == PARTTIMER){
        person->type = PARTTIMER;
        person->weight = 1;
    }
    else if (type == LAWYER){
        person->type = LAWYER;
        person->weight = 1.5;
    }
    else if (type == BOSS){
        person->type = BOSS;
        person->weight = 2;
    }
    else if (type == VISITOR){
        person->type = VISITOR;
        person->weight = 0.5;
    }
    
    list_add_tail(&person->list, &elevator_system->passenger_list);
    elevator_system->current_load += 1;

    if (!elevator_system->current_weight)
    {
        elevator_system->current_weight = 0;
    }
    elevator_system->current_weight += person->weight; //need to update to use doubles instead of ints

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

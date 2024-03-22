#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>



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
#define LOADING 3
#define UNLOADING 4
#define UP 3
#define DOWN 4
#define PARTTIMER 0
#define LAWYER 1
#define BOSS 2
#define VISITOR 3

#define PROC_NAME "elevator"

static struct mutex elevator_mutex;
static struct proc_dir_entry *elevator_entry;
static int direction = IDLE;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RYAN BAKER");
MODULE_DESCRIPTION("Kernel elevator system");
MODULE_VERSION("1.0");

struct passenger{
    int weight;
    int type;
    int source;
    int destination;
    struct list_head list;
};

struct elevator{
    int state;
    int current_floor;
    int current_load;
    int current_weight;
    
    struct list_head waiting_list;
    struct list_head passenger_list;
};

struct thread_parameter{
    int id;
    struct task_struct *kthread;
};

static struct elevator *elevator_system;
static struct thread_parameter *elevator_thread;
extern int (*STUB_start_elevator)(void);
extern int (*STUB_issue_request)(int, int, int);
extern int (*STUB_stop_elevator)(void);
static char passenger_type(int);
static int all_passengers(void);
static int waiting_passengers(int);
static int serviced_passengers(void);
static int all_waiting_passengers(void);

int start_elevator(void){
    if (elevator_system && elevator_system->state == ACTIVE){
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
    INIT_LIST_HEAD(&elevator_system->waiting_list);
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
    
    person->source = start_floor;
    person->destination = destination_floor;
    //adds the passenger to a waiting list of passengers
    list_add_tail(&person->list, &elevator_system->waiting_list);

    return 0;
}

int stop_elevator(void){
    if(list_empty(&elevator_system->passenger_list)){
        elevator_system->state = OFFLINE;
    }

    if (elevator_system->state == OFFLINE){
        return 1;
    }
    return 0;
}
int load_elevator(void){
    struct passenger *passenger_ptr, *next;
    int current_floor = elevator_system->current_floor;

    //check to see if there are passengers in the waiting list that are on current floor
    list_for_each_entry_safe(passenger_ptr, next, &elevator_system->waiting_list, list) {
        if (passenger_ptr->source == current_floor) {
            //move the passenger from the waiting list to the passenger list
            list_del(&passenger_ptr->list);
            list_add_tail(&passenger_ptr->list, &elevator_system->passenger_list);
            elevator_system->current_load++;
            elevator_system->current_weight += passenger_ptr->weight;

            //check if the elevator is at full capacity
            if (elevator_system->current_load >= MAX_PASSENGER_COUNT || elevator_system->current_weight >= MAX_ELEVATOR_WEIGHT) {
                return -1;
            }
        }
    }

    return 0;
}
int unload_elevator(void) {
    struct passenger *passenger_ptr, *next;
    int current_floor = elevator_system->current_floor;

    //check to see if there are passengers on the elevator with a destination of current floor
    list_for_each_entry_safe(passenger_ptr, next, &elevator_system->passenger_list, list) {
        if (passenger_ptr->destination == current_floor) {
            // Remove the passenger from the passenger list
            list_del(&passenger_ptr->list);
            elevator_system->current_load--;
            elevator_system->current_weight -= passenger_ptr->weight;
            kfree(passenger_ptr);
        }
    }

    return 0;
}


int move_elevator(int target_floor){
    if (target_floor > MAX_FLOOR || target_floor < MIN_FLOOR){
        return -1;
    }

    while (elevator_system->current_floor != target_floor){
        if (elevator_system->current_floor < target_floor){
	    direction = UP;
            elevator_system->current_floor++;
            ssleep(2);
        }
        else{
	    direction = DOWN;
            elevator_system->current_floor--;
            ssleep(2);
        }
    }
    return 0;
}

int elevator_loop(void *data) {
    struct thread_parameter *parm = data;
    
    while (!kthread_should_stop()) {
        mutex_lock(&elevator_mutex);
        
        // Check if elevator is active
        if (elevator_system->state == ACTIVE) {
            // Load elevator if there are passengers waiting
            if (elevator_system->state != LOADING && !list_empty(&elevator_system->waiting_list)) {
                elevator_system->state = LOADING;
                load_elevator();
                elevator_system->state = ACTIVE;
            }
            
            // Unload elevator if there are passengers to drop off
            if (elevator_system->state != UNLOADING && !list_empty(&elevator_system->passenger_list)) {
                elevator_system->state = UNLOADING;
                unload_elevator();
                elevator_system->state = ACTIVE;
            }
            
            // Move elevator only if it's not currently loading or unloading
            if (elevator_system->state == ACTIVE && elevator_system->current_load > 0) {
                struct passenger *next_passenger = list_first_entry(&elevator_system->passenger_list, struct passenger, list);
                move_elevator(next_passenger->destination);
            }
        }
        
        mutex_unlock(&elevator_mutex);
        
    }
    
    return 0;
}

void thread_init_parameter(struct thread_parameter *parm){
    static int id = 1;
    parm->id = id;
    parm->kthread = kthread_run(elevator_loop, parm, "Starting thread");
}

static char passenger_type(int type) {
	switch(type) {
		case PARTTIMER:
			return 'P';
		case LAWYER:
			return 'L';
		case BOSS:
			return 'B';
		case VISITOR:
			return 'V';
		default:
			return '?';
	}
}

static int waiting_passengers(int floor) {
	int count = 0;
	struct passenger *passenger_ptr;
	list_for_each_entry(passenger_ptr, &elevator_system->waiting_list, list) {
		if (passenger_ptr->source == floor) {
			count++;
		}
	}
	return count;
}

static int all_passengers() {
	int count = 0;
	struct passenger *passenger_ptr;
	list_for_each_entry(passenger_ptr, &elevator_system->passenger_list, list) {
		count++;
	}
	return count;
}

static int serviced_passengers() {
	int count = 0;
	int current_floor = elevator_system->current_floor;
	struct passenger *passenger_ptr;
	list_for_each_entry(passenger_ptr, &elevator_system->passenger_list, list) {
		if (passenger_ptr->destination == current_floor) {
			count++;
		}
	}
	return count;
}

static int all_waiting_passengers() {
	int count = 0;
	for (int i = MIN_FLOOR; i <= MAX_FLOOR; i++) {
		count += waiting_passengers(i);
	}
	return count;
}


static ssize_t elevator_read(struct file *m, char __user *ubuf, size_t count, loff_t *ppos) {
	char buf[10000];
	int len = 0;
	
	mutex_lock(&elevator_mutex);

	switch(elevator_system->state) {
		case OFFLINE:
			len += sprintf(buf + len, "Elevator state: OFFLINE\n");
			break;
		case IDLE:
			len += sprintf(buf + len, "Elevator state: IDLE\n");
			break;
		case LOADING:
                        len += sprintf(buf + len, "Elevator state: LOADING\n");
                        break;
		case ACTIVE:
			if (direction == UP)
				len += sprintf(buf + len, "Elevator state: UP\n");
			else if (direction == DOWN)
				len += sprintf(buf + len, "Elevator state: DOWN\n");
                        break;
		default:
			len += sprintf(buf + len, "Elevator state: UNKNOWN\n");
	}

	len += sprintf(buf + len, "Current floor: %d\n", elevator_system->current_floor);
	len += sprintf(buf + len, "Current load: %.1d lbs\n", elevator_system->current_weight);
	len += sprintf(buf + len, "Elevator status: ");
	
	struct passenger *passenger_ptr;
	list_for_each_entry(passenger_ptr, &elevator_system->passenger_list, list) {
		len += sprintf(buf + len, "%c%d ", passenger_type(passenger_ptr->type), 
				passenger_ptr->destination);
	}
	len += sprintf(buf + len, "\n\n");

	for (int i = MAX_FLOOR; i >= MIN_FLOOR; i--) {
		len += sprintf(buf + len, "[%c] Floor %d: %d ",
				(elevator_system->current_floor == i ? '*' : ' '),
				i, waiting_passengers(i));
		struct passenger *waiting;
		list_for_each_entry(waiting, &elevator_system->waiting_list, list) {
			if (waiting->source == i) {
				len += sprintf(buf + len, "%c%d ", 
						passenger_type(waiting->type), 
						waiting->destination);
			}
		}
		len += sprintf(buf + len, "\n");
	}

	len += sprintf(buf + len, "\nNumber of passengers: %d\n", all_passengers());
        len += sprintf(buf + len, "Number of passengers waiting: %d\n", 
			all_waiting_passengers());
        len += sprintf(buf + len, "\nNumber of passengers: %d\n", 
			serviced_passengers());

	mutex_unlock(&elevator_mutex);

	return simple_read_from_buffer(ubuf, count, ppos, buf, len);
}

static const struct proc_ops elevator_fops = {
        .proc_read = elevator_read,
};

static int __init elevator_init(void){
    printk(KERN_INFO "module loaded");
    mutex_init(&elevator_mutex);
    STUB_start_elevator = start_elevator;
    STUB_issue_request = issue_request;
    STUB_stop_elevator = stop_elevator;
    elevator_thread = kmalloc(sizeof(struct thread_parameter), GFP_KERNEL);
    elevator_entry = proc_create(PROC_NAME, 0 , NULL, &elevator_fops);
    if(!elevator_thread || !elevator_entry) {
         printk(KERN_ERR "Failed to allocate memory for elevator_thread\n");
         return -ENOMEM;
    }
    thread_init_parameter(elevator_thread);

    return 0;
}

static void __exit elevator_exit(void){
    if(elevator_thread){
        if(elevator_thread->kthread) {
            kthread_stop(elevator_thread->kthread);
        }
        kfree(elevator_thread);
        elevator_thread = NULL;
    }
    printk(KERN_INFO "ELEVATOR MODULE CLOSED");
}



module_init(elevator_init);
module_exit(elevator_exit);

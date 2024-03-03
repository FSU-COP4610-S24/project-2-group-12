#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/timekeeping.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/ktime.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Kajda");
MODULE_DESCRIPTION("A kernel module to track current and elapsed time");
MODULE_VERSION("0.1");

static struct proc_dir_entry *timer_entry;
static struct timespec64 ts_prev;

static ssize_t my_timer_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) {

	struct timespec64 ts_now;
	char buf[256];
	int len = 0;

	ktime_get_real_ts64(&ts_now);

	len = snprintf(buf, sizeof(buf), "Current Time: %lld.%09ld\n", (long long)ts_now.tv_sec, ts_now.tv_nsec);

	struct timespec64 elapsed;
        elapsed = timespec64_sub(ts_now, ts_prev);

	if (ts_prev.tv_sec != 0) {
		len = snprintf(buf, sizeof(buf), "Current Time: %lld.%09ld\nElapsed Time: %lld.%09ld\n", (long long)ts_now.tv_sec, ts_now.tv_nsec, (long long)elapsed.tv_sec, elapsed.tv_nsec);
	}

	ts_prev = ts_now;
	return simple_read_from_buffer(ubuf, count, ppos, buf, len);
}

static const struct proc_ops my_timer_fops = {
	.proc_read = my_timer_read,
};

static int __init my_timer_init(void) {
	timer_entry = proc_create("timer", 0644, NULL, &my_timer_fops);
	if (!timer_entry) {
		pr_err("Failed to create proc entry\n");
		return -ENOMEM;
	}
	pr_info("my_timer module loaded\n");
	return 0;
}

static void __exit my_timer_exit(void) {
	if (timer_entry)
		proc_remove(timer_entry);
	pr_info("my_timer module removed\n");
}

module_init(my_timer_init);
module_exit(my_timer_exit);

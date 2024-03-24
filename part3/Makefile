obj-m += src/elevator.o syscalls.o  # Added syscalls.o to be compiled as a module

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: syscalls.ko

syscalls.ko: syscalls.c  # Compile syscalls.c into a kernel module
    $(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean  # Ensure the clean command cleans up module build artifacts

.PHONY: all clean run

run:
	./test_syscalls  # Assuming test_syscalls is a binary you want to execute

test_syscalls:  # Compile the test_syscalls binary
    gcc -o test_syscalls test-syscalls.c  # Removed the unnecessary inclusion of the header file in the compilation command and corrected the output file name

clean:  # Extend the clean command to also remove the test_syscalls binary
    $(MAKE) -C $(KDIR) M=$(PWD) clean
    rm -f test_syscalls


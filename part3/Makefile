obj-m += src/elevator.o syscalls.o  # Compile elevator.o from src/elevator.c and syscalls.o from syscalls.c

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: syscalls.ko elevator.ko  # Build both syscalls.ko and elevator.ko kernel modules

syscalls.ko: syscalls.c  # Explicit rule for building syscalls.ko, may be unnecessary as it's covered by the default kernel module build process
	$(MAKE) -C $(KDIR) M=$(PWD) modules

elevator.ko:  # Explicit rule for building elevator.ko, also may be unnecessary for the same reason
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:  # Clean command to remove build artifacts
	$(MAKE) -C $(KDIR) M=$(PWD) clean

.PHONY: all clean


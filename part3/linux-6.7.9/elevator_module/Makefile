obj-m += elevator.o
KDIR := /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modles

clean:
	make -C $(KDIR) M=$(PWD) clean

ARCH=arm64
COMPILER=aarch64-linux-gnu-
obj-m :=gpio2.o
KERNELDIR :=~/hdd/DINESH/RPI/linux
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(COMPILER) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) ARCH=$(ARCH) clean

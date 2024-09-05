obj-m := adxl345.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# Remove unsupported floating-point options for aarch64
KBUILD_CFLAGS := $(filter-out -mfloat-abi=hard -mfpu=neon, $(KBUILD_CFLAGS))

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -f *.ko *.o *.bak *.mod* *.order *.symvers


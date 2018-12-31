ifneq ($(KERNELRELEASE),)
	obj-m := SimpleCharDrv.o

else
	KERNDIR ?= /lib/modules/`uname -r`/build
    PWD := `pwd`

default:
	sudo $(MAKE)  -C $(KERNDIR)  M=$(PWD) modules 

clean:
	sudo $(MAKE) -C $(KERNDIR) M=$(PWD) clean

endif



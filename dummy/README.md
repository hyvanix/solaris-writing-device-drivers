# Official Solaris Writing Device Drivers Documentation

GCC is the only thing that's actually required to build the sample driver in Oracle's Device Driver Tutorial.

The `dummy.c` file provides the following:

* Minimalist pseudo-device.
* Writes a message whenever a routine is entered.

### Build the driver:

```terminal
$ gcc -D_KERNEL -m64 -mcmodel=kernel -mno-red-zone -ffreestanding -nodefaultlibs -c dummy.c
$ ld -r -o dummy.ko dummy.o
```

### Copy the driver and the configuration file to /usr/kernel/drv|amd64/drv:

```terminal
$ sudo cp dummy.conf /usr/kernel/drv
$ cp dummy.ko /tmp
$ sudo ln -s /tmp/dummy.ko /usr/kernel/drv/amd64/dummy
```
### Add the driver:

```terminal
$ sudo add_drv dummy
$ dmesg |tail -n 3
Nov 25 10:10:57 omniosce dummy: [ID 513080 kern.notice] NOTICE: Inside _info
Nov 25 10:10:57 omniosce dummy: [ID 874762 kern.notice] NOTICE: Inside _init
Nov 25 10:10:57 omniosce dummy: [ID 678704 kern.notice] NOTICE: Inside dummy_attach
```

### Test and Verify

#### read from driver

```terminal
# cat /devices/pseudo/dummy\@0:0
# dmesg |tail -n 4
Nov 25 10:17:08 omniosce dummy: [ID 136952 kern.notice] NOTICE: Inside dummy_open
Nov 25 10:17:08 omniosce dummy: [ID 891851 kern.notice] NOTICE: Inside dummy_prop_op
Nov 25 10:17:08 omniosce dummy: [ID 709590 kern.notice] NOTICE: Inside dummy_read
Nov 25 10:17:08 omniosce dummy: [ID 550206 kern.notice] NOTICE: Inside dummy_close
```

#### write to driver

```terminal
# echo hello > /devices/pseudo/dummy\@0:0
-bash: echo: write error: Error 0
# dmesg |tail -n 4
Nov 25 10:17:16 omniosce dummy: [ID 136952 kern.notice] NOTICE: Inside dummy_open
Nov 25 10:17:16 omniosce dummy: [ID 891851 kern.notice] NOTICE: Inside dummy_prop_op
Nov 25 10:17:16 omniosce dummy: [ID 672780 kern.notice] NOTICE: Inside dummy_write
Nov 25 10:17:16 omniosce dummy: [ID 550206 kern.notice] NOTICE: Inside dummy_close
```

### Remove the driver:

```terminal
$ sudo rem_drv dummy
```

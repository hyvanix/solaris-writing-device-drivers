# Official Solaris Writing Device Drivers Documentation

## Modifying Data Stored in Kernel Memory
In this third version of the Quote Of The Day driver, the user can write to the data that is stored
in kernel memory. The pseudo device that is created in this section is a pseudo-disk device or
ramdisk device. A ramdisk device simulates a disk device by allocating kernel memory that is
subsequently used as data storage.


### Build the driver:

```terminal
$ gcc -D_KERNEL -m64 -mcmodel=kernel -mno-red-zone -ffreestanding -nodefaultlibs -c qotd_3.c
$ ld -r -o qotd.ko qotd_3.o
```

### Copy the driver and the configuration file to /usr/kernel/drv|amd64/drv:

```terminal
$ sudo cp qotd.conf /usr/kernel/drv
$ cp qotd.ko /tmp
$ sudo ln -s /tmp/qotd.ko /usr/kernel/drv/amd64/qotd
```
### Add the driver:

```terminal
$ sudo add_drv qotd
```

### Test and Verify

#### Confirm the psuedo device wrote message to system log and that the psuedo device is available under `/devices/psuedo/`

```terminal
$ dmesg |tail -n 2
Dec  7 17:54:03 benson pseudo: [ID 129642 kern.info] pseudo-device: qotd0
Dec  7 17:54:03 benson genunix: [ID 936769 kern.info] qotd0 is /pseudo/qotd@0
$ ll /devices/pseudo/qotd*
crw-------   1 root     sys      286,  0 Dec  7 17:54 /devices/pseudo/qotd@0:qotd_3
```

To test the qotd driver, you can use the cat & echo commands to access the device file for reading and writing:

```terminal
$ sudo cat /devices/pseudo/qotd@0:qotd_3
On the whole, I'd rather be in Philadelphia. - W. C. Fields  
```

```terninal
# echo "A life is not important except in the impact it has on others. - Jackie Robinson" >> /devices/pseudo/qotd@0:qotd_3
# cat /devices/pseudo/qotd@0:qotd_3
A life is not important except in the impact it has on others. - Jackie Robinson
```


### Remove the driver:

```terminal
$ sudo rem_drv qotd
Device busy
Cannot unload module: qotd
Will be unloaded upon reboot.
```

As you can see, the driver was not removed as we had anticipated. This is because we need to reset the ramdisk that we have created.

In order to do this, we neec to compiler the helper program and reset the driver, as follows:

```terminal
$ gcc -o qotdctl qotdctl.c
$ ./qodctl -d /devices/pseudo/qotd@0:qotd_3 -r
$ sudo rem_drv qotd
```

Also remove the symbolic link if you wish to continue with the next example:

```terminal
$ sudo rm /usr/kernel/drv/qotd
```


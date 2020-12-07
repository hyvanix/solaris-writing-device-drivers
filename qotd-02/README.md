# Official Solaris Writing Device Drivers Documentation

## Displaying Data on Demand
The sample code in this section creates a pseudo device that is controlled by the driver. The driver stores data in the device and makes the data available when the user accesses the device for reading.

### Build the driver:

```terminal
$ gcc -D_KERNEL -m64 -mcmodel=kernel -mno-red-zone -ffreestanding -nodefaultlibs -c qotd_2.c
$ ld -r -o qotd.ko qotd_2.o
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
Dec  4 07:31:46 benson pseudo: [ID 129642 kern.info] pseudo-device: qotd0
Dec  4 07:31:46 benson genunix: [ID 936769 kern.info] qotd0 is /pseudo/qotd@0
$ ll /devices/pseudo/qotd*
crw-------   1 root     sys      286,  0 Dec  4 07:31 /devices/pseudo/qotd@0:qotd

/devices/pseudo/qotd@0:
total 8
drwxr-xr-x   2 root     sys            2 Dec  4 07:35 .
drwxr-xr-x 106 root     sys          106 Dec  4 07:35 ..
```
To test the qotd driver, you can use the more command to access the device file for reading:

```terminal
philip@benson:$ sudo more -f /devices/pseudo/qotd@0:qotd
You can't have everything. Where would you put it? - Steven Wright
You can't have everything. Where would you put it? - Steven Wright
You can't have everything. Where would you put it? - Steven Wright
You can't have everything. Where would you put it? - Steven Wright
You can't have everything. Where would you put it? - Steven Wright
You can't have everything. Where would you put it? - Steven Wright
...
--More--(0%)
```

### Remove the driver:

```terminal
$ sudo rem_drv qotd
```

Also remove the symbolic link if you wish to continue with the next example:

```terminal
$ sudo rm /usr/kernel/drv/qotd
```


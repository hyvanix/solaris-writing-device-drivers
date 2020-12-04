# Official Solaris Writing Device Drivers Documentation

## Displaying Data Stored in Kernel Memory

The pseudo device driver presented in this section writes a constant string to a system log when the driver is loaded.

### Build the driver:

```terminal
$ gcc -D_KERNEL -m64 -mcmodel=kernel -mno-red-zone -ffreestanding -nodefaultlibs -c qotd_1.c
$ ld -r -o qotd.ko qotd_1.o
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

#### Confirm the psuedo device wrote message to system log

```terminal
$ dmesg |tail -n 1
Dec  4 19:57:20 omniosce qotd: [ID 197678 kern.notice] QOTD: Be careful about reading health books. You may die from a misprint. - Mark Twain
```

### Remove the driver:

```terminal
$ sudo rem_drv qotd
```

Also remove the symbolic link if you wish to continue with the next example:

```terminal
$ sudo rm /usr/kernel/drv/qotd
```

Notes on using rEFInd
=============================================

1. Create a disk image
   dd if=/dev/zero of=disk.img bs=1M count=32
2. Partition it (either legacy or GPT style partitions work)
    - Create one fat16 partition, labeled BOOT, flags boot, lba.
    - Create one ext4 partition, type Linux, for the root fs.
3. Setup loop device and loop partitions
   sudo losetup -f disk.img
   sudo partx -a /dev/loop0
4. Prepare the partition contents
   sudo mkfs.fat -F 16 -L BOOT /dev/loop0p1
   sudo mkfs.ext4 -L root /dev/loop0p2
   sudo mount /dev/loop0p1 /mnt
   sudo tar -C /mnt -xf output/images/refind.tar
   sudo umount /mnt
   sudo mount /dev/loop0p2 /mnt
   sudo tar -C /mnt -xf output/images/rootfs.tar
   sudo umount /mnt
5. Cleanup loop device
   sudo partx -d /dev/loop0
   sudo losetup -d /dev/loop0
6. Your disk.img is ready!

Configuring rEFInd
=============================================

rEFInd will search for refind_linux.conf files.

Place a refind_linux.conf file in the same location as your initrd:

"Boot Buildroot"  "initrd=/boot/initrd-%v root=/dev/initrd ro earlyprintk"

rEFInd will find all files with prefix initrd- and display options on screen,
defaulting to the most recent build version.

Example contents of /boot:

bzImage-buildroot-2022.05.1-104-1
initrd-buildroot-2022.05.1-104-1
refind_linux.conf

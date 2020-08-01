NVIDIA Jetson TX2

Intro
=====

This configuration adds support for the Jetson TX2 devkit. It should be
compatible with the other Jetson-series boards as well, but has not yet been
tested. (Other boards include the tx2i, nano...)

Building
========

Configure Buildroot
-------------------

For Jetson TX2:

  $ make jetsontx2_defconfig

Build the rootfs
----------------

You may now build your rootfs with:

  $ make


Flashing
========

Once the build process is finished you will have the target binaries in the
output/images directory, with a symlink to linux4tegra.

Flashing to the internal eMMC is done by booting to the official recovery mode,
and flashing the system from there. The default factory-flashed TX2 is suitable.

There are a lot of cases where the TX2 will not boot properly unless all of the
peripherals are fully disconnected, power is disconnected, everything fully
resets, and then the power is introduced back again.

The recovery mode of the Jetson is used to flash. Entering recovery:

 - Start with the machine powered off + fully unplugged.
 - Plug in the device to power, and connect a HDMI display.
 - Connect a micro-USB cable from the host PC to the target board.
 - Power on the device by holding the start button until the red light is lit.
 - Hold down the RST button and REC button simultaneously.
 - Release the RST button while holding down the REC button.
 - Wait a few seconds, then release the REC button.

To flash over USB:

```
cd output/images/linux4tegra
sudo bash ./flash.sh \
     -I ../rootfs.ext2 \
     -K ../Image \
     -L ../u-boot-dtb.bin \
     -C "ramdisk_size=100000 net.ifnames=0 elevator=deadline" \
     -d ../tegra186-quill-p3310-1000-c03-00-base.dtb \
     jetson-tx2-devkit mmcblk0p1
```

This will run the `flash.sh` script from L4T, and will setup the kernel, u-boot,
persist + boot-up partition mmcblk0p1. This may overwrite your existing work so
use it for initial setup only.

## Bootup Process

The TX2 and recent boards boot from the internal eMMC, at mmcblk0p1. The Jetson
Nano can boot to a SD card.

A "secure boot" process is used, with multiple bootloaders:

 - BootROM -> MB1 (TrustZone)
 - MB2/BPMP -> (Non-Trustzone)
 - Cboot (uses Little Kernel)
 - Uboot
 - Kernel
 
Uboot is flashed to the mmcblk0p1 emmc partition.

Cboot could be compiled from source, and the source is available from the
official sources, however, we do not (yet) compile cboot.


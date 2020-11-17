NVIDIA Jetson Nano

Intro
=====

This configuration adds support for the Jetson Nano devkit.

Building
========

Configure Buildroot
-------------------

For Jetson Nano:

  $ make jetsonnano_defconfig

Build the rootfs
----------------

You may now build your rootfs with:

  $ make


Flashing
========

Once the build process is finished you will have the target binaries in the
output/images directory with a copy of linux4tegra.

To format your SD card with the required partition layout, use the
"format-sd.sh" script located under board/jetson/nano/format-sd.sh:

  sudo \
    NVIDIA_SD=/dev/sdX \
    PATH=$(pwd)/output/host/sbin:$PATH \
    bash board/jetson/nano/format-sd.sh ./output/images

This will also flash the ext4 rootfs image to the SD card.

Bootup Process
==============

The Jetson Nano can boot to a SD card.

A "secure boot" process is used, with multiple bootloaders:

 - BootROM -> MB1 (TrustZone)
 - MB2/BPMP -> (Non-Trustzone)
 - Cboot (uses Little Kernel)
 - Uboot
 - Kernel
 
Cboot could be compiled from source, and the source is available from the
official sources, however, we do not (yet) compile cboot.


#!/bin/bash
set -eo pipefail

# NOTE: The following copyright applies to linux4tegra and associated tools:

# Copyright (c) 2019-2020, NVIDIA Corporation.  All Rights Reserved.
#
# NVIDIA Corporation and its licensors retain all intellectual property
# and proprietary rights in and to this software, related documentation
# and any modifications thereto.  Any use, reproduction, disclosure or
# distribution of this software and related documentation without an express
# license agreement from NVIDIA Corporation is strictly prohibited.

if [ $EUID != 0 ]; then
  echo "This script requires root."
fi

if [ -z "$NVIDIA_SD" ]; then
    echo "Please set NVIDIA_SD and try again."
    exit 1
fi

if [ ! -b "$NVIDIA_SD" ]; then
    echo "$NVIDIA_SD is not a block device or doesn't exist."
    exit 1
fi

IMAGES_DIR=$1
if [ -z $IMAGES_DIR ]; then
    echo "usage: $0 path/to/images/dir"
    exit 1
fi

uimg_path=$IMAGES_DIR/Image
if [ ! -f "$uimg_path" ]; then
  echo "Image not found, make sure Buildroot is done compiling."
  exit 1
fi

l4t_tools_path=$IMAGES_DIR/linux4tegra/tools
if [ ! -d $l4t_tools_path ]; then
    echo "linux4tegra tools not found, ensure buildroot is done compiling."
    exit 1
fi

# jetson-nano
boardid="3448"
target="jetson-nano-qspi-sd"
storage="sdcard"
rev="300" # from 100, 200, 300
chipid="0x21"

l4t_dir=${IMAGES_DIR}/linux4tegra
rootfs_img=$IMAGES_DIR/rootfs.ext2

# TODO: dynamic rootfs size: the following /almost/ works:
#rootfs_size=$(du -ms ${rootfs_img} | awk '{print $1}')
#rootfs_size=$((rootfs_size + (rootfs_size / 10)))

rootfs_size=2048

echo "creating signed images"
pushd ${l4t_dir}
export BOARDID="${boardid}"
export FAB="${rev}"

${l4t_dir}/flash.sh \
          --no-flash \
          --sign \
          --no-systemimg \
          -x ${chipid} \
          -B ${boardid} \
          -S "${rootfs_size}MiB" \
          -I $IMAGES_DIR/rootfs.ext2 \
          -K $IMAGES_DIR/u-boot-dtb.bin \
          -d $IMAGES_DIR/tegra210-p3448-0000-p3449-0000-b00.dtb \
          "${target}" "mmcblk0p1"
popd

bootloader_dir=${l4t_dir}/bootloader
if [ ! -f "${bootloader_dir}/flashcmd.txt" ]; then
		echo "ERROR: ${bootloader_dir}/flashcmd.txt not found"
		exit 1
fi

signed_image_dir=${bootloader_dir}/signed
if [ ! -d "${signed_image_dir}" ]; then
		echo "ERROR: ${signed_image_dir} not found"
		exit 1
fi

chipid=$(sed -nr 's/.*chip ([^ ]*).*/\1/p' "${bootloader_dir}/flashcmd.txt")
if [ "${chipid}" = "0x21" ]; then
		signed_cfg="flash.xml"
else
		signed_cfg="flash.xml.tmp"
fi

if [ ! -f "${signed_image_dir}/${signed_cfg}" ]; then
		echo "ERROR: ${signed_image_dir}/${signed_cfg} not found"
		exit 1
fi

echo "create partitions"
partitions=($(${l4t_tools_path}/nvptparser.py "${signed_image_dir}/${signed_cfg}" "${storage}"))
part_type=8300 # Linux Filesystem

sgdisk -og "${NVIDIA_SD}"
for part in "${partitions[@]}"; do
		eval "${part}"
		if [ "${part_name}" = "master_boot_record" ]; then
			  continue
		fi
		part_size=$((${part_size} / 512)) # convert to sectors
		sgdisk -n "${part_num}":0:+"${part_size}" \
			     -c "${part_num}":"${part_name}" \
			     -t "${part_num}":"${part_type}" "${NVIDIA_SD}"
done

PARTPROBE=$IMAGES_DIR/../sbin/partprobe
$PARTPROBE ${NVIDIA_SD} || true
sleep 1
if $PARTPROBE ${NVIDIA_SD}; then
    # wait for partitions to settle
    sleep 1
fi

echo "write partitions"
for part in "${partitions[@]}"; do
		eval "${part}"
		target_file=""
		if [ "${part_name}" = "APP" ]; then
			  target_file="${IMAGES_DIR}/rootfs.ext2" # Buildroot target system.
		elif [ -e "${signed_image_dir}/${part_file}" ]; then
			  target_file="${signed_image_dir}/${part_file}"
		elif [ -e "${bootloader_dir}/${part_file}" ]; then
			  target_file="${bootloader_dir}/${part_file}"
		fi

		echo "writing partition ${part_name}"
		if [ "${part_name}" = "master_boot_record" ]; then
			  echo "writing ${part_file}"
			  dd conv=notrunc conv=fsync if="${signed_image_dir}/${part_file}" of="${NVIDIA_SD}" bs="${part_size}" count=1
			  continue
		fi

		if [ "${target_file}" != "" ] && [ "${part_file}" != "" ]; then
			  echo "writing ${target_file}"
        target_part=${NVIDIA_SD}p${part_num}
        if [ ! -b ${target_part} ]; then
            target_part=${NVIDIA_SD}${part_num}
        fi
        if [ ! -b ${target_part} ]; then
            echo "Partition block device ${target_part} or ${NVIDIA_SD}p${part_num} does not exist!"
            exit 1
        fi
			  sudo dd conv=fsync if="${target_file}" of="${target_part}"
		fi
done

echo "Successfully flashed $NVIDIA_SD"


################################################################################
#
# libguestfs
#
################################################################################

LIBGUESTFS_VERSION = 1.48.1
LIBGUESTFS_SOURCE = libguestfs-$(LIBGUESTFS_VERSION).tar.gz
LIBGUESTFS_SITE = https://download.libguestfs.org/1.48-stable
LIBGUESTFS_INSTALL_STAGING = YES
LIBGUESTFS_LICENSE = GPL-2.0 (program), LGPL-2.0+ (library)
LIBGUESTFS_LICENSE_FILES = COPYING COPYING.LIB
LIBGUESTFS_CPE_ID_VENDOR = libguestfs
LIBGUESTFS_CPE_ID_PRODUCT = libguestfs

$(eval $(host-autotools-package))

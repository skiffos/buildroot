################################################################################
#
# embiggen-disk
#
################################################################################

EMBIGGEN_DISK_VERSION = c554fc1c93a4004ce0b6a3f69b0dabe0481a2308
EMBIGGEN_DISK_SITE = $(call github,bradfitz,embiggen-disk,$(EMBIGGEN_DISK_VERSION))
EMBIGGEN_DISK_LICENSE = Apache-2.0
EMBIGGEN_DISK_LICENSE_FILES = LICENSE

$(eval $(golang-package))

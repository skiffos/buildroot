################################################################################
#
# embiggen-disk
#
################################################################################

EMBIGGEN_DISK_VERSION = v20220519
EMBIGGEN_DISK_SITE = $(call github,skiffos,embiggen-disk,$(EMBIGGEN_DISK_VERSION))
EMBIGGEN_DISK_LICENSE = Apache-2.0
EMBIGGEN_DISK_LICENSE_FILES = LICENSE

EMBIGGEN_DISK_GOMOD = github.com/bradfitz/embiggen-disk

$(eval $(golang-package))

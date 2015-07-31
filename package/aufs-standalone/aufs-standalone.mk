################################################################################
#
# aufs-standalone
#
# patches for the linux kernel, used by the extension.
#
################################################################################

# linux-headers
AUFS_STANDALONE_VERSION = aufs$(call qstrip,$(BR2_PACKAGE_AUFS_STANDALONE_VERSION))
ifeq ($(BR2_PACKAGE_AUFS_STANDALONE_3X),y)
AUFS_STANDALONE_MAJOR_VERSION = aufs3
endif
ifeq ($(BR2_PACKAGE_AUFS_STANDALONE_4X),y)
AUFS_STANDALONE_MAJOR_VERSION = aufs4
endif
ifeq ($(BR2_PACKAGE_AUFS_STANDALONE_3X),y)
AUFS_STANDALONE_SITE = git://git.code.sf.net/p/aufs/aufs3-standalone
endif
ifeq ($(BR2_PACKAGE_AUFS_STANDALONE_4X),y)
AUFS_STANDALONE_SITE = $(call github,sfjro,aufs4-standalone,$(AUFS_STANDALONE_VERSION))
endif
AUFS_STANDALONE_LICENSE = GNU
AUFS_STANDALONE_LICENSE_FILES = COPYING

$(eval $(generic-package))

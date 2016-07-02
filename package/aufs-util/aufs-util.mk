################################################################################
#
# aufs-util
#
################################################################################

# linux-headers
AUFS_UTIL_VERSION = aufs$(call qstrip,$(BR2_PACKAGE_AUFS_UTIL_VERSION))
AUFS_UTIL_SITE = git://git.code.sf.net/p/aufs/aufs-util
AUFS_UTIL_DEPENDENCIES = linux
AUFS_UTIL_LICENSE = GNU
AUFS_UTIL_LICENSE_FILES = COPYING

# Slight hack for a bug with aufsmvdown
# Remove user setting from install command
define AUFS_UTIL_CONFIGURE_CMDS
	$(SED) 's/\.a\[/\.stbr\[/g' $(@D)/aumvdown.c
	$(SED) 's/\-o root \-g root //g' $(@D)/Makefile
endef

define AUFS_UTIL_BUILD_CMDS
	$(MAKE) -C $(LINUX_BUILDDIR) headers_install
	$(HOSTCC_NOCCACHE) -I $(LINUX_BUILDDIR)/usr/include/ $(@D)/ver.c -o $(@D)/ver
	$(HOSTCC_NOCCACHE) -I $(LINUX_BUILDDIR)/usr/include/ \
		-I $(@D)/libau \
		$(@D)/c2tmac.c -o $(@D)/c2tmac
	$(HOSTCC_NOCCACHE) -I $(LINUX_BUILDDIR)/usr/include/ \
		$(@D)/c2sh.c -o $(@D)/c2sh
	$(MAKE) -C $(@D) CPPFLAGS="-I $(LINUX_BUILDDIR)/usr/include/" HOSTCC="$(HOSTCC_NOCCACHE)" CC="$(TARGET_CC)" INSTALL="$(INSTALL)" all
endef

define AUFS_UTIL_INSTALL_TARGET_CMDS
	$(MAKE) -C $(@D) INSTALL="$(INSTALL)" DESTDIR="$(TARGET_DIR)" install
endef

$(eval $(generic-package))

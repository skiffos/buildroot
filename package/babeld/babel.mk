################################################################################
#
# babeld
#
################################################################################

BABELD_VERSION = 1.7.1
BABELD_SITE = https://www.irif.univ-paris-diderot.fr/~jch/software/files
BABELD_SOURCE = babeld-$(BABELD_VERSION).tar.gz
BABELD_LICENSE = as-is
BABELD_LICENSE_FILES = LICENSE

define BABELD_BUILD_CMDS
	$(MAKE) -C $(@D) CC="$(TARGET_CC)" CFLAGS="$(TARGET_CFLAGS)" LDFLAGS="$(TARGET_LDFLAGS)"
endef

define BABELD_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/babeld $(TARGET_DIR)/usr/bin/babeld
endef

$(eval $(generic-package))

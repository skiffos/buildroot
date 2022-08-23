################################################################################
#
# distrobox
#
################################################################################

DISTROBOX_VERSION = 1.3.1
DISTROBOX_SITE = $(call github,89luca89,distrobox,$(DISTROBOX_VERSION))
DISTROBOX_LICENSE = GPL-3.0+
DISTROBOX_LICENSE_FILES = COPYING.md

define DISTROBOX_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/distrobox* $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))

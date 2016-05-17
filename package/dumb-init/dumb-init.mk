################################################################################
#
# dumb-init
#
################################################################################

DUMB_INIT_VERSION = v1.2.0
DUMB_INIT_SITE = $(call github,Yelp,dumb-init,$(DUMB_INIT_VERSION))

DUMB_INIT_LICENSE = MIT
DUMB_INIT_LICENSE_FILES = LICENSE
DUMB_INIT_CFLAGS += -static

define DUMB_INIT_BUILD_CMDS
	$(TARGET_CC) \
		$(DUMB_INIT_CFLAGS) \
		-o $(@D)/dumb-init $(@D)/dumb-init.c
endef

define DUMB_INIT_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/dumb-init $(TARGET_DIR)/usr/bin/dumb-init
endef

$(eval $(generic-package))

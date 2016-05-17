################################################################################
#
# dumb-init
#
################################################################################

DUMB_INIT_VERSION = v1.2.0
DUMB_INIT_SITE = https://github.com/Yelp/dumb-init/archive
DUMB_INIT_SOURCE = $(DUMB_INIT_VERSION).tar.gz
DUMB_INIT_LICENSE = MIT
DUMB_INIT_LICENSE_FILES = LICENSE

define DUMB_INIT_BUILD_CMDS
	$(TARGET_CC) \
		-o $(@D)/dumb-init $(@D)/dumb-init.c
endef

define DUMB_INIT_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/dumb-init $(TARGET_DIR)/usr/bin/dumb-init
endef

$(eval $(generic-package))

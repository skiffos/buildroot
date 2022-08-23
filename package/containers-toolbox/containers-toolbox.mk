################################################################################
#
# containers-toolbox
#
################################################################################

# https://github.com/containers/toolbox/issues/1089
# CONTAINERS_TOOLBOX_VERSION = afb002c90cef42958943736e95cd85323e357e97
# CONTAINERS_TOOLBOX_SITE = $(call github,containers,toolbox,$(CONTAINERS_TOOLBOX_VERSION))

CONTAINERS_TOOLBOX_VERSION = c0104586773c197a99592752a0e62a6ab902faad
CONTAINERS_TOOLBOX_SITE = $(call github,skiffos,containers-toolbox,$(CONTAINERS_TOOLBOX_VERSION))
CONTAINERS_TOOLBOX_GOMOD = github.com/containers/toolbox
CONTAINERS_TOOLBOX_LICENSE = Apache-2.0
CONTAINERS_TOOLBOX_LICENSE_FILES = COPYING

CONTAINERS_TOOLBOX_LDFLAGS = \
	-X $(CONTAINERS_TOOLBOX_GOMOD)/pkg/version.currentVersion=$(CONTAINERS_TOOLBOX_VERSION)

define CONTAINERS_TOOLBOX_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/bin/containers-toolbox \
		$(TARGET_DIR)/usr/bin/toolbox
endef

define CONTAINERS_TOOLBOX_INSTALL_CFG_FILES
	$(INSTALL) -D -m 0755 $(@D)/data/config/toolbox.conf \
		$(TARGET_DIR)/etc/containers/toolbox.conf
	$(INSTALL) -D -m 0755 $(@D)/data/tmpfiles.d/toolbox.conf \
		$(TARGET_DIR)/etc/tmpfiles.d/toolbox.conf
endef
CONTAINERS_TOOLBOX_POST_INSTALL_TARGET_HOOKS += CONTAINERS_TOOLBOX_INSTALL_CFG_FILES

$(eval $(golang-package))

################################################################################
#
# meson-tools
#
################################################################################

MESON_TOOLS_VERSION = v0.1
MESON_TOOLS_SITE = $(call github,afaerber,meson-tools,$(MESON_TOOLS_VERSION))
MESON_TOOLS_LICENSE = GPL-2.0+
MESON_TOOLS_LICENSE_FILES = COPYING
HOST_MESON_TOOLS_DEPENDENCIES = host-openssl

define HOST_MESON_TOOLS_BUILD_CMDS
	$(HOST_MAKE_ENV) $(MAKE) CC="$(HOSTCC)" \
		CFLAGS="$(HOST_CFLAGS)" LDFLAGS="$(HOST_LDFLAGS) -lcrypto" \
		-C $(@D) all
endef

define HOST_MESON_TOOLS_INSTALL_CMDS
	$(INSTALL) -m 0755 -D $(@D)/amlbootsig $(HOST_DIR)/bin/amlbootsig
	$(INSTALL) -m 0755 -D $(@D)/amlinfo $(HOST_DIR)/bin/amlinfo
	$(INSTALL) -m 0755 -D $(@D)/unamlbootsig $(HOST_DIR)/bin/unamlbootsig
endef

$(eval $(host-generic-package))

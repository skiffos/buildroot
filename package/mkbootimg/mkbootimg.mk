################################################################################
#
# mkbootimg
#
################################################################################

MKBOOTIMG_VERSION = d4a2677828fe9b60117af8996dcf1dea85d6b431
MKBOOTIMG_SITE = $(call github,osm0sis,mkbootimg,$(MKBOOTIMG_VERSION))

MKBOOTIMG_LICENSE = BSD-3-Clause
MKBOOTIMG_LICENSE_FILES = NOTICE

HOST_MKBOOTIMG_TARGETS = mkbootimg unpackbootimg

define HOST_MKBOOTIMG_BUILD_CMDS
	$(foreach t,$(HOST_MKBOOTIMG_TARGETS),\
		$(HOST_MAKE_ENV) $(HOST_CONFIGURE_OPTS) $(MAKE) SRCDIR=$(@D) \
			-C $(@D) $(t))
endef

define HOST_MKBOOTIMG_INSTALL_CMDS
	$(foreach t,$(HOST_MKBOOTIMG_TARGETS),\
		$(INSTALL) -D -m 0755 $(@D)/$(t) $(HOST_DIR)/bin/$(notdir $(t))$(sep))
endef

$(eval $(host-generic-package))

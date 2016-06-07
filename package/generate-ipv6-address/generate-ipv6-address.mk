################################################################################
#
# generate-ipv6-address
#
################################################################################

GENERATE_IPV6_ADDRESS_VERSION = 0.1
GENERATE_IPV6_ADDRESS_SITE = https://www.irif.univ-paris-diderot.fr/~jch/software/files
GENERATE_IPV6_ADDRESS_SOURCE = generate-ipv6-address-$(GENERATE_IPV6_ADDRESS_VERSION).tar.gz
GENERATE_IPV6_ADDRESS_LICENSE = MIT

define GENERATE_IPV6_ADDRESS_BUILD_CMDS
	$(MAKE) -C $(@D) CC="$(TARGET_CC)" CFLAGS="$(TARGET_CFLAGS)" LDFLAGS="$(TARGET_LDFLAGS)"
endef

define GENERATE_IPV6_ADDRESS_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/generate-ipv6-address $(TARGET_DIR)/usr/bin/generate-ipv6-address
endef

$(eval $(generic-package))

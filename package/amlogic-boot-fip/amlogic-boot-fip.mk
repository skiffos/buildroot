################################################################################
#
# amlogic-boot-fip
#
################################################################################

AMLOGIC_BOOT_FIP_VERSION = e96b6a694380ff07d5a9e4be644ffe254bd18512
AMLOGIC_BOOT_FIP_SITE = $(call github,LibreELEC,amlogic-boot-fip,$(AMLOGIC_BOOT_FIP_VERSION))
AMLOGIC_BOOT_FIP_LICENSE = PROPRIETARY
AMLOGIC_BOOT_FIP_LICENSE_FILES = LICENSE
AMLOGIC_BOOT_FIP_REDISTRIBUTE = NO

AMLOGIC_BOOT_FIP_INSTALL_DIR = $(BINARIES_DIR)/amlogic-boot-fip
AMLOGIC_BOOT_FIP_DEVICE = $(call qstrip,$(BR2_PACKAGE_HOST_AMLOGIC_BOOT_FIP_DEVICE))

define HOST_AMLOGIC_BOOT_FIP_INSTALL_CMDS
	cp -dpfr $(@D)/$(AMLOGIC_BOOT_FIP_DEVICE)/. $(AMLOGIC_BOOT_FIP_INSTALL_DIR)/
endef

# check for empty device string when we're building
ifeq ($(BR2_PACKAGE_HOST_AMLOGIC_BOOT_FIP)$(BR_BUILDING),yy)
ifeq ($(AMLOGIC_BOOT_FIP_DEVICE),)
$(error No device specified for amlogic-boot-fip, please check your BR2_PACKAGE_HOST_AMLOGIC_BOOT_FIP_DEVICE setting)
endif
endif

$(eval $(host-generic-package))

################################################################################
#
# rtl8821cu
#
################################################################################

RTL8821CU_VERSION = 14798a1f917383acef2d8b3f7b40acaa64b5f5ef
RTL8821CU_SITE = $(call github,morrownr,8821cu-20210118,$(RTL8821CU_VERSION))
RTL8821CU_LICENSE = GPL-2.0
RTL8821CU_LICENSE_FILES = LICENSE

RTL8821CU_MODULE_MAKE_OPTS = \
	CONFIG_RTL8821CU=m \
	KVER=$(LINUX_VERSION_PROBED) \
	USER_EXTRA_CFLAGS="-DCONFIG_$(call qstrip,$(BR2_ENDIAN))_ENDIAN \
		-DCONFIG_IOCTL_CFG80211 -DRTW_USE_CFG80211_STA_EVENT"

$(eval $(kernel-module))
$(eval $(generic-package))

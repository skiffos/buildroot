################################################################################
#
# refind
#
################################################################################

REFIND_VERSION = 0.13.3.1
REFIND_SITE = http://downloads.sourceforge.net/project/refind/$(REFIND_VERSION)
REFIND_SOURCE = refind-src-$(REFIND_VERSION).tar.gz
REFIND_LICENSE = GPL-3.0+, GFDL-1.3+ (docs)
REFIND_LICENSE_FILES = COPYING.txt LICENSE.txt docs/refind/FDL-1.3.txt
REFIND_DEPENDENCIES = gnu-efi
REFIND_INSTALL_IMAGES = YES

REFIND_TARGET = all_gnuefi
REFIND_EFI_ARGS = \
	EFICRT0=$(STAGING_DIR)/usr/lib \
	EFIINC=$(STAGING_DIR)/usr/include/efi \
	EFILIB=$(STAGING_DIR)/usr/lib \
	GNUEFILIB=$(STAGING_DIR)/usr/lib \
	LIBDIR=$(STAGING_DIR)/usr/lib \
	LIBEFI=$(STAGING_DIR)/usr/lib/libefi.a

ifeq ($(BR2_x86_64),y)
REFIND_PLATFORM = x64
else ifeq ($(BR2_aarch64),y)
REFIND_PLATFORM = aa64
else
REFIND_PLATFORM = ia32
endif

REFIND_INSTALL_ARGS = \
		OSTYPE="linux" \
		Platform="$(REFIND_PLATFORM)" \
		InstallDir="$(BINARIES_DIR)/refind" \
		RootDir="$(BINARIES_DIR)/refind"

define REFIND_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE1) \
		CC="$(TARGET_CC)" \
		LD="$(TARGET_LD)" \
		OBJCOPY="$(TARGET_OBJCOPY)" \
		AS="$(TARGET_AS)" \
		PYTHON=$(HOST_DIR)/bin/python3 \
		$(REFIND_EFI_ARGS) -C $(@D) $(REFIND_TARGET)
endef

define REFIND_INSTALL_IMAGES_CMDS
	cd $(@D) && $(REFIND_INSTALL_ARGS) ./refind-install
endef

$(eval $(generic-package))

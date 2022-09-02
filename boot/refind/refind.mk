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
REFIND_ARCH = x86_64
REFIND_PLATFORM = x64
else ifeq ($(BR2_aarch64),y)
REFIND_ARCH = aarch64
REFIND_PLATFORM = aa64
else
REFIND_ARCH = ia32
REFIND_PLATFORM = ia32
endif

REFIND_BINARIES_DIR = $(BINARIES_DIR)/refind
REFIND_INSTALL_ARGS = \
		InstallDir="$(REFIND_BINARIES_DIR)" \
		OSTYPE="linux" \
		Platform="$(REFIND_PLATFORM)" \
		RootDir="$(REFIND_BINARIES_DIR)"

define REFIND_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE1) \
		ARCH="$(REFIND_ARCH)" \
		AS="$(TARGET_AS)" \
		CC="$(TARGET_CC)" \
		LD="$(TARGET_LD)" \
		MAKEWITH="GNUEFI" \
		OBJCOPY="$(TARGET_OBJCOPY)" \
		PYTHON=$(HOST_DIR)/bin/python3 \
		RANLIB="$(TARGET_RANLIB)" \
		$(REFIND_EFI_ARGS) -C $(@D) $(REFIND_TARGET)
endef

define REFIND_INSTALL_IMAGES_CMDS
	if [ -d $(REFIND_BINARIES_DIR) ]; then \
		rm -rf $(REFIND_BINARIES_DIR); \
	fi
	cd $(@D) && $(REFIND_INSTALL_ARGS) ./refind-install --yes --alldrivers
	mv $(REFIND_BINARIES_DIR)/EFI/refind/ $(REFIND_BINARIES_DIR)/EFI/BOOT/
	mv $(REFIND_BINARIES_DIR)/EFI/BOOT/refind_$(REFIND_PLATFORM).efi \
		$(REFIND_BINARIES_DIR)/EFI/BOOT/boot$(REFIND_PLATFORM).efi
	echo "boot$(REFIND_PLATFORM).efi" > $(REFIND_BINARIES_DIR)/startup.nsh
endef

$(eval $(generic-package))

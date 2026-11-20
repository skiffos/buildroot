################################################################################
#
# clover
#
################################################################################

CLOVER_VERSION = 4435598401a0e9fafb9739a7e6e097adbb0e3c1a
CLOVER_SOURCE_DATE_EPOCH = 1786385379
CLOVER_SITE = $(call github,CloverHackyColor,CloverBootloader,$(CLOVER_VERSION))
CLOVER_OPENCORPKG_VERSION = 3c845217937d8522030db95183b5d0948b70bd32
CLOVER_EXTRA_DOWNLOADS = https://github.com/acidanthera/OpenCorePkg/archive/$(CLOVER_OPENCORPKG_VERSION)/OpenCorePkg-$(CLOVER_OPENCORPKG_VERSION).tar.gz
CLOVER_LICENSE = BSD-2-Clause, BSD-3-Clause
CLOVER_LICENSE_FILES = LICENSE OpenCorePkg/LICENSE.txt
CLOVER_DEPENDENCIES = host-python3 host-nasm host-acpica host-util-linux host-zip
CLOVER_INSTALL_IMAGES = YES

# OpenCorePkg contains vendored code. Its top-level BSD-3-Clause license is
# declared above; its vendored components need a separate license audit.
define CLOVER_STAGE_OPENCORPKG
	mkdir -p $(@D)/OpenCorePkg
	$(TAR) -C $(@D)/OpenCorePkg --strip-components=1 \
		-xf $(CLOVER_DL_DIR)/OpenCorePkg-$(CLOVER_OPENCORPKG_VERSION).tar.gz
endef
CLOVER_POST_EXTRACT_HOOKS += CLOVER_STAGE_OPENCORPKG

define CLOVER_NORMALIZE_BASETOOLS_LINE_ENDINGS
	$(SED) 's/\r$$//' \
		$(@D)/BaseTools/Source/C/Common/EfiUtilityMsgs.c \
		$(@D)/BaseTools/Source/C/Common/StringFuncs.c \
		$(@D)/BaseTools/Source/C/BrotliCompress/dec/decode.c \
		$(@D)/BaseTools/Source/C/BrotliCompress/enc/encode.c \
		$(@D)/BaseTools/Source/C/GenFfs/GenFfs.c \
		$(@D)/BaseTools/Source/C/GenSec/GenSec.c \
		$(@D)/BaseTools/Source/C/LzmaCompress/Sdk/C/LzmaEnc.c
endef
CLOVER_POST_EXTRACT_HOOKS += CLOVER_NORMALIZE_BASETOOLS_LINE_ENDINGS

CLOVER_BUILD_ENV = \
	MAKEFLAGS= \
	SOURCE_DATE_EPOCH=$(CLOVER_SOURCE_DATE_EPOCH) \
	BUILD_CC="$(HOSTCC) -std=gnu17" \
	EXTRA_OPTFLAGS=-Wno-error=stringop-overflow \
	GCC161_BIN=$(TARGET_CROSS) \
	NASM_PREFIX=$(HOST_DIR)/bin/ \
	IASL_PREFIX=$(HOST_DIR)/bin/ \
	PYTHON_COMMAND=$(HOST_DIR)/bin/python3

define CLOVER_BUILD_CMDS
	export $(CLOVER_BUILD_ENV) && \
	$(@D)/ebuild.sh -gcc161 -n $(BR2_JLEVEL)
endef

CLOVER_EFI_DIR = $(BINARIES_DIR)/efi-part/EFI

define CLOVER_INSTALL_IMAGES_CMDS
	rm -rf $(CLOVER_EFI_DIR)/CLOVER
	mkdir -p $(CLOVER_EFI_DIR)
	cp -a $(@D)/CloverPackage/CloverV2/EFI/CLOVER $(CLOVER_EFI_DIR)/
	mv $(CLOVER_EFI_DIR)/CLOVER/drivers/off/UEFI/FileSystem/Ext4Dxe.efi \
		$(CLOVER_EFI_DIR)/CLOVER/drivers/UEFI/
endef

ifeq ($(BR2_TARGET_CLOVER_INSTALL_FALLBACK),y)
define CLOVER_INSTALL_FALLBACK
	mkdir -p $(CLOVER_EFI_DIR)/BOOT
	find $(CLOVER_EFI_DIR)/BOOT -maxdepth 1 -iname bootx64.efi -delete
	$(INSTALL) -m 0755 -D $(@D)/CloverPackage/CloverV2/EFI/BOOT/BOOTX64.efi \
		$(CLOVER_EFI_DIR)/BOOT/BOOTX64.efi
endef
CLOVER_POST_INSTALL_IMAGES_HOOKS += CLOVER_INSTALL_FALLBACK
endif

$(eval $(generic-package))

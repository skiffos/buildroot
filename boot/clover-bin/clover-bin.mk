################################################################################
#
# clover-bin
#
################################################################################

CLOVER_BIN_VERSION = 5174
CLOVER_BIN_SITE = https://github.com/CloverHackyColor/CloverBootloader/releases/download/$(CLOVER_BIN_VERSION)
CLOVER_BIN_SOURCE = CloverV2-$(CLOVER_BIN_VERSION).zip
CLOVER_BIN_EXTRA_DOWNLOADS = https://raw.githubusercontent.com/CloverHackyColor/CloverBootloader/$(CLOVER_BIN_VERSION)/LICENSE
CLOVER_BIN_LICENSE = BSD-2-Clause
CLOVER_BIN_LICENSE_FILES = LICENSE
CLOVER_BIN_INSTALL_IMAGES = YES

CLOVER_BIN_EXTRACT_CMDS = \
	bsdtar --strip-components=1 \
		-C $(CLOVER_BIN_DIR) \
		$(TAR_OPTIONS) $(CLOVER_BIN_DL_DIR)/$(CLOVER_BIN_SOURCE) -

define CLOVER_BIN_COPY_LICENSE
	cp $(CLOVER_BIN_DL_DIR)/LICENSE $(@D)/LICENSE
endef
CLOVER_BIN_POST_EXTRACT_HOOKS += CLOVER_BIN_COPY_LICENSE

CLOVER_BIN_EFI_DIR = $(BINARIES_DIR)/efi-part/EFI

# SkiffOS keeps its kernels on ext4, so Clover must load that filesystem.
define CLOVER_BIN_INSTALL_IMAGES_CMDS
	rm -rf $(CLOVER_BIN_EFI_DIR)/CLOVER
	mkdir -p $(CLOVER_BIN_EFI_DIR)
	cp -a $(@D)/EFI/CLOVER $(CLOVER_BIN_EFI_DIR)/
	mv $(CLOVER_BIN_EFI_DIR)/CLOVER/drivers/off/UEFI/FileSystem/Ext4Dxe.efi \
		$(CLOVER_BIN_EFI_DIR)/CLOVER/drivers/UEFI/
endef

ifeq ($(BR2_TARGET_CLOVER_BIN_INSTALL_FALLBACK),y)
define CLOVER_BIN_INSTALL_FALLBACK
	mkdir -p $(CLOVER_BIN_EFI_DIR)/BOOT
	find $(CLOVER_BIN_EFI_DIR)/BOOT -maxdepth 1 -iname bootx64.efi -delete
	$(INSTALL) -m 0755 -D $(@D)/EFI/BOOT/BOOTX64.efi \
		$(CLOVER_BIN_EFI_DIR)/BOOT/BOOTX64.efi
endef
CLOVER_BIN_POST_INSTALL_IMAGES_HOOKS += CLOVER_BIN_INSTALL_FALLBACK
endif

$(eval $(generic-package))

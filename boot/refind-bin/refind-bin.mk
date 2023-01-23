################################################################################
#
# refind-bin
#
################################################################################

REFIND_BIN_VERSION = 0.13.3.1
REFIND_BIN_SITE = http://downloads.sourceforge.net/project/refind/$(REFIND_BIN_VERSION)
REFIND_BIN_SOURCE = refind-bin-$(REFIND_BIN_VERSION).zip
REFIND_BIN_LICENSE = GPL-3.0+, GFDL-1.3+ (docs)
REFIND_BIN_LICENSE_FILES = COPYING.txt LICENSE.txt docs/refind/FDL-1.3.txt
REFIND_BIN_INSTALL_IMAGES = YES

ifeq ($(BR2_x86_64),y)
REFIND_BIN_ARCH = x86_64
REFIND_BIN_PLATFORM = x64
else ifeq ($(BR2_aarch64),y)
REFIND_BIN_ARCH = aarch64
REFIND_BIN_PLATFORM = aa64
else
REFIND_BIN_ARCH = ia32
REFIND_BIN_PLATFORM = ia32
endif

REFIND_BIN_EFI_PART_DIR = $(BINARIES_DIR)/efi-part
REFIND_BIN_BINARIES_DIR = $(REFIND_BIN_EFI_PART_DIR)/EFI/refind

REFIND_BIN_EXTRACT_CMDS = \
	bsdtar --strip-components=1 \
		-C $(REFIND_BIN_DIR) \
		$(TAR_OPTIONS) $(REFIND_BIN_DL_DIR)/$(REFIND_BIN_SOURCE) -

define REFIND_BIN_INSTALL_IMAGES_CMDS
	if [ -d $(REFIND_BIN_BINARIES_DIR) ]; then \
		rm -rf $(REFIND_BIN_BINARIES_DIR); \
	fi
	$(INSTALL) -m 0755 -D $(@D)/refind/refind_$(REFIND_BIN_PLATFORM).efi \
		$(REFIND_BIN_BINARIES_DIR)/refind_$(REFIND_BIN_PLATFORM).efi
	cp -r $(@D)/refind/drivers_$(REFIND_BIN_PLATFORM) \
		$(REFIND_BIN_BINARIES_DIR)/drivers_$(REFIND_BIN_PLATFORM)
	echo "refind_$(REFIND_BIN_PLATFORM).efi,rEFInd Boot Manager,,Entry for rEFInd" > \
		$(REFIND_BIN_BINARIES_DIR)/BOOT.CSV
	echo "# rEFInd configuration\ntimeout 20\n" > \
		$(REFIND_BIN_BINARIES_DIR)/refind.conf
	cp -r $(@D)/refind/icons $(REFIND_BIN_BINARIES_DIR)/icons
	cp -r $(@D)/{fonts,banners,keys} $(REFIND_BIN_BINARIES_DIR)/
endef

ifeq ($(BR2_TARGET_REFIND_BIN_RENAME_TO_BOOT),y)
define REFIND_BIN_IMAGES_RENAME_TO_BOOT
	if [ -d $(REFIND_BIN_EFI_PART_DIR)/EFI/BOOT ]; then \
		rm -rf $(REFIND_BIN_EFI_PART_DIR)/EFI/BOOT; \
	fi
	mv $(REFIND_BIN_BINARIES_DIR)/ $(REFIND_BIN_EFI_PART_DIR)/EFI/BOOT/
	mv $(REFIND_BIN_EFI_PART_DIR)/EFI/BOOT/refind_$(REFIND_BIN_PLATFORM).efi \
		$(REFIND_BIN_EFI_PART_DIR)/EFI/BOOT/BOOT$(REFIND_BIN_PLATFORM).EFI
	echo "BOOT$(REFIND_BIN_PLATFORM).EFI,rEFInd Boot Manager,,Entry for rEFInd" > \
		$(REFIND_BIN_EFI_PART_DIR)/EFI/BOOT/BOOT.CSV
endef
REFIND_BIN_POST_INSTALL_IMAGES_HOOKS += REFIND_BIN_IMAGES_RENAME_TO_BOOT
endif

$(eval $(generic-package))

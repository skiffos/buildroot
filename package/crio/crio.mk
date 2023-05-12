################################################################################
#
# crio
#
################################################################################

CRIO_VERSION = 1.27.0
CRIO_SITE = $(call github,cri-o,cri-o,v$(CRIO_VERSION))
CRIO_LICENSE = Apache-2.0
CRIO_LICENSE_FILES = LICENSE

CRIO_CPE_ID_VENDOR = kubernetes
CRIO_CPE_ID_PRODUCT = cri-o

CRIO_BUILD_TARGETS = cmd/crio cmd/crio-status
CRIO_DEPENDENCIES += libgpgme
CRIO_LDFLAGS = \
	-X $(CRIO_GOMOD)/internal/version.Version=$(CRIO_VERSION)
CRIO_TAGS = exclude_graphdriver_zfs

ifeq ($(BR2_INIT_SYSTEMD),y)
CRIO_TAGS += systemd
endif

ifeq ($(BR2_PACKAGE_LIBAPPARMOR),y)
CRIO_DEPENDENCIES += libapparmor
CRIO_TAGS += apparmor
endif

ifeq ($(BR2_PACKAGE_LIBSECCOMP),y)
CRIO_TAGS += seccomp
CRIO_DEPENDENCIES += libseccomp host-pkgconf
endif

ifeq ($(BR2_PACKAGE_LIBSELINUX),y)
CRIO_TAGS += selinux
CRIO_DEPENDENCIES += libselinux
endif

ifeq ($(BR2_PACKAGE_CRIO_DRIVER_BTRFS),y)
CRIO_DEPENDENCIES += btrfs-progs
else
CRIO_TAGS += exclude_graphdriver_btrfs
endif

ifeq ($(BR2_PACKAGE_CRIO_DRIVER_DEVICEMAPPER),y)
CRIO_DEPENDENCIES += lvm2
else
CRIO_TAGS += exclude_graphdriver_devicemapper
endif

ifeq ($(BR2_PACKAGE_CRIO_DRIVER_OSTREE),y)
CRIO_DEPENDENCIES += libostree
CRIO_TAGS += ostree
endif

define CRIO_BUILD_PINNS
	$(TARGET_MAKE_ENV) $(MAKE) CC="$(TARGET_CC)" CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)" STRIP="$(TARGET_STRIP)" \
		-C $(@D)/pinns ../bin/pinns
endef
CRIO_POST_BUILD_HOOKS += CRIO_BUILD_PINNS

define CRIO_INSTALL_TARGET_CMDS
	$(HOST_GO_COMMON_ENV) $(TARGET_MAKE_ENV) $(MAKE) -C $(@D) \
		DESTDIR=$(TARGET_DIR) PREFIX=$(TARGET_DIR)/usr ETCDIR=$(TARGET_DIR)/etc \
		OPT_CNI_BIN_DIR=$(TARGET_DIR)/opt/cni/bin install.bin-nobuild
	$(INSTALL) -d -m 700 $(TARGET_DIR)/etc/cni
	$(INSTALL) -d -m 700 $(TARGET_DIR)/etc/cni/net.d
	$(INSTALL) -D -m 644 $(@D)/contrib/cni/10-crio-bridge.conflist \
		$(TARGET_DIR)/etc/cni/net.d/10-crio-bridge.conflist
endef

define CRIO_INSTALL_INIT_SYSTEMD
	$(HOST_GO_COMMON_ENV) $(TARGET_MAKE_ENV) $(MAKE) -C $(@D) \
		DESTDIR=$(TARGET_DIR) PREFIX=$(TARGET_DIR)/usr ETCDIR=$(TARGET_DIR)/etc \
		OPT_CNI_BIN_DIR=$(TARGET_DIR)/opt/cni/bin install.systemd
	$(SED) 's,/usr/local/bin,/usr/bin,g' \
		$(TARGET_DIR)/usr/lib/systemd/system/{crio,crio-wipe}.service
endef

$(eval $(golang-package))

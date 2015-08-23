################################################################################
#
# pluginhook
#
################################################################################

PLUGINHOOK_VERSION = 7b91f7692d3ec494d4945f27d6b88864cd2f4bde
PLUGINHOOK_SITE = $(call github,progrium,pluginhook,$(PLUGINHOOK_VERSION))
PLUGINHOOK_DEPENDENCIES = host-golang
PLUGINHOOK_LICENSE = MIT
PLUGINHOOK_LICENSE_FILES = LICENSE

define PLUGINHOOK_CONFIGURE_CMDS
	mkdir -p $(@D)/vendor/src/golang.org/x/
	git clone https://github.com/golang/crypto.git $(@D)/vendor/src/golang.org/x/crypto
endef

define PLUGINHOOK_BUILD_CMDS
	export GOPATH="$(@D)/vendor"; \
	export GOOS=linux; \
	export GOARCH=$(ARCH); \
	cd $(@D); \
	$(GOLANG) build -v -o "$(@D)/pluginhook" -a .
endef

define PLUGINHOOK_INSTALL_TARGET_CMDS
	$(INSTALL) -m 0755 $(@D)/pluginhook $(TARGET_DIR)/usr/bin/pluginhook
endef

$(eval $(generic-package))

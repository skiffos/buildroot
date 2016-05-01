################################################################################
#
# runc
#
################################################################################

RUNC_VERSION = v0.1.1
RUNC_VERSION_COMMIT = baf6536d6259209c3edfa2b22237af82942d3dfa
RUNC_SITE = $(call github,opencontainers,runc,$(RUNC_VERSION))

RUNC_LICENSE = Apache-2.0
RUNC_LICENSE_FILES = LICENSE

RUNC_DEPENDENCIES = host-go

RUNC_MAKE_ENV = \
	GOBIN="$(@D)/bin" \
	GOPATH="$(@D)/Godeps/_workspace" \
	GOARCH=$(GO_GOARCH) \
	CGO_ENABLED=1

RUNC_GLDFLAGS = \
	-X main.gitCommit=$(RUNC_VERSION_COMMIT) \
	-extldflags '-static'

RUNC_GOTAGS = cgo static_build

ifeq ($(BR2_PACKAGE_LIBSECCOMP),y)
RUNC_GOTAGS += seccomp
RUNC_DEPENDENCIES += libseccomp
endif

define RUNC_CONFIGURE_CMDS
	# Put sources at prescribed GOPATH location.
	export $(RUNC_MAKE_ENV) && \
		mkdir -p $$GOPATH/src/github.com/opencontainers && \
		ln -s $(@D) $$GOPATH/src/github.com/opencontainers/runc
endef

define RUNC_BUILD_CMDS
	cd $(@D) && $(RUNC_MAKE_ENV) $(HOST_DIR)/usr/bin/go \
		build -v -o $(@D)/bin/runc -tags "$(RUNC_GOTAGS)" -ldflags "$(RUNC_GLDFLAGS)" .
endef

define RUNC_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/bin/runc $(TARGET_DIR)/usr/bin/runc
endef

$(eval $(generic-package))

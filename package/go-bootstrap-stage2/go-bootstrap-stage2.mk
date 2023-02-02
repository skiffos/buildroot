################################################################################
#
# go-bootstrap-stage2
#
################################################################################

GO_BOOTSTRAP_STAGE2_VERSION = 1.19.5
GO_BOOTSTRAP_STAGE2_SITE = https://storage.googleapis.com/golang
GO_BOOTSTRAP_STAGE2_SOURCE = go$(GO_BOOTSTRAP_STAGE2_VERSION).src.tar.gz

GO_BOOTSTRAP_STAGE2_LICENSE = BSD-3-Clause
GO_BOOTSTRAP_STAGE2_LICENSE_FILES = LICENSE

# Use go-bootstrap-stage1 to bootstrap.
HOST_GO_BOOTSTRAP_STAGE2_DEPENDENCIES = host-go-bootstrap-stage1

HOST_GO_BOOTSTRAP_STAGE2_ROOT = $(HOST_DIR)/lib/go-$(GO_BOOTSTRAP_STAGE2_VERSION)

# The go build system is not compatable with ccache, so use HOSTCC_NOCCACHE.
# See https://github.com/golang/go/issues/11685.
HOST_GO_BOOTSTRAP_STAGE2_MAKE_ENV = \
	GO111MODULE=off \
	GOROOT_BOOTSTRAP=$(HOST_GO_BOOTSTRAP_STAGE1_ROOT) \
	GOROOT_FINAL=$(HOST_GO_BOOTSTRAP_STAGE2_ROOT) \
	GOROOT="$(@D)" \
	GOBIN="$(@D)/bin" \
	GOOS=linux \
	CC=$(HOSTCC_NOCCACHE) \
	CXX=$(HOSTCXX_NOCCACHE) \
	CGO_ENABLED=0

define HOST_GO_BOOTSTRAP_STAGE2_BUILD_CMDS
	cd $(@D)/src && \
		$(HOST_GO_BOOTSTRAP_STAGE2_MAKE_ENV) ./make.bash $(if $(VERBOSE),-v)
endef

define HOST_GO_BOOTSTRAP_STAGE2_INSTALL_CMDS
	$(INSTALL) -D -m 0755 $(@D)/bin/go $(HOST_GO_BOOTSTRAP_STAGE2_ROOT)/bin/go
	$(INSTALL) -D -m 0755 $(@D)/bin/gofmt $(HOST_GO_BOOTSTRAP_STAGE2_ROOT)/bin/gofmt

	cp -a $(@D)/lib $(HOST_GO_BOOTSTRAP_STAGE2_ROOT)/

	mkdir -p $(HOST_GO_BOOTSTRAP_STAGE2_ROOT)/pkg
	cp -a $(@D)/pkg/include $(@D)/pkg/linux_* $(HOST_GO_BOOTSTRAP_STAGE2_ROOT)/pkg/
	cp -a $(@D)/pkg/tool $(HOST_GO_BOOTSTRAP_STAGE2_ROOT)/pkg/

	# https://golang.org/issue/2775
	cp -a $(@D)/src $(HOST_GO_BOOTSTRAP_STAGE2_ROOT)/

	# Set all file timestamps to prevent the go compiler from rebuilding any
	# built in packages when programs are built.
	find $(HOST_GO_BOOTSTRAP_STAGE2_ROOT) -type f -exec touch -r $(@D)/bin/go {} \;
endef

$(eval $(host-generic-package))

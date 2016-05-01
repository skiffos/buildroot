################################################################################
#
# docker-containerd
#
################################################################################

DOCKER_CONTAINERD_VERSION = v0.2.1
DOCKER_CONTAINERD_VERSION_COMMIT = ca47f7e76a93e9b3768ed084d62318e85bd9f4b2
DOCKER_CONTAINERD_SITE = $(call github,docker,containerd,$(DOCKER_CONTAINERD_VERSION))

DOCKER_CONTAINERD_LICENSE = Apache-2.0
DOCKER_CONTAINERD_LICENSE_FILES = LICENSE.code

DOCKER_CONTAINERD_DEPENDENCIES = host-go runc

DOCKER_CONTAINERD_MAKE_ENV = \
	GOBIN="$(@D)/bin" \
	GOPATH="$(@D)/vendor" \
	GOARCH=$(GO_GOARCH) \
	CGO_ENABLED=1

DOCKER_CONTAINERD_GLDFLAGS = \
	-X github.com/docker/containerd.GitCommit=$(DOCKER_CONTAINERD_VERSION_COMMIT) \
	-extldflags '-static'

define DOCKER_CONTAINERD_CONFIGURE_CMDS
	# Put sources at prescribed GOPATH location.
	export $(DOCKER_CONTAINERD_MAKE_ENV) && \
		mkdir -p $$GOPATH/src/github.com/docker && \
		ln -s $(@D) $$GOPATH/src/github.com/docker/containerd && \
		mkdir -p $$GOPATH/src/github.com/opencontainers && \
		ln -s $(RUNC_SRCDIR) $$GOPATH/src/github.com/opencontainers/runc
endef

define DOCKER_CONTAINERD_BUILD_CMDS
	cd $(@D) && export $(DOCKER_CONTAINERD_MAKE_ENV) && \
		$(HOST_DIR)/usr/bin/go build -v -o $(@D)/bin/ctr -ldflags "$(DOCKER_CONTAINERD_GLDFLAGS)" ./ctr && \
		$(HOST_DIR)/usr/bin/go build -v -o $(@D)/bin/containerd -ldflags "$(DOCKER_CONTAINERD_GLDFLAGS)" ./containerd && \
		$(HOST_DIR)/usr/bin/go build -v -o $(@D)/bin/containerd-shim -ldflags "$(DOCKER_CONTAINERD_GLDFLAGS)" ./containerd-shim
endef

define DOCKER_CONTAINERD_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(TARGET_DIR)/usr/bin/runc $(TARGET_DIR)/usr/bin/docker-runc
	$(INSTALL) -D -m 0755 $(@D)/bin/containerd $(TARGET_DIR)/usr/bin/docker-containerd
	$(INSTALL) -D -m 0755 $(@D)/bin/containerd-shim $(TARGET_DIR)/usr/bin/containerd-shim
endef

$(eval $(generic-package))

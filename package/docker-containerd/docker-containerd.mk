################################################################################
#
# docker-containerd
#
################################################################################

# Temporary bump until next release (v0.3.0) to fix amd64
# temporary fixup repo
# DOCKER_CONTAINERD_SITE = https://github.com/docker/containerd/archive
DOCKER_CONTAINERD_VERSION = fb41d9c33bd7df79e15bb5b3af92de475b5f4ada
DOCKER_CONTAINERD_VERSION_COMMIT = fb41d9c33bd7df79e15bb5b3af92de475b5f4ada
DOCKER_CONTAINERD_SITE = $(call github,paralin,containerd,$(DOCKER_CONTAINERD_VERSION))

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

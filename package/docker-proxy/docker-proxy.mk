################################################################################
#
# docker-proxy
#
################################################################################

DOCKER_PROXY_VERSION = 9647f993a81e404639592e8ed73693b48ec09c2e
DOCKER_PROXY_SITE = $(call github,docker,libnetwork,$(DOCKER_PROXY_VERSION))

DOCKER_PROXY_LICENSE = Apache-2.0
DOCKER_PROXY_LICENSE_FILES = LICENSE

DOCKER_PROXY_DEPENDENCIES = host-go host-pkgconf

DOCKER_PROXY_GOPATH = "$(@D)/gopath"
DOCKER_PROXY_MAKE_ENV = $(HOST_GO_TARGET_ENV) \
	CGO_ENABLED=1 \
	CGO_NO_EMULATION=1 \
	GOBIN="$(@D)/bin" \
	GOPATH="$(DOCKER_PROXY_GOPATH)" \
	PKG_CONFIG="$(PKG_CONFIG_HOST_BINARY)" \
	$(TARGET_MAKE_ENV)

ifeq ($(BR2_STATIC_LIBS),y)
DOCKER_PROXY_GLDFLAGS += -extldflags '-static'
endif

define DOCKER_PROXY_CONFIGURE_CMDS
	mkdir -p $(DOCKER_PROXY_GOPATH)/src/github.com/docker
	ln -fs $(@D) $(DOCKER_PROXY_GOPATH)/src/github.com/docker/libnetwork
endef

define DOCKER_PROXY_BUILD_CMDS
	cd $(@D)/gopath/src/github.com/docker/libnetwork; \
	$(DOCKER_PROXY_MAKE_ENV) \
	$(HOST_DIR)/usr/bin/go build -v \
		-o $(@D)/bin/docker-proxy \
		-ldflags "$(DOCKER_PROXY_GLDFLAGS)" \
		github.com/docker/libnetwork/cmd/proxy
endef

define DOCKER_PROXY_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/bin/docker-proxy $(TARGET_DIR)/usr/bin/docker-proxy
endef

$(eval $(generic-package))

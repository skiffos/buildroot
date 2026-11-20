################################################################################
#
# dbus-forwarding-proxy
#
################################################################################

DBUS_FORWARDING_PROXY_VERSION = 97fd27e6cad9b2dd4502663667a95e5e7cc887e2
DBUS_FORWARDING_PROXY_SITE = $(call github,igo95862,dbus-forwarding-proxy,$(DBUS_FORWARDING_PROXY_VERSION))
DBUS_FORWARDING_PROXY_DEPENDENCIES = host-pkgconf libglib2 systemd
DBUS_FORWARDING_PROXY_LICENSE = LGPL-2.1-or-later
DBUS_FORWARDING_PROXY_LICENSE_FILES = LICENSES/LGPL-2.1-or-later.txt

$(eval $(meson-package))

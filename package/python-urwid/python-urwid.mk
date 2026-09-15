################################################################################
#
# python-urwid
#
################################################################################

PYTHON_URWID_VERSION = 4.0.0
PYTHON_URWID_SOURCE = urwid-$(PYTHON_URWID_VERSION).tar.gz
PYTHON_URWID_SITE = https://files.pythonhosted.org/packages/1c/09/afbd44c7c57b1124d94ffe6321154798b816bd09c00e0aaabb701583a1c8
PYTHON_URWID_LICENSE = LGPL-2.1+
PYTHON_URWID_LICENSE_FILES = COPYING
PYTHON_URWID_SETUP_TYPE = setuptools
PYTHON_URWID_DEPENDENCIES = host-python-setuptools-scm

$(eval $(python-package))

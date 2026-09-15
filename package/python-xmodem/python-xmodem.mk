################################################################################
#
# python-xmodem
#
################################################################################

PYTHON_XMODEM_VERSION = 0.5.0
PYTHON_XMODEM_SOURCE = xmodem-$(PYTHON_XMODEM_VERSION).tar.gz
PYTHON_XMODEM_SITE = https://files.pythonhosted.org/packages/c7/03/a18c2b571266787aebb7cadc5d4c90af15ae7e949ae0ee99ed23b5ba4f3c
PYTHON_XMODEM_SETUP_TYPE = setuptools
PYTHON_XMODEM_LICENSE = MIT
PYTHON_XMODEM_LICENSE_FILES = LICENSE

$(eval $(python-package))
$(eval $(host-python-package))

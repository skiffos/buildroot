################################################################################
#
# python-uswid
#
################################################################################

PYTHON_USWID_VERSION = 0.6.0
PYTHON_USWID_SOURCE = uswid-$(PYTHON_USWID_VERSION).tar.gz
PYTHON_USWID_SITE = https://files.pythonhosted.org/packages/5b/4b/4eb0e287c6587f55212e87eaf24d262d21d47a56d034dfae11649eff613f
PYTHON_USWID_SETUP_TYPE = setuptools
PYTHON_USWID_LICENSE = BSD-2-Clause-Patent
PYTHON_USWID_LICENSE_FILES = LICENSE
HOST_PYTHON_USWID_DEPENDENCIES = \
	host-python-cbor2 \
	host-python-lxml \
	host-python-pefile

$(eval $(host-python-package))

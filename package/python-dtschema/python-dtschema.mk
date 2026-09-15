################################################################################
#
# python-dtschema
#
################################################################################

PYTHON_DTSCHEMA_VERSION = 2026.4
PYTHON_DTSCHEMA_SOURCE = dtschema-$(PYTHON_DTSCHEMA_VERSION).tar.gz
PYTHON_DTSCHEMA_SITE = https://files.pythonhosted.org/packages/f8/f0/3990f821c088a6107ce1ca1906fd123aebf3c2a0a4c82cb41d7d52664bc3
PYTHON_DTSCHEMA_SETUP_TYPE = setuptools
PYTHON_DTSCHEMA_LICENSE = BSD-2-Clause
PYTHON_DTSCHEMA_LICENSE_FILES = LICENSE.txt
PYTHON_DTSCHEMA_DEPENDENCIES = host-python-setuptools-scm

$(eval $(python-package))

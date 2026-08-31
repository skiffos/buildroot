################################################################################
#
# python-anyio
#
################################################################################

PYTHON_ANYIO_VERSION = 4.13.0
PYTHON_ANYIO_SOURCE = anyio-$(PYTHON_ANYIO_VERSION).tar.gz
PYTHON_ANYIO_SITE = https://files.pythonhosted.org/packages/19/14/2c5dd9f512b66549ae92767a9c7b330ae88e1932ca57876909410251fe13
PYTHON_ANYIO_SETUP_TYPE = setuptools
PYTHON_ANYIO_LICENSE = MIT
PYTHON_ANYIO_LICENSE_FILES = LICENSE
PYTHON_ANYIO_DEPENDENCIES = host-python-setuptools-scm

$(eval $(python-package))

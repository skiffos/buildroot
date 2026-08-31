################################################################################
#
# python-mako
#
################################################################################

PYTHON_MAKO_VERSION = 1.3.12
PYTHON_MAKO_SOURCE = mako-$(PYTHON_MAKO_VERSION).tar.gz
PYTHON_MAKO_SITE = https://files.pythonhosted.org/packages/00/62/791b31e69ae182791ec67f04850f2f062716bbd205483d63a215f3e062d3
PYTHON_MAKO_SETUP_TYPE = setuptools
PYTHON_MAKO_LICENSE = MIT
PYTHON_MAKO_LICENSE_FILES = LICENSE
PYTHON_MAKO_CPE_ID_VENDOR = sqlalchemy
PYTHON_MAKO_CPE_ID_PRODUCT = mako

# In host build, setup.py tries to download markupsafe if it is not installed
HOST_PYTHON_MAKO_DEPENDENCIES = host-python-markupsafe

$(eval $(python-package))
$(eval $(host-python-package))

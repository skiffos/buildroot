################################################################################
#
# python-more-itertools
#
################################################################################

PYTHON_MORE_ITERTOOLS_VERSION = 11.0.2
PYTHON_MORE_ITERTOOLS_SOURCE = more_itertools-$(PYTHON_MORE_ITERTOOLS_VERSION).tar.gz
PYTHON_MORE_ITERTOOLS_SITE = https://files.pythonhosted.org/packages/a2/f7/139d22fef48ac78127d18e01d80cf1be40236ae489769d17f35c3d425293
PYTHON_MORE_ITERTOOLS_SETUP_TYPE = flit
PYTHON_MORE_ITERTOOLS_LICENSE = MIT
PYTHON_MORE_ITERTOOLS_LICENSE_FILES = LICENSE

$(eval $(python-package))

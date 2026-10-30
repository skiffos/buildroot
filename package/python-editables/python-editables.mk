################################################################################
#
# python-editables
#
################################################################################

PYTHON_EDITABLES_VERSION = 0.6
PYTHON_EDITABLES_SOURCE = editables-$(PYTHON_EDITABLES_VERSION).tar.gz
PYTHON_EDITABLES_SITE = https://files.pythonhosted.org/packages/82/f8/02a4e9a0cb961b0feeb431ac96b231c157ecdcbbeacafe9e2fdb4b1dde39
PYTHON_EDITABLES_LICENSE = MIT
PYTHON_EDITABLES_LICENSE_FILES = LICENSE.txt
PYTHON_EDITABLES_SETUP_TYPE = setuptools

$(eval $(host-python-package))

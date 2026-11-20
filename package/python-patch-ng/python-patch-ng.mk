################################################################################
#
# python-patch-ng
#
################################################################################

PYTHON_PATCH_NG_VERSION = 1.19.1
PYTHON_PATCH_NG_SOURCE = patch_ng-$(PYTHON_PATCH_NG_VERSION).tar.gz
PYTHON_PATCH_NG_SITE = https://files.pythonhosted.org/packages/da/b6/8ea8095f964f93567bbe28709298b30104ad418b50d4217538387bf48f7d
PYTHON_PATCH_NG_SETUP_TYPE = setuptools
PYTHON_PATCH_NG_LICENSE = MIT
PYTHON_PATCH_NG_LICENSE_FILES = LICENSE

$(eval $(python-package))
$(eval $(host-python-package))

################################################################################
#
# python-sentry-sdk
#
################################################################################

PYTHON_SENTRY_SDK_VERSION = 2.58.0
PYTHON_SENTRY_SDK_SOURCE = sentry_sdk-$(PYTHON_SENTRY_SDK_VERSION).tar.gz
PYTHON_SENTRY_SDK_SITE = https://files.pythonhosted.org/packages/26/b3/fb8291170d0e844173164709fc0fa0c221ed75a5da740c8746f2a83b4eb1
PYTHON_SENTRY_SDK_SETUP_TYPE = setuptools
PYTHON_SENTRY_SDK_LICENSE = MIT
PYTHON_SENTRY_SDK_LICENSE_FILES = LICENSE

$(eval $(python-package))

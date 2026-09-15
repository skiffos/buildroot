################################################################################
#
# python-flask-smorest
#
################################################################################

PYTHON_FLASK_SMOREST_VERSION = 0.47.0
PYTHON_FLASK_SMOREST_SOURCE = flask_smorest-$(PYTHON_FLASK_SMOREST_VERSION).tar.gz
PYTHON_FLASK_SMOREST_SITE = https://files.pythonhosted.org/packages/99/b0/5edd5f3231ea26b52e786588c45d786df26929d2be8fec634bcb871b2a3f
PYTHON_FLASK_SMOREST_SETUP_TYPE = flit
PYTHON_FLASK_SMOREST_LICENSE = MIT
PYTHON_FLASK_SMOREST_LICENSE_FILES = LICENSE

$(eval $(python-package))

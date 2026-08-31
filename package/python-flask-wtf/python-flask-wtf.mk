################################################################################
#
# python-flask-wtf
#
################################################################################

PYTHON_FLASK_WTF_VERSION = 1.3.0
PYTHON_FLASK_WTF_SOURCE = flask_wtf-$(PYTHON_FLASK_WTF_VERSION).tar.gz
PYTHON_FLASK_WTF_SITE = https://files.pythonhosted.org/packages/91/f1/605a56d4ea217b307f3e6f4d663e0351253d85d841edc93ba559f0648e19
PYTHON_FLASK_WTF_LICENSE = BSD-3-Clause
PYTHON_FLASK_WTF_LICENSE_FILES = LICENSE.rst
PYTHON_FLASK_WTF_SETUP_TYPE = hatch

$(eval $(python-package))

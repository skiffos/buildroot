################################################################################
#
# python-marshmallow-sqlalchemy
#
################################################################################

PYTHON_MARSHMALLOW_SQLALCHEMY_VERSION = 1.5.0
PYTHON_MARSHMALLOW_SQLALCHEMY_SOURCE = marshmallow_sqlalchemy-$(PYTHON_MARSHMALLOW_SQLALCHEMY_VERSION).tar.gz
PYTHON_MARSHMALLOW_SQLALCHEMY_SITE = https://files.pythonhosted.org/packages/ee/fe/247c297809e64116f766716632adbc3f4cd06f376f56dc15bb92f170d247
PYTHON_MARSHMALLOW_SQLALCHEMY_SETUP_TYPE = flit
PYTHON_MARSHMALLOW_SQLALCHEMY_LICENSE = MIT
PYTHON_MARSHMALLOW_SQLALCHEMY_LICENSE_FILES = LICENSE

$(eval $(python-package))

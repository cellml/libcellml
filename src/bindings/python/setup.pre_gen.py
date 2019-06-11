""" libCellML Library: A library for the parsing, printing, and manipulation
of CellML 2.0 compliant models.

"""

classifiers = """\
Development Status :: 5 - Production/Stable
Intended Audience :: Developers
Intended Audience :: Education
Intended Audience :: Science/Research
License :: OSI Approved :: Apache Software License
Programming Language :: Python
Operating System :: Microsoft :: Windows
Operating System :: Unix
Operating System :: MacOS :: MacOS X
Topic :: Software Development :: Libraries :: Python Modules
"""

from setuptools import setup
from setuptools.dist import Distribution


doclines = __doc__.split("\n")


class BinaryDistribution(Distribution):
    def is_pure(self):
        return False

    def has_ext_modules(self):
        return True


setup(
    name='libcellml',
    version='0.2.0',
    author='libCellML Developers',
    author_email='libcellml@googlegroups.com',
    packages=['libcellml'],
    package_data={'libcellml': ['${TARGET_FILE_NAME_cellml}', '${TARGET_FILE_NAME_component}', '${TARGET_FILE_NAME_componententity}', '${TARGET_FILE_NAME_error}', '${TARGET_FILE_NAME_entity}', '${TARGET_FILE_NAME_enumerations}', '${TARGET_FILE_NAME_importsource}', '${TARGET_FILE_NAME_importedentity}', '${TARGET_FILE_NAME_logger}', '${TARGET_FILE_NAME_model}', '${TARGET_FILE_NAME_namedentity}', '${TARGET_FILE_NAME_orderedentity}', '${TARGET_FILE_NAME_parser}', '${TARGET_FILE_NAME_printer}', '${TARGET_FILE_NAME_reset}', '${TARGET_FILE_NAME_specificationrule}', '${TARGET_FILE_NAME_units}', '${TARGET_FILE_NAME_validator}', '${TARGET_FILE_NAME_variable}', '${TARGET_FILE_NAME_version}', '${TARGET_FILE_NAME_when}']},
    url='http://cellml.org',
    license='Apache Software License',
    description=doclines[0],
    classifiers=filter(None, classifiers.split("\n")),
    long_description=open('README.rst').read(),
    distclass=BinaryDistribution,
    include_package_data=True,
    zip_safe=False,
)

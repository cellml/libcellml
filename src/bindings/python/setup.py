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
    package_data={'libcellml': ['libcellmld.0.2.0.dylib', '_component.so', '_componententity.so', '_error.so', '_entity.so', '_enumerations.so', '_importsource.so', '_importedentity.so', '_logger.so', '_model.so', '_namedentity.so', '_orderedentity.so', '_parser.so', '_printer.so', '_reset.so', '_specificationrule.so', '_units.so', '_validator.so', '_variable.so', '_version.so', '_when.so']},
    url='http://cellml.org',
    license='Apache Software License',
    description=doclines[0],
    classifiers=filter(None, classifiers.split("\n")),
    long_description=open('README.rst').read(),
    distclass=BinaryDistribution,
    include_package_data=True,
    zip_safe=False,
)

#!/usr/bin/env python
#
# Tests the Python bindings for libcellml
#
# How to run tests
# ----------------
# - Run all tests:
#       $ python run
#   In bash, simply "./run" is enough.
#
# - Run a specific set of tests
#       $ python run test1 test2 etc.
#
# - Run tests with more output
#       $ python run -v
#   or
#       $ python run --verbose
#
# How to write tests
# ------------------
# - All tests must be inside the 'test' folder, with names like `test*.py`.
# - Tests must be grouped in classes extending `unittest.TestCase`
# - Individual tests are methods with a name of the form `test_*(self)`.
# - Don't use asserts etc. but use methods like `self.assertEqual()`.
#   See: https://docs.python.org/3/library/unittest.html#assert-methods
#
import os
import sys
import unittest

# Current directory
ROOT = os.path.abspath(os.path.dirname(__file__))

# All tests
TEST = os.path.join(ROOT, 'tests')

# Set verbosity
args = sys.argv[1:]
verbosity = 1
for x in ['-v', '--verbose']:
    try:
        args.remove(x)
        verbosity = 1000
    except ValueError:
        pass

# Load selected tests or discover all
loader = unittest.TestLoader()
if args:
    # Load selected tests
    # Make sure test module names start with 'test.'
    tests = [x if x[:5] == '.test' else 'test.' + x for x in args]
    suite = loader.loadTestsFromNames(tests)
else:
    # Discover all tests
    loader = unittest.TestLoader()
    suite = loader.discover(TEST)

# Run!
unittest.TextTestRunner(verbosity=verbosity).run(suite)

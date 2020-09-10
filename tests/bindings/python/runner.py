import coverage
import importlib
import unittest

suite = unittest.TestLoader().discover(".")

cov = coverage.Coverage(source=["libcellml"])
cov.set_option("run:plugins", ["exclude_until_coverage_plugin"])
#cov.set_option("exclude_until_coverage_plugin:marker", "# libCellML generated wrapper code starts here.")

cov.start()

unittest.TextTestRunner(verbosity=1).run(suite)

cov.stop()
cov.save()

cov.report()

#
# Tests the AnalyserExternalVariable class bindings
#
import unittest


class AnalyserExternalVariableTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Variable
        from libcellml import AnalyserExternalVariable

        v = Variable('test')
        aev = AnalyserExternalVariable(v)

        self.assertEqual(v.name(), aev.variable().name())

        d0 = Variable('d0')
        d1 = Variable('d1')
        d2 = Variable('d2')

        self.assertTrue(aev.addDependency(d0))
        self.assertTrue(aev.addDependency(d1))
        self.assertTrue(aev.addDependency(d2))

        self.assertEqual(3, aev.dependencyCount())

        self.assertIsNotNone(aev.dependency(0))
        self.assertIsNotNone(aev.dependencies())

        self.assertTrue(aev.containsDependency(d0))

        self.assertTrue(aev.removeDependency(d0))
        aev.removeAllDependencies()

        del [aev, v, d0, d1, d2]


if __name__ == '__main__':
    unittest.main()

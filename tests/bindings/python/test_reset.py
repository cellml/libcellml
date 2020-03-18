#
# Tests the Reset class bindings
#
import unittest


class ResetTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Reset

        x = Reset()
        del(x)

    def test_set_get_variable(self):
        from libcellml import Reset
        from libcellml import Variable

        r = Reset()
        v = Variable()
        v.setName("glucose")

        self.assertEqual(None, r.variable())

        r.setVariable(v)

        self.assertEqual("glucose", r.variable().name())

    def test_set_get_test_variable(self):
        from libcellml import Reset
        from libcellml import Variable

        r = Reset()
        v = Variable()
        v.setName("glucose")

        self.assertEqual(None, r.testVariable())

        r.setTestVariable(v)

        self.assertEqual("glucose", r.testVariable().name())

    def test_set_order(self):
        from libcellml import Reset

        x = Reset()
        x.setOrder(3)
        self.assertEqual(3, x.order())

    def test_is_order_set(self):
        from libcellml import Reset

        # bool isOrderSet()
        x = Reset()
        self.assertFalse(x.isOrderSet())
        x.setOrder(2)
        self.assertTrue(x.isOrderSet())

    def test_unset_order(self):
        from libcellml import Reset

        # unsetOrder()
        x = Reset()
        x.setOrder(-4)
        self.assertTrue(x.isOrderSet())
        x.unsetOrder()
        self.assertFalse(x.isOrderSet())

    def test_set_get_test_value(self):
        from libcellml import Reset

        x = Reset()
        self.assertEqual("", x.testValue())

        x.setTestValue("A MathML string.")

        self.assertEqual("A MathML string.", x.testValue())

    def test_set_get_reset_value(self):
        from libcellml import Reset

        x = Reset()
        self.assertEqual("", x.resetValue())

        x.setResetValue("A value MathML string.")

        self.assertEqual("A value MathML string.", x.resetValue())


if __name__ == '__main__':
    unittest.main()


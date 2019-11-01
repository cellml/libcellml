#
# Tests the bindings for OrderedEntity, which is the base class for all
# entities that can be ordered relative to one another.
#
import unittest


class OrderedEntityTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import When

        x = When()
        del x

    def test_set_order(self):
        from libcellml import When

        x = When()
        x.setOrder(3)
        self.assertEqual(3, x.order())

    def test_is_order_set(self):
        from libcellml import When

        # bool isOrderSet()
        x = When()
        self.assertFalse(x.isOrderSet())
        x.setOrder(2)
        self.assertTrue(x.isOrderSet())

    def test_unset_order(self):
        from libcellml import When

        # unsetOrder()
        x = When()
        x.setOrder(-4)
        self.assertTrue(x.isOrderSet())
        x.unsetOrder()
        self.assertFalse(x.isOrderSet())

    def test_set_get_condition(self):
        from libcellml import When

        x = When()
        self.assertEqual("", x.condition())

        x.setCondition("A MathML string.")

        self.assertEqual("A MathML string.", x.condition())

    def test_set_get_value(self):
        from libcellml import When

        x = When()
        self.assertEqual("", x.value())

        x.setValue("A value MathML string.")

        self.assertEqual("A value MathML string.", x.value())


if __name__ == '__main__':
    unittest.main()


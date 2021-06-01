#
# Tests the entity class bindings
#
import unittest


class EntityTestCase(unittest.TestCase):

    def test_create(self):
        from libcellml.entity import Entity

        self.assertRaises(AttributeError, Entity)

    def test_id(self):
        from libcellml import Model

        # std::string id()
        x = Model()
        self.assertEqual(x.id(), '')

        # void setId(const std::string &id)
        idx = 'test'
        x.setId(idx)
        self.assertEqual(x.id(), idx)

        x.removeId()
        self.assertEqual(x.id(), '')

    def test_parent(self):
        from libcellml import Model, Component

        x = Model("model")
        self.assertIsNone(x.parent())

        c = Component()
        self.assertIsNone(c.parent())
        c.setParent(x)
        self.assertEqual("model", c.parent().name())
        self.assertEqual(0, x.componentCount())

    def test_remove_parent(self):
        from libcellml import Model, Component

        m = Model()
        c = Component()
        c.setParent(m)
        self.assertIsNotNone(c.parent())
        c.removeParent()
        self.assertIsNone(c.parent())

    def test_has_parent(self):
        from libcellml import Component

        # bool hasParent(Component* c)
        x = Component()
        c1 = Component()
        self.assertFalse(x.hasParent())
        x.setParent(c1)
        self.assertTrue(x.hasParent())
        x.removeParent()
        self.assertFalse(x.hasParent())
        c2 = Component()
        c2.setParent(c1)
        x.setParent(c2)
        self.assertTrue(x.hasParent())

    def test_has_ancestor(self):
        from libcellml import Component

        # bool hasParent(Component* c)
        x = Component()
        c1 = Component()
        c2 = Component()
        self.assertFalse(c2.hasAncestor(c1))
        self.assertFalse(c2.hasAncestor(x))

        c1.setParent(x)
        c2.setParent(c1)
        self.assertTrue(c2.hasAncestor(c1))
        self.assertTrue(c2.hasAncestor(x))

    def test_equals(self):
        from libcellml import Units

        u1 = Units("second")
        u1.setId('units_second')

        u2 = Units("second")
        u2.setId('units_second')

        self.assertTrue(u1.equals(u2))


class ParentedEntityTestCase(unittest.TestCase):

    def test_create(self):
        from libcellml.parentedentity import ParentedEntity

        self.assertRaises(AttributeError, ParentedEntity)


class NamedEntityTestCase(unittest.TestCase):

    def test_create(self):
        from libcellml.namedentity import NamedEntity

        self.assertRaises(AttributeError, NamedEntity)


class LoggerTestCase(unittest.TestCase):

    def test_create(self):
        from libcellml.logger import Logger

        self.assertRaises(AttributeError, Logger)


if __name__ == '__main__':
    unittest.main()

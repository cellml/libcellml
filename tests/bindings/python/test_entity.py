#
# Tests the entity class bindings
#
import unittest


class EntityTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Entity

        x = Entity()
        del(x)
        y = Entity()
        z = Entity(y)
        del(y, z)

    def test_id(self):
        from libcellml import Entity

        # std::string getId()
        x = Entity()
        self.assertEqual(x.getId(), '')

        # void setId(const std::string &id)
        idx = 'test'
        x.setId(idx)
        self.assertEqual(x.getId(), idx)

    def test_copy_constructor(self):
        from libcellml import Entity

        x = Entity()
        idx = 'hello'
        x.setId(idx)
        y = Entity(x)
        self.assertEqual(y.getId(), idx)

    def test_get_parent_model(self):
        from libcellml import Entity

        # ModelPtr getParentModel
        # TODO: This method might be moved out of entity!
        # TODO: If not, this needs a workaround!
        x = Entity()
        self.assertIsNone(x.getParentModel())

    def test_get_parent_component(self):
        from libcellml import Entity

        # ComponentPtr getParentComponent
        # TODO: This method might be moved out of entity!
        # TODO: If not, this needs a workaround!
        x = Entity()
        self.assertIsNone(x.getParentComponent())

    def test_set_parent(self):
        from libcellml import Entity, Model, Component

        # void setParent(Model *parent)
        m = Model()
        x = Entity()
        x.setParent(m)
        self.assertIsNotNone(x.getParentModel())
        # TODO: Check equivalence

        c = Component()
        x = Entity()
        x.setParent(c)
        self.assertIsNotNone(x.getParentComponent())
        # TODO: Check equivalence

    def test_clear_parent(self):
        from libcellml import Entity, Model, Component

        # void clearParent()
        x = Entity()
        self.assertIsNone(x.getParentModel())
        x.setParent(Model())
        self.assertIsNotNone(x.getParentModel())
        x.clearParent()
        self.assertIsNone(x.getParentComponent())
        x.setParent(Component())
        self.assertIsNotNone(x.getParentComponent())
        x.clearParent()
        self.assertIsNone(x.getParentModel())
        self.assertIsNone(x.getParentComponent())

    def test_has_parent(self):
        from libcellml import Entity, Component

        # bool hasParent(Component* c)
        x = Entity()
        c = Component()
        self.assertFalse(x.hasParent(c))
        x.setParent(c)
        self.assertTrue(x.hasParent(c))
        x.clearParent()
        self.assertFalse(x.hasParent(c))
        d = Component()
        d.setParent(c)
        x.setParent(d)
        self.assertTrue(x.hasParent(d))
        self.assertTrue(x.hasParent(c))


if __name__ == '__main__':
    unittest.main()

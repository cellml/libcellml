#
# Tests the ComponentEntity class bindings
#
import unittest


class ComponentEntityTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import ComponentEntity

        # Test create/copy/destroy
        x = ComponentEntity()
        del(x)
        y = ComponentEntity()
        z = ComponentEntity(y)
        del(y, z)

    def test_inheritance(self):
        import libcellml
        from libcellml import ComponentEntity

        # Test inheritance
        x = ComponentEntity()
        self.assertIsInstance(x, libcellml.NamedEntity)
        self.assertIsInstance(x, libcellml.Entity)

        # Test access to inherited methods
        idx = 'test'
        self.assertEqual(x.id(), '')
        x.setId(idx)
        self.assertEqual(x.id(), idx)
        y = ComponentEntity(x)
        self.assertEqual(y.id(), idx)

    def test_add_component(self):
        from libcellml import ComponentEntity, Component

        # void addComponent(const ComponentPtr &c)
        x = ComponentEntity()
        y = Component()
        x.addComponent(y)

    def test_remove_component(self):
        from libcellml import ComponentEntity, Component

        # bool removeComponent(size_t index)
        x = ComponentEntity()
        self.assertFalse(x.removeComponent(0))
        self.assertFalse(x.removeComponent(1))
        self.assertFalse(x.removeComponent(-1))
        y = Component()
        x.addComponent(y)
        self.assertFalse(x.removeComponent(1))
        self.assertFalse(x.removeComponent(-1))
        self.assertTrue(x.removeComponent(0))
        del(x, y)

        # bool removeComponent(const std::string &name,
        #    bool searchEncapsulated=true)
        x = ComponentEntity()
        self.assertFalse(x.removeComponent('aaa'))
        self.assertFalse(x.removeComponent('aaa', True))
        self.assertFalse(x.removeComponent('aaa', False))
        self.assertFalse(x.removeComponent('aaa', 'hello'))
        self.assertFalse(x.removeComponent('aaa', 0))
        self.assertFalse(x.removeComponent('aaa', x))
        y = Component()
        name = 'ys-name'
        y.setName(name)
        x.addComponent(y)
        self.assertFalse(x.removeComponent('aaa'))
        self.assertFalse(x.removeComponent('aaa', True))
        self.assertFalse(x.removeComponent('aaa', False))
        self.assertTrue(x.removeComponent(name))
        z = Component()
        y.addComponent(z)
        x.addComponent(y)
        self.assertTrue(x.removeComponent(name))
        del(x, y, z)
        z = Component()
        z.setName(name)
        y = Component()
        y.addComponent(z)
        x = ComponentEntity()
        x.addComponent(y)
        self.assertFalse(x.removeComponent(name, False))
        self.assertTrue(x.removeComponent(name, True))
        self.assertFalse(x.removeComponent(name, True))
        del(x, y, z, name)

        # bool removeComponent(const ComponentPtr &component,
        #   bool searchEncapsulated=true)
        x = ComponentEntity()
        y = Component()
        self.assertFalse(x.removeComponent(y))
        self.assertFalse(x.removeComponent(y, True))
        self.assertFalse(x.removeComponent(y, False))
        self.assertFalse(x.removeComponent(y, 'hello'))
        self.assertFalse(x.removeComponent(y, 0))
        self.assertFalse(x.removeComponent(y, x))
        x.addComponent(y)
        self.assertTrue(x.removeComponent(y))
        self.assertFalse(x.removeComponent(y))
        del(x, y)
        z = Component()
        y = Component()
        y.addComponent(z)
        x = ComponentEntity()
        x.addComponent(y)
        self.assertFalse(x.removeComponent(z, False))
        self.assertTrue(x.removeComponent(z, True))
        self.assertFalse(x.removeComponent(z, True))
        del(x, y, z)

    def test_remove_all_components(self):
        from libcellml import ComponentEntity, Component

        # void removeAllComponents()
        x = ComponentEntity()
        x.removeAllComponents()
        x.addComponent(Component())
        self.assertEqual(x.componentCount(), 1)
        x.removeAllComponents()
        self.assertEqual(x.componentCount(), 0)

    def test_contains_component(self):
        from libcellml import ComponentEntity, Component

        # bool containsComponent(const std::string &name,
        #   bool searchEncapsulated)
        x = ComponentEntity()
        y = Component()
        name = 'blue'
        y.setName(name)
        self.assertFalse(x.containsComponent(name))
        self.assertFalse(x.containsComponent(name, True))
        self.assertFalse(x.containsComponent(name, False))
        self.assertFalse(x.containsComponent(name, name))
        x.addComponent(y)
        self.assertTrue(x.containsComponent(name))
        z = Component()
        name2 = 'green'
        z.setName(name2)
        y.addComponent(z)
        self.assertFalse(x.containsComponent(name2, False))
        self.assertFalse(x.containsComponent(name2, 0))
        self.assertTrue(x.containsComponent(name2, True))
        self.assertTrue(x.containsComponent(name2, name2))
        del(x, y, z, name, name2)

        # bool containsComponent(const ComponentPtr &component,
        #   bool searchEncapsulated)
        x = ComponentEntity()
        y = Component()
        self.assertFalse(x.containsComponent(y))
        self.assertFalse(x.containsComponent(y, True))
        self.assertFalse(x.containsComponent(y, False))
        self.assertFalse(x.containsComponent(y, y))
        x.addComponent(y)
        self.assertTrue(x.containsComponent(y))
        z = Component()
        y.addComponent(z)
        self.assertFalse(x.containsComponent(z, False))
        self.assertFalse(x.containsComponent(z, 0))
        self.assertTrue(x.containsComponent(z, True))
        self.assertTrue(x.containsComponent(z, z))
        del(x, y, z)

    def test_component(self):
        from libcellml import ComponentEntity, Component

        # ComponentPtr component(size_t index)
        name = 'testo'
        x = ComponentEntity()
        y = Component()
        y.setName(name)
        self.assertIsNone(x.component(0))
        self.assertIsNone(x.component(1))
        self.assertIsNone(x.component(-1))
        x.addComponent(y)
        self.assertIsNone(x.component(1))
        self.assertIsNone(x.component(-1))
        self.assertIsNotNone(x.component(0), y)
        self.assertEqual(x.component(0).name(), name)

        # ComponentPtr component(const std::string &name,
        #   bool searchEncapsulated=true)
        name = 'testo'
        x = ComponentEntity()
        y = Component()
        y.setName(name)
        self.assertIsNone(x.component('bonjour'))
        self.assertIsNone(x.component(name))
        self.assertIsNone(x.component(name, True))
        self.assertIsNone(x.component(name, False))
        self.assertIsNone(x.component(name, 1))
        self.assertIsNone(x.component(name, 'hello'))
        x.addComponent(y)
        self.assertIsNone(x.component('hola'))
        self.assertIsNotNone(x.component(name), y)
        self.assertEqual(x.component(name).name(), name)
        del(x, y, name)
        name = 'hiii'
        z = Component()
        z.setName(name)
        y = Component()
        y.addComponent(z)
        x = ComponentEntity()
        x.addComponent(y)
        self.assertIsNone(x.component(name, False))
        self.assertIsNone(x.component(name, 0))
        self.assertIsNone(x.component(name, []))
        self.assertIsNotNone(x.component(name))
        self.assertIsNotNone(x.component(name, True))
        self.assertIsNotNone(x.component(name, 1))
        self.assertIsNotNone(x.component(name, name))
        del(x, y, z, name)

    def test_take_component(self):
        from libcellml import ComponentEntity, Component

        # ComponentPtr takeComponent(size_t index)
        name = 'testo'
        x = ComponentEntity()
        y = Component()
        y.setName(name)
        self.assertIsNone(x.takeComponent(0))
        self.assertIsNone(x.takeComponent(1))
        self.assertIsNone(x.takeComponent(-1))
        x.addComponent(y)
        self.assertIsNone(x.takeComponent(1))
        self.assertIsNone(x.takeComponent(-1))
        self.assertIsNotNone(x.takeComponent(0), y)
        self.assertIsNone(x.takeComponent(0), y)
        x.addComponent(y)
        self.assertEqual(x.takeComponent(0).name(), name)
        self.assertIsNone(x.takeComponent(0), y)

        # ComponentPtr takeComponent(const std::string &name,
        #   bool searchEncapsulated=true)
        name = 'testo'
        x = ComponentEntity()
        y = Component()
        y.setName(name)
        self.assertIsNone(x.takeComponent('bonjour'))
        self.assertIsNone(x.takeComponent(name))
        self.assertIsNone(x.takeComponent(name, True))
        self.assertIsNone(x.takeComponent(name, False))
        self.assertIsNone(x.takeComponent(name, 1))
        self.assertIsNone(x.takeComponent(name, 'hello'))
        x.addComponent(y)
        self.assertIsNone(x.takeComponent('hola'))
        self.assertIsNotNone(x.takeComponent(name), y)
        self.assertIsNone(x.takeComponent(name), y)
        x.addComponent(y)
        self.assertEqual(x.takeComponent(name).name(), name)
        del(x, y, name)
        name = 'hiii'
        z = Component()
        z.setName(name)
        y = Component()
        y.addComponent(z)
        x = ComponentEntity()
        x.addComponent(y)
        self.assertIsNone(x.takeComponent(name, False))
        self.assertIsNone(x.takeComponent(name, 0))
        self.assertIsNone(x.takeComponent(name, []))
        self.assertIsNotNone(x.takeComponent(name))
        del(x, y, name)
        name = 'hiii'
        z = Component()
        z.setName(name)
        y = Component()
        y.addComponent(z)
        x = ComponentEntity()
        x.addComponent(y)
        self.assertIsNotNone(x.takeComponent(name, True))
        self.assertIsNone(x.takeComponent(name, True))
        del(x, y, name)
        name = 'hiii'
        z = Component()
        z.setName(name)
        y = Component()
        y.addComponent(z)
        x = ComponentEntity()
        x.addComponent(y)
        self.assertIsNotNone(x.takeComponent(name, 1))
        self.assertIsNone(x.takeComponent(name, 1))
        del(x, y, name)
        name = 'hiii'
        z = Component()
        z.setName(name)
        y = Component()
        y.addComponent(z)
        x = ComponentEntity()
        x.addComponent(y)
        self.assertIsNotNone(x.takeComponent(name, name))
        self.assertIsNone(x.takeComponent(name, name))
        del(x, y, z, name)

    def test_replace_component(self):
        from libcellml import ComponentEntity, Component

        # bool replaceComponent(size_t index, const ComponentPtr &c)
        x = ComponentEntity()
        a = Component()
        b = Component()
        self.assertFalse(x.replaceComponent(0, b))
        self.assertFalse(x.replaceComponent(1, b))
        self.assertFalse(x.replaceComponent(-1, b))
        x.addComponent(a)
        self.assertTrue(x.containsComponent(a))
        self.assertFalse(x.containsComponent(b))
        self.assertFalse(x.replaceComponent(1, b))
        self.assertFalse(x.replaceComponent(-1, b))
        self.assertTrue(x.replaceComponent(0, b))
        self.assertTrue(x.containsComponent(b))
        self.assertFalse(x.containsComponent(a))

        # bool replaceComponent(const std::string &name, const ComponentPtr &c,
        #   bool searchEncapsulated = true)
        x = ComponentEntity()
        a = Component()
        a.setName('a')
        b = Component()
        b.setName('b')
        self.assertFalse(x.replaceComponent('a', b))
        self.assertFalse(x.replaceComponent('b', a))
        x.addComponent(a)
        self.assertTrue(x.containsComponent(a))
        self.assertFalse(x.containsComponent(b))
        self.assertFalse(x.replaceComponent('b', a))
        self.assertTrue(x.replaceComponent('a', b))
        self.assertTrue(x.containsComponent(b))
        self.assertFalse(x.containsComponent(a))
        self.assertTrue(x.replaceComponent('b', a, True))
        self.assertTrue(x.replaceComponent('a', b, False))
        self.assertTrue(x.replaceComponent('b', a, 100))
        self.assertTrue(x.replaceComponent('a', b, []))
        self.assertTrue(x.replaceComponent('b', a, 'yes'))
        self.assertTrue(x.replaceComponent('a', b, a))
        del(x, a, b)

        # replaceComponent(const ComponentPtr &c1, const ComponentPtr &c2,
        #   bool searchEncapsulated = true)
        x = ComponentEntity()
        a = Component()
        b = Component()
        self.assertFalse(x.replaceComponent(a, b))
        self.assertFalse(x.replaceComponent(b, a))
        x.addComponent(a)
        self.assertTrue(x.containsComponent(a))
        self.assertFalse(x.containsComponent(b))
        self.assertFalse(x.replaceComponent(b, a))
        self.assertTrue(x.replaceComponent(a, b))
        self.assertTrue(x.containsComponent(b))
        self.assertFalse(x.containsComponent(a))
        self.assertTrue(x.replaceComponent(b, a, True))
        self.assertTrue(x.replaceComponent(a, b, False))
        self.assertTrue(x.replaceComponent(b, a, 100))
        self.assertTrue(x.replaceComponent(a, b, []))
        self.assertTrue(x.replaceComponent(b, a, 'yes'))
        self.assertTrue(x.replaceComponent(a, b, a))

    def test_component_count(self):
        from libcellml import ComponentEntity, Component

        # size_t componentCount()
        x = ComponentEntity()
        self.assertEqual(x.componentCount(), 0)
        x.addComponent(Component())
        self.assertEqual(x.componentCount(), 1)
        x.addComponent(Component())
        self.assertEqual(x.componentCount(), 2)
        y = Component()
        x.addComponent(y)
        self.assertEqual(x.componentCount(), 3)
        y.addComponent(Component())
        self.assertEqual(x.componentCount(), 3)
        y.addComponent(Component())
        self.assertEqual(x.componentCount(), 3)
        self.assertTrue(x.removeComponent(2))
        self.assertEqual(x.componentCount(), 2)
        self.assertTrue(x.removeComponent(0))
        self.assertEqual(x.componentCount(), 1)
        self.assertTrue(x.removeComponent(0))
        self.assertEqual(x.componentCount(), 0)

    def test_set_encapsulation_id(self):
        from libcellml import ComponentEntity

        # void setEncapsulationId(const std::string &id);
        x = ComponentEntity()
        x.setEncapsulationId('Hello')
        x.setEncapsulationId('')

    def test_encapsulation_id(self):
        from libcellml import ComponentEntity

        # std::string encapsulationId() const;
        x = ComponentEntity()
        self.assertEqual(x.encapsulationId(), '')
        x.setEncapsulationId('Hello')
        self.assertEqual(x.encapsulationId(), 'Hello')
        x.setEncapsulationId('')
        self.assertEqual(x.encapsulationId(), '')


if __name__ == '__main__':
    unittest.main()

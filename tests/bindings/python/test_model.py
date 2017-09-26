#
# Tests the Model class bindings
#
import sys
import unittest

class ModelTestCase(unittest.TestCase):

    def test_model(self):
        import libcellml
        from libcellml import Model
        
        # Test create/copy/destroy
        x = Model()
        del(x)
        y = Model()
        z = Model(y)
        del(y, z)
        
        # Test inheritance
        x = Model()
        self.assertIsInstance(x, libcellml.ComponentEntity)
        self.assertIsInstance(x, libcellml.ImportedEntity)
        self.assertIsInstance(x, libcellml.NamedEntity)
        self.assertIsInstance(x, libcellml.Entity)
        
        # Test access to inherited methods
        x = Model()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        y = Model(x)
        self.assertEqual(y.getId(), idx)
        del(x, y, idx)
        
        # Test own methods
        
        # void addUnits(const UnitsPtr &units)
        from libcellml import Units
        m = Model()
        u = Units()
        m.addUnits(u)
        del(m, u)
        
        # bool removeUnits(size_t index)
        m = Model()
        u = Units()
        self.assertFalse(m.removeUnits(0))
        self.assertFalse(m.removeUnits(1))
        self.assertFalse(m.removeUnits(-1))
        m.addUnits(u)
        self.assertFalse(m.removeUnits(1))
        self.assertFalse(m.removeUnits(-1))
        self.assertTrue(m.removeUnits(0))
        self.assertFalse(m.removeUnits(0))        
        del(m, u)
        
        # bool removeUnits(const std::string &name)
        name = 'bert'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertFalse(m.removeUnits(name))
        m.addUnits(u)
        self.assertFalse(m.removeUnits('ernie'))
        self.assertTrue(m.removeUnits(name))
        del(m, u, name)
        
        # bool removeUnits(const UnitsPtr &units)
        m = Model()
        u1 = Units()
        u2 = Units()
        self.assertFalse(m.removeUnits(u1))
        m.addUnits(u1)
        self.assertFalse(m.removeUnits(u2))
        self.assertTrue(m.removeUnits(u1))
        self.assertFalse(m.removeUnits(u1))
        del(m, u1, u2)
        
        # void removeAllUnits()
        m = Model()
        u1 = Units()
        u2 = Units()
        m.addUnits(u1)
        m.addUnits(u2)
        m.removeAllUnits()
        self.assertFalse(m.removeUnits(u1))
        self.assertFalse(m.removeUnits(u2))
        del(m, u1, u2)
        
        # bool hasUnits(const std::string &name)
        name = 'loud'
        m = Model()
        u = Units()
        u.setName(name)
        m.addUnits(u)
        self.assertFalse(m.hasUnits('hi'))
        self.assertTrue(m.hasUnits(name))
        del(name, m, u)
        
        # UnitsPtr getUnits(size_t index)
        name = 'naaame'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertIsNone(m.getUnits(0))
        self.assertIsNone(m.getUnits(1))
        self.assertIsNone(m.getUnits(-1))
        m.addUnits(u)
        self.assertIsNone(m.getUnits(1))
        self.assertIsNone(m.getUnits(-1))
        self.assertIsNotNone(m.getUnits(0))
        self.assertEqual(m.getUnits(0).getName(), name)
        del(m, u, name)
        
        # UnitsPtr getUnits(const std::string &name)
        name = 'kermit'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertIsNone(m.getUnits(name))
        m.addUnits(u)
        self.assertIsNotNone(m.getUnits(name))
        self.assertEqual(m.getUnits(name).getName(), name)
        del(m, u, name)
        
        # UnitsPtr takeUnits(size_t index)
        name = 'piggy'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertIsNone(m.takeUnits(0))
        self.assertIsNone(m.takeUnits(-1))
        self.assertIsNone(m.takeUnits(1))
        m.addUnits(u)
        self.assertIsNone(m.takeUnits(-1))
        self.assertIsNone(m.takeUnits(1))
        self.assertIsNotNone(m.takeUnits(0))
        self.assertIsNone(m.takeUnits(0))
        m.addUnits(Units())
        m.addUnits(u)
        self.assertEqual(m.takeUnits(1).getName(), name)
        del(m, u)
        
        # UnitsPtr takeUnits(const std::string &name)
        name = 'aloha'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertIsNone(m.takeUnits(name))
        m.addUnits(u)
        self.assertEquals(m.takeUnits(name).getName(), name)
        self.assertIsNone(m.takeUnits(name))
        del(m, u, name)
        
        # bool replaceUnits(size_t index, const UnitsPtr &units)
        m = Model()
        u1 = Units()
        u1.setName('a')
        m.addUnits(u1)
        u2 = Units()
        u2.setName('b')
        self.assertTrue(m.replaceUnits(0, u2))
        self.assertFalse(m.replaceUnits(1, u1))
        self.assertFalse(m.replaceUnits(-1, u1))
        self.assertEqual(m.getUnits(0).getName(), 'b')
        del(m, u1, u2)
        
        # bool replaceUnits(const std::string &name, const UnitsPtr &units)
        m = Model()
        a = Units()
        a.setName('a')
        m.addUnits(a)
        b = Units()
        b.setName('b')
        self.assertFalse(m.replaceUnits('b', a))
        self.assertTrue(m.replaceUnits('a', b))
        self.assertTrue(m.replaceUnits('b', a))
        self.assertFalse(m.replaceUnits('b', a))
        del(m, a, b)
        
        #TODO bool replaceUnits(const UnitsPtr &oldUnits, const UnitsPtr &newUnits)
        
        # size_t unitsCount()
        m = Model()
        self.assertEqual(m.unitsCount(), 0)
        m.addUnits(Units())
        self.assertEqual(m.unitsCount(), 1)
        m.addUnits(Units())
        self.assertEqual(m.unitsCount(), 2)
        m.removeAllUnits()
        self.assertEqual(m.unitsCount(), 0)
        del(m)

if __name__ == '__main__':
    unittest.main()

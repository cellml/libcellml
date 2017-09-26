#
# Tests the Units class bindings
#
import sys
import unittest

class UnitsTestCase(unittest.TestCase):

    def test_model(self):
        import libcellml
        from libcellml import Units
        
        # Test create/copy/destroy
        x = Units()
        del(x)
        y = Units()
        z = Units(y)
        del(y, z)
        
        # Test inheritance
        x = Units()
        self.assertIsInstance(x, libcellml.ImportedEntity)
        self.assertIsInstance(x, libcellml.NamedEntity)
        self.assertIsInstance(x, libcellml.Entity)
        
        # Test access to inherited methods
        x = Units()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        y = Units(x)
        self.assertEqual(y.getId(), idx)
        del(x, y, idx)
        
        # Test standard units
        u = Units()
        u.addUnit(Units.StandardUnit.AMPERE)
        u.addUnit(Units.StandardUnit.BECQUEREL)
        u.addUnit(Units.StandardUnit.CANDELA)
        u.addUnit(Units.StandardUnit.COULOMB)
        u.addUnit(Units.StandardUnit.DIMENSIONLESS)
        u.addUnit(Units.StandardUnit.FARAD)
        u.addUnit(Units.StandardUnit.GRAM)
        u.addUnit(Units.StandardUnit.GRAY)
        u.addUnit(Units.StandardUnit.HENRY)
        u.addUnit(Units.StandardUnit.HERTZ)
        u.addUnit(Units.StandardUnit.JOULE)
        u.addUnit(Units.StandardUnit.KATAL)
        u.addUnit(Units.StandardUnit.KELVIN)
        u.addUnit(Units.StandardUnit.KILOGRAM)
        u.addUnit(Units.StandardUnit.LITER)
        u.addUnit(Units.StandardUnit.LITRE)
        u.addUnit(Units.StandardUnit.LUMEN)
        u.addUnit(Units.StandardUnit.LUX)
        u.addUnit(Units.StandardUnit.METER)
        u.addUnit(Units.StandardUnit.METRE)
        u.addUnit(Units.StandardUnit.MOLE)
        u.addUnit(Units.StandardUnit.NEWTON)
        u.addUnit(Units.StandardUnit.OHM)
        u.addUnit(Units.StandardUnit.PASCAL)
        u.addUnit(Units.StandardUnit.RADIAN)
        u.addUnit(Units.StandardUnit.SECOND)
        u.addUnit(Units.StandardUnit.SIEMENS)
        u.addUnit(Units.StandardUnit.SIEVERT)
        u.addUnit(Units.StandardUnit.STERADIAN)
        u.addUnit(Units.StandardUnit.TESLA)
        u.addUnit(Units.StandardUnit.VOLT)
        u.addUnit(Units.StandardUnit.WATT)
        u.addUnit(Units.StandardUnit.WEBER)
        
        # Test prefixes
        u.addUnit('test', Units.Prefix.YOTTA)
        u.addUnit('test', Units.Prefix.ZETTA)
        u.addUnit('test', Units.Prefix.EXA)
        u.addUnit('test', Units.Prefix.PETA)
        u.addUnit('test', Units.Prefix.TERA)
        u.addUnit('test', Units.Prefix.GIGA)
        u.addUnit('test', Units.Prefix.MEGA)
        u.addUnit('test', Units.Prefix.KILO)
        u.addUnit('test', Units.Prefix.HECTO)
        u.addUnit('test', Units.Prefix.DECA)
        u.addUnit('test', Units.Prefix.DECI)
        u.addUnit('test', Units.Prefix.CENTI)
        u.addUnit('test', Units.Prefix.MILLI)
        u.addUnit('test', Units.Prefix.MICRO)
        u.addUnit('test', Units.Prefix.NANO)
        u.addUnit('test', Units.Prefix.PICO)
        u.addUnit('test', Units.Prefix.FEMTO)
        u.addUnit('test', Units.Prefix.ATTO)
        u.addUnit('test', Units.Prefix.ZEPTO)
        u.addUnit('test', Units.Prefix.YOCTO)

        # Test own methods
        
        # bool isBaseUnit()
        u = Units()
        self.assertTrue(u.isBaseUnit())
        u.addUnit(Units.StandardUnit.NEWTON)
        self.assertFalse(u.isBaseUnit())
        del(u)
        
        # void addUnit(const std::string &reference, const std::string &prefix,
        #   double exponent=1.0, double multiplier=1.0)
        u = Units()
        u.addUnit('a', 'b')
        u.addUnit('a', 'b', 2.0)
        u.addUnit('a', 'b', -1)
        u.addUnit('a', 'b', 0)
        u.addUnit('a', 'b', 3, 3)
        u.addUnit('a', 'b', 0.1, -1.2)
        del(u)
        
        # void addUnit(const std::string &reference, Prefix prefix,
        #   double exponent=1.0, double multiplier=1.0)
        u = Units()
        u.addUnit('a', Units.Prefix.YOTTA)
        u.addUnit('a', Units.Prefix.YOTTA, -1)
        u.addUnit('a', Units.Prefix.YOTTA, 2.3)
        u.addUnit('a', Units.Prefix.YOTTA, -1, 3)
        u.addUnit('a', Units.Prefix.YOTTA, -1, 2.3)
        u.addUnit('a', Units.Prefix.YOTTA, 1.2, 3.4)
        del(u)
        
        # void addUnit(const std::string &reference, double prefix,
        #   double exponent, double multiplier=1.0)
        u = Units()
        u.addUnit('a', 1.2, -1)
        u.addUnit('a', 1.2, 2.3)
        u.addUnit('a', 1.2, -1, 3)
        u.addUnit('a', 1.2, -1, 2.3)
        u.addUnit('a', 1.2, 1.2, 3.4)
        #TODO Ints get converted to Prefix enum, not to double!
        #u.addUnit('a', -1, -1)
        #u.addUnit('a', -1, 2.3)
        #u.addUnit('a', -1, -1, 3)
        #u.addUnit('a', -1, -1, 2.3)
        #u.addUnit('a', -1, 1.2, 3.4)
        del(u)
        
        # void addUnit(const std::string &reference, double exponent)
        u = Units()
        u.addUnit('a', 1.0)
        #TODO Ints get converted to Prefix enum, not to double!
        #u.addUnit('a', -1)
        del(u)
        
        # void addUnit(const std::string &reference)
        u = Units()
        u.addUnit('')
        u.addUnit('a')
        del(u)
        
        # void addUnit(StandardUnit standardRef, const std::string &prefix,
        #   double exponent=1.0, double multiplier=1.0)
        u = Units()
        u.addUnit(Units.StandardUnit.KATAL, 'pico')
        u.addUnit(Units.StandardUnit.KATAL, 'pico', 1.0)
        u.addUnit(Units.StandardUnit.KATAL, 'pico', -1)
        u.addUnit(Units.StandardUnit.KATAL, 'pico', 1.0, 2.0)
        u.addUnit(Units.StandardUnit.KATAL, 'pico', 1, 2.0)
        u.addUnit(Units.StandardUnit.KATAL, 'pico', -1, 2)
        del(u)
        
        # void addUnit(StandardUnit standardRef, Prefix prefix,
        #   double exponent=1.0, double multiplier=1.0)
        u = Units()
        u.addUnit(Units.StandardUnit.KATAL, Units.Prefix.PICO)
        u.addUnit(Units.StandardUnit.KATAL, Units.Prefix.PICO, 1.0)
        u.addUnit(Units.StandardUnit.KATAL, Units.Prefix.PICO, -1)
        u.addUnit(Units.StandardUnit.KATAL, Units.Prefix.PICO, 1.0, 2.0)
        u.addUnit(Units.StandardUnit.KATAL, Units.Prefix.PICO, 1, 2.0)
        u.addUnit(Units.StandardUnit.KATAL, Units.Prefix.PICO, -1, 2)
        del(u)
        
        # void addUnit(StandardUnit standardRef, double prefix,
        #   double exponent, double multiplier=1.0)
        u = Units()
        u.addUnit(Units.StandardUnit.KATAL, 1.0, 1.0)
        u.addUnit(Units.StandardUnit.KATAL, -1.0, -1.0)
        u.addUnit(Units.StandardUnit.KATAL, 1.0, 1.0, 1.0)
        u.addUnit(Units.StandardUnit.KATAL, -1.0, -1.0, 1.0)
        del(u)
        
        # void addUnit(StandardUnit standardRef, double exponent)
        u = Units()
        u.addUnit(Units.StandardUnit.KATAL, 1.0)
        u.addUnit(Units.StandardUnit.KATAL, -1.0)
        u.addUnit(Units.StandardUnit.KATAL, 1)
        u.addUnit(Units.StandardUnit.KATAL, -1)
        del(u)
        
        # void addUnit(StandardUnit standardRef)
        u = Units()
        u.addUnit(Units.StandardUnit.KATAL)
        del(u)
        
        # void getUnitAttributes(size_t index, std::string& reference,
        #   std::string &prefix, double &exponent, double &multiplier)
        u = Units()
        x = u.getUnitAttributes(0)
        self.assertIsInstance(x, list)
        self.assertEqual(x, ['', '', 1.0, 1.0])
        u.addUnit('blabla', 'hello', 1.2, 3.4)
        x = u.getUnitAttributes(0)
        self.assertIsInstance(x, list)
        self.assertEqual(x, ['blabla', 'hello', 1.2, 3.4])
        x = u.getUnitAttributes(1)
        self.assertIsInstance(x, list)
        self.assertEqual(x, ['', '', 1.0, 1.0])
        del(u, x)
        
        # void getUnitAttributes(const std::string &reference,
        #   std::string &prefix, double &exponent, double &multiplier) const;
        u = Units()
        x = u.getUnitAttributes('newton')
        self.assertIsInstance(x, list)
        self.assertEqual(x, ['newton', '', 1.0, 1.0])
        u.addUnit('few', 'bars', 4.3, 2.1)
        x = u.getUnitAttributes('newton')
        self.assertIsInstance(x, list)
        self.assertEqual(x, ['newton', '', 1.0, 1.0])
        x = u.getUnitAttributes('few')
        self.assertIsInstance(x, list)
        self.assertEqual(x, ['few', 'bars', 4.3, 2.1])
        del(u, x)
        
        # This method conflicts with getUnitAttributes(size_t, ...)
        # void getUnitAttributes(StandardUnit standardRef, std::string &prefix,
        #   double &exponent, double &multiplier) const;
        
        # bool removeUnit(size_t index)
        u = Units()
        self.assertFalse(u.removeUnit(0))
        self.assertFalse(u.removeUnit(1))
        self.assertFalse(u.removeUnit(-1))
        u.addUnit('hello')
        self.assertFalse(u.removeUnit(1))
        self.assertFalse(u.removeUnit(-1))
        self.assertTrue(u.removeUnit(0))
        self.assertFalse(u.removeUnit(0))
        del(u)
        
        # bool removeUnit(const std::string &reference)
        u = Units()
        self.assertFalse(u.removeUnit('hello'))
        u.addUnit('hello')
        self.assertFalse(u.removeUnit('hi'))
        self.assertTrue(u.removeUnit('hello'))
        self.assertFalse(u.removeUnit('hello'))
        del(u)

        # This method conflicts with removeUnit(size_t)        
        # bool removeUnit(StandardUnit standardRef)
        
        # size_t unitCount()
        u = Units()
        self.assertEqual(u.unitCount(), 0)
        u.addUnit('')
        self.assertEqual(u.unitCount(), 1)
        u.addUnit('')
        self.assertEqual(u.unitCount(), 2)
        del(u)
        
        # void removeAllUnits()
        u = Units()
        self.assertEqual(u.unitCount(), 0)
        u.addUnit('')
        self.assertEqual(u.unitCount(), 1)
        u.addUnit('')
        self.assertEqual(u.unitCount(), 2)
        u.removeAllUnits()
        self.assertEqual(u.unitCount(), 0)
        del(u)
        
        # void setSourceUnits(const ImportPtr &imp, const std::string &name)
        from libcellml import ImportSource
        i = ImportSource()
        u = Units()
        u.setSourceUnits(i, 'hello')
        del(u, i)

if __name__ == '__main__':
    unittest.main()

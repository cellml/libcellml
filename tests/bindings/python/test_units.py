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
        del(y,z)
        
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
        del(x, y)
        
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
        
        # Test own methods
        
        # bool isBaseUnit()
        u = Units()
        self.assertTrue(u.isBaseUnit())
        u.addUnit(Units.StandardUnit.NEWTON)
        self.assertFalse(u.isBaseUnit())
        
        
        # void addUnit(const std::string &reference, const std::string &prefix,
        #   double exponent=1.0, double multiplier=1.0)
        # void addUnit(const std::string &reference, Prefix prefix,
        #   double exponent=1.0, double multiplier=1.0)
        # void addUnit(const std::string &reference, double prefix,
        #   double exponent, double multiplier=1.0)
        # void addUnit(const std::string &reference, double exponent)
        # void addUnit(const std::string &reference)
        # void addUnit(StandardUnit standardRef, const std::string &prefix,
        #   double exponent=1.0, double multiplier=1.0)
        # void addUnit(StandardUnit standardRef, Prefix prefix,
        #   double exponent=1.0, double multiplier=1.0)
        # void addUnit(StandardUnit standardRef, double prefix,
        #   double exponent, double multiplier=1.0)
        # void addUnit(StandardUnit standardRef, double exponent)
        # void addUnit(StandardUnit standardRef)
        
        # Test built-in units
        #TODO

        
        # void getUnitAttributes(size_t index, std::string& reference,
        #   std::string &prefix, double &exponent, double &multiplier)
        # void getUnitAttributes(const std::string &reference,
        #   std::string &prefix, double &exponent, double &multiplier)
        # void getUnitAttributes(StandardUnit standardRef, std::string &prefix,
        #   double &exponent, double &multiplier)
        # bool removeUnit(size_t index)
        # bool removeUnit(const std::string &reference)
        # bool removeUnit(StandardUnit standardRef)
        # void removeAllUnits()
        # void setSourceUnits(const ImportPtr &imp, const std::string &name)
        # size_t unitCount()


if __name__ == '__main__':
    unittest.main()

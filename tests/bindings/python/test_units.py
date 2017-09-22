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
        
        # Test built-in units
        #TODO
        
        # Test own methods
        
        #bool isBaseUnit()
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

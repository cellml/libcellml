#
# Tests the Component class bindings
#
import unittest


class AnnotatorTestCase(unittest.TestCase):

    # def test_create_destroy(self):
    #     from libcellml import Annotator

    #     x = Annotator()
    #     self.assertIsNotNone(x)
    #     del(x)

    # def test_item(self):
    #     from libcellml import Annotator, Model, Parser
    #     annotator = Annotator()
    #     model = Model()
    #     parser = Parser()

    #     model_string = '<?xml version="1.0" encoding="UTF-8"?>\n' + \
    #         '<model xmlns="http://www.cellml.org/cellml/2.0#" name="everything" id="model_1">\n' + \
    #         '  <import xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="some-other-model.xml" id="import_1">\n' + \
    #         '    <component component_ref="a_component_in_that_model" name="component1" id="component_1"/>\n' + \
    #         '  </import>\n' + \
    #         '  <import xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="some-other-model.xml" id="import_2">\n' + \
    #         '    <units units_ref="a_units_in_that_model" name="units1" id="units_1"/>\n' + \
    #         '  </import>\n' + \
    #         '  <units name="units2" id="units_2">\n' + \
    #         '    <unit units="second" id="unit_1"/>\n' + \
    #         '  </units>\n' + \
    #         '  <units name="units3" id="units_3"/>\n' + \
    #         '  <units name="blob" id="units_4"/>\n' + \
    #         '  <component name="component2" id="component_2">\n' + \
    #         '    <variable name="variable1" units="units2" interface="private" id="variable_1"/>\n' + \
    #         '    <variable name="variable2" units="units2" id="variable_2"/>\n' + \
    #         '    <reset variable="variable1" test_variable="variable2" order="1" id="reset_1">\n' + \
    #         '      <test_value id="test_value_1">\n' + \
    #         '        <math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#" id="math_1">\n' + \
    #         '          <apply id="apply_1">\n' + \
    #         '            <eq id="eq_1"/>\n' + \
    #         '            <ci id="ci_1">variable1</ci>\n' + \
    #         '            <cn cellml:units="units2" id="cn_1">3.4</cn>\n' + \
    #         '          </apply>\n' + \
    #         '        </math>\n' + \
    #         '      </test_value>\n' + \
    #         '      <reset_value id="reset_value_1">\n' + \
    #         '        <math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#" id="math_2">\n' + \
    #         '          <apply id="apply_2">\n' + \
    #         '            <eq id="eq_2"/>\n' + \
    #         '            <ci id="ci_2">variable1</ci>\n' + \
    #         '            <cn cellml:units="units2" id="cn_2">9.0</cn>\n' + \
    #         '          </apply>\n' + \
    #         '        </math>\n' + \
    #         '      </reset_value>\n' + \
    #         '    </reset>\n' + \
    #         '  </component>\n' + \
    #         '  <component name="component3" id="component_3">\n' + \
    #         '    <variable name="variable4" units="units2" interface="public" id="variable_3"/>\n' + \
    #         '    <variable name="variable2" units="units2" interface="public" id="variable_4"/>\n' + \
    #         '    <math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#" id="math_3">\n' + \
    #         '      <apply id="apply_3">\n' + \
    #         '        <eq id="eq_3"/>\n' + \
    #         '        <ci id="ci_3">variable4</ci>\n' + \
    #         '        <cn cellml:units="units2" id="cn_3">9.0</cn>\n' + \
    #         '      </apply>\n' + \
    #         '    </math>\n' + \
    #         '  </component>\n' + \
    #         '  <connection component_1="component2" component_2="component3" id="connection_1">\n' + \
    #         '    <map_variables variable_1="variable1" variable_2="variable2" id="map_variables_1"/>\n' + \
    #         '    <map_variables variable_1="variable1" variable_2="variable4" id="map_variables_2"/>\n' + \
    #         '  </connection>\n' + \
    #         '  <encapsulation id="encapsulation_1">\n' + \
    #         '    <component_ref component="component2" id="component_ref_1">\n' + \
    #         '      <component_ref component="component3" id="component_ref_2"/>\n' + \
    #         '    </component_ref>\n' + \
    #         '  </encapsulation>\n' + \
    #         '</model>\n'

    #     model = parser.parseModel(model_string)
    #     annotator.build(model)

    #     v1v2 = (model.component("component2").variable("variable1"), model.component(
    #         "component2").component("component3").variable("variable2"))
    #     v1v4 = (model.component("component2").variable("variable1"), model.component(
    #         "component2").component("component3").variable("variable4"))

    #     self.assertEqual(model.name(), annotator.model("model_1").name())
    #     self.assertEqual(model.component("component1").name(),
    #                      annotator.component("component_1").name())
    #     self.assertEqual(model.component("component2").name(),
    #                      annotator.component("component_2").name())
    #     self.assertEqual(model.component("component2").name(),
    #                      annotator.component("component_ref_1").name())
    #     self.assertEqual(model.component("component2").component("component3").name(),
    #                      annotator.component("component_3").name())
    #     self.assertEqual(model.component("component2").component("component3").name(),
    #                      annotator.componentRef("component_ref_2").name())
    #     self.assertEqual(model.component("component1").importSource().url(),
    #                      annotator.importSource("import_1").url())
    #     self.assertEqual(model.units("units1").name(),
    #                      annotator.units("units_1").name())
    #     self.assertEqual(model.units("units1").importSource().url(),
    #                      annotator.importSource("import_2").url())
    #     self.assertEqual(model.units("units2").name(),
    #                      annotator.units("units_2").name())

    #     self.assertEqual(model.units("units2").name(),
    #                      annotator.unit("unit_1")[0].name())
    #     self.assertEqual(0, annotator.unit("unit_1")[1])

    #     self.assertEqual(model.component("component2").variable("variable1").name(),
    #                      annotator.variable("variable_1").name())

    #     self.assertEqual(model.component("component2").variable("variable2").name(),
    #                      annotator.variable("variable_2").name())
    #     self.assertEqual(model.component("component2").reset(0).variable().name(),
    #                      annotator.reset("reset_1").variable().name())
    #     self.assertEqual(model.component("component2").reset(0).testVariable().name(),
    #                      annotator.reset("reset_1").testVariable().name())
    #     self.assertEqual(model.component("component2").reset(0).testValue(),
    #                      annotator.testValue("test_value_1").testValue())
    #     self.assertEqual(model.component("component2").reset(0).resetValue(),
    #                      annotator.resetValue("reset_value_1").resetValue())

    #     self.assertEqual(model.component("component2").component("component3").variable("variable4").name(),
    #                      annotator.variable("variable_3").name())
    #     self.assertEqual(model.component("component2").component("component3").variable("variable2").name(),
    #                      annotator.variable("variable_4").name())
    #     self.assertEqual(v1v2[0].name(), annotator.connection(
    #         "connection_1")[0].name())
    #     self.assertEqual(v1v2[1].name(), annotator.connection(
    #         "connection_1")[1].name())
    #     self.assertEqual(v1v2[0].name(), annotator.mapVariables(
    #         "map_variables_1")[0].name())
    #     self.assertEqual(v1v2[1].name(), annotator.mapVariables(
    #         "map_variables_1")[1].name())
    #     self.assertEqual(v1v4[0].name(), annotator.mapVariables(
    #         "map_variables_2")[0].name())
    #     self.assertEqual(v1v4[1].name(), annotator.mapVariables(
    #         "map_variables_2")[1].name())

    #     self.assertEqual(None, annotator.model("i_dont_exist"))
    #     self.assertEqual(None, annotator.component("i_dont_exist"))
    #     self.assertEqual(None, annotator.variable("i_dont_exist"))
    #     self.assertEqual(None, annotator.units("i_dont_exist"))
    #     self.assertEqual((None, -1), annotator.unit("i_dont_exist"))
    #     self.assertEqual(None, annotator.reset("i_dont_exist"))
    #     self.assertEqual(None, annotator.resetValue("i_dont_exist"))
    #     self.assertEqual(None, annotator.testValue("i_dont_exist"))
    #     self.assertEqual(None, annotator.componentRef("i_dont_exist"))
    #     self.assertEqual((None, None), annotator.connection("i_dont_exist"))
    #     self.assertEqual((None, None), annotator.mapVariables("i_dont_exist"))
    #     self.assertEqual(None, annotator.importSource("i_dont_exist"))

    # def test_auto_ids(self):
    #     from libcellml import Annotator, Model, Parser, Variable
    #     annotator = Annotator()
    #     parser = Parser()
    #     model_string = '<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n' + \
    #                    '<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\">\n' + \
    #                    '  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n' + \
    #                    '    <component component_ref=\"a_component_in_that_model\" name=\"component1\" />\n' + \
    #                    '  </import>\n' + \
    #                    '  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n' + \
    #                    '    <units units_ref=\"a_units_in_that_model\" name=\"units1\"/>\n' + \
    #                    '  </import>\n' + \
    #                    '  <units name=\"units2\">\n' + \
    #                    '    <unit units=\"second\"/>\n' + \
    #                    '  </units>\n' + \
    #                    '  <units name=\"units3\"/>\n' + \
    #                    '  <units name=\"blob\"/>\n' + \
    #                    '  <component name=\"component2\">\n' + \
    #                    '    <variable name=\"variable1\" units=\"units2\" interface=\"private\"/>\n' + \
    #                    '    <variable name=\"variable2\" units=\"units2\"/>\n' + \
    #                    '    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\">\n' + \
    #                    '      <test_value>\n' + \
    #                    '        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n' + \
    #                    '          <apply>\n' + \
    #                    '            <eq/>\n' + \
    #                    '            <ci>variable1</ci>\n' + \
    #                    '            <cn cellml:units=\"units2\">3.4</cn>\n' + \
    #                    '          </apply>\n' + \
    #                    '        </math>\n' + \
    #                    '      </test_value>\n' + \
    #                    '      <reset_value>\n' + \
    #                    '        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n' + \
    #                    '          <apply>\n' + \
    #                    '            <eq/>\n' + \
    #                    '            <ci>variable1</ci>\n' + \
    #                    '            <cn cellml:units=\"units2\">9.0</cn>\n' + \
    #                    '          </apply>\n' + \
    #                    '        </math>\n' + \
    #                    '      </reset_value>\n' + \
    #                    '    </reset>\n' + \
    #                    '  </component>\n' + \
    #                    '  <component name=\"component3\">\n' + \
    #                    '    <variable name=\"variable4\" units=\"units2\" interface=\"public\"/>\n' + \
    #                    '    <variable name=\"variable2\" units=\"units2\" interface=\"public\"/>\n' + \
    #                    '    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n' + \
    #                    '      <apply>\n' + \
    #                    '        <eq/>\n' + \
    #                    '        <ci>variable4</ci>\n' + \
    #                    '        <cn cellml:units=\"units2\">9.0</cn>\n' + \
    #                    '      </apply>\n' + \
    #                    '    </math>\n' + \
    #                    '  </component>\n' + \
    #                    '  <connection component_1=\"component2\" component_2=\"component3\">\n' + \
    #                    '    <map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>\n' + \
    #                    '    <map_variables variable_1=\"variable1\" variable_2=\"variable4\"/>\n' + \
    #                    '  </connection>\n' + \
    #                    '  <encapsulation>\n' + \
    #                    '    <component_ref component=\"component2\">\n' + \
    #                    '      <component_ref component=\"component3\"/>\n' + \
    #                    '    </component_ref>\n' + \
    #                    '  </encapsulation>\n' + \
    #                    '</model>\n'

    #     model = parser.parseModel(model_string)
    #     annotator.build(model)

    #     annotator.setAutomaticIds()

    #     self.assertEqual("b4da55", model.id())
    #     self.assertEqual("b4da56", model.importSource(0).id())
    #     self.assertEqual("b4da57", model.importSource(1).id())
    #     self.assertEqual("b4da58", model.units(0).id())
    #     self.assertEqual("b4da59", model.units(1).id())
    #     self.assertEqual("b4da5a", model.units(2).id())
    #     self.assertEqual("b4da5b", model.units(3).id())
    #     self.assertEqual("b4da5c", model.units(1).unitId(0))
    #     self.assertEqual("b4da5d", model.component(0).id())
    #     self.assertEqual("b4da5e", model.component(1).id())
    #     self.assertEqual("b4da5f", model.component(1).component(0).id())
    #     self.assertEqual("b4da60", model.component(1).variable(0).id())
    #     self.assertEqual("b4da61", model.component(1).variable(1).id())
    #     self.assertEqual("b4da62", model.component(
    #         1).component(0).variable(0).id())
    #     self.assertEqual("b4da63", model.component(
    #         1).component(0).variable(1).id())

    #     self.assertEqual("b4da64", model.component(1).reset(0).id())
    #     self.assertEqual("b4da65", model.component(1).reset(0).resetValueId())
    #     self.assertEqual("b4da66", model.component(1).reset(0).testValueId())

    #     c2v1 = model.component("component2").variable("variable1")
    #     c2v2 = model.component("component2").variable("variable2")
    #     c3v4 = model.component("component3").variable("variable4")
    #     c3v2 = model.component("component3").variable("variable2")
    #     self.assertEqual(
    #         "b4da67", Variable.equivalenceConnectionId(c2v1, c3v2))
    #     self.assertEqual(
    #         "b4da68", Variable.equivalenceConnectionId(c2v1, c3v4))
    #     self.assertEqual("b4da69", Variable.equivalenceMappingId(c2v1, c3v2))
    #     self.assertEqual("b4da6a", Variable.equivalenceMappingId(c2v1, c3v4))
    #     self.assertEqual("b4da6b", model.component(
    #         "component2").encapsulationId())
    #     self.assertEqual("b4da6c", model.component(
    #         "component3").encapsulationId())
    #     self.assertEqual("b4da6d", model.encapsulationId())

    # def test_auto_ids_group(self):
    #     from libcellml import Annotator, Component, Model
    #     annotator = Annotator()
    #     model = Model()
    #     component1 = Component("c1")
    #     component2 = Component("c2")
    #     component3 = Component("c3")

    #     model.addComponent(component1)
    #     model.addComponent(component2)
    #     component2.addComponent(component3)

    #     annotator.build(model)

    #     self.assertEqual("", model.id())
    #     self.assertEqual("", component1.id())
    #     self.assertEqual("", component2.id())
    #     self.assertEqual("", component3.id())

    #     annotator.setAutomaticIds(Annotator.Type.COMPONENT)

    #     self.assertEqual("", model.id())
    #     self.assertEqual("b4da55", component1.id())
    #     self.assertEqual("b4da56", component2.id())
    #     self.assertEqual("b4da57", component3.id())

    def test_auto_id_individual(self):
        from libcellml import Annotator, Model, Parser, Variable
        annotator = Annotator()
        parser = Parser()
        model_string = '<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n' + \
            '<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\"  >\n' + \
            '  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" >\n' + \
            '    <component component_ref=\"a_component_in_that_model\" name=\"component1\" />\n' + \
            '  </import>\n' + \
            '  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\"  >\n' + \
            '    <units units_ref=\"a_units_in_that_model\" name=\"units1\"  />\n' + \
            '  </import>\n' + \
            '  <units name=\"units2\" >\n' + \
            '    <unit units=\"second\" />\n' + \
            '  </units>\n' + \
            '  <units name=\"units3\" />\n' + \
            '  <units name=\"blob\" />\n' + \
            '  <component name=\"component2\">\n' + \
            '    <variable name=\"variable1\" units=\"units2\" interface=\"private\" />\n' + \
            '    <variable name=\"variable2\" units=\"units2\" />\n' + \
            '    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" >\n' + \
            '      <test_value >\n' + \
            '        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n' + \
            '          <apply>\n' + \
            '            <eq/>\n' + \
            '            <ci>variable1</ci>\n' + \
            '            <cn cellml:units=\"units2\">3.4</cn>\n' + \
            '          </apply>\n' + \
            '        </math>\n' + \
            '      </test_value>\n' + \
            '      <reset_value >\n' + \
            '        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n' + \
            '          <apply>\n' + \
            '            <eq/>\n' + \
            '            <ci>variable1</ci>\n' + \
            '            <cn cellml:units=\"units2\">9.0</cn>\n' + \
            '          </apply>\n' + \
            '        </math>\n' + \
            '      </reset_value>\n' + \
            '    </reset>\n' + \
            '  </component>\n' + \
            '  <component name=\"component3\" >\n' + \
            '    <variable name=\"variable4\" units=\"units2\" interface=\"public\"  />\n' + \
            '    <variable name=\"variable2\" units=\"units2\" interface=\"public\"  />\n' + \
            '    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n' + \
            '      <apply>\n' + \
            '        <eq/>\n' + \
            '        <ci>variable4</ci>\n' + \
            '        <cn cellml:units=\"units2\">9.0</cn>\n' + \
            '      </apply>\n' + \
            '    </math>\n' + \
            '  </component>\n' + \
            '  <connection component_1=\"component2\" component_2=\"component3\" >\n' + \
            '    <map_variables variable_1=\"variable1\" variable_2=\"variable2\" />\n' + \
            '    <map_variables variable_1=\"variable2\" variable_2=\"variable4\" />\n' + \
            '  </connection>\n' + \
            '  <encapsulation >\n' + \
            '    <component_ref component=\"component2\" >\n' + \
            '      <component_ref component=\"component3\" />\n' + \
            '    </component_ref>\n' + \
            '  </encapsulation>\n' + \
            '</model>\n'
        model = parser.parseModel(model_string)

        annotator.build(model)

        self.assertTrue(annotator.setAutomaticId(
            Annotator.Type.COMPONENT, model.component(0)))
        self.assertEqual("b4da55", model.component(0).id())

        print(model.component(1).encapsulationId())
        self.assertTrue(annotator.setAutomaticId(
            Annotator.Type.COMPONENT_REF, model.component("component2")))
        self.assertEqual("b4da56", model.component("component2").encapsulationId())
        print(model.component("component2").encapsulationId()) 

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.CONNECTION,
                                                 model.component("component2").variable(
                                                     "variable1"),
                                                 model.component("component2").variable("variable1").equivalentVariable(0)))
        self.assertEqual("b4da57", Variable.equivalenceConnectionId(
            model.component("component2").variable("variable1"),
            model.component("component2").variable("variable1").equivalentVariable(0)))

        self.assertTrue(annotator.setAutomaticId(
            Annotator.Type.IMPORT, model.importSource(0)))
        self.assertEqual("b4da58", model.importSource(0).id())

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.MAP_VARIABLES,
                                                 model.component("component2").variable(
                                                     "variable2"),
                                                 model.component("component2").variable("variable2").equivalentVariable(0)))
        self.assertEqual(
            "b4da59", Variable.equivalenceMappingId(model.component("component2").variable("variable2"),
                                                    model.component("component2").variable("variable2").equivalentVariable(0)))

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.MODEL, model))
        self.assertEqual("b4da5a", model.id())

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.RESET,
                                                 model.component(1).reset(0)))
        self.assertEqual("b4da5b", model.component(1).reset(0).id())

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.RESET_VALUE,
                                                 model.component(1).reset(0)))
        self.assertEqual("b4da5c", model.component(1).reset(0).resetValueId())

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.TEST_VALUE,
                                                 model.component(1).reset(0)))
        self.assertEqual("b4da5d", model.component(1).reset(0).testValueId())

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.UNIT,
                                                 model.units(1), 0))
        self.assertEqual("b4da5e", model.units(1).unitId(0))

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.UNITS,
                                                 model.units(1)))
        self.assertEqual("b4da5f", model.units(1).id())

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.VARIABLE,
                                                 model.component(1).variable(0)))
        self.assertEqual("b4da60", model.component(1).variable(0).id())

        self.assertTrue(annotator.setAutomaticId(Annotator.Type.ENCAPSULATION,
                                                 model))
        self.assertEqual("b4da61", model.encapsulationId())


if __name__ == '__main__':
    unittest.main()

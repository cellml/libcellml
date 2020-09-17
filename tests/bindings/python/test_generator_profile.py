#
# Tests the GeneratorProfile class bindings
#
import unittest


class GeneratorProfileTestCase(unittest.TestCase):
    VALUE = "value"

    def test_create_destroy(self):
        from libcellml import GeneratorProfile

        x = GeneratorProfile()
        del x

    def test_generator_profile(self):
        from libcellml import GeneratorProfile

        # Create a default, i.e. C, profile.
        p = GeneratorProfile()
        self.assertEqual(GeneratorProfile.Profile.C, p.profile())

        # Make the profile a Python profile.
        p.setProfile(GeneratorProfile.Profile.PYTHON)
        self.assertEqual(GeneratorProfile.Profile.PYTHON, p.profile())

        # Create a Python profile.
        pp = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
        self.assertEqual(GeneratorProfile.Profile.PYTHON, pp.profile())

    @unittest.skip("Create tests script")
    def test_create_tests(self):
        import re
        from libcellml import GeneratorProfile

        p = GeneratorProfile()

        seen = {}

        def working_name(entry):
            name = re.sub('([A-Z]{1})', r'_\1', entry).lower()

            if name.startswith("set"):
                name = name[4:]

            return name

        def ignore(entry):
            if entry.startswith("_") or entry in ["Profile", "profile", "this", "thisown"]:
                return True

            return False

        def getSetNames(entry):
            if entry.startswith("set"):
                getter = entry[3:]
                getter = getter[0].lower() + getter[1:]

                return [getter, entry]
            else:
                setter = entry
                setter = "set" + setter[0].upper() + setter[1:]

                return [entry, setter]

        def printStringMethod(entry):
            [getter, setter] = getSetNames(entry)
            content = getattr(p, getter)()
            content = content.replace("\n", "\\n")

            print("        from libcellml import GeneratorProfile")
            print("        ")
            print("        g = GeneratorProfile()")
            print("        ")
            print(f"        self.assertEqual(\"{content}\", g.{getter}())")
            print(f"        g.{setter}(\"Some text content.\")")
            print(f"        self.assertEqual(\"Some text content.\", g.{getter}())")
            print("        ")

        def printHasMethod(entry):
            print("        from libcellml import GeneratorProfile")
            print("        ")
            print("        g = GeneratorProfile()")
            print("        ")
            print("        self.assertFalse(g.{0}())".format(entry))
            print("        ")

        def isStringMethod(name):
            return name.endswith("string")

        def isHasMethod(name):
            return name.startswith("has")

        for entry in dir(p):
            name = working_name(entry)

            if not ignore(entry) and not name in seen:
                seen[name] = True

                print("    def test_{0}(self):".format(name))

                if isStringMethod(name):
                    printStringMethod(entry)
                elif isHasMethod(name):
                    printHasMethod(entry)
                else:
                    print("        # Yikes missing this method: " + entry)

    def test_absolute_value_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("fabs", g.absoluteValueString())
        g.setAbsoluteValueString(VALUE)
        self.assertEqual(VALUE, g.absoluteValueString())

    def test_acos_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acos", g.acosString())
        g.setAcosString(VALUE)
        self.assertEqual(VALUE, g.acosString())

    def test_acosh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acosh", g.acoshString())
        g.setAcoshString(VALUE)
        self.assertEqual(VALUE, g.acoshString())

    def test_acot_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double acot(double x)\n{\n    return atan(1.0/x);\n}\n", g.acotFunctionString())
        g.setAcotFunctionString(VALUE)
        self.assertEqual(VALUE, g.acotFunctionString())

    def test_acot_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acot", g.acotString())
        g.setAcotString(VALUE)
        self.assertEqual(VALUE, g.acotString())

    def test_acoth_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double acoth(double x)\n{\n    double oneOverX = 1.0/x;\n\n    return 0.5*log((1.0+oneOverX)/(1.0-oneOverX));\n}\n",
            g.acothFunctionString())
        g.setAcothFunctionString(VALUE)
        self.assertEqual(VALUE, g.acothFunctionString())

    def test_acoth_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acoth", g.acothString())
        g.setAcothString(VALUE)
        self.assertEqual(VALUE, g.acothString())

    def test_acsc_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double acsc(double x)\n{\n    return asin(1.0/x);\n}\n", g.acscFunctionString())
        g.setAcscFunctionString(VALUE)
        self.assertEqual(VALUE, g.acscFunctionString())

    def test_acsc_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acsc", g.acscString())
        g.setAcscString(VALUE)
        self.assertEqual(VALUE, g.acscString())

    def test_acsch_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double acsch(double x)\n{\n    double oneOverX = 1.0/x;\n\n    return log(oneOverX+sqrt(oneOverX*oneOverX+1.0));\n}\n",
            g.acschFunctionString())
        g.setAcschFunctionString(VALUE)
        self.assertEqual(VALUE, g.acschFunctionString())

    def test_acsch_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acsch", g.acschString())
        g.setAcschString(VALUE)
        self.assertEqual(VALUE, g.acschString())

    def test_algebraic_variable_type_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("ALGEBRAIC", g.algebraicVariableTypeString())
        g.setAlgebraicVariableTypeString(VALUE)
        self.assertEqual(VALUE, g.algebraicVariableTypeString())

    def test_and_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.andFunctionString())
        g.setAndFunctionString(VALUE)
        self.assertEqual(VALUE, g.andFunctionString())

    def test_and_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" && ", g.andString())
        g.setAndString(VALUE)
        self.assertEqual(VALUE, g.andString())

    def test_array_element_separator_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(",", g.arrayElementSeparatorString())
        g.setArrayElementSeparatorString(VALUE)
        self.assertEqual(VALUE, g.arrayElementSeparatorString())

    def test_asec_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double asec(double x)\n{\n    return acos(1.0/x);\n}\n", g.asecFunctionString())
        g.setAsecFunctionString(VALUE)
        self.assertEqual(VALUE, g.asecFunctionString())

    def test_asec_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("asec", g.asecString())
        g.setAsecString(VALUE)
        self.assertEqual(VALUE, g.asecString())

    def test_asech_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double asech(double x)\n{\n    double oneOverX = 1.0/x;\n\n    return log(oneOverX+sqrt(oneOverX*oneOverX-1.0));\n}\n",
            g.asechFunctionString())
        g.setAsechFunctionString(VALUE)
        self.assertEqual(VALUE, g.asechFunctionString())

    def test_asech_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("asech", g.asechString())
        g.setAsechString(VALUE)
        self.assertEqual(VALUE, g.asechString())

    def test_asin_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("asin", g.asinString())
        g.setAsinString(VALUE)
        self.assertEqual(VALUE, g.asinString())

    def test_asinh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("asinh", g.asinhString())
        g.setAsinhString(VALUE)
        self.assertEqual(VALUE, g.asinhString())

    def test_assignment_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" = ", g.assignmentString())
        g.setAssignmentString(VALUE)
        self.assertEqual(VALUE, g.assignmentString())

    def test_atan_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("atan", g.atanString())
        g.setAtanString(VALUE)
        self.assertEqual(VALUE, g.atanString())

    def test_atanh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("atanh", g.atanhString())
        g.setAtanhString(VALUE)
        self.assertEqual(VALUE, g.atanhString())

    def test_ceiling_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("ceil", g.ceilingString())
        g.setCeilingString(VALUE)
        self.assertEqual(VALUE, g.ceilingString())

    def test_close_array_initializer_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("}", g.closeArrayInitializerString())
        g.setCloseArrayInitializerString(VALUE)
        self.assertEqual(VALUE, g.closeArrayInitializerString())

    def test_close_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("]", g.closeArrayString())
        g.setCloseArrayString(VALUE)
        self.assertEqual(VALUE, g.closeArrayString())

    def test_command_separator_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(";", g.commandSeparatorString())
        g.setCommandSeparatorString(VALUE)
        self.assertEqual(VALUE, g.commandSeparatorString())

    def test_comment_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("/* <CODE> */\n", g.commentString())
        g.setCommentString(VALUE)
        self.assertEqual(VALUE, g.commentString())

    def test_common_logarithm_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("log10", g.commonLogarithmString())
        g.setCommonLogarithmString(VALUE)
        self.assertEqual(VALUE, g.commonLogarithmString())

    def test_computed_constant_variable_type_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("COMPUTED_CONSTANT", g.computedConstantVariableTypeString())
        g.setComputedConstantVariableTypeString(VALUE)
        self.assertEqual(VALUE, g.computedConstantVariableTypeString())

    def test_conditional_operator_else_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(":<ELSE_STATEMENT>", g.conditionalOperatorElseString())
        g.setConditionalOperatorElseString(VALUE)
        self.assertEqual(VALUE, g.conditionalOperatorElseString())

    def test_conditional_operator_if_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("(<CONDITION>)?<IF_STATEMENT>", g.conditionalOperatorIfString())
        g.setConditionalOperatorIfString(VALUE)
        self.assertEqual(VALUE, g.conditionalOperatorIfString())

    def test_constant_variable_type_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("CONSTANT", g.constantVariableTypeString())
        g.setConstantVariableTypeString(VALUE)
        self.assertEqual(VALUE, g.constantVariableTypeString())

    def test_cos_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("cos", g.cosString())
        g.setCosString(VALUE)
        self.assertEqual(VALUE, g.cosString())

    def test_cosh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("cosh", g.coshString())
        g.setCoshString(VALUE)
        self.assertEqual(VALUE, g.coshString())

    def test_cot_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double cot(double x)\n{\n    return 1.0/tan(x);\n}\n", g.cotFunctionString())
        g.setCotFunctionString(VALUE)
        self.assertEqual(VALUE, g.cotFunctionString())

    def test_cot_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("cot", g.cotString())
        g.setCotString(VALUE)
        self.assertEqual(VALUE, g.cotString())

    def test_coth_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double coth(double x)\n{\n    return 1.0/tanh(x);\n}\n", g.cothFunctionString())
        g.setCothFunctionString(VALUE)
        self.assertEqual(VALUE, g.cothFunctionString())

    def test_coth_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("coth", g.cothString())
        g.setCothString(VALUE)
        self.assertEqual(VALUE, g.cothString())

    def test_csc_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double csc(double x)\n{\n    return 1.0/sin(x);\n}\n", g.cscFunctionString())
        g.setCscFunctionString(VALUE)
        self.assertEqual(VALUE, g.cscFunctionString())

    def test_csc_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("csc", g.cscString())
        g.setCscString(VALUE)
        self.assertEqual(VALUE, g.cscString())

    def test_csch_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double csch(double x)\n{\n    return 1.0/sinh(x);\n}\n", g.cschFunctionString())
        g.setCschFunctionString(VALUE)
        self.assertEqual(VALUE, g.cschFunctionString())

    def test_csch_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("csch", g.cschString())
        g.setCschString(VALUE)
        self.assertEqual(VALUE, g.cschString())

    def test_divide_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("/", g.divideString())
        g.setDivideString(VALUE)
        self.assertEqual(VALUE, g.divideString())

    def test_e_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("2.71828182845905", g.eString())
        g.setEString(VALUE)
        self.assertEqual(VALUE, g.eString())

    def test_empty_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.emptyMethodString())
        g.setEmptyMethodString(VALUE)
        self.assertEqual(VALUE, g.emptyMethodString())

    def test_eq_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.eqFunctionString())
        g.setEqFunctionString(VALUE)
        self.assertEqual(VALUE, g.eqFunctionString())

    def test_eq_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" == ", g.eqString())
        g.setEqString(VALUE)
        self.assertEqual(VALUE, g.eqString())

    def test_exponential_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("exp", g.exponentialString())
        g.setExponentialString(VALUE)
        self.assertEqual(VALUE, g.exponentialString())

    def test_false_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("0.0", g.falseString())
        g.setFalseString(VALUE)
        self.assertEqual(VALUE, g.falseString())

    def test_floor_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("floor", g.floorString())
        g.setFloorString(VALUE)
        self.assertEqual(VALUE, g.floorString())

    def test_geq_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.geqFunctionString())
        g.setGeqFunctionString(VALUE)
        self.assertEqual(VALUE, g.geqFunctionString())

    def test_geq_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" >= ", g.geqString())
        g.setGeqString(VALUE)
        self.assertEqual(VALUE, g.geqString())

    def test_gt_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.gtFunctionString())
        g.setGtFunctionString(VALUE)
        self.assertEqual(VALUE, g.gtFunctionString())

    def test_gt_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" > ", g.gtString())
        g.setGtString(VALUE)
        self.assertEqual(VALUE, g.gtString())

    def test_has_and_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasAndOperator())
        g.setHasAndOperator(False)
        self.assertFalse(g.hasAndOperator())

    def test_has_conditional_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasConditionalOperator())
        g.setHasConditionalOperator(False)
        self.assertFalse(g.hasConditionalOperator())

    def test_has_eq_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasEqOperator())
        g.setHasEqOperator(False)
        self.assertFalse(g.hasEqOperator())

    def test_has_geq_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasGeqOperator())
        g.setHasGeqOperator(False)
        self.assertFalse(g.hasGeqOperator())

    def test_has_gt_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasGtOperator())
        g.setHasGtOperator(False)
        self.assertFalse(g.hasGtOperator())

    def test_has_leq_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasLeqOperator())
        g.setHasLeqOperator(False)
        self.assertFalse(g.hasLeqOperator())

    def test_has_lt_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasLtOperator())
        g.setHasLtOperator(False)
        self.assertFalse(g.hasLtOperator())

    def test_has_neq_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasNeqOperator())
        g.setHasNeqOperator(False)
        self.assertFalse(g.hasNeqOperator())

    def test_has_not_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasNotOperator())
        g.setHasNotOperator(False)
        self.assertFalse(g.hasNotOperator())

    def test_has_or_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasOrOperator())
        g.setHasOrOperator(False)
        self.assertFalse(g.hasOrOperator())

    def test_has_power_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertFalse(g.hasPowerOperator())
        g.setHasPowerOperator(True)
        self.assertTrue(g.hasPowerOperator())

    def test_has_xor_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertFalse(g.hasXorOperator())
        g.setHasXorOperator(True)
        self.assertTrue(g.hasXorOperator())

    def test_implementation_compute_computed_constants_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void computeComputedConstants(double *variables)\n{\n<CODE>}\n",
                         g.implementationComputeComputedConstantsMethodString())
        g.setImplementationComputeComputedConstantsMethodString(VALUE)
        self.assertEqual(VALUE, g.implementationComputeComputedConstantsMethodString())

    def test_implementation_compute_rates_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "void computeRates(double voi, double *states, double *rates, double *variables)\n{\n<CODE>}\n",
            g.implementationComputeRatesMethodString())
        g.setImplementationComputeRatesMethodString(VALUE)
        self.assertEqual(VALUE, g.implementationComputeRatesMethodString())

    def test_implementation_compute_variables_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "void computeVariables(double voi, double *states, double *rates, double *variables)\n{\n<CODE>}\n",
            g.implementationComputeVariablesMethodString())
        g.setImplementationComputeVariablesMethodString(VALUE)
        self.assertEqual(VALUE, g.implementationComputeVariablesMethodString())

    def test_implementation_create_states_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double * createStatesArray()\n{\n    return (double *) malloc(STATE_COUNT*sizeof(double));\n}\n",
            g.implementationCreateStatesArrayMethodString())
        g.setImplementationCreateStatesArrayMethodString(VALUE)
        self.assertEqual(VALUE, g.implementationCreateStatesArrayMethodString())

    def test_implementation_create_variables_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double * createVariablesArray()\n{\n    return (double *) malloc(VARIABLE_COUNT*sizeof(double));\n}\n",
            g.implementationCreateVariablesArrayMethodString())
        g.setImplementationCreateVariablesArrayMethodString(VALUE)
        self.assertEqual(VALUE, g.implementationCreateVariablesArrayMethodString())

    def test_implementation_delete_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void deleteArray(double *array)\n{\n    free(array);\n}\n",
                         g.implementationDeleteArrayMethodString())
        g.setImplementationDeleteArrayMethodString(VALUE)
        self.assertEqual(VALUE, g.implementationDeleteArrayMethodString())

    def test_implementation_header_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("#include \"<INTERFACE_FILE_NAME>\"\n\n#include <math.h>\n#include <stdlib.h>\n",
                         g.implementationHeaderString())
        g.setImplementationHeaderString(VALUE)
        self.assertEqual(VALUE, g.implementationHeaderString())

    def test_implementation_initialize_states_and_constants_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void initializeStatesAndConstants(double *states, double *variables)\n{\n<CODE>}\n",
                         g.implementationInitializeStatesAndConstantsMethodString())
        g.setImplementationInitializeStatesAndConstantsMethodString(VALUE)
        self.assertEqual(VALUE, g.implementationInitializeStatesAndConstantsMethodString())

    def test_implementation_libcellml_version_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const char LIBCELLML_VERSION[] = \"<LIBCELLML_VERSION>\";\n",
                         g.implementationLibcellmlVersionString())
        g.setImplementationLibcellmlVersionString(VALUE)
        self.assertEqual(VALUE, g.implementationLibcellmlVersionString())

    def test_implementation_state_count_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const size_t STATE_COUNT = <STATE_COUNT>;\n", g.implementationStateCountString())
        g.setImplementationStateCountString(VALUE)
        self.assertEqual(VALUE, g.implementationStateCountString())

    def test_implementation_state_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const VariableInfo STATE_INFO[] = {\n<CODE>};\n", g.implementationStateInfoString())
        g.setImplementationStateInfoString(VALUE)
        self.assertEqual(VALUE, g.implementationStateInfoString())

    def test_implementation_variable_count_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const size_t VARIABLE_COUNT = <VARIABLE_COUNT>;\n", g.implementationVariableCountString())
        g.setImplementationVariableCountString(VALUE)
        self.assertEqual(VALUE, g.implementationVariableCountString())

    def test_implementation_variable_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const VariableInfoWithType VARIABLE_INFO[] = {\n<CODE>};\n",
                         g.implementationVariableInfoString())
        g.setImplementationVariableInfoString(VALUE)
        self.assertEqual(VALUE, g.implementationVariableInfoString())

    def test_implementation_version_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const char VERSION[] = \"0.1.0\";\n", g.implementationVersionString())
        g.setImplementationVersionString(VALUE)
        self.assertEqual(VALUE, g.implementationVersionString())

    def test_implementation_voi_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const VariableInfo VOI_INFO = <CODE>;\n", g.implementationVoiInfoString())
        g.setImplementationVoiInfoString(VALUE)
        self.assertEqual(VALUE, g.implementationVoiInfoString())

    def test_indent_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("    ", g.indentString())
        g.setIndentString(VALUE)
        self.assertEqual(VALUE, g.indentString())

    def test_inf_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("INFINITY", g.infString())
        g.setInfString(VALUE)
        self.assertEqual(VALUE, g.infString())

    def test_interface_compute_computed_constants_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void computeComputedConstants(double *variables);\n",
                         g.interfaceComputeComputedConstantsMethodString())
        g.setInterfaceComputeComputedConstantsMethodString(VALUE)
        self.assertEqual(VALUE, g.interfaceComputeComputedConstantsMethodString())

    def test_interface_compute_rates_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void computeRates(double voi, double *states, double *rates, double *variables);\n",
                         g.interfaceComputeRatesMethodString())
        g.setInterfaceComputeRatesMethodString(VALUE)
        self.assertEqual(VALUE, g.interfaceComputeRatesMethodString())

    def test_interface_compute_variables_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void computeVariables(double voi, double *states, double *rates, double *variables);\n",
                         g.interfaceComputeVariablesMethodString())
        g.setInterfaceComputeVariablesMethodString(VALUE)
        self.assertEqual(VALUE, g.interfaceComputeVariablesMethodString())

    def test_interface_create_states_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double * createStatesArray();\n", g.interfaceCreateStatesArrayMethodString())
        g.setInterfaceCreateStatesArrayMethodString(VALUE)
        self.assertEqual(VALUE, g.interfaceCreateStatesArrayMethodString())

    def test_interface_create_variables_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double * createVariablesArray();\n", g.interfaceCreateVariablesArrayMethodString())
        g.setInterfaceCreateVariablesArrayMethodString(VALUE)
        self.assertEqual(VALUE, g.interfaceCreateVariablesArrayMethodString())

    def test_interface_delete_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void deleteArray(double *array);\n", g.interfaceDeleteArrayMethodString())
        g.setInterfaceDeleteArrayMethodString(VALUE)
        self.assertEqual(VALUE, g.interfaceDeleteArrayMethodString())

    def test_interface_file_name_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("model.h", g.interfaceFileNameString())
        g.setInterfaceFileNameString(VALUE)
        self.assertEqual(VALUE, g.interfaceFileNameString())

    def test_interface_header_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("#pragma once\n\n#include <stddef.h>\n", g.interfaceHeaderString())
        g.setInterfaceHeaderString(VALUE)
        self.assertEqual(VALUE, g.interfaceHeaderString())

    def test_interface_initialize_states_and_constants_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void initializeStatesAndConstants(double *states, double *variables);\n",
                         g.interfaceInitializeStatesAndConstantsMethodString())
        g.setInterfaceInitializeStatesAndConstantsMethodString(VALUE)
        self.assertEqual(VALUE, g.interfaceInitializeStatesAndConstantsMethodString())

    def test_interface_libcellml_version_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const char LIBCELLML_VERSION[];\n", g.interfaceLibcellmlVersionString())
        g.setInterfaceLibcellmlVersionString(VALUE)
        self.assertEqual(VALUE, g.interfaceLibcellmlVersionString())

    def test_interface_state_count_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const size_t STATE_COUNT;\n", g.interfaceStateCountString())
        g.setInterfaceStateCountString(VALUE)
        self.assertEqual(VALUE, g.interfaceStateCountString())

    def test_interface_state_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const VariableInfo STATE_INFO[];\n", g.interfaceStateInfoString())
        g.setInterfaceStateInfoString(VALUE)
        self.assertEqual(VALUE, g.interfaceStateInfoString())

    def test_interface_variable_count_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const size_t VARIABLE_COUNT;\n", g.interfaceVariableCountString())
        g.setInterfaceVariableCountString(VALUE)
        self.assertEqual(VALUE, g.interfaceVariableCountString())

    def test_interface_variable_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const VariableInfoWithType VARIABLE_INFO[];\n", g.interfaceVariableInfoString())
        g.setInterfaceVariableInfoString(VALUE)
        self.assertEqual(VALUE, g.interfaceVariableInfoString())

    def test_interface_version_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const char VERSION[];\n", g.interfaceVersionString())
        g.setInterfaceVersionString(VALUE)
        self.assertEqual(VALUE, g.interfaceVersionString())

    def test_interface_voi_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const VariableInfo VOI_INFO;\n", g.interfaceVoiInfoString())
        g.setInterfaceVoiInfoString(VALUE)
        self.assertEqual(VALUE, g.interfaceVoiInfoString())

    def test_leq_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.leqFunctionString())
        g.setLeqFunctionString(VALUE)
        self.assertEqual(VALUE, g.leqFunctionString())

    def test_leq_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" <= ", g.leqString())
        g.setLeqString(VALUE)
        self.assertEqual(VALUE, g.leqString())

    def test_lt_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.ltFunctionString())
        g.setLtFunctionString(VALUE)
        self.assertEqual(VALUE, g.ltFunctionString())

    def test_lt_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" < ", g.ltString())
        g.setLtString(VALUE)
        self.assertEqual(VALUE, g.ltString())

    def test_max_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double max(double x, double y)\n{\n    return (x > y)?x:y;\n}\n", g.maxFunctionString())
        g.setMaxFunctionString(VALUE)
        self.assertEqual(VALUE, g.maxFunctionString())

    def test_max_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("max", g.maxString())
        g.setMaxString(VALUE)
        self.assertEqual(VALUE, g.maxString())

    def test_min_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double min(double x, double y)\n{\n    return (x < y)?x:y;\n}\n", g.minFunctionString())
        g.setMinFunctionString(VALUE)
        self.assertEqual(VALUE, g.minFunctionString())

    def test_min_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("min", g.minString())
        g.setMinString(VALUE)
        self.assertEqual(VALUE, g.minString())

    def test_minus_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("-", g.minusString())
        g.setMinusString(VALUE)
        self.assertEqual(VALUE, g.minusString())

    def test_nan_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("NAN", g.nanString())
        g.setNanString(VALUE)
        self.assertEqual(VALUE, g.nanString())

    def test_napierian_logarithm_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("log", g.napierianLogarithmString())
        g.setNapierianLogarithmString(VALUE)
        self.assertEqual(VALUE, g.napierianLogarithmString())

    def test_neq_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.neqFunctionString())
        g.setNeqFunctionString(VALUE)
        self.assertEqual(VALUE, g.neqFunctionString())

    def test_neq_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" != ", g.neqString())
        g.setNeqString(VALUE)
        self.assertEqual(VALUE, g.neqString())

    def test_not_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.notFunctionString())
        g.setNotFunctionString(VALUE)
        self.assertEqual(VALUE, g.notFunctionString())

    def test_not_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("!", g.notString())
        g.setNotString(VALUE)
        self.assertEqual(VALUE, g.notString())

    def test_open_array_initializer_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("{", g.openArrayInitializerString())
        g.setOpenArrayInitializerString(VALUE)
        self.assertEqual(VALUE, g.openArrayInitializerString())

    def test_open_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("[", g.openArrayString())
        g.setOpenArrayString(VALUE)
        self.assertEqual(VALUE, g.openArrayString())

    def test_or_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.orFunctionString())
        g.setOrFunctionString(VALUE)
        self.assertEqual(VALUE, g.orFunctionString())

    def test_or_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" || ", g.orString())
        g.setOrString(VALUE)
        self.assertEqual(VALUE, g.orString())

    def test_origin_comment_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "The content of this file was generated using <PROFILE_INFORMATION> libCellML <LIBCELLML_VERSION>.",
            g.originCommentString())
        g.setOriginCommentString(VALUE)
        self.assertEqual(VALUE, g.originCommentString())

    def test_pi_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("3.14159265358979", g.piString())
        g.setPiString(VALUE)
        self.assertEqual(VALUE, g.piString())

    def test_piecewise_else_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.piecewiseElseString())
        g.setPiecewiseElseString(VALUE)
        self.assertEqual(VALUE, g.piecewiseElseString())

    def test_piecewise_if_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.piecewiseIfString())
        g.setPiecewiseIfString(VALUE)
        self.assertEqual(VALUE, g.piecewiseIfString())

    def test_plus_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("+", g.plusString())
        g.setPlusString(VALUE)
        self.assertEqual(VALUE, g.plusString())

    def test_power_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("pow", g.powerString())
        g.setPowerString(VALUE)
        self.assertEqual(VALUE, g.powerString())

    def test_rates_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("rates", g.ratesArrayString())
        g.setRatesArrayString(VALUE)
        self.assertEqual(VALUE, g.ratesArrayString())

    def test_rem_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("fmod", g.remString())
        g.setRemString(VALUE)
        self.assertEqual(VALUE, g.remString())

    def test_sec_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double sec(double x)\n{\n    return 1.0/cos(x);\n}\n", g.secFunctionString())
        g.setSecFunctionString(VALUE)
        self.assertEqual(VALUE, g.secFunctionString())

    def test_sec_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sec", g.secString())
        g.setSecString(VALUE)
        self.assertEqual(VALUE, g.secString())

    def test_sech_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double sech(double x)\n{\n    return 1.0/cosh(x);\n}\n", g.sechFunctionString())
        g.setSechFunctionString(VALUE)
        self.assertEqual(VALUE, g.sechFunctionString())

    def test_sech_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sech", g.sechString())
        g.setSechString(VALUE)
        self.assertEqual(VALUE, g.sechString())

    def test_sin_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sin", g.sinString())
        g.setSinString(VALUE)
        self.assertEqual(VALUE, g.sinString())

    def test_sinh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sinh", g.sinhString())
        g.setSinhString(VALUE)
        self.assertEqual(VALUE, g.sinhString())

    def test_square_root_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sqrt", g.squareRootString())
        g.setSquareRootString(VALUE)
        self.assertEqual(VALUE, g.squareRootString())

    def test_square_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.squareString())
        g.setSquareString(VALUE)
        self.assertEqual(VALUE, g.squareString())

    def test_states_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("states", g.statesArrayString())
        g.setStatesArrayString(VALUE)
        self.assertEqual(VALUE, g.statesArrayString())

    def test_string_delimiter_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("\"", g.stringDelimiterString())
        g.setStringDelimiterString(VALUE)
        self.assertEqual(VALUE, g.stringDelimiterString())

    def test_tan_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("tan", g.tanString())
        g.setTanString(VALUE)
        self.assertEqual(VALUE, g.tanString())

    def test_tanh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("tanh", g.tanhString())
        g.setTanhString(VALUE)
        self.assertEqual(VALUE, g.tanhString())

    def test_times_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("*", g.timesString())
        g.setTimesString(VALUE)
        self.assertEqual(VALUE, g.timesString())

    def test_true_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("1.0", g.trueString())
        g.setTrueString(VALUE)
        self.assertEqual(VALUE, g.trueString())

    def test_variable_info_entry_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("{\"<NAME>\", \"<UNITS>\", \"<COMPONENT>\"}", g.variableInfoEntryString())
        g.setVariableInfoEntryString(VALUE)
        self.assertEqual(VALUE, g.variableInfoEntryString())

    def test_variable_info_object_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "typedef struct {\n    char name[<NAME_SIZE>];\n    char units[<UNITS_SIZE>];\n    char component[<COMPONENT_SIZE>];\n} VariableInfo;\n",
            g.variableInfoObjectString())
        g.setVariableInfoObjectString(VALUE)
        self.assertEqual(VALUE, g.variableInfoObjectString())

    def test_variable_info_with_type_entry_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("{\"<NAME>\", \"<UNITS>\", \"<COMPONENT>\", <TYPE>}", g.variableInfoWithTypeEntryString())
        g.setVariableInfoWithTypeEntryString(VALUE)
        self.assertEqual(VALUE, g.variableInfoWithTypeEntryString())

    def test_variable_info_with_type_object_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "typedef struct {\n    char name[<NAME_SIZE>];\n    char units[<UNITS_SIZE>];\n    char component[<COMPONENT_SIZE>];\n    VariableType type;\n} VariableInfoWithType;\n",
            g.variableInfoWithTypeObjectString())
        g.setVariableInfoWithTypeObjectString(VALUE)
        self.assertEqual(VALUE, g.variableInfoWithTypeObjectString())

    def test_variable_type_object_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("typedef enum {\n    CONSTANT,\n    COMPUTED_CONSTANT,\n    ALGEBRAIC\n} VariableType;\n",
                         g.variableTypeObjectString())
        g.setVariableTypeObjectString(VALUE)
        self.assertEqual(VALUE, g.variableTypeObjectString())

    def test_variables_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("variables", g.variablesArrayString())
        g.setVariablesArrayString(VALUE)
        self.assertEqual(VALUE, g.variablesArrayString())

    def test_voi_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("voi", g.voiString())
        g.setVoiString(VALUE)
        self.assertEqual(VALUE, g.voiString())

    def test_xor_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double xor(double x, double y)\n{\n    return (x != 0.0) ^ (y != 0.0);\n}\n",
                         g.xorFunctionString())
        g.setXorFunctionString(VALUE)
        self.assertEqual(VALUE, g.xorFunctionString())

    def test_xor_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("xor", g.xorString())
        g.setXorString(VALUE)
        self.assertEqual(VALUE, g.xorString())


if __name__ == '__main__':
    unittest.main()

%module(package="libcellml") generatorprofile

#define LIBCELLML_EXPORT

%include <std_string.i>

%import "createconstructor.i"
%import "types.i"

%feature("docstring") libcellml::GeneratorProfile
"Holds the information for the :class:`Generator` to generate code
according to this profile.";

%feature("docstring") libcellml::GeneratorProfile::profile
"Return the :enum:`GeneratorProfile::Profile` for this :class:`GeneratorProfile`.";

%feature("docstring") libcellml::GeneratorProfile::setProfile
"Set the :enum:`GeneratorProfile::Profile` for this :class:`GeneratorProfile`.";

%feature("docstring") libcellml::GeneratorProfile::hasInterface
"Test if this :class:`GeneratorProfile` requires an interface.";

%feature("docstring") libcellml::GeneratorProfile::setHasInterface
"Set whether this :class:`GeneratorProfile` requires an interface.";

%feature("docstring") libcellml::GeneratorProfile::assignmentString
"Return the \"assigment\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setAssignmentString
"Set the \"assigment\" operator.";

%feature("docstring") libcellml::GeneratorProfile::eqString
"Return the \"equivalence\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setEqString
"Set the \"equivalence\" operator.";

%feature("docstring") libcellml::GeneratorProfile::neqString
"Return the the \"nonequivalence\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setNeqString
"Set the \"nonequivalence\" operator.";

%feature("docstring") libcellml::GeneratorProfile::ltString
"Return the \"less than\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setLtString
"Set the \"less than\" operator.";

%feature("docstring") libcellml::GeneratorProfile::leqString
"Return the \"less than or equal to\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setLeqString
"Set the \"less than or equal to\" operator.";

%feature("docstring") libcellml::GeneratorProfile::gtString
"Return the \"greater than\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setGtString
"Set the \"greater than\" operator.";

%feature("docstring") libcellml::GeneratorProfile::geqString
"Return the \"greater than or equal to\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setGeqString
"Set the \"greater than or equal to\" operator.";

%feature("docstring") libcellml::GeneratorProfile::andString
"Return the \"and\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setAndString
"Set the \"and\" operator.";

%feature("docstring") libcellml::GeneratorProfile::orString
"Return the \"or\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setOrString
"Set the \"or\" operator.";

%feature("docstring") libcellml::GeneratorProfile::xorString
"Return the \"xor\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setXorString
"Set the \"xor\" operator.";

%feature("docstring") libcellml::GeneratorProfile::notString
"Return the \"not\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setNotString
"Set the \"not\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasEqOperator
"Test if this :class:`GeneratorProfile` has an \"equivalence\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasEqOperator
"Set whether this :class:`GeneratorProfile` has an \"equivalence\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasNeqOperator
"Test if this :class:`GeneratorProfile` has a \"nonequivalence\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasNeqOperator
"Set whether this :class:`GeneratorProfile` has a \"nonequivalence\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasLtOperator
"Test if this :class:`GeneratorProfile` has a \"less than\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasLtOperator
"Set whether this :class:`GeneratorProfile` has a \"less than\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasLeqOperator
"Test if this :class:`GeneratorProfile` has a \"less than or equal to\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasLeqOperator
"Set whether this :class:`GeneratorProfile` has a \"less than or equal to\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasGtOperator
"Test if this :class:`GeneratorProfile` has a \"greater than\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasGtOperator
"Set whether this :class:`GeneratorProfile` has a \"greater than\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasGeqOperator
"Test if this :class:`GeneratorProfile` has a \"greater than or equal to\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasGeqOperator
"Set whether this :class:`GeneratorProfile` has a \"greater than or equal to\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasAndOperator
"Test if this :class:`GeneratorProfile` has an \"and\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasAndOperator
"Set whether this :class:`GeneratorProfile` has an \"and\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasOrOperator
"Test if this :class:`GeneratorProfile` has an \"or\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasOrOperator
"Set whether this :class:`GeneratorProfile` has an \"or\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasXorOperator
"Test if this :class:`GeneratorProfile` has an \"xor\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasXorOperator
"Set whether this :class:`GeneratorProfile` has an \"xor\" operator.";

%feature("docstring") libcellml::GeneratorProfile::hasNotOperator
"Test if this :class:`GeneratorProfile` has a \"not\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasNotOperator
"Set whether this :class:`GeneratorProfile` has a \"not\" operator.";

%feature("docstring") libcellml::GeneratorProfile::plusString
"Return the string for the \"plus\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setPlusString
"Set the string for the \"plus\" operator.";

%feature("docstring") libcellml::GeneratorProfile::minusString
"Return the string for the \"minus\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setMinusString
"Set the string for the \"minus\" operator.";

%feature("docstring") libcellml::GeneratorProfile::timesString
"Return the string for the \"times\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setTimesString
"Set the string for the \"times\" operator.";

%feature("docstring") libcellml::GeneratorProfile::divideString
"Return the string for the \"divide\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setDivideString
"Set the string for the \"divide\" operator.";

%feature("docstring") libcellml::GeneratorProfile::powerString
"Return the string for the \"power\" operator or function.";

%feature("docstring") libcellml::GeneratorProfile::setPowerString
"Set the string for the \"power\" operator or function.";

%feature("docstring") libcellml::GeneratorProfile::squareRootString
"Return the string for the \"square root\" function.";

%feature("docstring") libcellml::GeneratorProfile::setSquareRootString
"Set the string for the \"square root\" function.";

%feature("docstring") libcellml::GeneratorProfile::squareString
"Return the string for the \"square\" function.";

%feature("docstring") libcellml::GeneratorProfile::setSquareString
"Set the string for the \"square\" function.";

%feature("docstring") libcellml::GeneratorProfile::absoluteValueString
"Return the string for the \"absolute value\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAbsoluteValueString
"Set the string for the \"absolute value\" function.";

%feature("docstring") libcellml::GeneratorProfile::exponentialString
"Return the string for the \"exponential\" function.";

%feature("docstring") libcellml::GeneratorProfile::setExponentialString
"Set the string for the \"exponential\" function.";

%feature("docstring") libcellml::GeneratorProfile::napierianLogarithmString
"Return the string for the \"Napierian logarithm\" function.";

%feature("docstring") libcellml::GeneratorProfile::setNapierianLogarithmString
"Set the string for the \"Napierian logarithm\" function.";

%feature("docstring") libcellml::GeneratorProfile::commonLogarithmString
"Return the string for the \"common logarithm\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCommonLogarithmString
"Set the string for the \"common logarithm\" function.";

%feature("docstring") libcellml::GeneratorProfile::ceilingString
"Return the string for the \"ceiling\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCeilingString
"Set the string for the \"ceiling\" function.";

%feature("docstring") libcellml::GeneratorProfile::floorString
"Return the string for the \"floor\" function.";

%feature("docstring") libcellml::GeneratorProfile::setFloorString
"Set the string for the \"floor\" function.";

%feature("docstring") libcellml::GeneratorProfile::minString
"Return the string for the \"minimum\" function.";

%feature("docstring") libcellml::GeneratorProfile::setMinString
"Set the string for the \"minimum\" function.";

%feature("docstring") libcellml::GeneratorProfile::maxString
"Return the string for the \"maximum\" function.";

%feature("docstring") libcellml::GeneratorProfile::setMaxString
"Set the string for the \"maximum\" function.";

%feature("docstring") libcellml::GeneratorProfile::remString
"Return the string for the \"remainder\" function.";

%feature("docstring") libcellml::GeneratorProfile::setRemString
"Set the string for the \"remainder\" function.";

%feature("docstring") libcellml::GeneratorProfile::hasPowerOperator
"Test if this :class:`GeneratorProfile` has a \"power\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasPowerOperator
"Set whether this :class:`GeneratorProfile` has a \"power\" operator.";

%feature("docstring") libcellml::GeneratorProfile::sinString
"Return the string for the \"sine\" function.";

%feature("docstring") libcellml::GeneratorProfile::setSinString
"Set the string for the \"sine\" function.";

%feature("docstring") libcellml::GeneratorProfile::cosString
"Return the string for the \"cosine\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCosString
"Set the string for the \"cosine\" function.";

%feature("docstring") libcellml::GeneratorProfile::tanString
"Return the string for the \"tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setTanString
"Set the string for the \"tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::secString
"Return the string for the \"secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setSecString
"Set the string for the \"secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::cscString
"Return the string for the \"cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCscString
"Set the string for the \"cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::cotString
"Return the string for the \"cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCotString
"Set the string for the \"cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::sinhString
"Return the string for the \"hyperbolic sine\" function.";

%feature("docstring") libcellml::GeneratorProfile::setSinhString
"Set the string for the \"hyperbolic sine\" function.";

%feature("docstring") libcellml::GeneratorProfile::coshString
"Return the string for the \"hyperbolic cosine\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCoshString
"Set the string for the \"hyperbolic cosine\" function.";

%feature("docstring") libcellml::GeneratorProfile::tanhString
"Return the string for the \"hyperbolic tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setTanhString
"Set the string for the \"hyperbolic tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::sechString
"Return the string for the \"hyperbolic secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setSechString
"Set the string for the \"hyperbolic secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::cschString
"Return the string for the \"hyperbolic cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCschString
"Set the string for the \"hyperbolic cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::cothString
"Return the string for the \"hyperbolic cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCothString
"Set the string for the \"hyperbolic cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::asinString
"Return the string for the \"arc sine\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAsinString
"Set the string for the \"arc sine\" function.";

%feature("docstring") libcellml::GeneratorProfile::acosString
"Return the string for the \"arc cosine\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcosString
"Set the string for the \"arc cosine\" function.";

%feature("docstring") libcellml::GeneratorProfile::atanString
"Return the string for the \"arc tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAtanString
"Set the string for the \"arc tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::asecString
"Return the string for the \"arc secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAsecString
"Set the string for the \"arc secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::acscString
"Return the string for the \"arc cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcscString
"Set the string for the \"arc cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::acotString
"Return the string for the \"arc cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcotString
"Set the string for the \"arc cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::asinhString
"Return the string for the \"arc hyperbolic sine\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAsinhString
"Set the string for the \"arc hyperbolic sine\" function.";

%feature("docstring") libcellml::GeneratorProfile::acoshString
"Return the string for the \"arc hyperbolic cosine\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcoshString
"Set the string for the \"arc hyperbolic cosine\" function.";

%feature("docstring") libcellml::GeneratorProfile::atanhString
"Return the string for the \"arc hyperbolic tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAtanhString
"Set the string for the \"arc hyperbolic tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::asechString
"Return the string for the \"arc hyperbolic secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAsechString
"Set the string for the \"arc hyperbolic secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::acschString
"Return the string for the \"arc hyperbolic cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcschString
"Set the string for the \"arc hyperbolic cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::acothString
"Return the string for the \"arc hyperbolic tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcothString
"Set the string for the \"arc hyperbolic tangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::conditionalOperatorIfString
"Return the \"if\" part of a \"conditional\" statement or operator.";

%feature("docstring") libcellml::GeneratorProfile::setConditionalOperatorIfString
"Set the \"if\" part of a \"conditional\" statement or operator.";

%feature("docstring") libcellml::GeneratorProfile::conditionalOperatorElseString
"Return the \"else\" part of a \"conditional\" statement or operator.";

%feature("docstring") libcellml::GeneratorProfile::setConditionalOperatorElseString
"Set the \"else\" part of a \"conditional\" statement or operator.";

%feature("docstring") libcellml::GeneratorProfile::piecewiseIfString
"Return the \"if\" part of a \"piecewise\" statement.";

%feature("docstring") libcellml::GeneratorProfile::setPiecewiseIfString
"Set the \"if\" part of a \"piecewise\" statement.";

%feature("docstring") libcellml::GeneratorProfile::piecewiseElseString
"Return the \"else\" part of a \"piecewise\" statement.";

%feature("docstring") libcellml::GeneratorProfile::setPiecewiseElseString
"Set the \"else\" part of a \"piecewise\" statement.";

%feature("docstring") libcellml::GeneratorProfile::hasConditionalOperator
"Test if this :class:`GeneratorProfile` has a \"conditional\" operator.";

%feature("docstring") libcellml::GeneratorProfile::setHasConditionalOperator
"Set whether this :class:`GeneratorProfile` has a \"conditional\" operator.";

%feature("docstring") libcellml::GeneratorProfile::trueString
"Return the string for \"true\".";

%feature("docstring") libcellml::GeneratorProfile::setTrueString
"Set the string for \"true\".";

%feature("docstring") libcellml::GeneratorProfile::falseString
"Return the string for \"false\".";

%feature("docstring") libcellml::GeneratorProfile::setFalseString
"Set the string for \"false\".";

%feature("docstring") libcellml::GeneratorProfile::eString
"Return the string for the \"exponential\" constant.";

%feature("docstring") libcellml::GeneratorProfile::setEString
"Set the string for the \"exponential\" constant.";

%feature("docstring") libcellml::GeneratorProfile::piString
"Return the string for pi.";

%feature("docstring") libcellml::GeneratorProfile::setPiString
"Set the string for pi.";

%feature("docstring") libcellml::GeneratorProfile::infString
"Return the string for \"infinity\".";

%feature("docstring") libcellml::GeneratorProfile::setInfString
"Set the string for \"infinity\".";

%feature("docstring") libcellml::GeneratorProfile::nanString
"Return the string for \"not-a-number\".";

%feature("docstring") libcellml::GeneratorProfile::setNanString
"Set the string for \"not-a-number\".";

%feature("docstring") libcellml::GeneratorProfile::eqFunctionString
"Return the string for the \"equivalence\" function.";

%feature("docstring") libcellml::GeneratorProfile::setEqFunctionString
"Set the string for the \"equivalence\" function.";

%feature("docstring") libcellml::GeneratorProfile::neqFunctionString
"Return the string for the \"nonequivalence\" function.";

%feature("docstring") libcellml::GeneratorProfile::setNeqFunctionString
"Set the string for the \"nonequivalence\" function.";

%feature("docstring") libcellml::GeneratorProfile::ltFunctionString
"Return the string for the \"less than\" function.";

%feature("docstring") libcellml::GeneratorProfile::setLtFunctionString
"Set the string for the \"less than\" function.";

%feature("docstring") libcellml::GeneratorProfile::leqFunctionString
"Return the string for the \"less than or equal to\" function.";

%feature("docstring") libcellml::GeneratorProfile::setLeqFunctionString
"Set the string for the \"less than or equal to\" function.";

%feature("docstring") libcellml::GeneratorProfile::gtFunctionString
"Return the string for the \"greater than\" function.";

%feature("docstring") libcellml::GeneratorProfile::setGtFunctionString
"Set the string for the \"greater than\" function.";

%feature("docstring") libcellml::GeneratorProfile::geqFunctionString
"Return the string for the \"greater than or equal to\" function.";

%feature("docstring") libcellml::GeneratorProfile::setGeqFunctionString
"Set the string for the \"greater than or equal to\" function.";

%feature("docstring") libcellml::GeneratorProfile::andFunctionString
"Return the string for the \"and\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAndFunctionString
"Set the string for the \"and\" function.";

%feature("docstring") libcellml::GeneratorProfile::orFunctionString
"Return the string for the \"or\" function.";

%feature("docstring") libcellml::GeneratorProfile::setOrFunctionString
"Set the string for the \"or\" function.";

%feature("docstring") libcellml::GeneratorProfile::xorFunctionString
"Return the string for the \"xor\" function.";

%feature("docstring") libcellml::GeneratorProfile::setXorFunctionString
"Set the string for the \"xor\" function.";

%feature("docstring") libcellml::GeneratorProfile::notFunctionString
"Return the string for the \"not\" function.";

%feature("docstring") libcellml::GeneratorProfile::setNotFunctionString
"Set the string for the \"not\" function.";

%feature("docstring") libcellml::GeneratorProfile::minFunctionString
"Return the string for the \"minimum\" function.";

%feature("docstring") libcellml::GeneratorProfile::setMinFunctionString
"Set the string for the \"minimum\" function.";

%feature("docstring") libcellml::GeneratorProfile::maxFunctionString
"Return the string for the \"maximum\" function.";

%feature("docstring") libcellml::GeneratorProfile::setMaxFunctionString
"Set the string for the \"maximum\" function.";

%feature("docstring") libcellml::GeneratorProfile::secFunctionString
"Return the string for the \"secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setSecFunctionString
"Set the string for the \"secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::cscFunctionString
"Return the string for the \"cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCscFunctionString
"Set the string for the \"cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::cotFunctionString
"Return the string for the \"cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCotFunctionString
"Set the string for the \"cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::sechFunctionString
"Return the string for the \"hyperbolic secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setSechFunctionString
"Set the string for the \"hyperbolic secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::cschFunctionString
"Return the string for the \"hyperbolic cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCschFunctionString
"Set the string for the \"hyperbolic cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::cothFunctionString
"Return the string for the \"hyperbolic cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setCothFunctionString
"Set the string for the \"hyperbolic cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::asecFunctionString
"Return the string for the \"arc secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAsecFunctionString
"Set the string for the \"arc secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::acscFunctionString
"Return the string for the \"arc cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcscFunctionString
"Set the string for the \"arc cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::acotFunctionString
"Return the string for the \"arc cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcotFunctionString
"Set the string for the \"arc cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::asechFunctionString
"Return the string for the \"arc hyperbolic secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAsechFunctionString
"Set the string for the \"arc hyperbolic secant\" function.";

%feature("docstring") libcellml::GeneratorProfile::acschFunctionString
"Return the string for the \"arc hyperbolic cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcschFunctionString
"Set the string for the \"arc hyperbolic cosecant\" function.";

%feature("docstring") libcellml::GeneratorProfile::acothFunctionString
"Return the string for the \"arc hyperbolic cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::setAcothFunctionString
"Set the string for the \"arc hyperbolic cotangent\" function.";

%feature("docstring") libcellml::GeneratorProfile::commentString
"Return the string for a comment.";

%feature("docstring") libcellml::GeneratorProfile::setCommentString
"Set the string for a comment. To be useful, the string should
contain the <CODE> tag, which will be replaced with a (proper) comment.";

%feature("docstring") libcellml::GeneratorProfile::originCommentString
"Return the string for an origin comment.";

%feature("docstring") libcellml::GeneratorProfile::setOriginCommentString
"Set the string for an origin comment. To be useful, the string
should contain the <PROFILE_INFORMATION> and <LIBCELLML_VERSION> tags,
which will be replaced with a statement about the profile and the version of
libCellML used respectively.";

%feature("docstring") libcellml::GeneratorProfile::interfaceFileNameString
"Return the string for the interface file name.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceFileNameString
"Set the string for the interface file name.";

%feature("docstring") libcellml::GeneratorProfile::interfaceHeaderString
"Return the string for the interface of a header.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceHeaderString
"Set the string for the interface of a header.";

%feature("docstring") libcellml::GeneratorProfile::implementationHeaderString
"Return the string for an implementation header.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationHeaderString
"Set the string for an implementation header.";

%feature("docstring") libcellml::GeneratorProfile::interfaceVersionString
"Return the string for the interface of the version constant.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceVersionString
"Set the string for the interface of the version constant.";

%feature("docstring") libcellml::GeneratorProfile::implementationVersionString
"Return the string for the implementation of the version constant.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationVersionString
"Set the string for the implementation of the version constant.";

%feature("docstring") libcellml::GeneratorProfile::interfaceLibcellmlVersionString
"Return the string for the interface of the libCellML version constant.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceLibcellmlVersionString
"Set the string for the interface of the libCellML version constant.";

%feature("docstring") libcellml::GeneratorProfile::implementationLibcellmlVersionString
"Return the string for the implementation of the libCellML version constant.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationLibcellmlVersionString
"Set the string for the implementation of the libCellML version constant.";

%feature("docstring") libcellml::GeneratorProfile::interfaceStateCountString
"Return the string for the interface of the state count constant.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceStateCountString
"Set the string for the interface of the state count constant.";

%feature("docstring") libcellml::GeneratorProfile::implementationStateCountString
"Return the string for the implementation of the state count constant.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationStateCountString
"Set the string for the implementation of the state count
constant. To be useful, the string should contain the <STATE_COUNT> tag,
which will be replaced with the number of states in the model.";

%feature("docstring") libcellml::GeneratorProfile::interfaceVariableCountString
"Return the string for the interface of the variable count constant.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceVariableCountString
"Set the string for the interface of the variable count constant.";

%feature("docstring") libcellml::GeneratorProfile::implementationVariableCountString
"Return the string for the implementation of the variable count constant.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationVariableCountString
"Set the string for the implementation of the variable count
constant. To be useful, the string should contain the <VARIABLE_COUNT>
tag, which will be replaced with the number of states in the model.";

%feature("docstring") libcellml::GeneratorProfile::variableTypeObjectString
"Return the string for the data structure for the variable type object.";

%feature("docstring") libcellml::GeneratorProfile::setVariableTypeObjectString
"Set the string for the data structure for the variable
type object.";

%feature("docstring") libcellml::GeneratorProfile::constantVariableTypeString
"Return the string for the name of the constant variable type.";

%feature("docstring") libcellml::GeneratorProfile::setConstantVariableTypeString
"Set the string for the name of the constant variable type.";

%feature("docstring") libcellml::GeneratorProfile::computedConstantVariableTypeString
"Return the string for the name of the computed constant variable type.";

%feature("docstring") libcellml::GeneratorProfile::setComputedConstantVariableTypeString
"Set the string for the name of the computed constant variable type.";

%feature("docstring") libcellml::GeneratorProfile::algebraicVariableTypeString
"Return the string for the name of the algebraic variable type.";

%feature("docstring") libcellml::GeneratorProfile::setAlgebraicVariableTypeString
"Set the string for the name of the algebraic variable type.";

%feature("docstring") libcellml::GeneratorProfile::externalVariableTypeString
"Return the string for the name of the external variable type.";

%feature("docstring") libcellml::GeneratorProfile::setExternalVariableTypeString
"Set the string for the name of the external variable type.";

%feature("docstring") libcellml::GeneratorProfile::variableInfoObjectString
"Return the string for the data structure for the variable
information object.";

%feature("docstring") libcellml::GeneratorProfile::setVariableInfoObjectString
"Set the string for the data structure for the variable
information object. To be useful, the string should contain the
<NAME_SIZE>, <UNITS_SIZE> and <COMPONENT_SIZE> tags, which will be
replaced with the maximum size of a string for holding the name of a
component, variable and units, respectively.";

%feature("docstring") libcellml::GeneratorProfile::variableInfoWithTypeObjectString
"Return the string for the data structure for the variable
information (incl. its type) object.";

%feature("docstring") libcellml::GeneratorProfile::setVariableInfoWithTypeObjectString
"Set the string for the data structure for the variable
information (incl. its type) object. To be useful, the string should
contain the <NAME_SIZE>, <UNITS_SIZE> and <COMPONENT_SIZE> tags, which
will be replaced with the maximum size of a string for holding the name
of a component, variable and units, respectively.";

%feature("docstring") libcellml::GeneratorProfile::interfaceVoiInfoString
"Return the string for the interface of some information about the
variable of integration.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceVoiInfoString
"Set the string for the interface of some information about the
variable of integration.";

%feature("docstring") libcellml::GeneratorProfile::implementationVoiInfoString
"Return the string for the implementation of some information
about the variable of integration.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationVoiInfoString
"Set the string for the implementation of some information about
the variable of integration. To be useful, the string should contain the
<CODE> tag, which will be replaced with some information about the
variable of integration.";

%feature("docstring") libcellml::GeneratorProfile::interfaceStateInfoString
"Return the string for the interface of some information about the
different states.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceStateInfoString
"Set the string for the interface of some information about the
different states.";

%feature("docstring") libcellml::GeneratorProfile::implementationStateInfoString
"Return the string for the implementation of some information
about the different states.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationStateInfoString
"Set the string for the implementation of some information about
the different states. To be useful, the string should contain the <CODE>
tag, which will be replaced with some information about the different
states.";

%feature("docstring") libcellml::GeneratorProfile::interfaceVariableInfoString
"Return the string for the interface of some information about the
different variables.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceVariableInfoString
"Set the string for the interface of some information about the
different variables.";

%feature("docstring") libcellml::GeneratorProfile::implementationVariableInfoString
"Return the string for the implementation of some information
about the different variables.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationVariableInfoString
"Set the string for the implementation of some information about
the different variables. To be useful, the string should contain the
<CODE> tag, which will be replaced with some information about the
different variables.";

%feature("docstring") libcellml::GeneratorProfile::variableInfoEntryString
"Return the string for an entry in an array for some information
about a variable.";

%feature("docstring") libcellml::GeneratorProfile::setVariableInfoEntryString
"Set the string for an entry in an array for some information
about a variable. To be useful, the string should contain the
<COMPONENT>, <NAME> and <UNITS> tags, which will be replaced with the
name of the component, name and units of a variable respectively.";

%feature("docstring") libcellml::GeneratorProfile::variableInfoWithTypeEntryString
"Return the string for an entry in an array for some information
about a variable (incl. its type).";

%feature("docstring") libcellml::GeneratorProfile::setVariableInfoWithTypeEntryString
"Set the string for an entry in an array for some information
about a variable (incl. its type). To be useful, the string should
contain the <COMPONENT>, <NAME> and <UNITS> tags, which will be replaced
with the name of the component, name and units of a variable.";

%feature("docstring") libcellml::GeneratorProfile::voiString
"Return the string for the name of the variable of integration.";

%feature("docstring") libcellml::GeneratorProfile::setVoiString
"Set the string for the name of the variable of integration.";

%feature("docstring") libcellml::GeneratorProfile::statesArrayString
"Return the string for the name of the states array.";

%feature("docstring") libcellml::GeneratorProfile::setStatesArrayString
"Set the string for the name of the states array.";

%feature("docstring") libcellml::GeneratorProfile::ratesArrayString
"Return the string for the name of the rates array.";

%feature("docstring") libcellml::GeneratorProfile::setRatesArrayString
"Set the string for the name of the rates array.";

%feature("docstring") libcellml::GeneratorProfile::variablesArrayString
"Return the string for the name of the variables array.";

%feature("docstring") libcellml::GeneratorProfile::setVariablesArrayString
"Set the string for the name of the variables array.";

%feature("docstring") libcellml::GeneratorProfile::setReturnCreatedArrayString
"Set the string for returning a created array. To be useful, the
string should contain the <ARRAY_SIZE> tag, which will be replaced with
the size of the array to be created.";

%feature("docstring") libcellml::GeneratorProfile::interfaceCreateStatesArrayMethodString
"Return the string for the interface to create the states array.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceCreateStatesArrayMethodString
"Set the string for the interface to create the states array. To
be useful, the string should contain the <CODE> tag, which will be
replaced with some code to create the states array.";

%feature("docstring") libcellml::GeneratorProfile::implementationCreateStatesArrayMethodString
"Return the string for the implementation to create the states
array.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationCreateStatesArrayMethodString
"Set the string for the implementation to create the states
array. To be useful, the string should contain the <CODE> tag, which will
be replaced with some code to create the states array.";

%feature("docstring") libcellml::GeneratorProfile::interfaceCreateVariablesArrayMethodString
"Return the string for the interface to create variables array.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceCreateVariablesArrayMethodString
"Set the string for the interface to create variables array. To
be useful, the string should contain the <CODE> tag, which will be
replaced with some code to create the variables array.";

%feature("docstring") libcellml::GeneratorProfile::implementationCreateVariablesArrayMethodString
"Return the string for the implementation to create the variables array.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationCreateVariablesArrayMethodString
"Set the string for the implementation to create the variables
array. To be useful, the string should contain the <CODE> tag, which will
be replaced with some code to create the variables array.";

%feature("docstring") libcellml::GeneratorProfile::interfaceDeleteArrayMethodString
"Return the string for the interface to delete an array.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceDeleteArrayMethodString
"Set the string for the interface to delete an array.";

%feature("docstring") libcellml::GeneratorProfile::implementationDeleteArrayMethodString
"Return the string for the implementation to delete an array.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationDeleteArrayMethodString
"Set the string for the implementation to delete an array.";

%feature("docstring") libcellml::GeneratorProfile::interfaceInitialiseStatesAndConstantsMethodString
"Return the string for the interface to initialise states and constants.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceInitialiseStatesAndConstantsMethodString
"Set the string for the interface to initialise states and constants.";

%feature("docstring") libcellml::GeneratorProfile::implementationInitialiseStatesAndConstantsMethodString
"Return the string for the implementation to initialise states and constants.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationInitialiseStatesAndConstantsMethodString
"Set the string for the implementation to initialise states and constants.";

%feature("docstring") libcellml::GeneratorProfile::interfaceComputeComputedConstantsMethodString
"Return the string for the interface to compute computed constants.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceComputeComputedConstantsMethodString
"Set the string for the interface to compute computed constants.";

%feature("docstring") libcellml::GeneratorProfile::implementationComputeComputedConstantsMethodString
"Return the string for the implementation to compute computed constants.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationComputeComputedConstantsMethodString
"Set the string for the implementation to compute computed constants.";

%feature("docstring") libcellml::GeneratorProfile::interfaceComputeRatesMethodString
"Return the string for the interface to compute rates.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceComputeRatesMethodString
"Set the string for the interface to compute rates.";

%feature("docstring") libcellml::GeneratorProfile::implementationComputeRatesMethodString
"Return the string for the implementation to compute rates.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationComputeRatesMethodString
"Set the string for the implementation to compute rates.";

%feature("docstring") libcellml::GeneratorProfile::interfaceComputeVariablesMethodString
"Return the string for the interface to compute variables.";

%feature("docstring") libcellml::GeneratorProfile::setInterfaceComputeVariablesMethodString
"Set the string for the interface to compute variables.";

%feature("docstring") libcellml::GeneratorProfile::implementationComputeVariablesMethodString
"Return the string for the implementation to compute variables.";

%feature("docstring") libcellml::GeneratorProfile::setImplementationComputeVariablesMethodString
"Set the string for the implementation to compute variables.";

%feature("docstring") libcellml::GeneratorProfile::emptyMethodString
"Return the string for an empty method.";

%feature("docstring") libcellml::GeneratorProfile::setEmptyMethodString
"Set the string for an empty method.";

%feature("docstring") libcellml::GeneratorProfile::indentString
"Return the string for an indent.";

%feature("docstring") libcellml::GeneratorProfile::setIndentString
"Set the string for an indent.";

%feature("docstring") libcellml::GeneratorProfile::openArrayInitialiserString
"Return the string for opening an array initialiser.";

%feature("docstring") libcellml::GeneratorProfile::setOpenArrayInitialiserString
"Set the string for opening an array initialiser.";

%feature("docstring") libcellml::GeneratorProfile::closeArrayInitialiserString
"Return the string for closing an array initialiser.";

%feature("docstring") libcellml::GeneratorProfile::setCloseArrayInitialiserString
"Set the string for closing an array initialiser.";

%feature("docstring") libcellml::GeneratorProfile::openArrayString
"Return the string for opening an array.";

%feature("docstring") libcellml::GeneratorProfile::setOpenArrayString
"Set the string for opening an array.";

%feature("docstring") libcellml::GeneratorProfile::closeArrayString
"Return the string for closing an array.";

%feature("docstring") libcellml::GeneratorProfile::setCloseArrayString
"Set the string for closing an array.";

%feature("docstring") libcellml::GeneratorProfile::arrayElementSeparatorString
"Return the string for separating elements in an array.";

%feature("docstring") libcellml::GeneratorProfile::setArrayElementSeparatorString
"Set the string for separating elements in an array.";

%feature("docstring") libcellml::GeneratorProfile::stringDelimiterString
"Return the string for a string delimiter.";

%feature("docstring") libcellml::GeneratorProfile::setStringDelimiterString
"Set the string for a string delimiter.";

%feature("docstring") libcellml::GeneratorProfile::commandSeparatorString
"Return the string for a command separator.";

%feature("docstring") libcellml::GeneratorProfile::setCommandSeparatorString
"Set the string for a command separator.";

%{
#include "libcellml/generatorprofile.h"

#include <memory>
%}

%create_constructor(GeneratorProfile)
%extend libcellml::GeneratorProfile {
    GeneratorProfile(libcellml::GeneratorProfile::Profile profileType) {
        auto ptr = new std::shared_ptr<  libcellml::GeneratorProfile >(libcellml::GeneratorProfile::create(profileType));
        return reinterpret_cast<libcellml::GeneratorProfile *>(ptr);
    }
}

%include "libcellml/generatorprofile.h"

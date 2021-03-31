/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

const libCellMLModule = require('libcellml.js/libcellml.common')
let libcellml = null

describe("GeneratorProfile tests", () => {
  beforeAll(async () => {
    libcellml = await libCellMLModule();
  });
  test("Checking GeneratorProfile.profile.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setProfile(libcellml.Profile.PYTHON)
    expect(x.profile()).toBe(libcellml.Profile.PYTHON)
  });
  test("Checking GeneratorProfile.hasInterface.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasInterface(true)
    expect(x.hasInterface()).toBe(true)
  });
  test("Checking GeneratorProfile.assignmentString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAssignmentString("something")
    expect(x.assignmentString()).toBe("something")
  });
  test("Checking GeneratorProfile.eqString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setEqString("something")
    expect(x.eqString()).toBe("something")
  });
  test("Checking GeneratorProfile.neqString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setNeqString("something")
    expect(x.neqString()).toBe("something")
  });
  test("Checking GeneratorProfile.ltString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setLtString("something")
    expect(x.ltString()).toBe("something")
  });
  test("Checking GeneratorProfile.leqString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setLeqString("something")
    expect(x.leqString()).toBe("something")
  });
  test("Checking GeneratorProfile.gtString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setGtString("something")
    expect(x.gtString()).toBe("something")
  });
  test("Checking GeneratorProfile.geqString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setGeqString("something")
    expect(x.geqString()).toBe("something")
  });
  test("Checking GeneratorProfile.andString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAndString("something")
    expect(x.andString()).toBe("something")
  });
  test("Checking GeneratorProfile.orString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setOrString("something")
    expect(x.orString()).toBe("something")
  });
  test("Checking GeneratorProfile.xorString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setXorString("something")
    expect(x.xorString()).toBe("something")
  });
  test("Checking GeneratorProfile.notString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setNotString("something")
    expect(x.notString()).toBe("something")
  });
  test("Checking GeneratorProfile.hasEqOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasEqOperator(true)
    expect(x.hasEqOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.hasNeqOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasNeqOperator(true)
    expect(x.hasNeqOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.hasLtOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasLtOperator(true)
    expect(x.hasLtOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.hasLeqOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasLeqOperator(true)
    expect(x.hasLeqOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.hasGtOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasGtOperator(true)
    expect(x.hasGtOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.hasGeqOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasGeqOperator(true)
    expect(x.hasGeqOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.hasAndOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasAndOperator(true)
    expect(x.hasAndOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.hasOrOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasOrOperator(true)
    expect(x.hasOrOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.hasXorOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasXorOperator(true)
    expect(x.hasXorOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.hasNotOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasNotOperator(true)
    expect(x.hasNotOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.plusString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setPlusString("something")
    expect(x.plusString()).toBe("something")
  });
  test("Checking GeneratorProfile.minusString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setMinusString("something")
    expect(x.minusString()).toBe("something")
  });
  test("Checking GeneratorProfile.timesString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setTimesString("something")
    expect(x.timesString()).toBe("something")
  });
  test("Checking GeneratorProfile.divideString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setDivideString("something")
    expect(x.divideString()).toBe("something")
  });
  test("Checking GeneratorProfile.powerString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setPowerString("something")
    expect(x.powerString()).toBe("something")
  });
  test("Checking GeneratorProfile.squareRootString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setSquareRootString("something")
    expect(x.squareRootString()).toBe("something")
  });
  test("Checking GeneratorProfile.squareString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setSquareString("something")
    expect(x.squareString()).toBe("something")
  });
  test("Checking GeneratorProfile.absoluteValueString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAbsoluteValueString("something")
    expect(x.absoluteValueString()).toBe("something")
  });
  test("Checking GeneratorProfile.exponentialString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setExponentialString("something")
    expect(x.exponentialString()).toBe("something")
  });
  test("Checking GeneratorProfile.naturalLogarithmString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setNaturalLogarithmString("something")
    expect(x.naturalLogarithmString()).toBe("something")
  });
  test("Checking GeneratorProfile.commonLogarithmString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCommonLogarithmString("something")
    expect(x.commonLogarithmString()).toBe("something")
  });
  test("Checking GeneratorProfile.ceilingString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCeilingString("something")
    expect(x.ceilingString()).toBe("something")
  });
  test("Checking GeneratorProfile.floorString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setFloorString("something")
    expect(x.floorString()).toBe("something")
  });
  test("Checking GeneratorProfile.minString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setMinString("something")
    expect(x.minString()).toBe("something")
  });
  test("Checking GeneratorProfile.maxString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setMaxString("something")
    expect(x.maxString()).toBe("something")
  });
  test("Checking GeneratorProfile.remString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setRemString("something")
    expect(x.remString()).toBe("something")
  });
  test("Checking GeneratorProfile.hasPowerOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasPowerOperator(true)
    expect(x.hasPowerOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.sinString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setSinString("something")
    expect(x.sinString()).toBe("something")
  });
  test("Checking GeneratorProfile.cosString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCosString("something")
    expect(x.cosString()).toBe("something")
  });
  test("Checking GeneratorProfile.tanString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setTanString("something")
    expect(x.tanString()).toBe("something")
  });
  test("Checking GeneratorProfile.secString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setSecString("something")
    expect(x.secString()).toBe("something")
  });
  test("Checking GeneratorProfile.cscString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCscString("something")
    expect(x.cscString()).toBe("something")
  });
  test("Checking GeneratorProfile.cotString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCotString("something")
    expect(x.cotString()).toBe("something")
  });
  test("Checking GeneratorProfile.sinhString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setSinhString("something")
    expect(x.sinhString()).toBe("something")
  });
  test("Checking GeneratorProfile.coshString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCoshString("something")
    expect(x.coshString()).toBe("something")
  });
  test("Checking GeneratorProfile.tanhString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setTanhString("something")
    expect(x.tanhString()).toBe("something")
  });
  test("Checking GeneratorProfile.sechString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setSechString("something")
    expect(x.sechString()).toBe("something")
  });
  test("Checking GeneratorProfile.cschString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCschString("something")
    expect(x.cschString()).toBe("something")
  });
  test("Checking GeneratorProfile.cothString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCothString("something")
    expect(x.cothString()).toBe("something")
  });
  test("Checking GeneratorProfile.asinString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAsinString("something")
    expect(x.asinString()).toBe("something")
  });
  test("Checking GeneratorProfile.acosString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcosString("something")
    expect(x.acosString()).toBe("something")
  });
  test("Checking GeneratorProfile.atanString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAtanString("something")
    expect(x.atanString()).toBe("something")
  });
  test("Checking GeneratorProfile.asecString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAsecString("something")
    expect(x.asecString()).toBe("something")
  });
  test("Checking GeneratorProfile.acscString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcscString("something")
    expect(x.acscString()).toBe("something")
  });
  test("Checking GeneratorProfile.acotString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcotString("something")
    expect(x.acotString()).toBe("something")
  });
  test("Checking GeneratorProfile.asinhString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAsinhString("something")
    expect(x.asinhString()).toBe("something")
  });
  test("Checking GeneratorProfile.acoshString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcoshString("something")
    expect(x.acoshString()).toBe("something")
  });
  test("Checking GeneratorProfile.atanhString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAtanhString("something")
    expect(x.atanhString()).toBe("something")
  });
  test("Checking GeneratorProfile.asechString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAsechString("something")
    expect(x.asechString()).toBe("something")
  });
  test("Checking GeneratorProfile.acschString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcschString("something")
    expect(x.acschString()).toBe("something")
  });
  test("Checking GeneratorProfile.acothString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcothString("something")
    expect(x.acothString()).toBe("something")
  });
  test("Checking GeneratorProfile.conditionalOperatorIfString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setConditionalOperatorIfString("something")
    expect(x.conditionalOperatorIfString()).toBe("something")
  });
  test("Checking GeneratorProfile.conditionalOperatorElseString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setConditionalOperatorElseString("something")
    expect(x.conditionalOperatorElseString()).toBe("something")
  });
  test("Checking GeneratorProfile.piecewiseIfString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setPiecewiseIfString("something")
    expect(x.piecewiseIfString()).toBe("something")
  });
  test("Checking GeneratorProfile.piecewiseElseString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setPiecewiseElseString("something")
    expect(x.piecewiseElseString()).toBe("something")
  });
  test("Checking GeneratorProfile.hasConditionalOperator.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setHasConditionalOperator(true)
    expect(x.hasConditionalOperator()).toBe(true)
  });
  test("Checking GeneratorProfile.trueString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setTrueString("something")
    expect(x.trueString()).toBe("something")
  });
  test("Checking GeneratorProfile.falseString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setFalseString("something")
    expect(x.falseString()).toBe("something")
  });
  test("Checking GeneratorProfile.eString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setEString("something")
    expect(x.eString()).toBe("something")
  });
  test("Checking GeneratorProfile.piString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setPiString("something")
    expect(x.piString()).toBe("something")
  });
  test("Checking GeneratorProfile.infString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInfString("something")
    expect(x.infString()).toBe("something")
  });
  test("Checking GeneratorProfile.nanString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setNanString("something")
    expect(x.nanString()).toBe("something")
  });
  test("Checking GeneratorProfile.eqFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setEqFunctionString("something")
    expect(x.eqFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.neqFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setNeqFunctionString("something")
    expect(x.neqFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.ltFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setLtFunctionString("something")
    expect(x.ltFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.leqFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setLeqFunctionString("something")
    expect(x.leqFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.gtFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setGtFunctionString("something")
    expect(x.gtFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.geqFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setGeqFunctionString("something")
    expect(x.geqFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.andFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAndFunctionString("something")
    expect(x.andFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.orFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setOrFunctionString("something")
    expect(x.orFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.xorFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setXorFunctionString("something")
    expect(x.xorFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.notFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setNotFunctionString("something")
    expect(x.notFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.minFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setMinFunctionString("something")
    expect(x.minFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.maxFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setMaxFunctionString("something")
    expect(x.maxFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.secFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setSecFunctionString("something")
    expect(x.secFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.cscFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCscFunctionString("something")
    expect(x.cscFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.cotFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCotFunctionString("something")
    expect(x.cotFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.sechFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setSechFunctionString("something")
    expect(x.sechFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.cschFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCschFunctionString("something")
    expect(x.cschFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.cothFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCothFunctionString("something")
    expect(x.cothFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.asecFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAsecFunctionString("something")
    expect(x.asecFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.acscFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcscFunctionString("something")
    expect(x.acscFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.acotFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcotFunctionString("something")
    expect(x.acotFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.asechFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAsechFunctionString("something")
    expect(x.asechFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.acschFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcschFunctionString("something")
    expect(x.acschFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.acothFunctionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAcothFunctionString("something")
    expect(x.acothFunctionString()).toBe("something")
  });
  test("Checking GeneratorProfile.commentString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCommentString("something")
    expect(x.commentString()).toBe("something")
  });
  test("Checking GeneratorProfile.originCommentString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setOriginCommentString("something")
    expect(x.originCommentString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceFileNameString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceFileNameString("something")
    expect(x.interfaceFileNameString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceHeaderString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceHeaderString("something")
    expect(x.interfaceHeaderString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationHeaderString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationHeaderString("something")
    expect(x.implementationHeaderString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceVersionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceVersionString("something")
    expect(x.interfaceVersionString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationVersionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationVersionString("something")
    expect(x.implementationVersionString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceLibcellmlVersionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceLibcellmlVersionString("something")
    expect(x.interfaceLibcellmlVersionString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationLibcellmlVersionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationLibcellmlVersionString("something")
    expect(x.implementationLibcellmlVersionString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceStateCountString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceStateCountString("something")
    expect(x.interfaceStateCountString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationStateCountString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationStateCountString("something")
    expect(x.implementationStateCountString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceVariableCountString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceVariableCountString("something")
    expect(x.interfaceVariableCountString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationVariableCountString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationVariableCountString("something")
    expect(x.implementationVariableCountString()).toBe("something")
  });
  test("Checking GeneratorProfile.variableTypeObjectString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setVariableTypeObjectString("something")
    expect(x.variableTypeObjectString()).toBe("something")
  });
  test("Checking GeneratorProfile.variableTypeObjectExternalTypeString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setVariableTypeObjectExternalTypeString("something")
    expect(x.variableTypeObjectExternalTypeString()).toBe("something")
  });
  test("Checking GeneratorProfile.constantVariableTypeString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setConstantVariableTypeString("something")
    expect(x.constantVariableTypeString()).toBe("something")
  });
  test("Checking GeneratorProfile.computedConstantVariableTypeString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setComputedConstantVariableTypeString("something")
    expect(x.computedConstantVariableTypeString()).toBe("something")
  });
  test("Checking GeneratorProfile.algebraicVariableTypeString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setAlgebraicVariableTypeString("something")
    expect(x.algebraicVariableTypeString()).toBe("something")
  });
  test("Checking GeneratorProfile.externalVariableTypeString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setExternalVariableTypeString("something")
    expect(x.externalVariableTypeString()).toBe("something")
  });
  test("Checking GeneratorProfile.variableInfoObjectString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setVariableInfoObjectString("something")
    expect(x.variableInfoObjectString()).toBe("something")
  });
  test("Checking GeneratorProfile.variableInfoWithTypeObjectString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setVariableInfoWithTypeObjectString("something")
    expect(x.variableInfoWithTypeObjectString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceVoiInfoString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceVoiInfoString("something")
    expect(x.interfaceVoiInfoString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationVoiInfoString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationVoiInfoString("something")
    expect(x.implementationVoiInfoString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceStateInfoString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceStateInfoString("something")
    expect(x.interfaceStateInfoString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationStateInfoString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationStateInfoString("something")
    expect(x.implementationStateInfoString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceVariableInfoString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceVariableInfoString("something")
    expect(x.interfaceVariableInfoString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationVariableInfoString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationVariableInfoString("something")
    expect(x.implementationVariableInfoString()).toBe("something")
  });
  test("Checking GeneratorProfile.variableInfoEntryString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setVariableInfoEntryString("something")
    expect(x.variableInfoEntryString()).toBe("something")
  });
  test("Checking GeneratorProfile.variableInfoWithTypeEntryString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setVariableInfoWithTypeEntryString("something")
    expect(x.variableInfoWithTypeEntryString()).toBe("something")
  });
  test("Checking GeneratorProfile.voiString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setVoiString("something")
    expect(x.voiString()).toBe("something")
  });
  test("Checking GeneratorProfile.statesArrayString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setStatesArrayString("something")
    expect(x.statesArrayString()).toBe("something")
  });
  test("Checking GeneratorProfile.ratesArrayString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setRatesArrayString("something")
    expect(x.ratesArrayString()).toBe("something")
  });
  test("Checking GeneratorProfile.variablesArrayString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setVariablesArrayString("something")
    expect(x.variablesArrayString()).toBe("something")
  });
  test("Checking GeneratorProfile.externalVariableMethodTypeDefinitionString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setExternalVariableMethodTypeDefinitionString("something")
    expect(x.externalVariableMethodTypeDefinitionString()).toBe("something")
  });
  test("Checking GeneratorProfile.externalVariableMethodParameterString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setExternalVariableMethodParameterString("something")
    expect(x.externalVariableMethodParameterString()).toBe("something")
  });
  test("Checking GeneratorProfile.externalVariableMethodCallString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setExternalVariableMethodCallString("something")
    expect(x.externalVariableMethodCallString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceCreateStatesArrayMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceCreateStatesArrayMethodString("something")
    expect(x.interfaceCreateStatesArrayMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationCreateStatesArrayMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationCreateStatesArrayMethodString("something")
    expect(x.implementationCreateStatesArrayMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceCreateVariablesArrayMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceCreateVariablesArrayMethodString("something")
    expect(x.interfaceCreateVariablesArrayMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationCreateVariablesArrayMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationCreateVariablesArrayMethodString("something")
    expect(x.implementationCreateVariablesArrayMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceDeleteArrayMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceDeleteArrayMethodString("something")
    expect(x.interfaceDeleteArrayMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationDeleteArrayMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationDeleteArrayMethodString("something")
    expect(x.implementationDeleteArrayMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceInitialiseStatesAndConstantsMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceInitialiseStatesAndConstantsMethodString("something")
    expect(x.interfaceInitialiseStatesAndConstantsMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationInitialiseStatesAndConstantsMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationInitialiseStatesAndConstantsMethodString("something")
    expect(x.implementationInitialiseStatesAndConstantsMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceComputeComputedConstantsMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceComputeComputedConstantsMethodString("something")
    expect(x.interfaceComputeComputedConstantsMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationComputeComputedConstantsMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationComputeComputedConstantsMethodString("something")
    expect(x.implementationComputeComputedConstantsMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceComputeRatesMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceComputeRatesMethodString("something")
    expect(x.interfaceComputeRatesMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationComputeRatesMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationComputeRatesMethodString("something")
    expect(x.implementationComputeRatesMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.interfaceComputeVariablesMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setInterfaceComputeVariablesMethodString("something")
    expect(x.interfaceComputeVariablesMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.implementationComputeVariablesMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setImplementationComputeVariablesMethodString("something")
    expect(x.implementationComputeVariablesMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.emptyMethodString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setEmptyMethodString("something")
    expect(x.emptyMethodString()).toBe("something")
  });
  test("Checking GeneratorProfile.indentString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setIndentString("something")
    expect(x.indentString()).toBe("something")
  });
  test("Checking GeneratorProfile.openArrayInitialiserString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setOpenArrayInitialiserString("something")
    expect(x.openArrayInitialiserString()).toBe("something")
  });
  test("Checking GeneratorProfile.closeArrayInitialiserString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCloseArrayInitialiserString("something")
    expect(x.closeArrayInitialiserString()).toBe("something")
  });
  test("Checking GeneratorProfile.openArrayString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setOpenArrayString("something")
    expect(x.openArrayString()).toBe("something")
  });
  test("Checking GeneratorProfile.closeArrayString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCloseArrayString("something")
    expect(x.closeArrayString()).toBe("something")
  });
  test("Checking GeneratorProfile.arrayElementSeparatorString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setArrayElementSeparatorString("something")
    expect(x.arrayElementSeparatorString()).toBe("something")
  });
  test("Checking GeneratorProfile.stringDelimiterString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setStringDelimiterString("something")
    expect(x.stringDelimiterString()).toBe("something")
  });
  test("Checking GeneratorProfile.commandSeparatorString.", () => {
    const x = new libcellml.GeneratorProfile(libcellml.Profile.C)

    x.setCommandSeparatorString("something")
    expect(x.commandSeparatorString()).toBe("something")
  });
})

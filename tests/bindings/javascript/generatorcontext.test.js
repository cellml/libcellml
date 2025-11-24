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

const loadLibCellML = require('libcellml.js/libcellml.common')
const { hhSquidAxon1952 } = require('./resources')

let libcellml = null

describe("GeneratorContext tests", () => {
    beforeAll(async () => {
        libcellml = await loadLibCellML()
    })
    test('Checking Generator tracking/untracking of variables.', () => {
        const p = new libcellml.Parser(true)
        const m = p.parseModel(hhSquidAxon1952)
        const v = m.componentByName("membrane", true).variableByName("Cm")
        const a = new libcellml.Analyser()

        a.analyseModel(m)

        const am = a.analyserModel()
        const av = am.analyserVariable(v)
        const gc = new libcellml.GeneratorContext()

        gc.untrackVariable(av)

        expect(gc.isTrackedVariable(av)).toBe(false)
        expect(gc.isUntrackedVariable(av)).toBe(true)

        gc.trackVariable(av)

        expect(gc.isTrackedVariable(av)).toBe(true)
        expect(gc.isUntrackedVariable(av)).toBe(false)

        gc.untrackAllConstants(am)

        expect(gc.trackedConstantCount(am)).toBe(0)
        expect(gc.untrackedConstantCount(am)).toBe(5)

        gc.trackAllConstants(am)

        expect(gc.trackedConstantCount(am)).toBe(5)
        expect(gc.untrackedConstantCount(am)).toBe(0)

        gc.untrackAllComputedConstants(am)

        expect(gc.trackedComputedConstantCount(am)).toBe(0)
        expect(gc.untrackedComputedConstantCount(am)).toBe(3)

        gc.trackAllComputedConstants(am)

        expect(gc.trackedComputedConstantCount(am)).toBe(3)
        expect(gc.untrackedComputedConstantCount(am)).toBe(0)

        gc.untrackAllAlgebraicVariables(am)

        expect(gc.trackedAlgebraicVariableCount(am)).toBe(0)
        expect(gc.untrackedAlgebraicVariableCount(am)).toBe(10)

        gc.trackAllAlgebraicVariables(am)

        expect(gc.trackedAlgebraicVariableCount(am)).toBe(10)
        expect(gc.untrackedAlgebraicVariableCount(am)).toBe(0)

        gc.untrackAllVariables(am)

        expect(gc.trackedVariableCount(am)).toBe(0)
        expect(gc.untrackedVariableCount(am)).toBe(18)

        gc.trackAllVariables(am)

        expect(gc.trackedVariableCount(am)).toBe(18)
        expect(gc.untrackedVariableCount(am)).toBe(0)
    })
})

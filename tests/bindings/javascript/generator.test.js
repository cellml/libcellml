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
const { basicModel, hhSquidAxon1952 } = require('./resources')

let libcellml = null

describe("Generator tests", () => {
    beforeAll(async () => {
        libcellml = await loadLibCellML()
    })
    test('Checking Generator profile manipulation.', () => {
        const g = new libcellml.Generator()
        const gP = new libcellml.GeneratorProfile(libcellml.GeneratorProfile.Profile.C)

        expect(g.profile().commentString()).toBe("/* [CODE] */\n")

        gP.setProfile(libcellml.GeneratorProfile.Profile.PYTHON)
        g.setProfile(gP)

        expect(g.profile().commentString()).toBe("# [CODE]\n")
    })
    test('Checking Generator tracking/untracking of variables.', () => {
        const p = new libcellml.Parser(true)
        const m = p.parseModel(hhSquidAxon1952)
        const v = m.componentByName("membrane", true).variableByName("Cm")
        const a = new libcellml.Analyser()

        a.analyseModel(m)

        const am = a.analyserModel()
        const av = am.analyserVariable(v)
        const g = new libcellml.Generator()

        g.untrackVariable(av)

        expect(g.isTrackedVariable(av)).toBe(false)
        expect(g.isUntrackedVariable(av)).toBe(true)

        g.trackVariable(av)

        expect(g.isTrackedVariable(av)).toBe(true)
        expect(g.isUntrackedVariable(av)).toBe(false)

        g.untrackAllConstants(am)

        expect(g.trackedConstantCount(am)).toBe(0)
        expect(g.untrackedConstantCount(am)).toBe(5)

        g.trackAllConstants(am)

        expect(g.trackedConstantCount(am)).toBe(5)
        expect(g.untrackedConstantCount(am)).toBe(0)

        g.untrackAllComputedConstants(am)

        expect(g.trackedComputedConstantCount(am)).toBe(0)
        expect(g.untrackedComputedConstantCount(am)).toBe(3)

        g.trackAllComputedConstants(am)

        expect(g.trackedComputedConstantCount(am)).toBe(3)
        expect(g.untrackedComputedConstantCount(am)).toBe(0)

        g.untrackAllAlgebraic(am)

        expect(g.trackedAlgebraicCount(am)).toBe(0)
        expect(g.untrackedAlgebraicCount(am)).toBe(10)

        g.trackAllAlgebraic(am)

        expect(g.trackedAlgebraicCount(am)).toBe(10)
        expect(g.untrackedAlgebraicCount(am)).toBe(0)

        g.untrackAllVariables(am)

        expect(g.trackedVariableCount(am)).toBe(0)
        expect(g.untrackedVariableCount(am)).toBe(18)

        g.trackAllVariables(am)

        expect(g.trackedVariableCount(am)).toBe(18)
        expect(g.untrackedVariableCount(am)).toBe(0)
    })
    test('Checking Generator code generation.', () => {
        const g = new libcellml.Generator()
        const p = new libcellml.Parser(true)

        m = p.parseModel(basicModel)
        a = new libcellml.Analyser()

        a.analyseModel(m)

        am = a.analyserModel()

        const interface_lines = g.interfaceCode(am).split('\n')
        expect(interface_lines.length).toBe(38)

        const implementation_lines = g.implementationCode(am).split('\n')
        expect(implementation_lines.length).toBe(97)

        const equation_line_1 = libcellml.Generator.equationCode(a.analyserModel().analyserEquation(0).ast())
        expect(equation_line_1.length).toBe(14)

        const gp = new libcellml.GeneratorProfile(libcellml.GeneratorProfile.Profile.PYTHON)
        const equation_line_2 = libcellml.Generator.equationCodeByProfile(a.analyserModel().analyserEquation(0).ast(), gp)
        expect(equation_line_2.length).toBe(14)
    })
})

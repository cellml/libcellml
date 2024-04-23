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

describe("Interpreter tests", () => {
    beforeAll(async () => {
        libcellml = await loadLibCellML()
    })

    function expectArray(expectedValues, values) {
        expect(expectedValues.length).toBe(values.size())

        for (let i = 0; i < expectedValues.length; ++i) {
            if (Number.isNaN(expectedValues[i])) {
                expect(Number.isNaN(values.get(i))).toBe(true)
            } else {
                expect(expectedValues[i]).toBeCloseTo(values.get(i))
            }
        }
    }

    test('Checking Interpreter model manipulation.', () => {
        const i = new libcellml.Interpreter()
        const p = new libcellml.Parser(true)

        m = p.parseModel(hhSquidAxon1952)
        a = new libcellml.Analyser()

        a.analyseModel(m)

        expect(i.model()).toBe(null)

        i.setModel(a.model())

        expect(i.model()).toBeDefined()

        expect(i.voi()).toBe(0.0)

        const NaN_x_4 = Array(4).fill(Number.NaN)
        const NaN_x_18 = Array(18).fill(Number.NaN)

        expectArray(NaN_x_4, i.states())
        expectArray(NaN_x_4, i.rates())
        expectArray(NaN_x_18, i.variables())

        i.initialiseVariables()
        i.computeComputedConstants()
        i.computeRates(0.0)
        i.computeVariables(0.0)

        expectArray([0.0, 0.6, 0.05, 0.325], i.states())
        expectArray([0.60076875, -0.0004555239065400646, 0.012385538355398518, -0.0013415722863204596], i.rates())
        expectArray([0.0, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.04742587317756678, 12.0, 36.0, 0.05819767068693265, 0.125], i.variables())
    })
})

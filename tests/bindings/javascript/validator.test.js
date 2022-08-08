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
const { sineModel } = require('./resources')

let libcellml = null

describe("Validator tests", () => {
  beforeAll(async () => {
    libcellml = await libCellMLModule();
  });
  test("Checking Validator.validateModel.", () => {
    const x = new libcellml.Validator()
    const p = new libcellml.Parser()

    const m = p.parseModel(sineModel)

    x.validateModel(m)

    expect(x.issueCount()).toBe(0)
  });
})

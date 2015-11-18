/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Some license of other
*/

#include "gtest/gtest.h"

#include <libcellml>

/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */

TEST(Coverage, import) {
    std::string e = "";
    libcellml::Import i, im;

    im = std::move(i);

    // Copy constructor
    libcellml::Import ic(im);

    EXPECT_EQ(e, ic.serialise(libcellml::FORMAT_XML));
}

TEST(Coverage, entity) {
    std::string ex = "";

    libcellml::Entity e, em;

    EXPECT_EQ(ex, e.serialise(libcellml::FORMAT_XML));
    em = std::move(e);

    libcellml::Model m;
    e.setParent(&m);

    EXPECT_EQ(&m, e.getParent());

    libcellml::Component c;
    e.setParent(&c);

    EXPECT_EQ(&c, e.getParent());
}


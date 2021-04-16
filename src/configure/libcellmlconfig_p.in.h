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

#pragma once

/**
 * @brief Define a size type for the zlib uncompress function.
 *
 * Windows and Unices have opposite ideas about the size type
 * required for zlib's uncompress function.  This typedef is
 * configured to work dependent on the platform.
 */
typedef @UNCOMPRESS_SIZE_TYPE@ UNCOMPRESS_SIZE_TYPE;

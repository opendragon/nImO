#--------------------------------------------------------------------------------------------------
#
#  File:       Tests/CMakeLists.txt
#
#  Project:    nImO
#
#  Contains:   The CMAKE definitions for the unit test application.
#
#  Written by: Norman Jaffe
#
#  Copyright:  (c) 2016 by OpenDragon.
#
#              All rights reserved. Redistribution and use in source and binary forms, with or
#              without modification, are permitted provided that the following conditions are met:
#                * Redistributions of source code must retain the above copyright notice, this list
#                  of conditions and the following disclaimer.
#                * Redistributions in binary form must reproduce the above copyright notice, this
#                  list of conditions and the following disclaimer in the documentation and / or
#                  other materials provided with the distribution.
#                * Neither the name of the copyright holders nor the names of its contributors may
#                  be used to endorse or promote products derived from this software without
#                  specific prior written permission.
#
#              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
#              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
#              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
#              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
#              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#              ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
#              DAMAGE.
#
#  Created:    2016-02-18
#
#--------------------------------------------------------------------------------------------------

include_directories("${nImO_SOURCE_DIR}")

set(THIS_TARGET nImOatomicTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else(WIN32)
    set(VERS_RESOURCE "")
endif(WIN32)

configure_file(${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)

#add_library(nImOcommonTestSupport)

enable_testing()

add_executable(${THIS_TARGET}
               nImOatomicTest.cpp
               ${VERS_RESOURCE})

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be
# processed once.
#target_link_libraries(${THIS_TARGET} nImOcommonTestSupport ${nImO_LINK_LIBRARIES})
target_link_libraries(${THIS_TARGET} ${nImO_LINK_LIBRARIES})

if(APPLE)
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                       libnImOcommon.dylib "@rpath/libnImOcommon.dylib" ${THIS_TARGET})

    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                       libodLogging.dylib "@rpath/libodLogging.dylib" ${THIS_TARGET})

endif(APPLE)

# Test empty buffer chunk
add_test(NAME TestEmptyBufferChunk COMMAND ${THIS_TARGET} 1)
# Test buffer chunk with 1 byte
add_test(NAME TestBufferChunkWithSingleByte COMMAND ${THIS_TARGET} 2)
# Test buffer chunk filled with data
add_test(NAME TestFilledBufferChunk COMMAND ${THIS_TARGET} 3)
# Test buffer chunk overfilled with data
add_test(NAME TestOverfilledBufferChunk COMMAND ${THIS_TARGET} 4)
# Test buffer chunk reset
add_test(NAME TestBufferChunkReset COMMAND ${THIS_TARGET} 5)

# Test empty string buffer
add_test(NAME TestEmptyStringBuffer COMMAND ${THIS_TARGET} 10)
# Test string buffer with no characters
add_test(NAME TestStringBufferWithNoCharacters COMMAND ${THIS_TARGET} 11 "" "")
# Test string buffer with single character
add_test(NAME TestStringBufferWithSingleCharacter COMMAND ${THIS_TARGET} 11 "a" "a")
# Test string buffer with multiple characters
add_test(NAME TestStringBufferWithMultipleCharacters COMMAND ${THIS_TARGET} 11 "abcde" "abcde")
# Test string buffer with false
add_test(NAME TestStringBufferWithFalse COMMAND ${THIS_TARGET} 12 0 false)
# Test string buffer with true
add_test(NAME TestStringBufferWithTrue COMMAND ${THIS_TARGET} 12 1 true)
# Test string buffer with integer zero
add_test(NAME TestStringBufferWithIntegerZero COMMAND ${THIS_TARGET} 13 0 0)
# Test string buffer with positive integer
add_test(NAME TestStringBufferWithPositiveInteger COMMAND ${THIS_TARGET} 13 12345 12345)
# Test string buffer with negative integer
add_test(NAME TestStringBufferWithNegativeInteger COMMAND ${THIS_TARGET} 13 "-12345" "-12345")
# Test string buffer with empty string
add_test(NAME TestStringBufferWithEmptyString COMMAND ${THIS_TARGET} 14 "" "\"\"")
# Test string buffer with simple string
add_test(NAME TestStringBufferWithSimpleString COMMAND ${THIS_TARGET} 14 abcde "\"abcde\"")
# Test string buffer with string with double quotes
add_test(NAME TestStringBufferWithStringWithDblQuotes COMMAND ${THIS_TARGET} 14 "ab\"cde" "'ab\"cde'")
# Test string buffer with string with single quotes
add_test(NAME TestStringBufferWithStringWithSnglQuotes COMMAND ${THIS_TARGET} 14 "ab'cde" "\"ab'cde\"")
# Test string buffer with string with escaped characters
add_test(NAME TestStringBufferWithStringWithEscapedChars COMMAND ${THIS_TARGET} 15)
# Test string buffer with floating point zero
add_test(NAME TestStringBufferWithFloatingPointZero COMMAND ${THIS_TARGET} 16 "0.0" "0")
# Test string buffer with simple positive floating point
add_test(NAME TestStringBufferWithPositiveFloatingPoint COMMAND ${THIS_TARGET} 16 "1234.5" "1234.5")
# Test string buffer with simple negative floating point
add_test(NAME TestStringBufferWithNegativeFloatingPoint COMMAND ${THIS_TARGET} 16 "-1234.5" "-1234.5")
# Test string buffer with very small floating point
add_test(NAME TestStringBufferWithVerySmallFloatingPoint COMMAND ${THIS_TARGET} 16 "1e-20" "1E-20")
# Test string buffer with very big floating point
add_test(NAME TestStringBufferWithVeryBigFloatingPoint COMMAND ${THIS_TARGET} 16 "1e22" "1E+22")
# Test big string buffer
add_test(NAME TestBigStringBuffer COMMAND ${THIS_TARGET} 17)
# Test string buffer with empty blob
add_test(NAME TestStringBufferWithEmptyBlob COMMAND ${THIS_TARGET} 18)
# Test string buffer with simple blob
add_test(NAME TestStringBufferWithSmallBlob COMMAND ${THIS_TARGET} 19)
# Test string buffer with big blob
add_test(NAME TestStringBufferWithBigBlob COMMAND ${THIS_TARGET} 20)
# Test string buffer reset
add_test(NAME TestStringBufferReset COMMAND ${THIS_TARGET} 21)

# Test default boolean value
add_test(NAME TestDefaultBooleanValue COMMAND ${THIS_TARGET} 50)
# Test false boolean value
add_test(NAME TestFalseBooleanValue COMMAND ${THIS_TARGET} 51 0 "false")
# Test true boolean value
add_test(NAME TestTrueBooleanValue COMMAND ${THIS_TARGET} 51 1 "true")
# Test default number value
add_test(NAME TestDefaultNumberValue COMMAND ${THIS_TARGET} 52)
# Test integer number value
add_test(NAME TestIntegerNumberValue COMMAND ${THIS_TARGET} 53 "12345" "12345")
# Test floating point number value
add_test(NAME TestFloatingPointNumberValue COMMAND ${THIS_TARGET} 53 "123.45" "123.45")
# Test default string value
add_test(NAME TestDefaultStringValue COMMAND ${THIS_TARGET} 54)
# Test short string value
add_test(NAME TestShortStringValue COMMAND ${THIS_TARGET} 55 "abcdef" "\"abcdef\"")
# Test string value with escaped characters
add_test(NAME TestStringValueWithEscapedChars COMMAND ${THIS_TARGET} 56)
# Test default blob value
add_test(NAME TestDefaultBlobValue COMMAND ${THIS_TARGET} 57)
# Test small blob value
add_test(NAME TestSmallBlobValue COMMAND ${THIS_TARGET} 58)
# Test big blob value
add_test(NAME TestBigBlobValue COMMAND ${THIS_TARGET} 59)
# Test boolean copy constructor and assignment operators
add_test(NAME TestBooleanCopyAndAssign COMMAND ${THIS_TARGET} 60)
# Test integer number copy constructor and assignment operators
add_test(NAME TestIntegerCopyAndAssign COMMAND ${THIS_TARGET} 61)
# Test floating point copy constructor and assignment operators
add_test(NAME TestFloatingPointCopyAndAssign COMMAND ${THIS_TARGET} 62)
# Test string copy constructor and assignment operators
add_test(NAME TestStringCopyAndAssign COMMAND ${THIS_TARGET} 63)
# Test blob copy constructor and assignment operator
add_test(NAME TestBlobCopyAndAssign COMMAND ${THIS_TARGET} 64)

# Test valid boolean compares
add_test(NAME TestValidBooleanCompares COMMAND ${THIS_TARGET} 80)
# Test valid number compares
add_test(NAME TestValidNumberCompares COMMAND ${THIS_TARGET} 81)
# Test valid string compares
add_test(NAME TestValidStringCompares COMMAND ${THIS_TARGET} 82)
# Test valid blob compares
add_test(NAME TestValidBlobCompares COMMAND ${THIS_TARGET} 83)
# Test invalid boolean compares
add_test(NAME TestInvalidBooleanCompares COMMAND ${THIS_TARGET} 84)
# Test invalid number compares
add_test(NAME TestInvalidNumberCompares COMMAND ${THIS_TARGET} 85)
# Test invalid string compares
add_test(NAME TestInvalidStringCompares COMMAND ${THIS_TARGET} 86)
# Test invalid blob compares
add_test(NAME TestInvalidBlobCompares COMMAND ${THIS_TARGET} 87)

set(THIS_TARGET nImOcontainerTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else(WIN32)
    set(VERS_RESOURCE "")
endif(WIN32)

configure_file(${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)

#add_library(nImOcommonTestSupport)

enable_testing()

add_executable(${THIS_TARGET}
               nImOcontainerTest.cpp
               ${VERS_RESOURCE})

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be
# processed once.
#target_link_libraries(${THIS_TARGET} nImOcommonTestSupport ${nImO_LINK_LIBRARIES})
target_link_libraries(${THIS_TARGET} ${nImO_LINK_LIBRARIES})

if(APPLE)
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                       libnImOcommon.dylib "@rpath/libnImOcommon.dylib" ${THIS_TARGET})

    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                       libodLogging.dylib "@rpath/libodLogging.dylib" ${THIS_TARGET})

endif(APPLE)

# Test empty array
add_test(NAME TestEmptyArrayValue COMMAND ${THIS_TARGET} 1)
# Test singular array
add_test(NAME TestSingularArrayValue COMMAND ${THIS_TARGET} 2)
# Test small array
add_test(NAME TestSmallArrayValue COMMAND ${THIS_TARGET} 3)
# Test big array
add_test(NAME TestBigArrayValue COMMAND ${THIS_TARGET} 4)

# Test empty map
add_test(NAME TestEmptyMapValue COMMAND ${THIS_TARGET} 20)
# Test singular map with boolean keys
add_test(NAME TestSingularBooleanMapValue COMMAND ${THIS_TARGET} 21)
# Test singular map with integer keys
add_test(NAME TestSingularIntegerMapValue COMMAND ${THIS_TARGET} 22)
# Test singular map with string keys
add_test(NAME TestSingularStringMapValue COMMAND ${THIS_TARGET} 23)
# Test small map with boolean keys
add_test(NAME TestSmallBooleanMapValue COMMAND ${THIS_TARGET} 24)
# Test small map with integer keys
add_test(NAME TestSmallIntegerMapValue COMMAND ${THIS_TARGET} 25)
# Test small map with string keys
add_test(NAME TestSmallStringMapValue COMMAND ${THIS_TARGET} 26)

# Test empty set
add_test(NAME TestEmptySetValue COMMAND ${THIS_TARGET} 40)
# Test singular set with boolean keys
add_test(NAME TestSingularBooleanSetValue COMMAND ${THIS_TARGET} 41)
# Test singular set with integer keys
add_test(NAME TestSingularIntegerSetValue COMMAND ${THIS_TARGET} 42)
# Test singular set with string keys
add_test(NAME TestSingularStringSetValue COMMAND ${THIS_TARGET} 43)
# Test small set with boolean keys
add_test(NAME TestSmallBooleanSetValue COMMAND ${THIS_TARGET} 44)
# Test small set with integer keys
add_test(NAME TestSmallIntegerSetValue COMMAND ${THIS_TARGET} 45)
# Test small set with string keys
add_test(NAME TestSmallStringSetValue COMMAND ${THIS_TARGET} 46)

# Test array with array
add_test(NAME TestArrayWithArrayValue COMMAND ${THIS_TARGET} 60)
# Test array with map
add_test(NAME TestArrayWithMapValue COMMAND ${THIS_TARGET} 61)
# Test array with set
add_test(NAME TestArrayWithSetValue COMMAND ${THIS_TARGET} 62)
# Test map with array
add_test(NAME TestMapWithArrayValue COMMAND ${THIS_TARGET} 63)
# Test map with map
add_test(NAME TestMapWithMapValue COMMAND ${THIS_TARGET} 64)
# Test map with set
add_test(NAME TestMapWithSetValue COMMAND ${THIS_TARGET} 65)

# Test boolean map with incompatible keys
add_test(NAME TestBooleanMapValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 80)
# Test integer map with incompatible keys
add_test(NAME TestIntegerMapValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 81)
# Test string map with incompatible keys
add_test(NAME TestStringMapValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 82)
# Test boolean set with incompatible keys
add_test(NAME TestBooleanSetValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 83)
# Test integer set with incompatible keys
add_test(NAME TestIntegerSetValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 84)
# Test string set with incompatible keys
add_test(NAME TestStringSetValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 85)

# Test valid array compares
add_test(NAME TestValidArrayCompares COMMAND ${THIS_TARGET} 100)
# Test valid boolean map compares
add_test(NAME TestValidBooleanMapCompares COMMAND ${THIS_TARGET} 101)
# Test valid integer map compares
add_test(NAME TestValidIntegerMapCompares COMMAND ${THIS_TARGET} 102)
# Test valid string map compares
add_test(NAME TestValidStringMapCompares COMMAND ${THIS_TARGET} 103)
# Test valid boolean set compares
add_test(NAME TestValidBooleanSetCompares COMMAND ${THIS_TARGET} 104)
# Test valid integer set compares
add_test(NAME TestValidIntegerSetCompares COMMAND ${THIS_TARGET} 105)
# Test valid string set compares
add_test(NAME TestValidStringSetCompares COMMAND ${THIS_TARGET} 106)
# Test invalid array compares
add_test(NAME TestInvalidArrayCompares COMMAND ${THIS_TARGET} 107)
# Test invalid boolean map compares
add_test(NAME TestInvalidBooleanMapCompares COMMAND ${THIS_TARGET} 108)
# Test invalid integer map compares
add_test(NAME TestInvalidIntegerMapCompares COMMAND ${THIS_TARGET} 109)
# Test invalid string map compares
add_test(NAME TestInvalidStringMapCompares COMMAND ${THIS_TARGET} 110)
# Test invalid boolean set compares
add_test(NAME TestInvalidBooleanSetCompares COMMAND ${THIS_TARGET} 111)
# Test invalid integer set compares
add_test(NAME TestInvalidIntegerSetCompares COMMAND ${THIS_TARGET} 112)
# Test invalid string set compares
add_test(NAME TestInvalidStringSetCompares COMMAND ${THIS_TARGET} 113)

# Test array indices
add_test(NAME TestArrayIndices COMMAND ${THIS_TARGET} 120)
# Test boolean map searches
add_test(NAME TestBooleanMapSearches COMMAND ${THIS_TARGET} 121)
# Test integer map searches
add_test(NAME TestIntegerMapSearches COMMAND ${THIS_TARGET} 122)
# Test string map searches
add_test(NAME TestStringMapSearches COMMAND ${THIS_TARGET} 123)
# Test boolean set searches
add_test(NAME TestBooleanSetSearches COMMAND ${THIS_TARGET} 124)
# Test integer set searches
add_test(NAME TestIntegerSetSearches COMMAND ${THIS_TARGET} 125)
# Test string set searches
add_test(NAME TestStringSetSearches COMMAND ${THIS_TARGET} 126)

set(THIS_TARGET nImOparserTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else(WIN32)
    set(VERS_RESOURCE "")
endif(WIN32)

configure_file(${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)

#add_library(nImOcommonTestSupport)

enable_testing()

add_executable(${THIS_TARGET}
               nImOparserTest.cpp
               ${VERS_RESOURCE})

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be
# processed once.
#target_link_libraries(${THIS_TARGET} nImOcommonTestSupport ${nImO_LINK_LIBRARIES})
target_link_libraries(${THIS_TARGET} ${nImO_LINK_LIBRARIES})

if(APPLE)
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                       libnImOcommon.dylib "@rpath/libnImOcommon.dylib" ${THIS_TARGET})

    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                       libodLogging.dylib "@rpath/libodLogging.dylib" ${THIS_TARGET})

endif(APPLE)

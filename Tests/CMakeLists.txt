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

set(THIS_TARGET nImOconvertersTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else()
    set(VERS_RESOURCE "")
endif()

configure_file(${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)

#add_library(nImOcommonTestSupport)

enable_testing()

add_executable(${THIS_TARGET}
               nImOconvertersTest.cpp
               ${VERS_RESOURCE})

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be
# processed once.
#target_link_libraries(${THIS_TARGET} nImOcommonTestSupport ${nImO_LINK_LIBRARIES})
target_link_libraries(${THIS_TARGET} ${nImO_LINK_LIBRARIES})

fix_dynamic_libs(${THIS_TARGET})

# Test integer size for value of 0
add_test(NAME TestIntegerSize0 COMMAND ${THIS_TARGET} 1 0 1)
# Test integer size for value of 1
add_test(NAME TestIntegerSize1 COMMAND ${THIS_TARGET} 1 1 1)
# Test integer size for value of -1
add_test(NAME TestIntegerSizeMinus1 COMMAND ${THIS_TARGET} 1 -1 1)
# Test integer size for value of 127
add_test(NAME TestIntegerSize127 COMMAND ${THIS_TARGET} 1 127 1)
# Test integer size for value of -128
add_test(NAME TestIntegerSizeMinus128 COMMAND ${THIS_TARGET} 1 -128 1)
# Test integer size for value of 240
add_test(NAME TestIntegerSize240 COMMAND ${THIS_TARGET} 1 240 2)
# Test integer size for value of -240
add_test(NAME TestIntegerSizeMinus240 COMMAND ${THIS_TARGET} 1 -240 2)
# Test integer size for value of 255
add_test(NAME TestIntegerSize255 COMMAND ${THIS_TARGET} 1 255 2)
# Test integer size for value of -255
add_test(NAME TestIntegerSizeMinus255 COMMAND ${THIS_TARGET} 1 -255 2)
# Test integer size for value of 1024
add_test(NAME TestIntegerSize1024 COMMAND ${THIS_TARGET} 1 1024 2)
# Test integer size for value of -1024
add_test(NAME TestIntegerSizeMinus1024 COMMAND ${THIS_TARGET} 1 -1024 2)
# Test integer size for value of 32767
add_test(NAME TestIntegerSize32767 COMMAND ${THIS_TARGET} 1 32767 2)
# Test integer size for value of -32768
add_test(NAME TestIntegerSizeMinus32768 COMMAND ${THIS_TARGET} 1 -32768 2)
# Test integer size for value of 48000
add_test(NAME TestIntegerSize48k COMMAND ${THIS_TARGET} 1 48000 3)
# Test integer size for value of -48000
add_test(NAME TestIntegerSizeMinus48k COMMAND ${THIS_TARGET} 1 -48000 3)
# Test integer size for value of 8000000
add_test(NAME TestIntegerSize8m COMMAND ${THIS_TARGET} 1 8000000 3)
# Test integer size for value of -8000000
add_test(NAME TestIntegerSizeMinus8m COMMAND ${THIS_TARGET} 1 -8000000 3)
# Test integer size for value of 16000000
add_test(NAME TestIntegerSize16m COMMAND ${THIS_TARGET} 1 16000000 4)
# Test integer size for value of -16000000
add_test(NAME TestIntegerSizeMinus16m COMMAND ${THIS_TARGET} 1 -16000000 4)
# Test integer size for value of 20000000
add_test(NAME TestIntegerSize20m COMMAND ${THIS_TARGET} 1 20000000 4)
# Test integer size for value of -20000000
add_test(NAME TestIntegerSizeMinus20m COMMAND ${THIS_TARGET} 1 -20000000 4)
# Test integer size for value of 2000000000
add_test(NAME TestIntegerSize2g COMMAND ${THIS_TARGET} 1 2000000000 4)
# Test integer size for value of -2000000000
add_test(NAME TestIntegerSizeMinus2g COMMAND ${THIS_TARGET} 1 -2000000000 4)
# Test integer size for value of 4000000000
add_test(NAME TestIntegerSize4g COMMAND ${THIS_TARGET} 1 4000000000 5)
# Test integer size for value of -4000000000
add_test(NAME TestIntegerSizeMinus4g COMMAND ${THIS_TARGET} 1 -4000000000 5)
# Test integer size for value of 8000000000
add_test(NAME TestIntegerSize8g COMMAND ${THIS_TARGET} 1 8000000000 5)
# Test integer size for value of -8000000000
add_test(NAME TestIntegerSizeMinus8g COMMAND ${THIS_TARGET} 1 -8000000000 5)
# Test integer size for value of 500000000000
add_test(NAME TestIntegerSize500g COMMAND ${THIS_TARGET} 1 500000000000 5)
# Test integer size for value of -500000000000
add_test(NAME TestIntegerSizeMinus500g COMMAND ${THIS_TARGET} 1 -500000000000 5)
# Test integer size for value of 2000000000000
add_test(NAME TestIntegerSize2t COMMAND ${THIS_TARGET} 1 2000000000000 6)
# Test integer size for value of -2000000000000
add_test(NAME TestIntegerSizeMinus2t COMMAND ${THIS_TARGET} 1 -2000000000000 6)
# Test integer size for value of 35000000000000
add_test(NAME TestIntegerSize35t COMMAND ${THIS_TARGET} 1 35000000000000 6)
# Test integer size for value of -35000000000000
add_test(NAME TestIntegerSizeMinus35t COMMAND ${THIS_TARGET} 1 -35000000000000 6)
# Test integer size for value of 280000000000000
add_test(NAME TestIntegerSize280t COMMAND ${THIS_TARGET} 1 280000000000000 7)
# Test integer size for value of -280000000000000
add_test(NAME TestIntegerSizeMinus280t COMMAND ${THIS_TARGET} 1 -280000000000000 7)
# Test integer size for value of 2200000000000000
add_test(NAME TestIntegerSize2200t COMMAND ${THIS_TARGET} 1 2200000000000000 7)
# Test integer size for value of -2200000000000000
add_test(NAME TestIntegerSizeMinus2200t COMMAND ${THIS_TARGET} 1 -2200000000000000 7)
# Test integer size for value of 4600000000000000000
add_test(NAME TestIntegerSize4600kt COMMAND ${THIS_TARGET} 1 4600000000000000000 8)
# Test integer size for value of -4600000000000000000
add_test(NAME TestIntegerSizeMinus4600kt COMMAND ${THIS_TARGET} 1 -4600000000000000000 8)
# Test floating point size
add_test(NAME TestFloatingPointSize COMMAND ${THIS_TARGET} 2)
# Test integer conversion for value of 0
add_test(NAME TestIntegerConversion0 COMMAND ${THIS_TARGET} 3 0)
# Test integer conversion for value of 1
add_test(NAME TestIntegerConversion1 COMMAND ${THIS_TARGET} 3 1)
# Test integer conversion for value of -1
add_test(NAME TestIntegerConversionMinus1 COMMAND ${THIS_TARGET} 3 -1)
# Test integer conversion for value of 127
add_test(NAME TestIntegerConversion127 COMMAND ${THIS_TARGET} 3 127)
# Test integer conversion for value of -128
add_test(NAME TestIntegerConversionMinus128 COMMAND ${THIS_TARGET} 3 -128)
# Test integer conversion for value of 240
add_test(NAME TestIntegerConversion240 COMMAND ${THIS_TARGET} 3 240)
# Test integer conversion for value of -240
add_test(NAME TestIntegerConversionMinus240 COMMAND ${THIS_TARGET} 3 -240)
# Test integer conversion for value of 255
add_test(NAME TestIntegerConversion255 COMMAND ${THIS_TARGET} 3 255)
# Test integer conversion for value of -255
add_test(NAME TestIntegerConversionMinus255 COMMAND ${THIS_TARGET} 3 -255)
# Test integer conversion for value of 1024
add_test(NAME TestIntegerConversion1024 COMMAND ${THIS_TARGET} 3 1024)
# Test integer conversion for value of -1024
add_test(NAME TestIntegerConversionMinus1024 COMMAND ${THIS_TARGET} 3 -1024)
# Test integer conversion for value of 32767
add_test(NAME TestIntegerConversion32767 COMMAND ${THIS_TARGET} 3 32767)
# Test integer conversion for value of -32768
add_test(NAME TestIntegerConversionMinus32768 COMMAND ${THIS_TARGET} 3 -32768)
# Test integer conversion for value of 48000
add_test(NAME TestIntegerConversion48k COMMAND ${THIS_TARGET} 3 48000)
# Test integer conversion for value of -48000
add_test(NAME TestIntegerConversionMinus48k COMMAND ${THIS_TARGET} 3 -48000)
# Test integer conversion for value of 8000000
add_test(NAME TestIntegerConversion8m COMMAND ${THIS_TARGET} 3 8000000)
# Test integer conversion for value of -8000000
add_test(NAME TestIntegerConversionMinus8m COMMAND ${THIS_TARGET} 3 -8000000)
# Test integer conversion for value of 16000000
add_test(NAME TestIntegerConversion16m COMMAND ${THIS_TARGET} 3 16000000)
# Test integer conversion for value of -16000000
add_test(NAME TestIntegerConversionMinus16m COMMAND ${THIS_TARGET} 3 -16000000)
# Test integer conversion for value of 20000000
add_test(NAME TestIntegerConversion20m COMMAND ${THIS_TARGET} 3 20000000)
# Test integer conversion for value of -20000000
add_test(NAME TestIntegerConversionMinus20m COMMAND ${THIS_TARGET} 3 -20000000)
# Test integer conversion for value of 2000000000
add_test(NAME TestIntegerConversion2g COMMAND ${THIS_TARGET} 3 2000000000)
# Test integer conversion for value of -2000000000
add_test(NAME TestIntegerConversionMinus2g COMMAND ${THIS_TARGET} 3 -2000000000)
# Test integer conversion for value of 4000000000
add_test(NAME TestIntegerConversion4g COMMAND ${THIS_TARGET} 3 4000000000)
# Test integer conversion for value of -4000000000
add_test(NAME TestIntegerConversionMinus4g COMMAND ${THIS_TARGET} 3 -4000000000)
# Test integer conversion for value of 8000000000
add_test(NAME TestIntegerConversion8g COMMAND ${THIS_TARGET} 3 8000000000)
# Test integer conversion for value of -8000000000
add_test(NAME TestIntegerConversionMinus8g COMMAND ${THIS_TARGET} 3 -8000000000)
# Test integer conversion for value of 500000000000
add_test(NAME TestIntegerConversion500g COMMAND ${THIS_TARGET} 3 500000000000)
# Test integer conversion for value of -500000000000
add_test(NAME TestIntegerConversionMinus500h COMMAND ${THIS_TARGET} 3 -500000000000)
# Test integer conversion for value of 2000000000000
add_test(NAME TestIntegerConversion2t COMMAND ${THIS_TARGET} 3 2000000000000)
# Test integer conversion for value of -2000000000000
add_test(NAME TestIntegerConversionMinus2t COMMAND ${THIS_TARGET} 3 -2000000000000)
# Test integer conversion for value of 35000000000000
add_test(NAME TestIntegerConversion35t COMMAND ${THIS_TARGET} 3 35000000000000)
# Test integer conversion for value of -35000000000000
add_test(NAME TestIntegerConversionMinus35t COMMAND ${THIS_TARGET} 3 -35000000000000)
# Test integer conversion for value of 280000000000000
add_test(NAME TestIntegerConversion280t COMMAND ${THIS_TARGET} 3 280000000000000)
# Test integer conversion for value of -280000000000000
add_test(NAME TestIntegerConversionMinus280t COMMAND ${THIS_TARGET} 3 -280000000000000)
# Test integer conversion for value of 2200000000000000
add_test(NAME TestIntegerConversion2200t COMMAND ${THIS_TARGET} 3 2200000000000000)
# Test integer conversion for value of -2200000000000000
add_test(NAME TestIntegerConversionMinus2200t COMMAND ${THIS_TARGET} 3 -2200000000000000)
# Test integer conversion for value of 4600000000000000000
add_test(NAME TestIntegerConversion4600kt COMMAND ${THIS_TARGET} 3 4600000000000000000)
# Test integer conversion for value of -4600000000000000000
add_test(NAME TestIntegerConversionMinus4600kt COMMAND ${THIS_TARGET} 3 -4600000000000000000)
# Test floating point conversion
add_test(NAME TestFloatingPointConversion COMMAND ${THIS_TARGET} 4)

set(THIS_TARGET nImOatomicTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else()
    set(VERS_RESOURCE "")
endif()

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

fix_dynamic_libs(${THIS_TARGET})

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
add_test(NAME TestStringBufferWithStringWithDblQuotes COMMAND ${THIS_TARGET} 14 "ab\"cde"
         "'ab\"cde'")
# Test string buffer with string with single quotes
add_test(NAME TestStringBufferWithStringWithSnglQuotes COMMAND ${THIS_TARGET} 14 "ab'cde"
         "\"ab'cde\"")
# Test string buffer with string with escaped characters
add_test(NAME TestStringBufferWithStringWithEscapedChars COMMAND ${THIS_TARGET} 15)
# Test string buffer with floating point zero
add_test(NAME TestStringBufferWithFloatingPointZero COMMAND ${THIS_TARGET} 16 "0.0" "0")
# Test string buffer with simple positive floating point
add_test(NAME TestStringBufferWithPositiveFloatingPoint COMMAND ${THIS_TARGET} 16 "1234.5"
         "1234.5")
# Test string buffer with simple negative floating point
add_test(NAME TestStringBufferWithNegativeFloatingPoint COMMAND ${THIS_TARGET} 16 "-1234.5"
         "-1234.5")
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

# Test default logical value
add_test(NAME TestDefaultLogicalValue COMMAND ${THIS_TARGET} 50)
# Test false logical value
add_test(NAME TestFalseLogicalValue COMMAND ${THIS_TARGET} 51 0 "false")
# Test true logical value
add_test(NAME TestTrueLogicalValue COMMAND ${THIS_TARGET} 51 1 "true")
# Test default number value
add_test(NAME TestDefaultIntegerValue COMMAND ${THIS_TARGET} 52)
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
# Test logical copy constructor and assignment operators
add_test(NAME TestLogicalCopyAndAssign COMMAND ${THIS_TARGET} 60)
# Test integer number copy constructor and assignment operators
add_test(NAME TestIntegerCopyAndAssign COMMAND ${THIS_TARGET} 61)
# Test floating point copy constructor and assignment operators
add_test(NAME TestFloatingPointCopyAndAssign COMMAND ${THIS_TARGET} 62)
# Test string copy constructor and assignment operators
add_test(NAME TestStringCopyAndAssign COMMAND ${THIS_TARGET} 63)
# Test blob copy constructor and assignment operator
add_test(NAME TestBlobCopyAndAssign COMMAND ${THIS_TARGET} 64)

# Test valid logical compares
add_test(NAME TestValidLogicalCompares COMMAND ${THIS_TARGET} 80)
# Test valid number compares
add_test(NAME TestValidNumberCompares COMMAND ${THIS_TARGET} 81)
# Test valid string compares
add_test(NAME TestValidStringCompares COMMAND ${THIS_TARGET} 82)
# Test valid blob compares
add_test(NAME TestValidBlobCompares COMMAND ${THIS_TARGET} 83)
# Test invalid logical compares
add_test(NAME TestInvalidLogicalCompares COMMAND ${THIS_TARGET} 84)
# Test invalid number compares
add_test(NAME TestInvalidNumberCompares COMMAND ${THIS_TARGET} 85)
# Test invalid string compares
add_test(NAME TestInvalidStringCompares COMMAND ${THIS_TARGET} 86)
# Test invalid blob compares
add_test(NAME TestInvalidBlobCompares COMMAND ${THIS_TARGET} 87)

set(THIS_TARGET nImOcontainerTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else()
    set(VERS_RESOURCE "")
endif()

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

fix_dynamic_libs(${THIS_TARGET})

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
# Test singular map with logical keys
add_test(NAME TestSingularLogicalMapValue COMMAND ${THIS_TARGET} 21)
# Test singular map with integer keys
add_test(NAME TestSingularIntegerMapValue COMMAND ${THIS_TARGET} 22)
# Test singular map with string keys
add_test(NAME TestSingularStringMapValue COMMAND ${THIS_TARGET} 23)
# Test small map with logical keys
add_test(NAME TestSmallLogicalMapValue COMMAND ${THIS_TARGET} 24)
# Test small map with integer keys
add_test(NAME TestSmallIntegerMapValue COMMAND ${THIS_TARGET} 25)
# Test small map with string keys
add_test(NAME TestSmallStringMapValue COMMAND ${THIS_TARGET} 26)

# Test empty set
add_test(NAME TestEmptySetValue COMMAND ${THIS_TARGET} 40)
# Test singular set with logical keys
add_test(NAME TestSingularLogicalSetValue COMMAND ${THIS_TARGET} 41)
# Test singular set with integer keys
add_test(NAME TestSingularIntegerSetValue COMMAND ${THIS_TARGET} 42)
# Test singular set with string keys
add_test(NAME TestSingularStringSetValue COMMAND ${THIS_TARGET} 43)
# Test small set with logical keys
add_test(NAME TestSmallLogicalSetValue COMMAND ${THIS_TARGET} 44)
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

# Test logical map with incompatible keys
add_test(NAME TestLogicalMapValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 80)
# Test integer map with incompatible keys
add_test(NAME TestIntegerMapValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 81)
# Test string map with incompatible keys
add_test(NAME TestStringMapValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 82)
# Test logical set with incompatible keys
add_test(NAME TestLogicalSetValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 83)
# Test integer set with incompatible keys
add_test(NAME TestIntegerSetValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 84)
# Test string set with incompatible keys
add_test(NAME TestStringSetValueWithIncompatibleKeys COMMAND ${THIS_TARGET} 85)

# Test valid array compares
add_test(NAME TestValidArrayCompares COMMAND ${THIS_TARGET} 100)
# Test valid logical map compares
add_test(NAME TestValidLogicalMapCompares COMMAND ${THIS_TARGET} 101)
# Test valid integer map compares
add_test(NAME TestValidIntegerMapCompares COMMAND ${THIS_TARGET} 102)
# Test valid string map compares
add_test(NAME TestValidStringMapCompares COMMAND ${THIS_TARGET} 103)
# Test valid logical set compares
add_test(NAME TestValidLogicalSetCompares COMMAND ${THIS_TARGET} 104)
# Test valid integer set compares
add_test(NAME TestValidIntegerSetCompares COMMAND ${THIS_TARGET} 105)
# Test valid string set compares
add_test(NAME TestValidStringSetCompares COMMAND ${THIS_TARGET} 106)
# Test invalid array compares
add_test(NAME TestInvalidArrayCompares COMMAND ${THIS_TARGET} 107)
# Test invalid logical map compares
add_test(NAME TestInvalidLogicalMapCompares COMMAND ${THIS_TARGET} 108)
# Test invalid integer map compares
add_test(NAME TestInvalidIntegerMapCompares COMMAND ${THIS_TARGET} 109)
# Test invalid string map compares
add_test(NAME TestInvalidStringMapCompares COMMAND ${THIS_TARGET} 110)
# Test invalid logical set compares
add_test(NAME TestInvalidLogicalSetCompares COMMAND ${THIS_TARGET} 111)
# Test invalid integer set compares
add_test(NAME TestInvalidIntegerSetCompares COMMAND ${THIS_TARGET} 112)
# Test invalid string set compares
add_test(NAME TestInvalidStringSetCompares COMMAND ${THIS_TARGET} 113)

# Test array indices
add_test(NAME TestArrayIndices COMMAND ${THIS_TARGET} 120)
# Test logical map searches
add_test(NAME TestLogicalMapSearches COMMAND ${THIS_TARGET} 121)
# Test integer map searches
add_test(NAME TestIntegerMapSearches COMMAND ${THIS_TARGET} 122)
# Test string map searches
add_test(NAME TestStringMapSearches COMMAND ${THIS_TARGET} 123)
# Test logical set searches
add_test(NAME TestLogicalSetSearches COMMAND ${THIS_TARGET} 124)
# Test integer set searches
add_test(NAME TestIntegerSetSearches COMMAND ${THIS_TARGET} 125)
# Test string set searches
add_test(NAME TestStringSetSearches COMMAND ${THIS_TARGET} 126)

set(THIS_TARGET nImOparserTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else()
    set(VERS_RESOURCE "")
endif()

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

fix_dynamic_libs(${THIS_TARGET})

# Test parse of logical false value
add_test(NAME TestLogicalFalseValue COMMAND ${THIS_TARGET} 1 t "false" "false")
# Test parse of logical true value
add_test(NAME TestLogicalTrueValue COMMAND ${THIS_TARGET} 1 t "true" "true")
# Test parse of abbreviated logical false value
add_test(NAME TestAbbreviatedLogicalFalseValue COMMAND ${THIS_TARGET} 1 t "fal" "false")
# Test parse of abbreviated logical true value
add_test(NAME TestAbbreviatedLogicalTrueValue COMMAND ${THIS_TARGET} 1 t "tru" "true")
# Test parse of minimal logical false value
add_test(NAME TestMinimalLogicalFalseValue COMMAND ${THIS_TARGET} 1 t "f" "false")
# Test parse of minimal logical true value
add_test(NAME TestMinimalLogicalTrueValue COMMAND ${THIS_TARGET} 1 t "t" "true")
# Test parse of invalid logical value
add_test(NAME TestInvalidLogicalValue COMMAND ${THIS_TARGET} 1 f "42" "")
# Test parse of invalid logical false value
add_test(NAME TestInvalidLogicalFalseValue COMMAND ${THIS_TARGET} 1 f "falze" "")
# Test parse of invalid logical true value
add_test(NAME TestInvalidLogicalTrueValue COMMAND ${THIS_TARGET} 1 f "trve" "")
# Test parse of whitespace and logical false value
add_test(NAME TestWhitespaceAndLogicalFalseValue COMMAND ${THIS_TARGET} 1 t "fa  " "false")
# Test parse of whitespace and logical true value
add_test(NAME TestWhitespaceAndLogicalTrueValue COMMAND ${THIS_TARGET} 1 t "tr  " "true")

# Test parse of number value
add_test(NAME TestNumberValue01 COMMAND ${THIS_TARGET} 2 t "0" "0")
# Test parse of number value
add_test(NAME TestNumberValue02 COMMAND ${THIS_TARGET} 2 t "1234" "1234")
# Test parse of number value
add_test(NAME TestNumberValue03 COMMAND ${THIS_TARGET} 2 t "1234.5" "1234.5")
# Test parse of number value
add_test(NAME TestNumberValue04 COMMAND ${THIS_TARGET} 2 t "-1234.5" "-1234.5")
# Test parse of number value
add_test(NAME TestNumberValue05 COMMAND ${THIS_TARGET} 2 t "-.5" "-0.5")
# Test parse of number value
add_test(NAME TestNumberValue06 COMMAND ${THIS_TARGET} 2 t ".5" "0.5")
# Test parse of number value
add_test(NAME TestNumberValue07 COMMAND ${THIS_TARGET} 2 t "+.5" "0.5")
# Test parse of number value
add_test(NAME TestNumberValue08 COMMAND ${THIS_TARGET} 2 t "0.5" "0.5")
# Test parse of number value
add_test(NAME TestNumberValue09 COMMAND ${THIS_TARGET} 2 t "1e2" "100")
# Test parse of number value
add_test(NAME TestNumberValue10 COMMAND ${THIS_TARGET} 2 t "1E+2" "100")
# Test parse of number value
add_test(NAME TestNumberValue11 COMMAND ${THIS_TARGET} 2 t "1e-2" "0.01")
# Test parse of number value
add_test(NAME TestNumberValue12 COMMAND ${THIS_TARGET} 2 t "-1e2" "-100")
# Test parse of number value
add_test(NAME TestNumberValue13 COMMAND ${THIS_TARGET} 2 t "-1e+2" "-100")
# Test parse of number value
add_test(NAME TestNumberValue14 COMMAND ${THIS_TARGET} 2 t "-1e-2" "-0.01")
# Test parse of number value
add_test(NAME TestNumberValue15 COMMAND ${THIS_TARGET} 2 t "+1e2" "100")
# Test parse of number value
add_test(NAME TestNumberValue16 COMMAND ${THIS_TARGET} 2 t "+1e+2" "100")
# Test parse of number value
add_test(NAME TestNumberValue17 COMMAND ${THIS_TARGET} 2 t "+1e-2" "0.01")
# Test parse of number value
add_test(NAME TestNumberValue18 COMMAND ${THIS_TARGET} 2 t "-.5e0" "-0.5")
# Test parse of number value
add_test(NAME TestNumberValue19 COMMAND ${THIS_TARGET} 2 t ".5e1" "5")
# Test parse of number value
add_test(NAME TestNumberValue20 COMMAND ${THIS_TARGET} 2 t "+.5e-001" "0.05")
# Test parse of number value
add_test(NAME TestNumberValue21 COMMAND ${THIS_TARGET} 2 t "0.5E3" "500")

# Test parse of invalid number value
add_test(NAME TestInvalidNumberValue01 COMMAND ${THIS_TARGET} 2 f "f" "")
# Test parse of invalid number value
add_test(NAME TestInvalidNumberValue02 COMMAND ${THIS_TARGET} 2 f "+-" "")
# Test parse of invalid number value
add_test(NAME TestInvalidNumberValue03 COMMAND ${THIS_TARGET} 2 f "+e" "")
# Test parse of invalid number value
add_test(NAME TestInvalidNumberValue04 COMMAND ${THIS_TARGET} 2 f "-e" "")
# Test parse of invalid number value
add_test(NAME TestInvalidNumberValue05 COMMAND ${THIS_TARGET} 2 f "1a" "")
# Test parse of invalid number value
add_test(NAME TestInvalidNumberValue06 COMMAND ${THIS_TARGET} 2 f "1.f" "")
# Test parse of invalid number value
add_test(NAME TestInvalidNumberValue07 COMMAND ${THIS_TARGET} 2 f "1ex" "")
# Test parse of invalid number value
add_test(NAME TestInvalidNumberValue08 COMMAND ${THIS_TARGET} 2 f "1e+-" "")
# Test parse of invalid number value
add_test(NAME TestInvalidNumberValue09 COMMAND ${THIS_TARGET} 2 f ".e" "")

# Test parse of string value
add_test(NAME TestStringValue01 COMMAND ${THIS_TARGET} 3 t "'abc'" "\"abc\"")
# Test parse of string value
add_test(NAME TestStringValue02 COMMAND ${THIS_TARGET} 3 t "\"abc\"" "\"abc\"")
# Test parse of string value
add_test(NAME TestStringValue03 COMMAND ${THIS_TARGET} 3 t "\"\"" "\"\"")
# Test parse of string value
add_test(NAME TestStringValue04 COMMAND ${THIS_TARGET} 3 t "''" "\"\"")
# Test parse of string value
add_test(NAME TestStringValue05 COMMAND ${THIS_TARGET} 3 t "\"\\\"\"" "'\"'")
# Test parse of string value
add_test(NAME TestStringValue06 COMMAND ${THIS_TARGET} 3 t "\"'\"" "\"'\"")
# Test parse of string value
add_test(NAME TestStringValue07 COMMAND ${THIS_TARGET} 3 t "\"@\\a\\b\\t\\n\\v\\f\\r\\s=\""
         "\"@\\a\\b\\t\\n\\v\\f\\r =\"")
# Test parse of string value
add_test(NAME TestStringValue08 COMMAND ${THIS_TARGET} 3 t
         "\"@\\007\\010\\011\\012\\013\\014\\015\\033\\040=\"" "\"@\\a\\b\\t\\n\\v\\f\\r\\e =\"")
# Test parse of string value
add_test(NAME TestStringValue09 COMMAND ${THIS_TARGET} 3 t
         "\"@\\C-g\\C-H\\C-i\\C-J\\C-k\\C-L\\C-m\\C-[=\"" "\"@\\a\\b\\t\\n\\v\\f\\r\\e=\"")
# Test parse of string value
add_test(NAME TestStringValue10 COMMAND ${THIS_TARGET} 3 t "\"@\\cg\\cH\\ci\\cJ\\ck\\cL\\cm\\c[=\""
         "\"@\\a\\b\\t\\n\\v\\f\\r\\e=\"")
# Test parse of string value
add_test(NAME TestStringValue11 COMMAND ${THIS_TARGET} 3 t "\"@\\M-!\\M-0\\M-A=\""
         "\"@\\M-!\\M-0\\M-A=\"")
# Test parse of string value
add_test(NAME TestStringValue12 COMMAND ${THIS_TARGET} 3 t "\"@\\241\\260\\301=\""
         "\"@\\M-!\\M-0\\M-A=\"")
# Test parse of string value
add_test(NAME TestStringValue13 COMMAND ${THIS_TARGET} 3 t
         "\"@\\M-\\C-@\\M-\\C-_\\200\\237\\377=\""
         "\"@\\M-\\C-@\\M-\\C-_\\M-\\C-@\\M-\\C-_\\377=\"")

# Test parse of string value
add_test(NAME TestInvalidStringValue01 COMMAND ${THIS_TARGET} 3 f "'abc" "")
# Test parse of string value
add_test(NAME TestInvalidStringValue02 COMMAND ${THIS_TARGET} 3 f "\"abc" "")
# Test parse of string value
add_test(NAME TestInvalidStringValue03 COMMAND ${THIS_TARGET} 3 f "\"" "")
# Test parse of string value
add_test(NAME TestInvalidStringValue04 COMMAND ${THIS_TARGET} 3 f "'" "")
# Test parse of string value
add_test(NAME TestInvalidStringValue05 COMMAND ${THIS_TARGET} 3 f "\"@\\x\\y\\z=\"" "")
# Test parse of string value
add_test(NAME TestInvalidStringValue06 COMMAND ${THIS_TARGET} 3 f "\"@\\008\\009=\"" "")
# Test parse of string value
add_test(NAME TestInvalidStringValue07 COMMAND ${THIS_TARGET} 3 f "\"@\\C-0\\C-1=\"" "")
# Test parse of string value
add_test(NAME TestInvalidStringValue08 COMMAND ${THIS_TARGET} 3 f "\"@\\c0\\c9=\"" "")
# Test parse of string value
add_test(NAME TestInvalidStringValue09 COMMAND ${THIS_TARGET} 3 f "\"@\\M-\\C-0\\M-\\C-9=\"" "")

# Test parse of array value
add_test(NAME TestArrayValue01 COMMAND ${THIS_TARGET} 4 t "( )" "( )")
# Test parse of array value
add_test(NAME TestArrayValue02 COMMAND ${THIS_TARGET} 4 t "()" "( )")
# Test parse of array value
add_test(NAME TestArrayValue03 COMMAND ${THIS_TARGET} 4 t "( 42 )" "( 42 )")
# Test parse of array value
add_test(NAME TestArrayValue04 COMMAND ${THIS_TARGET} 4 t "(42)" "( 42 )")
# Test parse of array value
add_test(NAME TestArrayValue05 COMMAND ${THIS_TARGET} 4 t "(t)" "( true )")
# Test parse of array value
add_test(NAME TestArrayValue06 COMMAND ${THIS_TARGET} 4 t "('abc')" "( \"abc\" )")
# Test parse of array value
add_test(NAME TestArrayValue07 COMMAND ${THIS_TARGET} 4 t "(42.25 fa)" "( 42.25 false )")
# Test parse of array value
add_test(NAME TestArrayValue08 COMMAND ${THIS_TARGET} 4 t "(fa 17)" "( false 17 )")
# Test parse of array value
add_test(NAME TestArrayValue09 COMMAND ${THIS_TARGET} 4 t "(12 'abc' t)"
         "( 12 \"abc\" true )")

# Test parse of array value
add_test(NAME TestInvalidArrayValue01 COMMAND ${THIS_TARGET} 4 f "(" "")
# Test parse of array value
add_test(NAME TestInvalidArrayValue02 COMMAND ${THIS_TARGET} 4 f "(]" "")
# Test parse of array value
add_test(NAME TestInvalidArrayValue03 COMMAND ${THIS_TARGET} 4 f "( 42 " "")
# Test parse of array value
add_test(NAME TestInvalidArrayValue04 COMMAND ${THIS_TARGET} 4 f "(12 'abc' t" "")
# Test parse of array value
add_test(NAME TestInvalidArrayValue05 COMMAND ${THIS_TARGET} 4 f "(12t)" "")
# Test parse of array value
add_test(NAME TestInvalidArrayValue06 COMMAND ${THIS_TARGET} 4 f "(t'abc')" "")
# Test parse of array value
add_test(NAME TestInvalidArrayValue07 COMMAND ${THIS_TARGET} 4 f "('abc'12)" "")

# Test parse of set value
add_test(NAME TestSetValue01 COMMAND ${THIS_TARGET} 5 t "[ ]" "[ ]")
# Test parse of set value
add_test(NAME TestSetValue02 COMMAND ${THIS_TARGET} 5 t "[]" "[ ]")
# Test parse of set value
add_test(NAME TestSetValue03 COMMAND ${THIS_TARGET} 5 t "[ 42 ]" "[ 42 ]")
# Test parse of set value
add_test(NAME TestSetValue04 COMMAND ${THIS_TARGET} 5 t "[42]" "[ 42 ]")
# Test parse of set value
add_test(NAME TestSetValue05 COMMAND ${THIS_TARGET} 5 t "[t]" "[ true ]")
# Test parse of set value
add_test(NAME TestSetValue06 COMMAND ${THIS_TARGET} 5 t "['abc']" "[ \"abc\" ]")

# Test parse of set value
add_test(NAME TestInvalidSetValue01 COMMAND ${THIS_TARGET} 5 f "[42.25]" "")
# Test parse of set value
add_test(NAME TestInvalidSetValue02 COMMAND ${THIS_TARGET} 5 f "[fa 17]" "")
# Test parse of set value
add_test(NAME TestInvalidSetValue03 COMMAND ${THIS_TARGET} 5 f "[12 13 'abc']" "")
# Test parse of set value
add_test(NAME TestInvalidSetValue04 COMMAND ${THIS_TARGET} 5 f "[" "")
# Test parse of set value
add_test(NAME TestInvalidSetValue05 COMMAND ${THIS_TARGET} 5 f "[)" "")
# Test parse of set value
add_test(NAME TestInvalidSetValue06 COMMAND ${THIS_TARGET} 5 f "[ 42 " "")

# Test parse of map value
add_test(NAME TestMapValue01 COMMAND ${THIS_TARGET} 6 t "{ }" "{ }")
# Test parse of map value
add_test(NAME TestMapValue02 COMMAND ${THIS_TARGET} 6 t "{}" "{ }")
# Test parse of map value
add_test(NAME TestMapValue03 COMMAND ${THIS_TARGET} 6 t "{ 42 > 12 }" "{ 42 > 12 }")
# Test parse of map value
add_test(NAME TestMapValue04 COMMAND ${THIS_TARGET} 6 t "{42>12}" "{ 42 > 12 }")
# Test parse of map value
add_test(NAME TestMapValue05 COMMAND ${THIS_TARGET} 6 t "{t>\"abc\"}" "{ true > \"abc\" }")
# Test parse of map value
add_test(NAME TestMapValue06 COMMAND ${THIS_TARGET} 6 t "{'abc'>12.5}" "{ \"abc\" > 12.5 }")
# Test parse of map value
add_test(NAME TestMapValue07 COMMAND ${THIS_TARGET} 6 t "{ 42 > [] }" "{ 42 > [ ] }")
# Test parse of map value
add_test(NAME TestMapValue08 COMMAND ${THIS_TARGET} 6 t "{ 42 > () }" "{ 42 > ( ) }")
# Test parse of map value
add_test(NAME TestMapValue09 COMMAND ${THIS_TARGET} 6 t "{ 42 > {} }" "{ 42 > { } }")

# Test parse of map value
add_test(NAME TestInvalidMapValue01 COMMAND ${THIS_TARGET} 6 f "{42.25}" "")
# Test parse of map value
add_test(NAME TestInvalidMapValue02 COMMAND ${THIS_TARGET} 6 f "{fa 17}" "")
# Test parse of map value
add_test(NAME TestInvalidMapValue03 COMMAND ${THIS_TARGET} 6 f "{12 13 'abc'}" "")
# Test parse of map value
add_test(NAME TestInvalidMapValue04 COMMAND ${THIS_TARGET} 6 f "{" "")
# Test parse of map value
add_test(NAME TestInvalidMapValue05 COMMAND ${THIS_TARGET} 6 f "{)" "")
# Test parse of map value
add_test(NAME TestInvalidMapValue06 COMMAND ${THIS_TARGET} 6 f "{ 42 " "")

# Test parse of implicit array
add_test(NAME TestImplicitArrayValue01 COMMAND ${THIS_TARGET} 7 t "1 2" "( 1 2 )")
# Test parse of implicit array
add_test(NAME TestImplicitArrayValue02 COMMAND ${THIS_TARGET} 7 t "1 t" "( 1 true )")
# Test parse of implicit array
add_test(NAME TestImplicitArrayValue03 COMMAND ${THIS_TARGET} 7 t "'abc' 2" "( \"abc\" 2 )")
# Test parse of implicit array
add_test(NAME TestImplicitArrayValue04 COMMAND ${THIS_TARGET} 7 t "(1 2) 3" "( ( 1 2 ) 3 )")

# Test parse of implicit array
add_test(NAME TestInvalidImplicitArrayValue01 COMMAND ${THIS_TARGET} 7 f "1 (" "")
# Test parse of implicit array
add_test(NAME TestInvalidImplicitArrayValue02 COMMAND ${THIS_TARGET} 7 f "1 tx" "")
# Test parse of implicit array
add_test(NAME TestInvalidImplicitArrayValue03 COMMAND ${THIS_TARGET} 7 f "'abc' 2f" "")
# Test parse of implicit array
add_test(NAME TestInvalidImplicitArrayValue04 COMMAND ${THIS_TARGET} 7 f "(1 2) {" "")

set(THIS_TARGET nImOmessageInsertTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else()
    set(VERS_RESOURCE "")
endif()

configure_file(${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)

#add_library(nImOcommonTestSupport)

enable_testing()

add_executable(${THIS_TARGET}
               nImOmessageInsertTest.cpp
               ${VERS_RESOURCE})

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be
# processed once.
#target_link_libraries(${THIS_TARGET} nImOcommonTestSupport ${nImO_LINK_LIBRARIES})
target_link_libraries(${THIS_TARGET} ${nImO_LINK_LIBRARIES})

fix_dynamic_libs(${THIS_TARGET})

# Test empty message
add_test(NAME TestInsertEmptyMessage COMMAND ${THIS_TARGET} 1)
# Test message with logical
add_test(NAME TestInsertLogicalMessage COMMAND ${THIS_TARGET} 2)
# Test message with tiny integer
add_test(NAME TestInsertTinyIntegerMessage COMMAND ${THIS_TARGET} 3)
# Test message with short integer 
add_test(NAME TestInsertShortIntegerMessage COMMAND ${THIS_TARGET} 4)
# Test message with medium integer
add_test(NAME TestInsertMediumIntegerMessage COMMAND ${THIS_TARGET} 5)
# Test message with big integer 
add_test(NAME TestInsertBigIntegerMessage COMMAND ${THIS_TARGET} 6)
# Test message with empty string
add_test(NAME TestInsertEmptyStringMessage COMMAND ${THIS_TARGET} 7)
# Test message with short string
add_test(NAME TestInsertShortStringMessage COMMAND ${THIS_TARGET} 8)
# Test message with medium string
add_test(NAME TestInsertMediumStringMessage COMMAND ${THIS_TARGET} 9)
# Test message with empty blob
add_test(NAME TestInsertEmptyBlobMessage COMMAND ${THIS_TARGET} 10)
# Test message with short blob
add_test(NAME TestInsertShortBlobMessage COMMAND ${THIS_TARGET} 11)
# Test message with medium blob
add_test(NAME TestInsertMediumBlobMessage COMMAND ${THIS_TARGET} 12)
# Test message with single float
add_test(NAME TestInsertSingleFloatMessage COMMAND ${THIS_TARGET} 13)
# Test message with multiple escapes
add_test(NAME TestInsertMultipleEscapesMessage COMMAND ${THIS_TARGET} 14)

# Test message with empty array
add_test(NAME TestInsertEmptyArrayMessage COMMAND ${THIS_TARGET} 100)
# Test message with empty map
add_test(NAME TestInsertEmptyMapMessage COMMAND ${THIS_TARGET} 101)
# Test message with empty set
add_test(NAME TestInsertEmptySetMessage COMMAND ${THIS_TARGET} 102)

# Test message with array with one logical
add_test(NAME TestInsertArrayWithOneLogicalMessage COMMAND ${THIS_TARGET} 110)
# Test message with array with one integer
add_test(NAME TestInsertArrayWithOneIntegerMessage COMMAND ${THIS_TARGET} 111)
# Test message with array with one double
add_test(NAME TestInsertArrayWithOneDoubleMessage COMMAND ${THIS_TARGET} 112)
# Test message with array with one string
add_test(NAME TestInsertArrayWithOneStringMessage COMMAND ${THIS_TARGET} 113)
# Test message with array with one blob
add_test(NAME TestInsertArrayWithOneBlobMessage COMMAND ${THIS_TARGET} 114)
# Test message with array with one empty array
add_test(NAME TestInsertArrayWithOneEmptyArrayMessage COMMAND ${THIS_TARGET} 115)
# Test message with array with one empty map
add_test(NAME TestInsertArrayWithOneEmptyMapMessage COMMAND ${THIS_TARGET} 116)
# Test message with array with one empty set
add_test(NAME TestInsertArrayWithOneEmptySetMessage COMMAND ${THIS_TARGET} 117)

# Test message with array with two logicals
add_test(NAME TestInsertArrayWithTwoLogicalsMessage COMMAND ${THIS_TARGET} 130)
# Test message with array with two integers
add_test(NAME TestInsertArrayWithTwoIntegersMessage COMMAND ${THIS_TARGET} 131)
# Test message with array with two doubles
add_test(NAME TestInsertArrayWithTwoDoublesMessage COMMAND ${THIS_TARGET} 132)
# Test message with array with two strings
add_test(NAME TestInsertArrayWithTwoStringsMessage COMMAND ${THIS_TARGET} 133)
# Test message with array with two blobs
add_test(NAME TestInsertArrayWithTwoBlobsMessage COMMAND ${THIS_TARGET} 134)
# Test message with array with two empty arrays
add_test(NAME TestInsertArrayWithTwoEmptyArraysMessage COMMAND ${THIS_TARGET} 135)
# Test message with array with two empty maps
add_test(NAME TestInsertArrayWithTwoEmptyMapsMessage COMMAND ${THIS_TARGET} 136)
# Test message with array with two empty sets
add_test(NAME TestInsertArrayWithTwoEmptySetsMessage COMMAND ${THIS_TARGET} 137)
# Test message with array with empty array and empty map
add_test(NAME TestInsertArrayWithEmptyArrayAndEmptyMapMessage COMMAND ${THIS_TARGET} 138)
# Test message with array with empty map and empty set
add_test(NAME TestInsertArrayWithEmptyMapAndEmptySetMessage COMMAND ${THIS_TARGET} 139)
# Test message with array with empty set and empty array
add_test(NAME TestInsertArrayWithEmptySetAndEmptyArrayMessage COMMAND ${THIS_TARGET} 140)
# Test message with array with many doubles
add_test(NAME TestInsertArrayWithManyDoublesMessage COMMAND ${THIS_TARGET} 141)

# Test message with logical map
add_test(NAME TestInsertLogicalMapMessage COMMAND ${THIS_TARGET} 160)
# Test message with integer map
add_test(NAME TestInsertIntegerMapMessage COMMAND ${THIS_TARGET} 161)
# Test message with string map
add_test(NAME TestInsertStringMapMessage COMMAND ${THIS_TARGET} 162)
# Test message with logical set
add_test(NAME TestInsertLogicalSetMessage COMMAND ${THIS_TARGET} 163)
# Test message with integer set
add_test(NAME TestInsertIntegerSetMessage COMMAND ${THIS_TARGET} 164)
# Test message with string set
add_test(NAME TestInsertStringSetMessage COMMAND ${THIS_TARGET} 165)

set(THIS_TARGET nImOmessageExtractTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else()
    set(VERS_RESOURCE "")
endif()

configure_file(${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)

#add_library(nImOcommonTestSupport)

enable_testing()

add_executable(${THIS_TARGET}
               nImOmessageExtractTest.cpp
               ${VERS_RESOURCE})

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be
# processed once.
#target_link_libraries(${THIS_TARGET} nImOcommonTestSupport ${nImO_LINK_LIBRARIES})
target_link_libraries(${THIS_TARGET} ${nImO_LINK_LIBRARIES})

fix_dynamic_libs(${THIS_TARGET})

# Test empty message
add_test(NAME TestExtractEmptyMessage COMMAND ${THIS_TARGET} 1)
# Test message with logical
add_test(NAME TestExtractLogicalMessage COMMAND ${THIS_TARGET} 2)
# Test message with tiny integer
add_test(NAME TestExtractTinyIntegerMessage COMMAND ${THIS_TARGET} 3)
# Test message with short integer 
add_test(NAME TestExtractShortIntegerMessage COMMAND ${THIS_TARGET} 4)
# Test message with medium integer
add_test(NAME TestExtractMediumIntegerMessage COMMAND ${THIS_TARGET} 5)
# Test message with big integer 
add_test(NAME TestExtractBigIntegerMessage COMMAND ${THIS_TARGET} 6)
# Test message with empty string
add_test(NAME TestExtractEmptyStringMessage COMMAND ${THIS_TARGET} 7)
# Test message with short string
add_test(NAME TestExtractShortStringMessage COMMAND ${THIS_TARGET} 8)
# Test message with medium string
add_test(NAME TestExtractMediumStringMessage COMMAND ${THIS_TARGET} 9)
# Test message with empty blob
add_test(NAME TestExtractEmptyBlobMessage COMMAND ${THIS_TARGET} 10)
# Test message with short blob
add_test(NAME TestExtractShortBlobMessage COMMAND ${THIS_TARGET} 11)
# Test message with medium blob
add_test(NAME TestExtractMediumBlobMessage COMMAND ${THIS_TARGET} 12)
# Test message with single float
add_test(NAME TestExtractSingleFloatMessage COMMAND ${THIS_TARGET} 13)

# Test message with empty array
add_test(NAME TestExtractEmptyArrayMessage COMMAND ${THIS_TARGET} 100)
# Test message with empty map
add_test(NAME TestExtractEmptyMapMessage COMMAND ${THIS_TARGET} 101)
# Test message with empty set
add_test(NAME TestExtractEmptySetMessage COMMAND ${THIS_TARGET} 102)

# Test message with array with one logical
add_test(NAME TestExtractArrayWithOneLogicalMessage COMMAND ${THIS_TARGET} 110)
# Test message with array with one integer
add_test(NAME TestExtractArrayWithOneIntegerMessage COMMAND ${THIS_TARGET} 111)
# Test message with array with one double
add_test(NAME TestExtractArrayWithOneDoubleMessage COMMAND ${THIS_TARGET} 112)
# Test message with array with one string
add_test(NAME TestExtractArrayWithOneStringMessage COMMAND ${THIS_TARGET} 113)
# Test message with array with one blob
add_test(NAME TestExtractArrayWithOneBlobMessage COMMAND ${THIS_TARGET} 114)
# Test message with array with one empty array
add_test(NAME TestExtractArrayWithOneEmptyArrayMessage COMMAND ${THIS_TARGET} 115)
# Test message with array with one empty map
add_test(NAME TestExtractArrayWithOneEmptyMapMessage COMMAND ${THIS_TARGET} 116)
# Test message with array with one empty set
add_test(NAME TestExtractArrayWithOneEmptySetMessage COMMAND ${THIS_TARGET} 117)

# Test message with array with two logicals
add_test(NAME TestExtractArrayWithTwoLogicalsMessage COMMAND ${THIS_TARGET} 130)
# Test message with array with two integers
add_test(NAME TestExtractArrayWithTwoIntegersMessage COMMAND ${THIS_TARGET} 131)
# Test message with array with two doubles
add_test(NAME TestExtractArrayWithTwoDoublesMessage COMMAND ${THIS_TARGET} 132)
# Test message with array with two strings
add_test(NAME TestExtractArrayWithTwoStringsMessage COMMAND ${THIS_TARGET} 133)
# Test message with array with two blobs
add_test(NAME TestExtractArrayWithTwoBlobsMessage COMMAND ${THIS_TARGET} 134)
# Test message with array with two empty arrays
add_test(NAME TestExtractArrayWithTwoEmptyArraysMessage COMMAND ${THIS_TARGET} 135)
# Test message with array with two empty maps
add_test(NAME TestExtractArrayWithTwoEmptyMapsMessage COMMAND ${THIS_TARGET} 136)
# Test message with array with two empty sets
add_test(NAME TestExtractArrayWithTwoEmptySetsMessage COMMAND ${THIS_TARGET} 137)
# Test message with array with empty array and empty map
add_test(NAME TestExtractArrayWithEmptyArrayAndEmptyMapMessage COMMAND ${THIS_TARGET} 138)
# Test message with array with empty map and empty set
add_test(NAME TestExtractArrayWithEmptyMapAndEmptySetMessage COMMAND ${THIS_TARGET} 139)
# Test message with array with empty set and empty array
add_test(NAME TestExtractArrayWithEmptySetAndEmptyArrayMessage COMMAND ${THIS_TARGET} 140)
# Test message with array with many doubles
add_test(NAME TestExtractArrayWithManyDoublesMessage COMMAND ${THIS_TARGET} 141)

# Test message with logical map
add_test(NAME TestExtractLogicalMapMessage COMMAND ${THIS_TARGET} 160)
# Test message with integer map
add_test(NAME TestExtractIntegerMapMessage COMMAND ${THIS_TARGET} 161)
# Test message with string map
add_test(NAME TestExtractStringMapMessage COMMAND ${THIS_TARGET} 162)
# Test message with logical set
add_test(NAME TestExtractLogicalSetMessage COMMAND ${THIS_TARGET} 163)
# Test message with integer set
add_test(NAME TestExtractIntegerSetMessage COMMAND ${THIS_TARGET} 164)
# Test message with string set
add_test(NAME TestExtractStringSetMessage COMMAND ${THIS_TARGET} 165)

set(THIS_TARGET nImObadMessageTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else()
    set(VERS_RESOURCE "")
endif()

configure_file(${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)

#add_library(nImOcommonTestSupport)

enable_testing()

add_executable(${THIS_TARGET}
               nImObadMessageTest.cpp
               ${VERS_RESOURCE})

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be
# processed once.
#target_link_libraries(${THIS_TARGET} nImOcommonTestSupport ${nImO_LINK_LIBRARIES})
target_link_libraries(${THIS_TARGET} ${nImO_LINK_LIBRARIES})

fix_dynamic_libs(${THIS_TARGET})

## Test message with initial end tag
add_test(NAME TestMessageInitialEndTag COMMAND ${THIS_TARGET} 1)
## Test message with terminal start tag
add_test(NAME TestMessageTerminalStartTag COMMAND ${THIS_TARGET} 2)
## Test empty message with content
add_test(NAME TestEmptyMessageWithContent COMMAND ${THIS_TARGET} 3)
## Test non-empty message without content
add_test(NAME TestNonEmptyMessageWithoutContent COMMAND ${THIS_TARGET} 4)
## Test non-empty message with mismatched initial start tag
add_test(NAME TestNonEmptyMessageWithMismatchedInitialStartTag COMMAND ${THIS_TARGET} 5)
## Test non-empty message with mismatched terminal end tag
add_test(NAME TestNonEmptyMessageWithMismatchedTerminalEndTag COMMAND ${THIS_TARGET} 6)
## Test message with invalid content tag
add_test(NAME TestNonEmptyMessageWithInvalidContentTag COMMAND ${THIS_TARGET} 7)
## Test message with bad float count
add_test(NAME TestNonEmptyMessageWithZeroFloatCount COMMAND ${THIS_TARGET} 8)
## Test message with string with bad length
add_test(NAME TestNonEmptyMessageWithStringWithInvalidLength COMMAND ${THIS_TARGET} 9)
## Test message with blob with invalid length
add_test(NAME TestNonEmptyMessageWithBlobWithInvalidLength COMMAND ${THIS_TARGET} 10)

## Test message with array with initial end tag
add_test(NAME TestNonEmptyMessageWithArrayWithInitialEndTag COMMAND ${THIS_TARGET} 20)
## Test message with array with terminal start tag
add_test(NAME TestNonEmptyMessageWithArrayWithTerminalStartTag COMMAND ${THIS_TARGET} 21)
## Test message with empty array with content
add_test(NAME TestNonEmptyMessageWithEmptyArrayWithContent COMMAND ${THIS_TARGET} 22)
## Test message with non-empty array without content
add_test(NAME TestNonEmptyMessageWithNonEmptyArrayWithoutContent COMMAND ${THIS_TARGET} 23)
## Test message with array with invalid count
add_test(NAME TestNonEmptyMessageWithNonEmptyArrayWithInvalidCount COMMAND ${THIS_TARGET} 24)
## Test message with array with too few values
add_test(NAME TestNonEmptyMessageWithNonEmptyArrayWithTooFewValues COMMAND ${THIS_TARGET} 25)
## Test message with array with too many values
add_test(NAME TestNonEmptyMessageWithNonEmptyArrayWithTooManyValues COMMAND ${THIS_TARGET} 26)
## Test message with array with too many float values
add_test(NAME TestNonEmptyMessageWithNonEmptyArrayWithTooManyFloats COMMAND ${THIS_TARGET} 27)

## Test message with map with initial end tag
add_test(NAME TestNonEmptyMessageWithMapWithInitialEndTag COMMAND ${THIS_TARGET} 40)
## Test message with map with terminal start tag
add_test(NAME TestNonEmptyMessageWithMapWithTerminalStartTag COMMAND ${THIS_TARGET} 41)
## Test message with empty map with content
add_test(NAME TestNonEmptyMessageWithEmptyMapWithContent COMMAND ${THIS_TARGET} 42)
## Test message with non-empty map without content
add_test(NAME TestNonEmptyMessageWithNonEmptyMapWithoutContent COMMAND ${THIS_TARGET} 43)
## Test message with map with invalid count
add_test(NAME TestNonEmptyMessageWithNonEmptyMapWithInvalidCount COMMAND ${THIS_TARGET} 44)
## Test message with map with too few values
add_test(NAME TestNonEmptyMessageWithNonEmptyMapWithTooFewValues COMMAND ${THIS_TARGET} 45)
## Test message with map with too many values
add_test(NAME TestNonEmptyMessageWithNonEmptyMapWithTooManyValues COMMAND ${THIS_TARGET} 46)
## Test message with map with odd number of values
add_test(NAME TestNonEmptyMessageWithNonEmptyMapWithIncompletePair COMMAND ${THIS_TARGET} 47)

## Test message with set with initial end tag
add_test(NAME TestNonEmptyMessageWithSetWithInitialEndTag COMMAND ${THIS_TARGET} 60)
## Test message with set with terminal start tag
add_test(NAME TestNonEmptyMessageWithSetWithTerminalStartTag COMMAND ${THIS_TARGET} 61)
## Test message with empty set with content
add_test(NAME TestNonEmptyMessageWithEmptySetWithContent COMMAND ${THIS_TARGET} 62)
## Test message with non-empty set without content
add_test(NAME TestNonEmptyMessageWithNonEmptySetWithoutContent COMMAND ${THIS_TARGET} 63)
## Test message with set with invalid count
add_test(NAME TestNonEmptyMessageWithNonEmptySetWithInvalidCount COMMAND ${THIS_TARGET} 64)
## Test message with set with too few values
add_test(NAME TestNonEmptyMessageWithNonEmptySetWithTooFewValues COMMAND ${THIS_TARGET} 65)
## Test message with set with too many values
add_test(NAME TestNonEmptyMessageWithNonEmptySetWithTooManyValues COMMAND ${THIS_TARGET} 66)

set(THIS_TARGET nImOzeroConfTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else()
    set(VERS_RESOURCE "")
endif()

configure_file(${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)

#add_library(nImOcommonTestSupport)

enable_testing()

add_executable(${THIS_TARGET}
               nImOzeroConfTest.cpp
               ${VERS_RESOURCE})

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be
# processed once.
#target_link_libraries(${THIS_TARGET} nImOcommonTestSupport ${nImO_LINK_LIBRARIES})
target_link_libraries(${THIS_TARGET} ${nImO_LINK_LIBRARIES})

fix_dynamic_libs(${THIS_TARGET})

## Test parse of logical false value
#add_test(NAME TestLogicalFalseValue COMMAND ${THIS_TARGET} 1 t "false" "false")
## Test parse of logical true value
#add_test(NAME TestLogicalTrueValue COMMAND ${THIS_TARGET} 1 t "true" "true")
## Test parse of abbreviated logical false value
#add_test(NAME TestAbbreviatedLogicalFalseValue COMMAND ${THIS_TARGET} 1 t "fal" "false")
## Test parse of abbreviated logical true value
#add_test(NAME TestAbbreviatedLogicalTrueValue COMMAND ${THIS_TARGET} 1 t "tru" "true")
## Test parse of minimal logical false value
#add_test(NAME TestMinimalLogicalFalseValue COMMAND ${THIS_TARGET} 1 t "f" "false")
## Test parse of minimal logical true value
#add_test(NAME TestMinimalLogicalTrueValue COMMAND ${THIS_TARGET} 1 t "t" "true")
## Test parse of invalid logical value
#add_test(NAME TestInvalidLogicalValue COMMAND ${THIS_TARGET} 1 f "42" "")
## Test parse of invalid logical false value
#add_test(NAME TestInvalidLogicalFalseValue COMMAND ${THIS_TARGET} 1 f "falze" "")
## Test parse of invalid logical true value
#add_test(NAME TestInvalidLogicalTrueValue COMMAND ${THIS_TARGET} 1 f "trve" "")
## Test parse of whitespace and logical false value
#add_test(NAME TestWhitespaceAndLogicalFalseValue COMMAND ${THIS_TARGET} 1 t "fa  " "false")
## Test parse of whitespace and logical true value
#add_test(NAME TestWhitespaceAndLogicalTrueValue COMMAND ${THIS_TARGET} 1 t "tr  " "true")
#
## Test parse of number value
#add_test(NAME TestNumberValue01 COMMAND ${THIS_TARGET} 2 t "0" "0")
## Test parse of number value
#add_test(NAME TestNumberValue02 COMMAND ${THIS_TARGET} 2 t "1234" "1234")
## Test parse of number value
#add_test(NAME TestNumberValue03 COMMAND ${THIS_TARGET} 2 t "1234.5" "1234.5")
## Test parse of number value
#add_test(NAME TestNumberValue04 COMMAND ${THIS_TARGET} 2 t "-1234.5" "-1234.5")
## Test parse of number value
#add_test(NAME TestNumberValue05 COMMAND ${THIS_TARGET} 2 t "-.5" "-0.5")
## Test parse of number value
#add_test(NAME TestNumberValue06 COMMAND ${THIS_TARGET} 2 t ".5" "0.5")
## Test parse of number value
#add_test(NAME TestNumberValue07 COMMAND ${THIS_TARGET} 2 t "+.5" "0.5")
## Test parse of number value
#add_test(NAME TestNumberValue08 COMMAND ${THIS_TARGET} 2 t "0.5" "0.5")
## Test parse of number value
#add_test(NAME TestNumberValue09 COMMAND ${THIS_TARGET} 2 t "1e2" "100")
## Test parse of number value
#add_test(NAME TestNumberValue10 COMMAND ${THIS_TARGET} 2 t "1E+2" "100")
## Test parse of number value
#add_test(NAME TestNumberValue11 COMMAND ${THIS_TARGET} 2 t "1e-2" "0.01")
## Test parse of number value
#add_test(NAME TestNumberValue12 COMMAND ${THIS_TARGET} 2 t "-1e2" "-100")
## Test parse of number value
#add_test(NAME TestNumberValue13 COMMAND ${THIS_TARGET} 2 t "-1e+2" "-100")
## Test parse of number value
#add_test(NAME TestNumberValue14 COMMAND ${THIS_TARGET} 2 t "-1e-2" "-0.01")
## Test parse of number value
#add_test(NAME TestNumberValue15 COMMAND ${THIS_TARGET} 2 t "+1e2" "100")
## Test parse of number value
#add_test(NAME TestNumberValue16 COMMAND ${THIS_TARGET} 2 t "+1e+2" "100")
## Test parse of number value
#add_test(NAME TestNumberValue17 COMMAND ${THIS_TARGET} 2 t "+1e-2" "0.01")
## Test parse of number value
#add_test(NAME TestNumberValue18 COMMAND ${THIS_TARGET} 2 t "-.5e0" "-0.5")
## Test parse of number value
#add_test(NAME TestNumberValue19 COMMAND ${THIS_TARGET} 2 t ".5e1" "5")
## Test parse of number value
#add_test(NAME TestNumberValue20 COMMAND ${THIS_TARGET} 2 t "+.5e-001" "0.05")
## Test parse of number value
#add_test(NAME TestNumberValue21 COMMAND ${THIS_TARGET} 2 t "0.5E3" "500")
#
## Test parse of invalid number value
#add_test(NAME TestInvalidNumberValue01 COMMAND ${THIS_TARGET} 2 f "f" "")
## Test parse of invalid number value
#add_test(NAME TestInvalidNumberValue02 COMMAND ${THIS_TARGET} 2 f "+-" "")
## Test parse of invalid number value
#add_test(NAME TestInvalidNumberValue03 COMMAND ${THIS_TARGET} 2 f "+e" "")
## Test parse of invalid number value
#add_test(NAME TestInvalidNumberValue04 COMMAND ${THIS_TARGET} 2 f "-e" "")
## Test parse of invalid number value
#add_test(NAME TestInvalidNumberValue05 COMMAND ${THIS_TARGET} 2 f "1a" "")
## Test parse of invalid number value
#add_test(NAME TestInvalidNumberValue06 COMMAND ${THIS_TARGET} 2 f "1.f" "")
## Test parse of invalid number value
#add_test(NAME TestInvalidNumberValue07 COMMAND ${THIS_TARGET} 2 f "1ex" "")
## Test parse of invalid number value
#add_test(NAME TestInvalidNumberValue08 COMMAND ${THIS_TARGET} 2 f "1e+-" "")
## Test parse of invalid number value
#add_test(NAME TestInvalidNumberValue09 COMMAND ${THIS_TARGET} 2 f ".e" "")
#
## Test parse of string value
#add_test(NAME TestStringValue01 COMMAND ${THIS_TARGET} 3 t "'abc'" "\"abc\"")
## Test parse of string value
#add_test(NAME TestStringValue02 COMMAND ${THIS_TARGET} 3 t "\"abc\"" "\"abc\"")
## Test parse of string value
#add_test(NAME TestStringValue03 COMMAND ${THIS_TARGET} 3 t "\"\"" "\"\"")
## Test parse of string value
#add_test(NAME TestStringValue04 COMMAND ${THIS_TARGET} 3 t "''" "\"\"")
## Test parse of string value
#add_test(NAME TestStringValue05 COMMAND ${THIS_TARGET} 3 t "\"\\\"\"" "'\"'")
## Test parse of string value
#add_test(NAME TestStringValue06 COMMAND ${THIS_TARGET} 3 t "\"'\"" "\"'\"")
## Test parse of string value
#add_test(NAME TestStringValue07 COMMAND ${THIS_TARGET} 3 t "\"@\\a\\b\\t\\n\\v\\f\\r\\e\\s=\""
#         "\"@\\a\\b\\t\\n\\v\\f\\r\\e =\"")
## Test parse of string value
#add_test(NAME TestStringValue08 COMMAND ${THIS_TARGET} 3 t
#         "\"@\\007\\010\\011\\012\\013\\014\\015\\033\\040=\"" "\"@\\a\\b\\t\\n\\v\\f\\r\\e =\"")
## Test parse of string value
#add_test(NAME TestStringValue09 COMMAND ${THIS_TARGET} 3 t
#         "\"@\\C-g\\C-H\\C-i\\C-J\\C-k\\C-L\\C-m\\C-[=\"" "\"@\\a\\b\\t\\n\\v\\f\\r\\e=\"")
## Test parse of string value
#add_test(NAME TestStringValue10 COMMAND ${THIS_TARGET} 3 t "\"@\\cg\\cH\\ci\\cJ\\ck\\cL\\cm\\c[=\""
#         "\"@\\a\\b\\t\\n\\v\\f\\r\\e=\"")
## Test parse of string value
#add_test(NAME TestStringValue11 COMMAND ${THIS_TARGET} 3 t "\"@\\M-!\\M-0\\M-A=\""
#         "\"@\\M-!\\M-0\\M-A=\"")
## Test parse of string value
#add_test(NAME TestStringValue12 COMMAND ${THIS_TARGET} 3 t "\"@\\241\\260\\301=\""
#         "\"@\\M-!\\M-0\\M-A=\"")
## Test parse of string value
#add_test(NAME TestStringValue13 COMMAND ${THIS_TARGET} 3 t "\"@\\M-\\C-@\\M-\\C-_\\200\\237\\377=\""
#         "\"@\\M-\\C-@\\M-\\C-_\\M-\\C-@\\M-\\C-_\\377=\"")
#
## Test parse of string value
#add_test(NAME TestInvalidStringValue01 COMMAND ${THIS_TARGET} 3 f "'abc" "")
## Test parse of string value
#add_test(NAME TestInvalidStringValue02 COMMAND ${THIS_TARGET} 3 f "\"abc" "")
## Test parse of string value
#add_test(NAME TestInvalidStringValue03 COMMAND ${THIS_TARGET} 3 f "\"" "")
## Test parse of string value
#add_test(NAME TestInvalidStringValue04 COMMAND ${THIS_TARGET} 3 f "'" "")
## Test parse of string value
#add_test(NAME TestInvalidStringValue05 COMMAND ${THIS_TARGET} 3 f "\"@\\x\\y\\z=\"" "")
## Test parse of string value
#add_test(NAME TestInvalidStringValue06 COMMAND ${THIS_TARGET} 3 f "\"@\\008\\009=\"" "")
## Test parse of string value
#add_test(NAME TestInvalidStringValue07 COMMAND ${THIS_TARGET} 3 f "\"@\\C-0\\C-1=\"" "")
## Test parse of string value
#add_test(NAME TestInvalidStringValue08 COMMAND ${THIS_TARGET} 3 f "\"@\\c0\\c9=\"" "")
## Test parse of string value
#add_test(NAME TestInvalidStringValue09 COMMAND ${THIS_TARGET} 3 f "\"@\\M-\\C-0\\M-\\C-9=\"" "")
#
## Test parse of array value
#add_test(NAME TestArrayValue01 COMMAND ${THIS_TARGET} 4 t "( )" "( )")
## Test parse of array value
#add_test(NAME TestArrayValue02 COMMAND ${THIS_TARGET} 4 t "()" "( )")
## Test parse of array value
#add_test(NAME TestArrayValue03 COMMAND ${THIS_TARGET} 4 t "( 42 )" "( 42 )")
## Test parse of array value
#add_test(NAME TestArrayValue04 COMMAND ${THIS_TARGET} 4 t "(42)" "( 42 )")
## Test parse of array value
#add_test(NAME TestArrayValue05 COMMAND ${THIS_TARGET} 4 t "(t)" "( true )")
## Test parse of array value
#add_test(NAME TestArrayValue06 COMMAND ${THIS_TARGET} 4 t "('abc')" "( \"abc\" )")
## Test parse of array value
#add_test(NAME TestArrayValue07 COMMAND ${THIS_TARGET} 4 t "(42.25 fa)" "( 42.25 false )")
## Test parse of array value
#add_test(NAME TestArrayValue08 COMMAND ${THIS_TARGET} 4 t "(fa 17)" "( false 17 )")
## Test parse of array value
#add_test(NAME TestArrayValue09 COMMAND ${THIS_TARGET} 4 t "(12 'abc' t)"
#         "( 12 \"abc\" true )")
#
## Test parse of array value
#add_test(NAME TestInvalidArrayValue01 COMMAND ${THIS_TARGET} 4 f "(" "")
## Test parse of array value
#add_test(NAME TestInvalidArrayValue02 COMMAND ${THIS_TARGET} 4 f "(]" "")
## Test parse of array value
#add_test(NAME TestInvalidArrayValue03 COMMAND ${THIS_TARGET} 4 f "( 42 " "")
## Test parse of array value
#add_test(NAME TestInvalidArrayValue04 COMMAND ${THIS_TARGET} 4 f "(12 'abc' t" "")
## Test parse of array value
#add_test(NAME TestInvalidArrayValue05 COMMAND ${THIS_TARGET} 4 f "(12t)" "")
## Test parse of array value
#add_test(NAME TestInvalidArrayValue06 COMMAND ${THIS_TARGET} 4 f "(t'abc')" "")
## Test parse of array value
#add_test(NAME TestInvalidArrayValue07 COMMAND ${THIS_TARGET} 4 f "('abc'12)" "")
#
## Test parse of set value
#add_test(NAME TestSetValue01 COMMAND ${THIS_TARGET} 5 t "[ ]" "[ ]")
## Test parse of set value
#add_test(NAME TestSetValue02 COMMAND ${THIS_TARGET} 5 t "[]" "[ ]")
## Test parse of set value
#add_test(NAME TestSetValue03 COMMAND ${THIS_TARGET} 5 t "[ 42 ]" "[ 42 ]")
## Test parse of set value
#add_test(NAME TestSetValue04 COMMAND ${THIS_TARGET} 5 t "[42]" "[ 42 ]")
## Test parse of set value
#add_test(NAME TestSetValue05 COMMAND ${THIS_TARGET} 5 t "[t]" "[ true ]")
## Test parse of set value
#add_test(NAME TestSetValue06 COMMAND ${THIS_TARGET} 5 t "['abc']" "[ \"abc\" ]")
#
## Test parse of set value
#add_test(NAME TestInvalidSetValue01 COMMAND ${THIS_TARGET} 5 f "[42.25]" "")
## Test parse of set value
#add_test(NAME TestInvalidSetValue02 COMMAND ${THIS_TARGET} 5 f "[fa 17]" "")
## Test parse of set value
#add_test(NAME TestInvalidSetValue03 COMMAND ${THIS_TARGET} 5 f "[12 13 'abc']" "")
## Test parse of set value
#add_test(NAME TestInvalidSetValue04 COMMAND ${THIS_TARGET} 5 f "[" "")
## Test parse of set value
#add_test(NAME TestInvalidSetValue05 COMMAND ${THIS_TARGET} 5 f "[)" "")
## Test parse of set value
#add_test(NAME TestInvalidSetValue06 COMMAND ${THIS_TARGET} 5 f "[ 42 " "")
#
## Test parse of map value
#add_test(NAME TestMapValue01 COMMAND ${THIS_TARGET} 6 t "{ }" "{ }")
## Test parse of map value
#add_test(NAME TestMapValue02 COMMAND ${THIS_TARGET} 6 t "{}" "{ }")
## Test parse of map value
#add_test(NAME TestMapValue03 COMMAND ${THIS_TARGET} 6 t "{ 42 > 12 }" "{ 42 > 12 }")
## Test parse of map value
#add_test(NAME TestMapValue04 COMMAND ${THIS_TARGET} 6 t "{42>12}" "{ 42 > 12 }")
## Test parse of map value
#add_test(NAME TestMapValue05 COMMAND ${THIS_TARGET} 6 t "{t>\"abc\"}" "{ true > \"abc\" }")
## Test parse of map value
#add_test(NAME TestMapValue06 COMMAND ${THIS_TARGET} 6 t "{'abc'>12.5}" "{ \"abc\" > 12.5 }")
## Test parse of map value
#add_test(NAME TestMapValue07 COMMAND ${THIS_TARGET} 6 t "{ 42 > [] }" "{ 42 > [ ] }")
## Test parse of map value
#add_test(NAME TestMapValue08 COMMAND ${THIS_TARGET} 6 t "{ 42 > () }" "{ 42 > ( ) }")
## Test parse of map value
#add_test(NAME TestMapValue09 COMMAND ${THIS_TARGET} 6 t "{ 42 > {} }" "{ 42 > { } }")
#
## Test parse of map value
#add_test(NAME TestInvalidMapValue01 COMMAND ${THIS_TARGET} 6 f "{42.25}" "")
## Test parse of map value
#add_test(NAME TestInvalidMapValue02 COMMAND ${THIS_TARGET} 6 f "{fa 17}" "")
## Test parse of map value
#add_test(NAME TestInvalidMapValue03 COMMAND ${THIS_TARGET} 6 f "{12 13 'abc'}" "")
## Test parse of map value
#add_test(NAME TestInvalidMapValue04 COMMAND ${THIS_TARGET} 6 f "{" "")
## Test parse of map value
#add_test(NAME TestInvalidMapValue05 COMMAND ${THIS_TARGET} 6 f "{)" "")
## Test parse of map value
#add_test(NAME TestInvalidMapValue06 COMMAND ${THIS_TARGET} 6 f "{ 42 " "")
#
## Test parse of implicit array
#add_test(NAME TestImplicitArrayValue01 COMMAND ${THIS_TARGET} 7 t "1 2" "( 1 2 )")
## Test parse of implicit array
#add_test(NAME TestImplicitArrayValue02 COMMAND ${THIS_TARGET} 7 t "1 t" "( 1 true )")
## Test parse of implicit array
#add_test(NAME TestImplicitArrayValue03 COMMAND ${THIS_TARGET} 7 t "'abc' 2" "( \"abc\" 2 )")
## Test parse of implicit array
#add_test(NAME TestImplicitArrayValue04 COMMAND ${THIS_TARGET} 7 t "(1 2) 3" "( ( 1 2 ) 3 )")
#
## Test parse of implicit array
#add_test(NAME TestInvalidImplicitArrayValue01 COMMAND ${THIS_TARGET} 7 f "1 (" "")
## Test parse of implicit array
#add_test(NAME TestInvalidImplicitArrayValue02 COMMAND ${THIS_TARGET} 7 f "1 tx" "")
## Test parse of implicit array
#add_test(NAME TestInvalidImplicitArrayValue03 COMMAND ${THIS_TARGET} 7 f "'abc' 2f" "")
## Test parse of implicit array
#add_test(NAME TestInvalidImplicitArrayValue04 COMMAND ${THIS_TARGET} 7 f "(1 2) {" "")

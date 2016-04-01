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

set(THIS_TARGET nImOcommonTest)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
else(WIN32)
    set(VERS_RESOURCE "")
endif(WIN32)

configure_file(${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)

#add_library(nImOcommonTestSupport)

enable_testing()

add_executable(${THIS_TARGET}
               nImOcommonTest.cpp
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
add_test(NAME TestEmptyStringBuffer COMMAND ${THIS_TARGET} 6)
# Test string buffer with no characters
add_test(NAME TestStringBufferWithNoCharacters COMMAND ${THIS_TARGET} 7 "" "")
# Test string buffer with single character
add_test(NAME TestStringBufferWithSingleCharacter COMMAND ${THIS_TARGET} 7 "a" "a")
# Test string buffer with multiple characters
add_test(NAME TestStringBufferWithMultipleCharacters COMMAND ${THIS_TARGET} 7 "abcde" "abcde")
# Test string buffer with false
add_test(NAME TestStringBufferWithFalse COMMAND ${THIS_TARGET} 8 0 false)
# Test string buffer with true
add_test(NAME TestStringBufferWithTrue COMMAND ${THIS_TARGET} 8 1 true)
# Test string buffer with integer zero
add_test(NAME TestStringBufferWithIntegerZero COMMAND ${THIS_TARGET} 9 0 0)
# Test string buffer with positive integer
add_test(NAME TestStringBufferWithPositiveInteger COMMAND ${THIS_TARGET} 9 12345 12345)
# Test string buffer with negative integer
add_test(NAME TestStringBufferWithNegativeInteger COMMAND ${THIS_TARGET} 9 "-12345" "-12345")
# Test string buffer with empty string
add_test(NAME TestStringBufferWithEmptyString COMMAND ${THIS_TARGET} 10 "" "\"\"")
# Test string buffer with simple string
add_test(NAME TestStringBufferWithSimpleString COMMAND ${THIS_TARGET} 10 abcde "\"abcde\"")
# Test string buffer with string with double quotes
add_test(NAME TestStringBufferWithStringWithDblQuotes COMMAND ${THIS_TARGET} 10 "ab\"cde" "'ab\"cde'")
# Test string buffer with string with single quotes
add_test(NAME TestStringBufferWithStringWithSnglQuotes COMMAND ${THIS_TARGET} 10 "ab'cde" "\"ab'cde\"")
# Test string buffer with string with escaped characters
add_test(NAME TestStringBufferWithStringWithEscapedChars COMMAND ${THIS_TARGET} 11)
# Test string buffer with floating point zero
add_test(NAME TestStringBufferWithFloatingPointZero COMMAND ${THIS_TARGET} 12 "0.0" "0")
# Test string buffer with simple positive floating point
add_test(NAME TestStringBufferWithPositiveFloatingPoint COMMAND ${THIS_TARGET} 12 "1234.5" "1234.5")
# Test string buffer with simple negative floating point
add_test(NAME TestStringBufferWithNegativeFloatingPoint COMMAND ${THIS_TARGET} 12 "-1234.5" "-1234.5")
# Test string buffer with very small floating point
add_test(NAME TestStringBufferWithVerySmallFloatingPoint COMMAND ${THIS_TARGET} 12 "1e-20" "1E-20")
# Test string buffer with very big floating point
add_test(NAME TestStringBufferWithVeryBigFloatingPoint COMMAND ${THIS_TARGET} 12 "1e22" "1E+22")
# Test big string buffer
add_test(NAME TestBigStringBuffer COMMAND ${THIS_TARGET} 13)
# Test string buffer with empty blob
add_test(NAME TestStringBufferWithEmptyBlob COMMAND ${THIS_TARGET} 14)
# Test string buffer with simple blob
add_test(NAME TestStringBufferWithSmallBlob COMMAND ${THIS_TARGET} 15)
# Test string buffer with big blob
add_test(NAME TestStringBufferWithBigBlob COMMAND ${THIS_TARGET} 16)
# Test string buffer reset
add_test(NAME TestStringBufferReset COMMAND ${THIS_TARGET} 17)


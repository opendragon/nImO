#--------------------------------------------------------------------------------------------------
#
#  File:       non-iOS/Tests/CMakeLists.txt
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

set(THIS_SOURCE_DIR ${nImO_SOURCE_DIR}/Tests)

include(Test_converters.txt)
include(Test_atomic.txt)
include(Test_container.txt)
include(Test_parser.txt)
include(Test_messageInsert.txt)
include(Test_messageExtract.txt)
include(Test_badMessage.txt)
include(Test_channel.txt)
include(Test_zeroConf.txt)
include(Test_argumentDescriptors.txt)

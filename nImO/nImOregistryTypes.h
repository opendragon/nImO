//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistryTypes.h
//
//  Project:    nImO
//
//  Contains:   The type declarations for nImO registries.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2023 by OpenDragon.
//
//              All rights reserved. Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following conditions are met:
//                * Redistributions of source code must retain the above copyright notice, this list
//                  of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright notice, this
//                  list of conditions and the following disclaimer in the documentation and / or
//                  other materials provided with the distribution.
//                * Neither the name of the copyright holders nor the names of its contributors may
//                  be used to endorse or promote products derived from this software without
//                  specific prior written permission.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//              ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//              DAMAGE.
//
//  Created:    2023-03-12
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOregistryTypes_H_))
# define nImOregistryTypes_H_ /* Header guard */

# include <nImOcommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The type declarations for %nImO registries. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief The kind of service being registered. */
    enum class ServiceType : uint8_t
    {
        /*! @brief A general servic with no special attributes.*/
        GenericService,

        /*! @brief A launcher service. */
        LauncherService,

        /*! @brief An I/O service that has both inputs and outputs. */
        FilterService,

        /*! @brief An I/O service that only has inputs. */
        InputService,

        /*! @brief An I/O service that only has outputs. */
        OutputService
    }; // ServiceType

    /*! @brief The data found in the Registry for a channel. */
    struct ChannelInfo
    {
        /*! @brief @c true if the data is valid. */
        bool    _found{false};

        /*! @brief The name of the node for the channel. */
        std::string _node{};

        /*! @brief The path of the channel on the node. */
        std::string _path{};

        /*! @brief @c true if the channel is for output from a service. */
        bool    _isOutput{false};

        /*! @brief The type of data carried by the channel. */
        std::string _dataType{};

        /*! @brief The allowed transport types for the channel. */
        TransportType   _modes{TransportType::kAny};

        /*! @brief @c true if the channel is connected to another channel. */
        bool    _inUse{false};

        /*! @brief The constructor. */
        inline ChannelInfo
            (void)
        {
        }

    }; // ChannelInfo

    /*! @brief The data found in the Registry for a connection. */
    struct ConnectionInfo
    {
        /*! @brief @c true if the data is valid. */
        bool    _found{false};

        /*! @brief The name of the input node for the channel. */
        std::string _fromNode{};

        /*! @brief The path of the input channel on the node. */
        std::string _fromPath{};

        /*! @brief The name of the output node for the channel. */
        std::string _toNode{};

        /*! @brief The path of the output channel on the node. */
        std::string _toPath{};

        /*! @brief The type of data carried by the channel. */
        std::string _dataType{};

        /*! @brief The allowed transport types for the channel. */
        TransportType   _mode{TransportType::kAny};

        /*! @brief The constructor. */
        inline ConnectionInfo
            (void)
        {
        }

    }; // ConnectionInfo

    /*! @brief The launch information for a node. */
    struct LaunchDetails
    {
        /*! @brief @c true if the data is valid. */
        bool    _found{false};

        /*! @brief The path to the executable for the node. */
        std::string _execPath{};

        /*! @brief The path to the directory where the executable for the node was launched. */
        std::string _launchDirectory{};

        /*! @brief The command line used to launch the executable for the node. */
        std::string _commandLine{};

        /*! @brief The constructor. */
        inline LaunchDetails
            (void)
        {
        }

    }; // LaunchDetails

    /*! @brief The data found in the Registry for a machine. */
    struct MachineInfo
    {
        /*! @brief @c true if the data is valid. */
        bool    _found{false};

        /*! @brief The name of the machine. */
        std::string _name{};

        /*! @brief The address of the machine. */
        uint32_t _address{0};

        /*! @brief The constructor. */
        inline MachineInfo
            (void)
        {
        }

    }; // MachineInfo

    /*! @brief The data found in the Registry for a node. */
    struct NodeInfo
    {
        /*! @brief @c true if the data is valid. */
        bool    _found{false};

        /*! @brief The command IP address and port that was found.*/
        Connection  _connection{};

        /*! @brief The name of the node. */
        std::string _name{};
        
        /*! @brief The nature of the service associated with the node. */
        ServiceType _serviceType{ServiceType::GenericService};

        /*! @brief The constructor. */
        inline NodeInfo
            (void)
        {
        }

    }; // NodeInfo

    /*! @brief Contains a sequence of ChannelInfo values. */
    typedef std::vector<ChannelInfo>    ChannelInfoVector;

    /*! @brief Contains a sequence of ConnectionInfo values. */
    typedef std::vector<ConnectionInfo> ConnectionInfoVector;

    /*! @brief Contains a sequence of MachineInfo values. */
    typedef std::vector<MachineInfo>    MachineInfoVector;

    /*! @brief Contains a sequence of NodeInfo values. */
    typedef std::vector<NodeInfo>   NodeInfoVector;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, ChannelInfo> ChannelInfoOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, ChannelInfoVector> ChannelInfoVectorOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, ConnectionInfo> ConnectionInfoOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, ConnectionInfoVector>   ConnectionInfoVectorOrFailure;

    /*! @brief Contains @c true and the result if there was no problem ans @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, LaunchDetails> LaunchDetailsOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, MachineInfo> MachineInfoOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, MachineInfoVector> MachineInfoVectorOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, NodeInfo> NodeInfoOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, NodeInfoVector> NodeInfoVectorOrFailure;

} // nImO

#endif // not defined(nImOregistryTypes_H_)

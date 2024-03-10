//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOchannelName.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the names of snImO channels.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2020 by OpenDragon.
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
//  Created:    2020-03-04
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOchannelName_H_))
# define nImOchannelName_H_ /* Header guard */

# include <BasicTypes/nImOstring.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO channels. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide network connection points. */
    class ChannelName final
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The constructor. */
            ChannelName
                (void) = default;

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            ChannelName
                (const ChannelName &  other);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            ChannelName
                (ChannelName &&	other)
                noexcept;

            /*! @brief Generate the path component of a ChannelName.
             @param[in] base The base name of the path, which can be blank.
             @param[in] forOutput @c true if this is an output channel and @c false otherwise.
             @param[in] numChannels The total number of channels for output (forOutput=true) or input (forOutput=false).
             @param[in] channelNumber The index for the channel (1-origin).
             @param[out] path The generated path.
             @return @c true if the base name was valid so that the path could be generated. */
            static bool
            generatePath
                (const std::string &    base,
                 const bool             forOutput,
                 const int64_t          numChannels,
                 const int64_t          channelNumber,
                 std::string &          path);

            /*! @brief Return the name in standard form.
             @return The name in standard form. */
            std::string
            getName
                (void)
                const;

            /*! @brief Return the name of the network for the channel.
             @return The network name for the channel. */
            inline const std::string &
            getNetwork
                (void)
                const
            {
                return _network;
            }

            /*! @brief Return the name of the node for the channel.
             @return The node name for the channel. */
            inline const std::string &
            getNode
                (void)
                const
            {
                return _node;
            }

            /*! @brief Return the path for the channel.
             @return The path for the channel. */
            inline const std::string &
            getPath
                (void)
                const
            {
                return _path;
            }

            /*! @brief Return the transport mechanism for the channel.
             @return The transport mechanism for the channel. */
            inline TransportType
            getTransport
                (void)
                const
            {
                return _transport;
            }

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            ChannelName &
            operator=
                (const ChannelName &  other);

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            ChannelName &
            operator=
                (ChannelName &&  other)
                noexcept;

            /*! @brief Extracts a ChannelName from a string.
             @param[in] input The string being processed.
             @param[out] problemDescription A description of the first problem with the input that was detected.
             @return @c nullptr if the ChannelName could not be extracted or a non-@c nullptr ChannelName if extraction was successful. */
            static SpChannelName
            parse
                (const std::string &    input,
                 std::string &          problemDescription);

            /*! @brief Exchanges the contents of the object with those of other.
             @param[in,out] other The object to be swapped with. */
            void
            swap
                (ChannelName &  other);

            /*! @brief Returns TransportType value corresponding to a name.
             @param[in] aName The name of the TransportType to be converted.
             @return The TransportType value corresponding to the name. */
            static TransportType
            transportFromName
                (const std::string &    aName);

            /*! @brief Returns the set of names for TransportType values.
             @return The standard names for the TransportType values. */
            static StdStringSet
            transportNames
                (void);

            /*! @brief Returns the name corresponding to a TransportType value.
             @param[in] aValue The TransportType value to be converted.
             @return The standard name for the TransportType value. */
            static std::string
            transportToName
                (const TransportType    aValue);

            /*! @brief Check if the provided string is a valid network name.
             @parm[in] input The string being checked.
             @return @c true if the string is in the correct format for a network name. */
            static bool
            validNetwork
                (const std::string &    input);

            /*! @brief Check if the provided string is a valid node name.
             @parm[in] input The string being checked.
             @return @c true if the string is in the correct format for a node name. */
            static bool
            validNode
                (const std::string &    input);

            /*! @brief Check if the provided string is a valid channel path.
             @parm[in] input The string being checked.
             @return @c true if the string is in the correct format for a channel path. */
            static bool
            validPath
                (const std::string &    input);

            /*! @brief Check if the provided string is a valid transport.
             @parm[in] input The string being checked.
             @return @c true if the string is in the correct format for a transport. */
            static bool
            validTransport
                (const std::string &    input);

        protected :
            // Protected methods.

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The associated network name. */
            std::string _network{};

            /*! @brief The associated node name. */
            std::string _node{};

            /*! @brief The associated path. */
            std::string _path{};

            /*! @brief The associated transport mechanism. */
            TransportType   _transport{TransportType::kUnknown};

    }; // ChannelName

    /*! @brief Checks a segment of a name for validity.
     @param[in] inString The string to be analyzed.
     @return @c true if the string is a valid name and @c false otherwise. */
    bool
    ValidNameSegment
        (const std::string &    inString);

    /*! @brief The standard name for any protocol. */
    extern const std::string    kProtocolAnyName;

    /*! @brief The standard name for the TCP protocol. */
    extern const std::string    kProtocolTcpName;

    /*! @brief The standard name for the UDP protocol. */
    extern const std::string    kProtocolUdpName;

    /*! @brief The standard name for an unknown protocol. */
    extern const std::string    kProtocolUnknownName;

} // nImO

#endif // not defined(nImOchannelName_H_)

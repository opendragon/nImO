//--------------------------------------------------------------------------------------------------
//
//  File:       nImOwatchThread.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for a thread to transfer information from nImO to a window.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2026 by OpenDragon.
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
//  Created:    2026-09-27
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOwatchThread_H_))
# define nImOwatchThread_H_ /* Header guard */

# include <nImOreceiveQueue.h>
# include <QDebug>
# include <QThread>
//# include <QAction>
//# include <QTextEdit>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a thread to transfer information from #nImO to a window. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The source of a message. */
    enum MessageSource
    {
        /*! @brief The message was from a log source. */
        kMessageFromLog = 1,
        /*! @brief The message was from a Registry search. */
        kMessageFromRegistrySearch,
        /*! @brief The message is a status report. */
        kMessageFromStatus
    };  // MessageSource

    /*! @brief A class to monitor the receive queue for the application. */
    class WatchThread final : public QThread
    {
        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = QThread;

            Q_OBJECT

        public :
            // Public methods.

            /*! @brief The constructor. */
            WatchThread
                (nImO::ReceiveQueue &   theQueue,
                 Ptr(QObject)           parent = nullptr);

            /*! @brief The destructor. */
            virtual ~WatchThread
                (void);

        signals:
            // Public signals.

            void
            addLine
                (QString    aLine);

        protected :
            // Protected methods.

            void
            run
                (void)
                override;

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.
        
            /*! @brief The sequence of received messages. */
            ReceiveQueue &  _receiveQueue;

    }; // WatchThread

    /*! @brief Set to @c true to cause the watch thread to terminate. */
    extern std::atomic_bool gWatchThreadStop;

} // nImO
#endif // not defined(nImOwatchThread_H_)

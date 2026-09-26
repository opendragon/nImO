//--------------------------------------------------------------------------------------------------
//
//  File:       nImOwatchWindow.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for a GUI window to continuously display information from nImO.
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
//  Created:    2026-09-26
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOwatchWindow_H_))
# define nImOwatchWindow_H_ /* Header guard */

# include <QMainWindow>
# include <QAction>
# include <QDebug>
# include <QTextEdit>

//# include <Contexts/nImOinputOutputContext.h>
//# include <nImOcallbackFunction.h>

//# if MAC_OR_LINUX_OR_BSD_
//#  pragma GCC diagnostic push
//#  pragma GCC diagnostic ignored "-Wunused-function"
//# endif // MAC_OR_LINUX_OR_BSD_
//# include <mdns.hpp>
//# if MAC_OR_LINUX_OR_BSD_
//#  pragma GCC diagnostic pop
//# endif // MAC_OR_LINUX_OR_BSD_

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a GUI window to continuously display information from #nImO. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide a GUI window for the application. */
    class WatchWindow : public QMainWindow
    {
        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = QMainWindow;

            Q_OBJECT
        public:
            // Public methods.

            /*! @brief The constructor.
             @param[in] parent The owning Widget.
             @param[in] flags The flags defining the behaviour of the window. */
            WatchWindow
                (QWidget *          parent = nullptr,
                 Qt::WindowFlags    flags = Qt::WindowFlags());

            /*! @brief Add a line to the text area.
             @param[in] aLine The text to be added. */
            void
            addText
                (QString    aLine);

            /*! @brief The destructor. */
            virtual ~WatchWindow
                (void);

            /*! @brief Check the state of the watch log flag.
             @return @c true if watching log messages is enabled. */
            bool
            isWatchLogChecked
                (void)
                const;

            /*! @brief Check the state of the watch Registry search flag.
             @return @c true if watching Registry search messages is enabled. */
            bool
            isWatchRegistrySearchChecked
                (void)
                const;

            /*! @brief Check the state of the watch status flag.
             @return @c true if watching status messages is enabled. */
            bool
            isWatchStatusChecked
                (void)
                const;

            /*! @brief Scroll the window to the last line added. */
            void
            scrollToLastLine
                (void);

        protected :
            // Protected methods.

        private :
            // Private methods.

            /*! @brief Set up the menus and actions for the window. */
            void
            createActions
                (void);

        private slots:
            // Private slots.

            /*! @brief Clear the text area. */
            void
            clearTextArea
                (void);
        
            /*! @brief Display information about the application. */
            void
            describe
                (void);

            /*! @brief Signal to stop watching messages. */
            void
            stopRunning
                (void);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The embedded text area. */
            QTextEdit * _textWidget{nullptr};

            /*! @brief The menu item that controls watching for log messages. */
            QAction *   _watchLogAction{nullptr};

            /*! @brief The menu item that controls watching for registry search messages. */
            QAction *   _watchRegistrySearchAction{nullptr};

            /*! @brief The menu item that controls watching for status messages. */
            QAction *   _watchStatusAction{nullptr};

    };  // WatchWindow

} // nImO

#endif // not defined(nImOwatchWindow_H_)

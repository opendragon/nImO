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

# include <nImOcommon.h>
# include <QMainWindow>
# include <QAction>
# include <QDebug>
# include <QRegularExpression>
# include <QTextEdit>

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
    // Forward declarations.
    class WatchFilterDialog;

    class WatchFilter final
    {
        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :

            // Private type definitions.

        public:
            // Public methods.

            /*! @brief The constructor.
             @param[in] parent The owning Widget.
             @param[in] flags The flags defining the behaviour of the window. */
            WatchFilter
                (void/*Ptr(QWidget)       parent = nullptr,
                 Qt::WindowFlags    flags = Qt::WindowFlags()*/);

            /*! @brief The destructor. */
            ~WatchFilter
                (void);

            /*! @brief Check if the filter is case-insensitive.
             @return @c true if the filter is case-insensitive. */
            inline bool
            isCaseInsensitive
                (void)
                const
            {
                return _caseInsensitive;
            }

            /*! @brief Check if the filter is enabled.
             @return @c true if the filter is enabled. */
            inline bool &
            isEnabled
                (void)
            {
                return _enabled;
            }

            /*! @brief Check if the filter is valid.
             @return @c true if the filter is valid. */
            inline bool &
            isValid
                (void)
            {
                return _valid;
            }

            /*! @brief Return the filter expression.
             @return The filter expression. */
            inline QString
            expression
                (void)
                const
            {
                return _expression;
            }

            /*! @brief Check if a string matches the filter expression.
             @param[in] inLine The string to check.
             @return @c true if the string matches the filter expression. */
            bool
            matches
                (QString    inLine);

            /*! @brief Set  the filter expression.
             @param[in] newExpression The filter expression.
             @param[in] caseInsensitive @c true if not case-sensitive. */
            void
            setExpression
                (QString    newExpression,
                 const bool caseInsensitive);

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

            /*! @brief @c true if the filter can be used.  */
            bool    _caseInsensitive;

            /*! @brief @c true if the filter can be used.  */
            bool    _enabled;

            /*! @brief The string version of the filter.  */
            QString _expression;

            /*! @brief The regular expression matching the provided string expression. */
            QRegularExpression  _pattern;

            /*! @brief @c true if the filter is useable.  */
            bool    _valid;

    };  // WatchFilter

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
                (Ptr(QWidget)       parent = nullptr,
                 Qt::WindowFlags    flags = Qt::WindowFlags());

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

            /*! @brief Add a line to the text area.
             @param[in] aLine The text to be added. */
            void
            addText
                (QString    aLine);

            /*! @brief Clear the text area. */
            void
            clearTextArea
                (void);
        
            /*! @brief Configure the 'exclude' filter. */
            void
            configureExcludeFilter
                (void);

            /*! @brief Configure the 'include' filter. */
            void
            configureIncludeFilter
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
            Ptr(QTextEdit)  _textWidget{nullptr};

            /*! @brief The menu item that specifies 'exclude' filtering.  */
            Ptr(QAction)    _watchExcludeAction{nullptr};

            /*! @brief The dialog to configure the 'exclude' filter. */
            Ptr(WatchFilterDialog)  _watchExcludeDialog{nullptr};

            /*! @brief The filter to handle explicit exclusion of text.  */
            Ptr(WatchFilter)    _watchExcludeFilter{nullptr};

            /*! @brief The menu item that specifies 'include' filtering.  */
            Ptr(QAction)    _watchIncludeAction{nullptr};

            /*! @brief The dialog to configure the 'include' filter. */
            Ptr(WatchFilterDialog)  _watchIncludeDialog{nullptr};

            /*! @brief The filter to handle explicit inclusion of text.  */
            Ptr(WatchFilter)    _watchIncludeFilter{nullptr};

            /*! @brief The menu item that controls watching for log messages.  */
            Ptr(QAction)    _watchLogAction{nullptr};

            /*! @brief The menu item that controls watching for registry search messages.  */
            Ptr(QAction)    _watchRegistrySearchAction{nullptr};

            /*! @brief The menu item that controls watching for status messages. */
            Ptr(QAction)    _watchStatusAction{nullptr};

    };  // WatchWindow

} // nImO

#endif // not defined(nImOwatchWindow_H_)

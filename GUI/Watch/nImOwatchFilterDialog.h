//--------------------------------------------------------------------------------------------------
//
//  File:       nImOWatchFilterDialog.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for a dialog window to set up a filter.
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
//  Created:    2026-10-30
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOWatchFilterDialog_H_))
# define nImOWatchFilterDialog_H_ /* Header guard */

# include "nImOwatchWindow.h"
# include <QCheckBox>
# include <QDebug>
# include <QDialog>
# include <QLineEdit>
# include <QPushButton>
# include <QTextEdit>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a dialog window to set up a filter. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to set up a filter. */
    class WatchFilterDialog final : public QDialog
    {
        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = QDialog;

            Q_OBJECT

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] theFilter The filter to be configured.
             @param[in] isExclude @c true if the dialog is for an 'exclude' filter.
             @param[in] parent The owning window. */
            WatchFilterDialog
                (WatchFilter &      theFilter,
                 const bool         isExclude,
                 Ptr(WatchWindow)   parent = nullptr);

            /*! @brief The destructor. */
            virtual ~WatchFilterDialog
                (void);

        signals:
            // Public signals.

        protected :
            // Protected methods.

            /*! @brief The event handler for show event.
             @param[in] event The event of interest. */
            virtual void
            showEvent
                (Ptr(QShowEvent)    event)
                override;

        private :
            // Private methods.

            /*! @brief Handle the editingFinished signal from the filterText field. */
            void
            filterEditingFinished
                (void);

            /*! @brief Handle the clicked signal from the finishButton field. */
            void
            updateFilter
                (void);

            /*! @brief Check if the fields are all valid.
             @return @c true if the fields are all valid. */
            bool
            validate
                (void);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief Revert any changes when pressed. */
            Ptr(QPushButton)    _cancelButton;

            /*! @brief The resulting filter will be case-insensitive. */
            Ptr(QCheckBox)  _caseInsensitiveCheckBox;

            /*! @brief Allows the filter to be used when selected. */
            Ptr(QCheckBox)  _enableCheckBox;

            /*! @brief The filter to be configured. */
            WatchFilter &   _filter;

            /*! @brief The expression for the filter. */
            Ptr(QLineEdit)  _filterText;

            /*! @brief Save changes when pressed. */
            Ptr(QPushButton)    _finishButton;

            /*! @brief @c true if an 'exclude' filter is being configured. */
            bool    _isExclude;

            /*! @brief A direct reference to the parent window. */
            Ptr(WatchWindow)    _owner;

            /*! @brief The status of the filter. */
            Ptr(QTextEdit)  _statusText;

    }; // WatchFilterDialog

} // nImO
#endif /* nImOWatchFilterDialog_H_ */

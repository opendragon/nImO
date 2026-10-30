//--------------------------------------------------------------------------------------------------
//
//  File:       nImOWatchFilterDialog.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for a dialog window to set up a filter.
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

#include "nImOwatchFilterDialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a dialog window to set up a filter. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::WatchFilterDialog::WatchFilterDialog
    (WatchFilter &      theFilter,
     const bool         isExclude,
     Ptr(WatchWindow)   parent) :
        inherited{parent}, _cancelButton{new QPushButton{this}}, _caseInsensitiveCheckBox{new QCheckBox{this}},
        _enableCheckBox{new QCheckBox{this}}, _filter{theFilter}, _filterText{new QLineEdit{this}},
        _finishButton{new QPushButton{this}}, _isExclude{isExclude}, _owner{parent}, _statusText{new QTextEdit{this}}
{
    ODL_ENTER(); //####
    ODL_P1(parent); //####
    auto    vBoxLayout{new QVBoxLayout{this}};
    auto    topHBoxLayout{new QHBoxLayout{this}};
    auto    middleHBoxLayout{new QHBoxLayout{this}};
    auto    statusHBoxLayout{new QHBoxLayout{this}};
    auto    bottomHBoxLayout{new QHBoxLayout{this}};
    auto    topLeftLabel{new QLabel{this}};

    _finishButton->setText(tr("Finish"));
    _cancelButton->setText(tr("Cancel"));
    topLeftLabel->setText(tr("Filter Expression:"));
    _enableCheckBox->setText(tr("Enabled"));
    _caseInsensitiveCheckBox->setText(tr("Case Insensitive"));
    _statusText->setText(tr("Ok so far"));
    _statusText->setReadOnly(true);
    _filterText->setFixedWidth(400);
    topHBoxLayout->addWidget(topLeftLabel);
    topHBoxLayout->addWidget(_filterText);
    middleHBoxLayout->addWidget(_enableCheckBox);
    middleHBoxLayout->addStretch();
    middleHBoxLayout->addWidget(_caseInsensitiveCheckBox);
    bottomHBoxLayout->addWidget(_finishButton, 0);
    bottomHBoxLayout->addStretch();
    bottomHBoxLayout->addWidget(_cancelButton, 0);
    statusHBoxLayout->addWidget(_statusText, 1);
    vBoxLayout->addLayout(topHBoxLayout);
    vBoxLayout->addLayout(middleHBoxLayout);
    vBoxLayout->addLayout(statusHBoxLayout);
    vBoxLayout->addLayout(bottomHBoxLayout);
    setLayout(vBoxLayout);
    if (_isExclude)
    {
        setWindowTitle(tr("Set Up The Exclude Filter"));
    }
    else
    {
        setWindowTitle(tr("Set Up The Include Filter"));
    }
    connect(_filterText, &QLineEdit::editingFinished, this, &WatchFilterDialog::filterEditingFinished);
    connect(_cancelButton, &QPushButton::clicked, this, &QDialog::close);
    connect(_finishButton, &QPushButton::clicked, this, &WatchFilterDialog::updateFilter);
    setMaximumHeight(230);
    setMaximumWidth(550);
    setMinimumHeight(230);
    setMinimumWidth(550);
    ODL_EXIT_P(this); //####
}   // nImO::WatchFilterDialog::WatchFilterDialog

nImO::WatchFilterDialog::~WatchFilterDialog
    (void)
{
    ODL_ENTER(); //####
    ODL_EXIT(); //####
}   // nImO::WatchFilterDialog::~WatchFilterDialog

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::WatchFilterDialog::filterEditingFinished
    (void)
{
    ODL_ENTER(); //####
    _finishButton->setEnabled(validate());
    ODL_EXIT(); //####
}   // nImO::WatchFilterDialog::filterEditingFinished

void
nImO::WatchFilterDialog::showEvent
    (Ptr(QShowEvent)    event)
{
    ODL_ENTER(); //####
    inherited::showEvent(event);
    _enableCheckBox->setCheckState(_filter.isEnabled() ? Qt::Checked : Qt::Unchecked);
    _caseInsensitiveCheckBox->setCheckState(_filter.isCaseInsensitive() ? Qt::Checked : Qt::Unchecked);
    _filterText->setText(_filter.expression());
    _finishButton->setEnabled(validate());
    ODL_EXIT(); //####
}   // nImO::WatchFilterDialog::showEvent

void
nImO::WatchFilterDialog::updateFilter
    (void)
{
    ODL_ENTER(); //####
    _filter.setExpression(_filterText->text(), _caseInsensitiveCheckBox->isChecked());
    _filter.isEnabled() = _enableCheckBox->isChecked();
    _filter.isValid() = true;
    close();
    ODL_EXIT(); //####
}   // nImO::WatchFilterDialog::updateFilter

bool
nImO::WatchFilterDialog::validate
    (void)
{
    ODL_ENTER(); //####
    bool    okSoFar{! _filterText->text().isEmpty()};

    if (okSoFar)
    {
        QRegularExpression  textExpression{_filterText->text()};

        if (_caseInsensitiveCheckBox->isChecked())
        {
            textExpression.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
        }
        if (textExpression.isValid())
        {
            _statusText->setText(tr("The filter expression is valid."));
        }
        else
        {
            _statusText->setText("Filter expression problem: " + textExpression.errorString());
            okSoFar = false;
        }
    }
    else
    {
        _statusText->setText(tr("The filter expression is empty."));
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
}   // nImO::WatchFilterDialog::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

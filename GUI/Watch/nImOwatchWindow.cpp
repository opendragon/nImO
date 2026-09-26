//--------------------------------------------------------------------------------------------------
//
//  File:       nImOwatchWindow.h
//
//  Project:    nImO
//
//  Contains:   The class definition for a GUI window to continuously display information from nImO.
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

#include "nImOwatchWindow.h"

#include <nImOmainSupport.h>

#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QScreen>
#include <QScrollBar>
#include <QToolBar>
#include <QToolButton>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a callback function for adding input channels. */
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

nImO::WatchWindow::WatchWindow
    (QWidget *          parent,
     Qt::WindowFlags    flags) :
        inherited{parent, flags}, _textWidget{new QTextEdit(this)}
{
    ODL_ENTER(); //####
    setWindowTitle(QApplication::applicationDisplayName());
    auto    screen{QGuiApplication::primaryScreen()->availableGeometry()};
    auto    height{screen.height()};
    auto    width{screen.width()};

    setGeometry(width / 4, height / 4, width / 2, height / 2);
    _textWidget->setLineWrapMode(QTextEdit::NoWrap);
    _textWidget->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    setCentralWidget(_textWidget);
    createActions();
    ODL_EXIT_P(this); //####
}   // nImO::WatchWindow::WatchWindow

nImO::WatchWindow::~WatchWindow
    (void)
{
    ODL_ENTER(); //####
    stopRunning();
    ODL_EXIT(); //####
}   // nImO::WatchWindow::~WatchWindow

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::WatchWindow::addText
    (QString    aLine)
{
    ODL_ENTER(); //####
    _textWidget->append(aLine);
    ODL_EXIT(); //####
}   // nImO::WatchWindow::addText

void
nImO::WatchWindow::clearTextArea
    (void)
{
    ODL_ENTER(); //####
    _textWidget->clear();
    ODL_EXIT(); //####
}   // nImO::WatchWindow::clearTextArea

void
nImO::WatchWindow::createActions
    (void)
{
    ODL_ENTER(); //####
    auto    aboutAction{new QAction(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout), tr("&About"), this)};

    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, &QAction::triggered, this, &WatchWindow::describe);
    auto    clearTextAction{new QAction(tr("Clear Text Area"), this)};

    connect(clearTextAction, &QAction::triggered, this, &WatchWindow::clearTextArea);
    auto    exitAction{new QAction(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit), tr("E&xit"), this)};

    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, &QAction::triggered, this, &WatchWindow::stopRunning);//&QWidget::close);
    _watchLogAction = new QAction(tr("Watch for log messages"), this);
    _watchLogAction->setCheckable(true);
    _watchLogAction->setChecked(true);
    _watchRegistrySearchAction = new QAction(tr("Watch for Registry search messages"));
    _watchRegistrySearchAction->setCheckable(true);
    _watchStatusAction = new QAction(tr("Watch for status messages"), this);
    _watchStatusAction->setCheckable(true);
    auto    optionsMenu{menuBar()->addMenu(tr("&Options"))};
    auto    viewMenu{menuBar()->addMenu(tr("&View"))};

    optionsMenu->addAction(_watchLogAction);
    optionsMenu->addAction(_watchRegistrySearchAction);
    optionsMenu->addAction(_watchStatusAction);
    viewMenu->addAction(aboutAction);
    viewMenu->addAction(clearTextAction);
    viewMenu->addAction(exitAction); // This connects the action to the main menu!
    ODL_EXIT(); //####
}   // nImO::WatchWindow::createActions

void
nImO::WatchWindow::describe
    (void)
{
    ODL_ENTER(); //####
    QMessageBox     msgBox(this);

    msgBox.setText(QApplication::applicationDisplayName());
    msgBox.setInformativeText(tr("An application to explore GUI features for nImO."));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    ODL_EXIT(); //####
}   // nImO::WatchWindow::describe

bool
nImO::WatchWindow::isWatchLogChecked
    (void)
    const
{
    ODL_ENTER(); //####
    auto    result{(nullptr != _watchLogAction) && _watchLogAction->isChecked()};

    ODL_EXIT_B(result); //####
    return result;
}   // nImO::WatchWindow::isWatchLogChecked

bool
nImO::WatchWindow::isWatchRegistrySearchChecked
    (void)
    const
{
    ODL_ENTER(); //####
    auto    result{(nullptr != _watchRegistrySearchAction) && _watchRegistrySearchAction->isChecked()};

    ODL_EXIT_B(result); //####
    return result;
}   // nImO::WatchWindow::isWatchRegistrySearchChecked

bool
nImO::WatchWindow::isWatchStatusChecked
    (void)
    const
{
    ODL_ENTER(); //####
    auto    result{(nullptr != _watchStatusAction) && _watchStatusAction->isChecked()};

    ODL_EXIT_B(result); //####
    return result;
}   // nImO::WatchWindow::isWatchStatusChecked

void
nImO::WatchWindow::scrollToLastLine
 (void)
{
    ODL_ENTER(); //####
    auto    horiz{_textWidget->horizontalScrollBar()};
    auto    vert{_textWidget->verticalScrollBar()};

    horiz->setValue(horiz->minimum());
    vert->setValue(vert->maximum());
    ODL_EXIT(); //####
}   // nImO::WatchWindow::scrollToLastLine

void
nImO::WatchWindow::stopRunning
    (void)
{
    ODL_ENTER(); //####
    if (nImO::gKeepRunning)
    {
        nImO::gKeepRunning = false;
        close();
    }
    ODL_EXIT(); //####
}   // nImO::WatchWindow:::stopRunning

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

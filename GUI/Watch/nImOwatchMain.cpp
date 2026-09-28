//--------------------------------------------------------------------------------------------------
//
//  File:       nImOwatchMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to display information about nImO.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-04-12
//
//--------------------------------------------------------------------------------------------------

#include "nImOwatchThread.h"
#include "nImOwatchWindow.h"

//#include <BasicTypes/nImOinteger.h>
//#include <BasicTypes/nImOstring.h>
//#include <Containers/nImOstringBuffer.h>
//#include <Containers/nImOarray.h>
//#include <Containers/nImOmap.h>
#include <Contexts/nImOsearchContext.h>
#include <nImOcallbackFunction.h>
#include <nImOmainSupport.h>
#include <nImOreceiveFromMulticast.h>
#include <nImOstandardOptions.h>
#include <QApplication>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A GUI application to display information about #nImO. */

/*! @dir Watch
 @brief The set of files that implement the Watch application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The sequence of received messages. */
static nImO::ReceiveQueue   lReceiveQueue;

/*! @brief A class to provide values that are used for handling callbacks for the application. */
class WatchBreakHandler final : public nImO::CallbackFunction
{
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The class that this class is derived from. */
        using inherited = CallbackFunction;

    public :
        // Public methods.

        /*! @brief The constructor. */
        inline WatchBreakHandler
            (void) :
                inherited()
        {
        }

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Process a break signal.
         @return @c true on success. */
        bool
        operator()
            (void)
            override
        {
            ODL_OBJENTER(); //####
            lReceiveQueue.stop();
            nImO::gWatchThreadStop = true;
            ODL_B1(nImO::gWatchThreadStop); //####
            ODL_OBJEXIT_B(true); //####
            return true;
        }

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

}; // WatchBreakHandler

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for reporting information on #nImO.

 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    nImO::DescriptorVector  argumentList;
    nImO::StandardOptions   optionValues;
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Watch nImO"s, "nImOwatch"s, 2024, nImO::kCopyrightName, optionValues, nullptr,
                                     nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipLoggingOption | nImO::kSkipMachineOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            QApplication    app(argc, argv);
            auto            window{new nImO::WatchWindow};

            QApplication::setApplicationDisplayName(progName.c_str());
            window->show();
            nImO::SetSignalHandlers(nImO::CatchSignal);
            nImO::SearchContext ourContext{"watch"s, optionValues._logging};
            auto                loggingConnection{ourContext.getLoggingInfo()};
            auto                registrySearchConnection{ourContext.getRegistrySearchInfo()};
            auto                statusConnection{ourContext.getStatusInfo()};
            auto                logReceiver{std::make_shared<nImO::ReceiveFromMulticast>(ourContext.getService(), loggingConnection, lReceiveQueue, nImO::kMessageFromLog)};
            auto                registrySearchReceiver{std::make_shared<nImO::ReceiveFromMulticast>(ourContext.getService(), registrySearchConnection, lReceiveQueue,
                                                                                                    nImO::kMessageFromRegistrySearch)};
            auto                statusReceiver{std::make_shared<nImO::ReceiveFromMulticast>(ourContext.getService(), statusConnection, lReceiveQueue, nImO::kMessageFromStatus)};

            nImO::SetSpecialBreakObject(new WatchBreakHandler);
            auto    watchThread{new nImO::WatchThread(lReceiveQueue, window)};

            ODL_P1(watchThread); //####
            QObject::connect(watchThread, SIGNAL(addLine(QString)), window, SLOT(addText(QString)));
            watchThread->start();
            exitCode = app.exec();
            if (nullptr != watchThread)
            {
                nImO::gWatchThreadStop = true;
                ODL_B1(nImO::gWatchThreadStop); //####
                watchThread->quit();
                watchThread->wait();
                watchThread = nullptr;
            }
        }
        catch (const std::string &  fault)
        {
            std::cerr << "Exception: " << fault << "\n";
            exitCode = -1;
        }
        catch (...)
        {
            ODL_LOG("Exception caught"); //####
            exitCode = -1;
        }
    }
    ODL_EXIT_I(exitCode); //####
    return exitCode;
} // main

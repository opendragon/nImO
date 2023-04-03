//--------------------------------------------------------------------------------------------------
//
//  File:       nImOlistMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to report the visible nImO channels.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2016 by OpenDragon.
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
//  Created:    2016-02-19
//
//--------------------------------------------------------------------------------------------------

#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOstandardOptions.h>
#include <nImOstringsArgumentDescriptor.h>
#include <nImOutilityContext.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to report the visible #nImO channels. */

/*! @dir List
 @brief The set of files that implement the List application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The available choices. */
enum class Choice
{
    /*! @brief Return information on the known applications. */
    kApps,

    /*! @brief Return information on the known channels. */
    kChan,

    /*! @brief Return information on the known connections. */
    kConn,

    /*! @brief Return information on the known services. */
    kServ,

    /*! @brief Return information on the known nodes. */
    kNode,

    /*! @brief Return information on the known applications, channels, connections and services. */
    kAll

}; // Choice

/*! @brief Convenience structure for choices. */
struct ChoiceInfo
{
    /*! @brief A particular choice. */
    Choice  _choice;

    /*! @brief The description of the choice. */
    std::string _description;

    /*! @brief The constructor.
     @param[in] choice The choice value associated with the description.
     @param[in] description The text describing the choice. */
    ChoiceInfo
        (const Choice           choice,
         const std::string &    description) :
            _choice(choice), _description(description)
    {
    }

}; // ChoiceInfo

typedef std::map<std::string, ChoiceInfo> ChoiceMap;

static ChoiceMap  lChoiceMap;

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Writes out a description of the 'choice' argument.
 @param[in,out] outStream The stream to write to. */
static void
helpForList
    (std::ostream & outStream)
{
    size_t  choiceWidth = 0;

    outStream << "Available choices:" << std::endl;
    for (auto walker(lChoiceMap.begin()); walker != lChoiceMap.end(); ++walker)
    {
        size_t  thisWidth = walker->first.length();

        if (thisWidth > choiceWidth)
        {
            choiceWidth = thisWidth;
        }
    }
    choiceWidth += 2;
    for (auto walker(lChoiceMap.begin()); walker != lChoiceMap.end(); ++walker)
    {
        std::string padding;

        padding.append(choiceWidth - walker->first.length(), ' ');
        outStream << "  " << walker->first << padding << walker->second._description << std::endl;
    }
} // helpForList

/*! @brief Output the known nodes.
 @param[in] proxy The connection to the Registry.
 @param[in] options The options to apply.
 @return @c true if no errors encountered or @c false if there was a problem. */
static bool
listNodes
    (nImO::RegistryProxy &      proxy,
     nImO::StandardOptions &    options)
{
    bool                        okSoFar = true;
    nImO::RegStringSetOrFailure statusWithStrings = proxy.getNodes();

    ODL_B1("okSoFar <- ", okSoFar); //!!!
    if (statusWithStrings.first.first)
    {
        nImO::StringSet nodes = statusWithStrings.second;

        if (nodes.empty())
        {
            std::cout << "** No nodes **" << std::endl;
        }
        else
        {
            if (nImO::OutputFlavour::FlavourJSON == options._flavour)
            {
                std::cout << "{ " << std::endl;
            }
            for (auto walker(nodes.begin()); nodes.end() != walker; )
            {
                std::string                 nodeName{nImO::SanitizeString(*walker, nImO::OutputFlavour::FlavourJSON == options._flavour)};
                nImO::RegNodeInfoOrFailure  statusWithInfo = proxy.getNodeInformation(nodeName);

                ++walker;
                if (statusWithInfo.first.first)
                {
                    if (statusWithInfo.second._found)
                    {
                        switch (options._flavour)
                        {
                            case nImO::OutputFlavour::FlavourNormal :
                                std::cout << nodeName << ' ' << statusWithInfo.second._connection._address << std::endl;
                                break;

                            case nImO::OutputFlavour::FlavourJSON :
                                std::cout << CHAR_DOUBLEQUOTE_ << nodeName << T_(CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_) <<
                                            statusWithInfo.second._connection._address << CHAR_DOUBLEQUOTE_;
                                if (nodes.end() != walker)
                                {
                                    std::cout << ",";
                                }
                                std::cout << std::endl;
                                break;

                            case nImO::OutputFlavour::FlavourTabs :
                                std::cout << nodeName << '\t' << statusWithInfo.second._connection._address << std::endl;
                                break;

                            default :
                                break;

                        }
                    }
                }
                else
                {
                    std::cerr << "Problem with 'getNodeInformation': " << statusWithInfo.first.second << std::endl;
                    okSoFar = false;
                    ODL_B1("okSoFar <- ", okSoFar); //!!!
                    break;
                }
            }
            if (nImO::OutputFlavour::FlavourJSON == options._flavour)
            {
                std::cout << " }" << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "Problem with 'getNodes': " << statusWithStrings.first.second << std::endl;
        okSoFar = false;
        ODL_B1("okSoFar <- ", okSoFar); //!!!
    }
    return okSoFar;
} // listNodes

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for reporting the visible #nImO channels.

 Standard output will receive a list of the visible #nImO channels.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string progName{*argv};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::ReportVersions();
    lChoiceMap.insert({"apps", ChoiceInfo{Choice::kApps, "available applications"}});
    lChoiceMap.insert({"chan", ChoiceInfo{Choice::kChan, "available channels"}});
    lChoiceMap.insert({"conn", ChoiceInfo{Choice::kConn, "active connections"}});
    lChoiceMap.insert({"serv", ChoiceInfo{Choice::kServ, "active services"}});
    lChoiceMap.insert({"node", ChoiceInfo{Choice::kNode, "active nodes"}});
    lChoiceMap.insert({"all", ChoiceInfo{Choice::kAll, "all"}});
    nImO::StringSet choiceSet;

    for (auto & walker : lChoiceMap)
    {
        choiceSet.insert(walker.first);
    }
    nImO::StringsArgumentDescriptor firstArg{"choice", T_("Objects to report"), nImO::ArgumentMode::Optional, "all", choiceSet};
    nImO::DescriptorVector          argumentList;
    nImO::StandardOptions           optionValues;
    int                             exitCode = 0;

    argumentList.push_back(&firstArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "List information about objects in the nImO space", "nImOlist node", 2016,
                                     NIMO_COPYRIGHT_NAME_, optionValues, helpForList, nImO::kSkipLoggingOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            nImO::SpContextWithNetworking   ourContext{new nImO::UtilityContext{progName, "list", optionValues._logging}};
            nImO::Connection                registryConnection;

            ODL_P1("ourContext <- ", ourContext.get()); //!!!
            if (ourContext->asUtilityContext()->findRegistry(registryConnection))
            {
                std::string choice{firstArg.getCurrentValue()};
                auto        match{lChoiceMap.find(choice)};

                if (match != lChoiceMap.end())
                {
                    nImO::RegistryProxy proxy{ourContext, registryConnection};

                    switch (match->second._choice)
                    {
                        case Choice::kApps :
                            // TBD
                            break;

                        case Choice::kChan :
                            // TBD
                            break;

                        case Choice::kConn :
                            // TBD
                            break;

                        case Choice::kServ :
                            // TBD
                            break;

                        case Choice::kNode :
                            if (! listNodes(proxy, optionValues))
                            {
                                exitCode = 1;
                            }
                            break;

                        case Choice::kAll :
                            // TBD
                            break;

                    }
                }
            }
            else
            {
                ourContext->report("Registry not found.");
                exitCode = 2;
            }
            ourContext->report("exiting.");
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

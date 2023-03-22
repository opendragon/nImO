//
//  nImOmainSupport.h
//  nImO
//
//  Created by Norman Jaffe on 2023/03/22.
//  Copyright © 2023 Norman Jaffe. All rights reserved.
//

#ifndef nImOmainSupport_hpp
#define nImOmainSupport_hpp

# include <nImOcommon.h>

namespace nImO
{

    /*! @brief The signal handler to catch requests to stop the application.
     @param[in] signal The signal being handled. */
    void
    CatchSignal
        (const int  signal);

    /*! @brief Set to @c false when a SIGINT occurs. */
    extern std::atomic<bool>    gKeepRunning;

} // nImO

#endif /* nImOmainSupport_hpp */

#General Packaging Stuff
set(CPACK_CREATE_DESKTOP_LINKS "nImO manager")
set(CPACK_DISPLAY_NAME "n-Input m-Output")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "nImO Package")
set(CPACK_PACKAGE_EXECUTABLES "nImO manager" "nImO manager")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "nImO")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY_ "nImO")
set(CPACK_PACKAGE_NAME "nImO")
set(CPACK_PACKAGE_VERSION "${nImO_VERSION_STRING}")
set(CPACK_PACKAGE_VERSION_MAJOR "${nImO_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${nImO_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${nImO_VERSION_PATCH}")
set(CPACK_RESOURCE_FILE_LICENSE "${nImO_SOURCE_DIR}/license.txt")
set(CPACK_RESOURCE_FILE_README "${nImO_SOURCE_DIR}/README.txt")
set(CPACK_VENDOR "OpenDragon")

#display name for our components
set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Standard Applications")
set(CPACK_COMPONENT_EXAMPLEAPPS_DISPLAY_NAME "Example Applications")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Header Files")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "nImO Libraries")
set(CPACK_COMPONENT_SOURCECODE_DISPLAY_NAME "Source Code")
set(CPACK_COMPONENT_MANUALS_DISPLAY_NAME "Manuals")

#descriptions for our components
set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION "The executables that support running the nImO middleware")
set(CPACK_COMPONENT_EXAMPLEAPPS_DESCRIPTION "Examples of nImO applications")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION "The header files required for new development")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "The fundamental files for an nImO installation")
set(CPACK_COMPONENT_SOURCECODE_DESCRIPTION
    "The source files for a nImO installation, required for extending or modifying the core applications or libraries")
set(CPACK_COMPONENT_MANUALS_DESCRIPTION "The nImO manuals")

#set up dependencies
set(CPACK_COMPONENT_APPLICATIONS_DEPENDS libraries)
set(CPACK_COMPONENT_EXAMPLEAPPS_DEPENDS libraries)
set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)
set(CPACK_COMPONENT_SOURCECODE_DEPENDS libraries headers)
set(CPACK_COMPONENT_MANUALS_DEPENDS libraries)

#set up CPack groups
set(CPACK_COMPONENT_APPLICATIONS_GROUP "Core")
set(CPACK_COMPONENT_EXAMPLEAPPS_GROUP "Optional")
set(CPACK_COMPONENT_HEADERS_GROUP "Core")
set(CPACK_COMPONENT_LIBRARIES_GROUP "Core")
set(CPACK_COMPONENT_SOURCECODE_GROUP "Optional")
set(CPACK_COMPONENT_MANUALS_GROUP "Optional")

#set up CPack constraints
set(CPACK_COMPONENT_LIBRARIES_REQUIRED ON)
set(CPACK_COMPONENT_EXAMPLEAPPS_DISABLED ON)
set(CPACK_COMPONENT_SOURCECODE_DISABLED ON)
set(CPACK_COMPONENT_MANUALS_DISABLED ON)

#CPack group descriptions
set(CPACK_COMPONENT_GROUP_CORE_DESCRIPTION "The core nImO libraries and executables")
set(CPACK_COMPONENT_GROUP_CORE_BOLD_TITLE ON)
set(CPACK_COMPONENT_GROUP_OPTIONAL_DESCRIPTION
    "Example applications, manuals and source code for the libraries and standard applications")
	
set(CPACK_COMPONENTS_ALL applications exampleapps headers libraries sourcecode manuals)

#end General Packaging stuff

# platform independent install step:
#
# NOTE: since we're not currently using CPack on mac, everything falls under WIN32 below:
#

#Windows specific install step
if(WIN32)
    set(CPACK_GENERATOR NSIS)

    install(FILES
            "${nImO_SOURCE_DIR}/vc_redist.x64.exe"
            "${nImO_SOURCE_DIR}/bonjoursdksetup.exe"
            DESTINATION support
            COMPONENT libraries)

    # copy yarp and ACE DLL's to install location
    # set env variables for nImO_YARP_DIR and nImO_ACE_ROOT
    # so VS external, preconfigured projects can find them

    # Note that we can't use ENV(ACE_ROOT) or ENV(YARP_DIR),
    # as they contain backslashes when building for Windows!
    #set(nImO_ACE_ROOT "${nImO_SOURCE_DIR}/../ACE_wrappers")
    set(nImO_ACE_ROOT "${ACE_INCLUDE_DIR}")
    set(nImO_YARP_DIR "${nImO_SOURCE_DIR}/../yarp_MPlusM")

    #ACE DLL
    install(FILES
            "${nImO_ACE_ROOT}/lib/ACE.dll"
            DESTINATION bin
            COMPONENT libraries)
    install(FILES
            "${nImO_ACE_ROOT}/lib/ACEd.dll"
            DESTINATION bin
            COMPONENT libraries)
    #ACE LIB
    install(FILES
            "${nImO_ACE_ROOT}/lib/ACE.lib"
            DESTINATION lib
            COMPONENT libraries)
    install(FILES
            "${nImO_ACE_ROOT}/lib/ACEd.lib"
            DESTINATION lib
            COMPONENT libraries)

    #YARP HEADERS
    install(DIRECTORY "${nImO_YARP_DIR}/generated_include"
            DESTINATION yarp
            COMPONENT libraries)

    install(DIRECTORY "${nImO_YARP_DIR}/src/libYARP_OS/include"
            DESTINATION yarp/src/libYARP_OS
            COMPONENT libraries)

    install(DIRECTORY "${nImO_YARP_DIR}/src/libYARP_name/include"
            DESTINATION yarp/src/libYARP_name
            COMPONENT libraries)

    install(DIRECTORY "${nImO_YARP_DIR}/src/libYARP_dev/include"
            DESTINATION yarp/src/libYARP_dev
            COMPONENT libraries)

    install(DIRECTORY "${nImO_YARP_DIR}/src/libYARP_math/include"
            DESTINATION yarp/src/libYARP_math
            COMPONENT libraries)

    install(DIRECTORY "${nImO_YARP_DIR}/src/libYARP_sig/include"
            DESTINATION yarp/src/libYARP_sig
            COMPONENT libraries)

    #YARP EXES
    install(FILES
            #"${nImO_YARP_DIR}/bin/Release/yarp.exe"
            "${CMAKE_INSTALL_PREFIX}/bin/yarp.exe"
            #"${nImO_YARP_DIR}/bin/Release/yarpserver.exe"
            "${CMAKE_INSTALL_PREFIX}/bin/yarpserver.exe"
            #"${nImO_YARP_DIR}/bin/Release/yarpserver2.exe"
            "${CMAKE_INSTALL_PREFIX}/bin/yarpserver2.exe"
            #"${nImO_YARP_DIR}/bin/Release/yarpserver3.exe"
            "${CMAKE_INSTALL_PREFIX}/bin/yarpserver3.exe"
            #"${nImO_YARP_DIR}/bin/Release/yarp-config.exe"
            "${CMAKE_INSTALL_PREFIX}/bin/yarp-config.exe"
            DESTINATION bin
            COMPONENT applications)

    #YARP LIBS
    install(FILES
            #"${nImO_YARP_DIR}/lib/Release/YARP_OS.lib"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_OS.lib"
            #"${nImO_YARP_DIR}/lib/Release/YARP_dev.lib"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_dev.lib"
            #"${nImO_YARP_DIR}/lib/Release/YARP_name.lib"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_name.lib"
            #"${nImO_YARP_DIR}/lib/Release/YARP_init.lib"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_init.lib"
            #"${nImO_YARP_DIR}/lib/Release/YARP_sig.lib"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_sig.lib"
            DESTINATION lib
            COMPONENT libraries)

    #YARP DLLS
    install(FILES
            #"${nImO_YARP_DIR}/lib/Release/YARP_OS.dll"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_OS.dll"
            #"${nImO_YARP_DIR}/lib/Release/YARP_dev.dll"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_dev.dll"
            #"${nImO_YARP_DIR}/lib/Release/YARP_name.dll"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_name.dll"
            #"${nImO_YARP_DIR}/lib/Release/YARP_init.dll"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_init.dll"
            #"${nImO_YARP_DIR}/lib/Release/YARP_sig.dll"
            "${CMAKE_INSTALL_PREFIX}/lib/YARP_sig.dll"
            DESTINATION bin
            COMPONENT libraries)

	#Configuration files
	install(FILES
                "${nImO_SOURCE_DIR}/standardApplications.txt"
                DESTINATION support
                COMPONENT libraries)

	#OTHER EXES
	install(FILES
                "${nImO_SOURCE_DIR}/../Utilities_mm_manager/Builds/VisualStudio2015/x64/Release/nImO manager.exe"
                DESTINATION bin
                COMPONENT applications)

    #Source archives
    install(FILES
            "${nImO_SOURCE_DIR}/../archives/ACE_wrappers.zip"
            "${nImO_SOURCE_DIR}/../archives/Core_MPlusM-master.zip"
            "${nImO_SOURCE_DIR}/../archives/OGDF.zip"
            "${nImO_SOURCE_DIR}/../archives/Utilities_mm_manager-master.zip"
            "${nImO_SOURCE_DIR}/../archives/Utilities_ServiceViewer-master.zip"
            "${nImO_SOURCE_DIR}/../archives/yarp_MPlusM-master.zip"
            DESTINATION src
            COMPONENT sourcecode)

    #Documentation
    install(FILES
            "${nImO_SOURCE_DIR}/../archives/Documentation.zip"
            DESTINATION manuals
            COMPONENT manuals)

    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin/nImO manager.exe")
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_NSIS_MUI_ICON "${nImO_SOURCE_DIR}/InstallerIcon.ico")
    set(CPACK_NSIS_MUI_UNIICON "${nImO_SOURCE_DIR}/InstallerIcon.ico")
    set(CPACK_NSIS_URL_INFO_ABOUT "http://www.mplusm.ca")

    #Finally, set some nImO Environment variables (WINDOWS ONLY!)
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
        "
        CreateDirectory 'C:\\\\Users\\\\Public\\\\Documents\\\\nImO'
        CopyFiles '$INSTDIR/support/standardApplications.txt' 'C:\\\\Users\\\\Public\\\\Documents\\\\nImO'
        ExecWait '$INSTDIR/support/vc_redist.x64.exe'
        ExecWait '$INSTDIR/support/bonjoursdksetup.exe'
        WriteRegStr HKCU 'Environment' 'nImO_YARP_DIR' '$INSTDIR/yarp'
        WriteRegStr HKCU 'Environment' 'nImO_ACE_ROOT' '$INSTDIR/ACE_wrappers'	
        Delete '$INSTDIR/support/bonjoursdksetup.exe'
        CreateShortCut \\\"$DESKTOP\\\\nImO manager.lnk\\\" \\\"$INSTDIR\\\\bin\\\\nImO manager.exe\\\"
        ")

    #And, unset them when we uninstall!
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
        "
        DeleteRegValue HKCU 'Environment' 'nImO_YARP_DIR'
        DeleteRegValue HKCU 'Environment' 'nImO_ACE_ROOT'
        Delete \\\"$DESKTOP\\\\nImO manager.lnk\\\"
        ")

endif(WIN32)

include(CPack)

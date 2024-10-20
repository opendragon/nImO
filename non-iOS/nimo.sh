#!/bin/sh

THIS_FILE_NAME=$(basename $0)

function list_commands() {
    echo "  where <command> is"
    echo "    adda       add an application"
    echo "    addc       add a channel to a node"
    echo "    bridge     connect two subnets"
    echo "    check      return zero if the registry is detected"
    echo "    connect    connect two channels together"
    echo "    disconnect break the connection between two channels"
    echo "    help       list the available commands"
    echo "    list       list channels, applications, services, et cetera"
    echo "    loada      load a set of applications"
    echo "    loads      load a setup"
    echo "    log        report on nImO"
    echo "    playback   write messages stored in a file"
    echo "    post       write to the log"
    echo "    read       read from a channel"
    echo "    record     write messages received to a file"
    echo "    remove     remove an application"
    echo "    start      start an application"
    echo "    stop       stop one or all applications except active log programs"
    echo "    storea     store a set of applications"
    echo "    stores     store a setup"
    echo "    update     update an application"
    echo "    version    report the version numbers of the libraries"
    echo "    write      write to a channel"
}

function usage() {
    echo "USAGE: $THIS_FILE_NAME <command> [<options>]"
    list_commands
}

function usage_help() {
    if [[ $# -eq 0 ]]; then
        echo "USAGE: $THIS_FILE_NAME help [<command>]"
        list_commands
    else
        COMMAND=$1
        case $COMMAND in
            "adda")
               nImOaddApp -h
                ;;
            "addc")
               nImOaddChannel -h
                ;;
            "bridge")
               nImObridge -h
                ;;
            "check")
                nImOcheck -h
                ;;
            "connect")
                nImOconnect -h
                ;;
            "disconnect")
                nImOdisconnect -h
                ;;
            "help")
                usage_help
                ;;
            "list")
                nImOlist -h
                ;;
            "loada")
                nImOloadApps -h
                ;;
            "loads")
                nImOloadSetup -h
                ;;
            "log")
                nImOlog -h
                ;;
            "playback")
                nImOplayback -h
                ;;
            "post")
                nImOpost -h
                ;;
            "read")
                nImOread -h
                ;;
            "record")
                nImOrecord -h
                ;;
            "remove")
                nImOremoveApp -h
                ;;
            "start")
                nImOstart -h
                ;;
            "stop")
                nImOstop -h
                ;;
            "storea")
                nImOstoreApps -h
                ;;
            "stores")
                nImOstoreSetup -h
                ;;
            "update")
                nImOupdateApp -h
                ;;
            "version")
                nImOversion -h
                ;;
            "write")
                nImOwrite -h
                ;;
            *)
                usage_help
                ;;
        esac
    fi
}

if [[ $# -eq 0 ]]; then
    usage
else
    COMMAND=$1
    shift
    case $COMMAND in
        "adda")
            if [[ $# -eq 0 ]]; then
                usage_help adda
            else
                nImOaddApp $*
            fi
            ;;
        "addc")
            if [[ $# -eq 0 ]]; then
                usage_help addc
            else
                nImOaddChannel $*
            fi
            ;;
        "bridge")
            if [[ $# -eq 0 ]]; then
                usage_help bridge
            else
                nImObridge $*
            fi
            ;;
        "check")
            nImOcheck $*
            ;;
        "connect")
            if [[ $# -eq 0 ]]; then
                usage_help connect
            else
                nImOconnect $*
            fi
            ;;
        "disconnect")
            if [[ $# -eq 0 ]]; then
                usage_help disconnect
            else
                nImOdisconnect $*
            fi
            ;;
        "help")
            usage_help $*
            ;;
        "list")
            if [[ $# -eq 0 ]]; then
                usage_help list
            else
                nImOlist $*
            fi
            ;;
        "loada")
            if [[ $# -eq 0 ]]; then
                usage_help loada
            else
                nImOloadApps $*
            fi
            ;;
        "loads")
            if [[ $# -eq 0 ]]; then
                usage_help loads
            else
                nImOloadSetup $*
            fi
            ;;
        "log")
            nImOlog $*
            ;;
        "playback")
            if [[ $# -eq 0 ]]; then
                usage_help playback
            else
                nImOplayback $*
            fi
            ;;
        "post")
            if [[ $# -eq 0 ]]; then
                usage_help post
            else
                nImOpost $*
            fi
            ;;
        "read")
            nImOread $*
            ;;
        "record")
            if [[ $# -eq 0 ]]; then
                usage_help record
            else
                nImOrecord $*
            fi
            ;;
        "remove")
            if [[ $# -eq 0 ]]; then
                usage_help remove
            else
                nImOremoveApp $*
            fi
            ;;
        "start")
            if [[ $# -eq 0 ]]; then
                usage_help start
            else
                nImOstart $*
            fi
            ;;
        "stop")
            nImOstop $*
            ;;
        "storea")
            if [[ $# -eq 0 ]]; then
                usage_help storea
            else
                nImOstoreApps $*
            fi
            ;;
        "stores")
            if [[ $# -eq 0 ]]; then
                usage_help stores
            else
                nImOstoreSetup $*
            fi
            ;;
        "update")
            if [[ $# -eq 0 ]]; then
                usage_help update
            else
                nImOupdateApp $*
            fi
            ;;
        "version")
            nImOversion $*
            ;;
        "write")
            nImOwrite $*
            ;;
        *)
            usage
            ;;
    esac
fi

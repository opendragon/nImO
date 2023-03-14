#!/bin/sh

THIS_FILE_NAME=$(basename $0)

function list_commands() {
    echo "  where <command> is"
    echo "    add        add an application"
    echo "    bridge     connect two subnets"
    echo "    connect    connect two channels together"
    echo "    disconnect break the connection between two channels"
    echo "    help       list the available commands"
    echo "    info       report on a channel"
    echo "    list       list channels, applications, services, et cetera"
    echo "    loada      load a set of applications"
    echo "    loads      load a setup"
    echo "    monitor    report on nImO"
    echo "    post       write to the log"
    echo "    read       read from a channel"
    echo "    remove     remove an application"
    echo "    shutdown   shutdown all applicationts except active monitors"
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
            "add")
               nImOaddApp -h
                ;;
            "bridge")
               nImObridge -h
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
            "info")
                nImOinfo -h
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
            "monitor")
                nImOmonitor -h
                ;;
            "post")
                nImOpost -h
                ;;
            "read")
                nImOread -h
                ;;
            "remove")
                nImOremoveApp -h
                ;;
            "shutdown")
                nImOshutdown -h
                ;;
            "storea")
                nImOstoreApps -h
                ;;
            "stores")
                nImOstoreSetup -h
                ;;
            "updte")
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
        "add")
            if [[ $# -eq 0 ]]; then
                usage_help add
            else
                nImOaddApp $*
            fi
            ;;
        "bridge")
            if [[ $# -eq 0 ]]; then
                usage_help bridge
            else
                nImObridge $*
            fi
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
        "info")
            if [[ $# -eq 0 ]]; then
                usage_help info
            else
                nImOinfo $*
            fi
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
        "monitor")
            nImOmonitor $*
            ;;
        "post")
            if [[ $# -eq 0 ]]; then
                usage_help post
            else
                nImOpost $*
            fi
            ;;
        "read")
            if [[ $# -eq 0 ]]; then
                usage_help read
            else
                nImOread $*
            fi
            ;;
        "remove")
            if [[ $# -eq 0 ]]; then
                usage_help remove
            else
                nImOremoveApp $*
            fi
            ;;
        "shutdown")
            nImOshutdown $*
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
            if [[ $# -eq 0 ]]; then
                usage_help write
            else
                nImOwrite $*
            fi
            ;;
        *)
            usage
            ;;
    esac
fi

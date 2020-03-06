#!/bin/sh

THIS_FILE_NAME=$(basename $0)

function list_commands() {
    echo "  where <command> is"
    echo "    add        add an application"
    echo "    connect    connect two channels together"
    echo "    disconnect break the connection between two channels"
    echo "    help       list the available commands"
    echo "    info       report on a channel"
    echo "    launch     launch an application"
    echo "    list       list channels, applications, services, et cetera"
    echo "    read       read from a channel"
    echo "    remove     remove an application"
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
            "launch")
                nImOlaunch -h
                ;;
            "list")
                nImOlist -h
                ;;
            "read")
                nImOread -h
                ;;
            "remove")
                nImOremoveApp -h
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
        "launch")
            if [[ $# -eq 0 ]]; then
                usage_help launch
            else
                nImOlaunch $*
            fi
            ;;
        "list")
            if [[ $# -eq 0 ]]; then
                usage_help list
            else
                nImOlist $*
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

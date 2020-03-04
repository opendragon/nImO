#!/bin/sh

THIS_FILE_NAME=$(basename $0)

function list_commands() {
    echo "  where <command> is"
    echo "    add"
    echo "    connect"
    echo "    disconnect"
    echo "    help"
    echo "    info"
    echo "    launch"
    echo "    list"
    echo "    read"
    echo "    remove"
    echo "    version"
    echo "    write"
}

function usage() {
    echo "USAGE: $THIS_FILE_NAME <command> [<options>]"
    list_commands
}

function usage_list() {
    echo "USAGE: $THIS_FILE_NAME list <type>"
    echo "  where <type> is"
    echo "    apps"
    echo "    chan"
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
                if [[ $# -eq 1 ]]; then
                    usage_list
                else
                    TYPE=$2
                    case $TYPE in
                        "apps")
                            nImOlistApps -h
                            ;;
                        *)
                            nImOlist -h
                            ;;
                    esac
                fi
                ;;
            "read")
                nImOlaunch -h
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
                TYPE=$1
                case $TYPE in
                    "apps")
                        nImOlistApps
                        ;;
                    *)
                        nImOlist $*
                        ;;
                esac
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

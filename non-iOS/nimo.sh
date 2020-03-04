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
}

function usage_help() {
    if [[ $# -eq 0 ]]; then
        echo "USAGE: $THIS_FILE_NAME help [<command>]"
        list_commands
    else
        COMMAND=$1
        case $COMMAND in
            "add")
               $NIMO_BIN_PATH/nImOaddApp -h
                ;;
            "connect")
                $NIMO_BIN_PATH/nImOconnect -h
                ;;
            "disconnect")
                $NIMO_BIN_PATH/nImOdisconnect -h
                ;;
            "help")
                usage_help
                ;;
            "info")
                $NIMO_BIN_PATH/nImOinfo -h
                ;;
            "launch")
                $NIMO_BIN_PATH/nImOlaunch -h
                ;;
            "list")
                if [[ $# -eq 1 ]]; then
                    usage_list
                else
                    TYPE=$2
                    case $TYPE in
                        "apps")
                            $NIMO_BIN_PATH/nImOlistApps -h
                            ;;
                        *)
                            $NIMO_BIN_PATH/nImOlist -h
                            ;;
                    esac
                fi
                ;;
            "read")
                $NIMO_BIN_PATH/nImOlaunch -h
                ;;
            "remove")
                $NIMO_BIN_PATH/nImOremoveApp -h
                ;;
            "version")
                $NIMO_BIN_PATH/nImOversion -h
                ;;
            "write")
                $NIMO_BIN_PATH/nImOwrite -h
                ;;
            *)
                usage_help
                ;;
        esac
    fi
}

NIMO_BIN_PATH="$(dirname $(realpath $0))"
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
                $NIMO_BIN_PATH/nImOaddApp $*
            fi
            ;;
        "connect")
            if [[ $# -eq 0 ]]; then
                usage_help connect
            else
                $NIMO_BIN_PATH/nImOconnect $*
            fi
            ;;
        "disconnect")
            if [[ $# -eq 0 ]]; then
                usage_help disconnect
            else
                $NIMO_BIN_PATH/nImOdisconnect $*
            fi
            ;;
        "help")
            usage_help $*
            ;;
        "info")
            if [[ $# -eq 0 ]]; then
                usage_help info
            else
                $NIMO_BIN_PATH/nImOinfo $*
            fi
            ;;
        "launch")
            if [[ $# -eq 0 ]]; then
                usage_help launch
            else
                $NIMO_BIN_PATH/nImOlaunch $*
            fi
            ;;
        "list")
            if [[ $# -eq 0 ]]; then
                usage_help list
            else
                TYPE=$1
                case $TYPE in
                    "apps")
                        $NIMO_BIN_PATH/nImOlistApps
                        ;;
                    *)
                        $NIMO_BIN_PATH/nImOlist $*
                        ;;
                esac
            fi
            ;;
        "read")
            if [[ $# -eq 0 ]]; then
                usage_help read
            else
                $NIMO_BIN_PATH/nImOread $*
            fi
            ;;
        "remove")
            if [[ $# -eq 0 ]]; then
                usage_help remove
            else
                $NIMO_BIN_PATH/nImOremoveApp $*
            fi
            ;;
        "version")
            $NIMO_BIN_PATH/nImOversion
            ;;
        "write")
            if [[ $# -eq 0 ]]; then
                usage_help write
            else
                $NIMO_BIN_PATH/nImOwrite $*
            fi
            ;;
        *)
            usage
            ;;
    esac
fi

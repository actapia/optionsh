#!/usr/bin/env bash
if (( BASH_VERSINFO[0] < 4 || ( BASH_VERSINFO[0] == 4 && BASH_VERSINFO[1] < 3) )); then
    echo "optionsh is only compatible with Bash 4.3+"
fi

function parse_args {
    local -n ARGS=$2
    #declare -A ARGS
    json_file="${1%.*}.json"
    result="$(optionsh "$1" "${@:3}"< "$json_file")"
    exit_code=$?
    if [ $exit_code -ne 0 ]; then
	echo "$result"
	return $exit_code
    elif [ $exit_code -eq 0 ]; then
	while read -r line; do
	    IFS=":" read -r arg value <<<"$line"
	    if ! [ -z "$arg" ]; then
		ARGS["$arg"]="$value"
	    fi
	done <<<"$result"
    fi
}

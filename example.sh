#!/usr/bin/env bash
source optionsh.sh
declare -A MYARGS
parse_args $0 MYARGS "$@"
parse_result=$?
if [ $parse_result -ne 0 ]; then
    if [ $parse_result -eq 101 ]; then
	exit 0
    else
	exit $parse_result
    fi
fi
for arg in "${!MYARGS[@]}"; do
    echo "MYARGS[$arg]=${MYARGS[$arg]}"
done

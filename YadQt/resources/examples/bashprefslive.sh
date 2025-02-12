#!/bin/bash

#use tempfile
pushd $(dirname $0)

cat exampleprefs.data|yadqt --type=prefsdialog -t "Example Prefs" --buttons="apply|ok|cancel" -a yadprefsexample --fromstdin --ipseparator=newline --opseparator=newline --buttons="ok|cancel|apply"|while read;do echo ">>>>"${REPLY}"<<<<<";done

popd
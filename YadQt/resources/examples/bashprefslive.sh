#!/bin/bash

#use tempfile

cat exampleprefs.data|yadqt --type=prefsdialog -t "Example Prefs" -a yadprefsexample --fromstdin --ipseparator=newline --opseparator=newline|while read;do echo ">>>>"${REPLY}"<<<<<";done


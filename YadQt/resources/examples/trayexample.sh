#!/bin/bash

pushd $(dirname $0)
	echo -e "Open Home\nuser-home\nxdg-open ${HOME}"|cat - ./traydata | yadqt --type=traymenu --title="Open Folders" --fromstdin --ipseparator=newline --icon=system-file-manager --timeout=1000 &
	echo "XTerm|xterm|xterm|Open Google|google-chrome|xdg-open https://www.google.com|New Email|mail_new|xdg-email" | yadqt --type=traymenu --title="Run Apps" --fromstdin --icon=system-run --timeout=1000 &
	./localapps &
popd
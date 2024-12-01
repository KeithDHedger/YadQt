#!/bin/bash
#
#©K. D. Hedger. Sun  1 Dec 14:43:47 GMT 2024 keithdhedger@gmail.com
#
#This file (screenshoter.sh) is part of YadQt.
#
#YadQt is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#YadQt is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with YadQt.  If not, see <http://www.gnu.org/licenses/>.
#
#requires maim xdotool

OK=0
while read
	do
		OK=1
		eval $REPLY
	done< <(cat shooter.data|yadqt --type=prefsdialog -a YadQTScreenshooter -t "YadQT Screenshooter" --fromstdin --ipseparator=newline --opseparator=newline 2>/dev/null)

if [ $OK -eq 0 ];then
	exit 0
fi

echo delay=$delay
echo file=$save_file_as
echo capture_mouse=$capture_mouse
echo open_in_gimp=$open_in_gimp

if [ $capture_mouse -eq 1 ];then
	cursor=
	if [ $delay -eq 0 ];then
		delay=0.1
	fi
else
	cursor="-u"
fi


case $select_type in
	"Select Window")
		maim  $cursor -i $(xdotool selectwindow) --delay=$delay $save_file_as
		;;
	"Select Area")
		maim --select $cursor --delay=$delay $save_file_as
		;;
	"Select Screen")
		maim $cursor --capturebackground --delay=$delay $save_file_as
		;;
	"Select Window And Borders")
		DATA=$(slop -f '%g %i')
		WIND=$(echo $DATA|awk '{print $2}')
		GEOM=$(echo $DATA|awk '{print $1}')

		xdotool windowactivate $WIND 2>/dev/null
		xdotool windowraise $WIND sleep 0.5 2>/dev/null
		maim $cursor --geometry=$GEOM --delay=$delay $save_file_as
		;;
esac

if [ $open_in_gimp -eq 1 ];then
	gimp $save_file_as &
fi
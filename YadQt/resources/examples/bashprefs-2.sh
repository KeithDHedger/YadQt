#!/bin/bash

#directly eval

while read
	do
		eval $REPLY
	done< <(cat exampleprefs.data|yadqt --type=prefsdialog -t "Example Prefs" -a yadprefsexample --fromstdin --ipseparator=newline --opseparator=newline 2>/dev/null)

echo prefs_combo_name_1=$prefs_combo_name_1
echo combo_name_2=$combo_name_2
echo prefs_edit_two=$prefs_edit_two
echo edit_three=$edit_three
echo prefs_check_1=$prefs_check_1
echo use_theme=$use_theme
echo prefs_main_colour_2=$prefs_main_colour_2
echo second_col= $second_col
echo prefs_main_font=$prefs_main_font
echo secondary_font=$secondary_font
echo folder_one=$folder_one
echo fiile_one=$fiile_one

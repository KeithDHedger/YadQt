# YadQt
This is an app to produce simple Qt dialogs from the command line, similar to YAD for gtk.<br>

To build/install:
````console
./autogen.sh --prefix=/usr
make
make install
````

QUICK USE:<br>
yadqt -h
```console
Usage: ./yadqt [options]

Options:
  -h, --help                   Displays help on commandline options.
  --help-all                   Displays help including Qt specific options.
  -t, --title <YadQt>          Title.
  -b, --body <Information>     Body.
  -d, --default <keithhedger>  Default text.
  --width <640>                Dialog width.
  --height <400>               Dialog height.
  --btntoerr                   Print button to stderr.
  --buttons <Ok>               Buttons.
  --type <about>               Box Type.
````
yadqt --type=fatal -t "my title" -b "some info"  -d "some info" --buttons="abort" --btntoerr 2>/dev/pts/2;echo $?<br>
yadqt --type=aboutqt<br>
yadqt --type=getitem -t "my title" -b "some input"  -d "one|three|two|end" --btntoerr 2>/dev/pts/2;echo $?<br>
yadqt --type=gettext -t "my title" -b "some input"  -d "default input txt";echo $?<br>
yadqt --type=info -t "my title" -b "some info"  -d "some info" --buttons="abort" --btntoerr 2>/dev/pts/2;echo $?<br>
yadqt --type=form -t "Simple Form" -b "Entry 1|Box Two|Data 3|Last Box" --btntoerr --default="default 1|box 2|box n"  2>/dev/pts/2;echo $?<br>
yadqt --type=form -t "Simple Form" -b "Entry 1|Box Two|Data 3|Last Box"  --default="default 1|box 2|box n" --width=300<br>
yadqt --type=list -t "Simple List" --default="$(cat /etc/fstab|tr '\n' '|')" --multiple --btntoerr --width=600 --height=350 2>/dev/pts/2;echo $?<br>
yadqt --type=list -t "Simple List" --default="default 1|item 2|item 3|num 4|five|666|item nth" --multiple  ;echo $?<br>

<br>
Some options are not yet implemented<br>
<br>
TODO<br>
documentation :(<br>
more boxes<br>
set i/p and o/p seperator for data.

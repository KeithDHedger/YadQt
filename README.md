# YadQt
This is an app to produce simple Qt dialogs from the command line, similar to YAD for gtk.<br>

QUICK USE:<br>
yadqt -h
```sh
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
<br>
Some options are not yet implemented<br>
<br>
TODO<br>
documentation :(<br>
more boxes<br>

# YadQt
This is an app to produce simple Qt dialogs from the command line, similar to YAD for gtk.<br>

To build/install:
````console
./autogen.sh --prefix=/usr
make
make install
````

**QUICK USE:** <br>
yadqt -h
```console
Usage: yadqt [options]

Options:
  -h, --help                   Displays help on commandline options.
  --help-all                   Displays help including Qt specific options.
  -v, --version                Displays version information.
  -t, --title <YadQt>          Title.
  -b, --body <Information>     Body.
  -d, --default <keithhedger>  Default text ( lists, forms etc ).
  --fromstdin                  Read default data from stdin.
  --width <640>                Dialog width ( set to 0 for default size for
                               dialog ).
  --height <320>               Dialog height ( set to 0 for default size for
                               dialog ).
  --opseparator <|>            Separator for multi item output ( use "newline"
                               to use '\n' ).
  --ipseparator <|>            Separator for multi item default text input ( use "newline"
                               to use '\n' ).
  --multiple                   Select multiple items ( lists ).
  --btntoerr                   Print button to stderr.
  --buttons <Ok>               Buttons ( for info boxes ).
  --type <aboutqt>             Box Type ( no type will display aboutbox for Qt ).
````

**Dialog types:**<br>
about<br>
aboutqt<br>
query<br>
info<br>
warn<br>
fatal<br>
input<br>
getitem<br>
form<br>
list<br>
textfile<br>
imagefile<br>
colour<br>
font<br>
text<br>
tailbox<br>

**Examples:**<br>
````yadqt --type=aboutqt````<br>

````yadqt --type=fatal -t "DANGER!" -b "BSOD!" --buttons="abort|Ignore" --btntoerr 2>/dev/pts/2;echo $?````<br>
![fatal](screenshots/fatal.png "yadqt --type=fatal")<br>

````cat /usr/include/linux/limits.h|yadqt --type=getitem -t "Select Item" -b "Items:"  --ipseparator=newline --fromstdin````<br>
````yadqt --type=getitem -t "my title" -b "some input"  -d "one|three|two|end" --btntoerr 2>/dev/pts/2;echo $?````<br>
![fatal](screenshots/getitem.png "yadqt --type=getitem")<br>

````yadqt --type=input -t "my title" -b "some input"  -d "default input txt";echo $?````<br>
![fatal](screenshots/input.png "yadqt --type=input")<br>

````yadqt --type=info -b "Some info for you" --buttons="ok" --btntoerr 2>/dev/pts/2;echo $?````<br>
![fatal](screenshots/info.png "yadqt \--type=info")<br>

````yadqt --type=form -t "Simple Form" -b "Entry 1|Box Two|Data 3|Last Box" --btntoerr --default="default 1|box 2|box n"  2>/dev/pts/2;echo $?````<br>
![fatal](screenshots/form.png "yadqt --type=form")<br>

````yadqt --type=form -t "Simple Form" -b "Entry 1|Box Two|Data 3|Last Box"  --default="default 1|box 2|box n" --width=300 --height=0````<br>
![fatal](screenshots/form2.png "yadqt --type=form")<br>

````yadqt --type=list -t "Simple List" --default="$(cat /etc/fstab|tr '\\n' '|')" --multiple --btntoerr --width=600 --height=350 2>/dev/pts/2;echo $?````<br>
````yadqt --type=list -t "Simple List" --default="$(cat /etc/fstab)" --btntoerr --width=600 --height=350 --ipseparator="newline"````<br>
````yadqt --type=list -t "Simple List" --default="default 1|item 2|item 3|num 4|five|666|item nth" --multiple  --opseparator="newline";echo $?````<br>
![fatal](screenshots/list1.png "yadqt --type=list")<br>

````yadqt --type=text -t "Show Text" --default="some text@second line@third line" --ipseparator=@````<br>
![fatal](screenshots/text1.png "yadqt --type=text")<br>

````while read;do echo $REPLY;done< <(cat /etc/fstab)|yadqt --type=text --fromstdin --width=800 -t "Show Text"````<br>
![fatal](screenshots/text2.png "yadqt --type=text")<br>

````yadqt --type=textfile --width=800 --height=400 -d /usr/include/linux/limits.h  --btntoerr  2>/dev/pts/3;echo $?````<br>
![fatal](screenshots/textfile.png "yadqt --type=textfile")<br>

````yadqt --type=imagefile -d '/home/keithhedger/WallpapersByCatagory/AllHallows/halloween-graveyard.gif'````<br>
````yadqt --type=imagefile -d '/home/keithhedger/Backgrounds/bc3.png' --height=420 --width=640````<br>
![fatal](screenshots/image.png "yadqt --type=imagefile")<br>

````yadqt --type=colour --default="#c080ff80" -t "Select a colour..."|yadqt --type=input -t "Results" -b "Colour Selected" --fromstdin````<br>
````yadqt --type=colour --default="#c080ff80" --btntoerr -t "Select a colour..."  2>/dev/pts/2;echo $?````<br>
![fatal](screenshots/colour.png "yadqt --type=colour")<br>

````yadqt --type=font -d "Monospace,20"````<br>
![fatal](screenshots/font.png "yadqt --type=font")<br>

````ls -1 ~|yadqt --type=tailbox -t "Tail box" --width=800````<br>
![fatal](screenshots/tailbox.png "yadqt --type=tailbox")<br>

**Simple search in current folder:**<br>
Searches files for text and opens in default app.
```console
find .  -print0 |xargs -0 grep -s --binary-files=without-match --ignore-case --binary-files=without-match --line-number "$(yadqt --type=input -t Search -b "Search for")"|yadqt --type=list -t "Found" --width 800 --fromstdin --ipseparator=newline |awk -F: '{print $1}'|xargs xdg-open
````
![fatal](screenshots/search1.png "Search example")<br>
![fatal](screenshots/search2.png "Search example")<br>

<br>
Some options are not yet implemented<br>
<br>
TODO<br>
documentation - ONGOING ... :(<br>
more boxes<br>
set o/p separator for data.DONE<br>
set i/p separator for data.DONE<br>

/*
 *
 * ©K. D. Hedger. Fri 23 Aug 20:36:56 BST 2024 keithdhedger@gmail.com

 * This file (main.cpp) is part of YadQt.

 * YadQt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * YadQt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with YadQt.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "globals.h"

int main(int argc, char **argv)
{
	QApplication			app(argc,argv);
	QStringList			xtraargs;

	DataClass			data;
	InfoBoxClass			info(&app,&data);
	InputDialogsClass	input(&app,&data);
	FormsClass			forms(&app,&data);
	ListBoxClass			list(&app,&data);
	FilesClass			files(&app,&data);
	OrphanDialogClass	orphans(&app,&data);
	unsigned				retval=0;

	QIcon::setFallbackThemeName("gnome");

	app.setQuitOnLastWindowClosed(true);
	app.setOrganizationName("KDHedger");
	app.setApplicationName(PACKAGE_NAME);
	app.setApplicationVersion(PACKAGE_VERSION);
	app.processEvents();

	data.parser.setApplicationDescription("This is an app to produce simple Qt dialogs from the command line, similar to YAD for gtk");
	data.parser.addHelpOption();
	data.parser.addVersionOption();
	data.parser.addOptions(
		{
			{{"a","appname"},"Application name.",PACKAGE_NAME},
			{{"t","title"},"Title.",PACKAGE_NAME},
			{{"b","body"},"Body.",data.body},
			{{"d","default","data"},"Default text ( lists, forms etc, 1st positional arg passed will overide this ).",QDir::home().dirName()},
			{"fromstdin","Read default data from stdin."},
			{"width","Dialog width ( set to 0 for default size for dialog ).","0"},
			{"height","Dialog height ( set to 0 for default size for dialog ).","0"},
			{"opseparator","Separator for multi item output ( use \"newline\" to use '\\n' ).",data.opsep},
			{"ipseparator","Separator for multi item default text input ( use \"newline\" to use '\\n' ).",data.ipsep},
			{"multiple","Select multiple items ( lists )."},
			{"btntoerr","Print button to stderr."},
			{"buttons","Buttons ( for info boxes ).","Ok"},
			{"icon","Icon to use for tray menu.",data.theIcon},
			{"timeout","Timeout to use for tray menu message in mS( 0=no message ).","0"},
			{"allowreload","Add 'Reload' item to tray menu."},
			{"runfirst","Run application  ARG before starting/reloading traymenu.",data.runThisfirst},
			{"remember","Remembers last tray menu context menu item and sets main icon to menuitem icon, middle click then reactives last item."},
			{"type","Box Type ( no type will display aboutbox for Qt )\n\nTypes are:\nabout aboutqt query info warn fatal input getitem form list textfile imagefile colour font text tailbox notepad richtext openfile savefile prefsdialog tabbedprefsdialog traymenu help.\nMore info and examples here:\nhttps://keithdhedger.github.io/pages/yadqt/yadqt.html","aboutqt"},
	});

	app.setWindowIcon(QIcon::fromTheme("user-info"));
	data.parser.process(app.arguments());

	if(data.parser.isSet("title")==true)
		data.title=data.parser.value("title");

	if(data.parser.isSet("allowreload")==true)
		data.allowRestart=true;

	if(data.parser.isSet("remember")==true)
		data.rememberItem=true;

	if(data.parser.isSet("fromstdin")==true)
		{
			data.dataFromStdIn=true;
			QTextStream	datastream(stdin);
    			QString		datain=datastream.readAll().trimmed();
    			data.defaultText=datain;
		}
	else
		{
			if(data.parser.isSet("default")==true)
				data.defaultText=data.parser.value("default");
			else if(data.parser.isSet("data")==true)
				data.defaultText=data.parser.value("data");
		}

	if(data.parser.isSet("runfirst")==true)
		data.runThisfirst=data.parser.value("runfirst");

	if(data.parser.isSet("body")==true)
		data.body=data.parser.value("body");

	if(data.parser.isSet("appname"))
		{
			app.setApplicationName(data.parser.value("appname"));
		}

	if(data.parser.isSet("icon"))
		{
			data.theIcon=data.parser.value("icon").trimmed();
		}

	if(data.parser.isSet("timeout"))
		{
			data.timeOut=data.parser.value("timeout").toInt();
		}

	if(data.parser.isSet("width"))
		{
			data.customSize=true;
			data.width=data.parser.value("width").toInt();
		}
	if(data.parser.isSet("height"))
		{
			data.customSize=true;
			data.height=data.parser.value("height").toInt();
		}
	if(data.parser.isSet("opseparator"))
		{
			if(data.parser.value("opseparator").compare("newline")==0)
				data.opsep="\n";
			else
				data.opsep=data.parser.value("opseparator");
		}
	if(data.parser.isSet("ipseparator"))
		{
			if(data.parser.value("ipseparator").compare("newline")==0)
				data.ipsep="\n";
			else
				data.ipsep=data.parser.value("ipseparator");
		}
	if(data.parser.isSet("type"))
		{
			data.getBoxType();
			data.setDButtons();
			if(data.parser.isSet("buttons")==false)
				{
					data.dbutton=QDialogButtonBox::Ok;
					data.bb->setStandardButtons(data.dbutton);
				}

			xtraargs=data.parser.positionalArguments();
			if(xtraargs.isEmpty()==false)
				data.defaultText=xtraargs.first();

			switch(data.boxType)
				{
//info boxes
					case ABOUT:
					case ABOUTQT:
					case QUERY:
					case INFO:
					case WARN:
					case FATAL:
						info.showDialog();
						break;

//input boxes
					case GETINPUT:
						input.getTextInput();
						break;
					case GETITEM:
						input.getItem();
						break;
//forms
					case GETFORM:
						forms.getForm();
						break;
//list
					case GETLIST:
						list.getList();
						break;
//files
					case SHOWTEXTFILE:
						files.showTextFile(true);
						break;
					case GETTEXT:
						files.showTextFile(false);
						break;
					case SHOWIMAGEFILE:
						files.showImageFile();
						break;
//orphans
					case GETCOLOUR:
						orphans.getColour();
						break;
					case GETFONT:
						orphans.getFont();
						break;
					case TAILBOX:
						orphans.tailBox();
						break;
					case NOTEPAD:
						orphans.notePad();
						break;
					case RICHTEXT:
						orphans.richText();
						break;
						break;
//files
					case OPENFILE:
						orphans.openFile();
						break;
					case SAVEFILE:
						orphans.saveFile();
						break;
//prefs
					case PREFSDIALOG:
						orphans.prefsDialog(false);
						break;
					case TABBEDPREFSDIALOG:
						orphans.prefsDialog(true);
						break;
//tray menu
					case TRAYMENU:
						orphans.trayMenu();
						break;
//yadqt help
					case YADQTHELP:
						orphans.yadQtHelp();
						break;

				}
		}
	else
		{
			data.body="<b>YadQt</b><br>Create Qt dialogs from shell scripts<br><br><a href=\"https://keithdhedger.github.io\">Website</a><br><br><a href=\"mailto:keithdhedger@gmail.com\">Mail Me</a>";
			data.boxType=ABOUT ;
			info.showDialog();
		}

	if(data.parser.isSet("btntoerr"))
		qDebug()<<QMessageBox::StandardButton(data.retButton);

	return(data.retval);
}
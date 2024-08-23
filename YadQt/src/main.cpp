
#include "globals.h"
#include "config.h"

int main(int argc, char **argv)
{
	QApplication			app(argc,argv);

	DataClass			data;
	InfoBoxClass			info(&app,&data);
	InputDialogsClass	input(&app,&data);
	FormsClass			forms(&app,&data);
	ListBoxClass			list(&app,&data);
	FilesClass			files(&app,&data);
	OrphanDialogClass	orphans(&app,&data);

	unsigned				retval=0;

	app.setApplicationVersion(VERSION);
	data.parser.addHelpOption();
	data.parser.addVersionOption();
	data.parser.addOptions(
		{
			{{"t","title"},"Title.","YadQt"},
			{{"b","body"},"Body.","Information"},
			{{"d","default"},"Default text ( lists, forms etc ).",QDir::home().dirName()},
			{"fromstdin","Read default data from stdin."},
			{"width","Dialog width ( set to 0 for default size for dialog ).","640"},
			{"height","Dialog height ( set to 0 for default size for dialog ).","320"},
			{"opseparator","Separator for multi item output ( use \"newline\" to use '\\n' ).","|"},
			{"ipseparator","Separator for multi item default text input ( use \"newline\" to use '\\n' ).","|"},
			{"multiple","Select multiple items ( lists )."},
			{"btntoerr","Print button to stderr."},
			{"buttons","Buttons ( for info boxes ).","Ok"},
			{"type","Box Type ( no type will display aboutbox for Qt ).","aboutqt"},
	});

	app.setWindowIcon(QIcon::fromTheme("user-info"));
	data.parser.process(app.arguments());
	data.title=data.parser.value("title");
	if(data.parser.isSet("fromstdin")==true)
		{
			QTextStream	datastream(stdin);
    			QString		datain = datastream.readAll();
    			datain=LFSTK_UtilityClass::LFSTK_strStrip(datain.toStdString()).c_str();
    			data.defaultText=datain;
		}
	else
		{
			data.defaultText=data.parser.value("default");
		}
	data.body=data.parser.value("body");
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

			switch(data.boxType)
				{
//info boxes
					case ABOUT:
					case ABOUTQT:
					case QUERY:
					case INFO:
					case WARN:
					case FATAL:
						retval=info.showDialog();
						break;

//input boxes
					case GETINPUT:
						retval=input.getTextInput();
						break;
					case GETITEM:
						retval=input.getItem();
						break;
//forms
					case GETFORM:
						if(data.parser.isSet("buttons")==false)
							data.dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Ok|(unsigned int)QDialogButtonBox::Cancel);
						retval=forms.getForm();
						break;
//list
					case GETLIST:
						if(data.parser.isSet("buttons")==false)
							data.dbutton=QDialogButtonBox::Ok;
						retval=list.getList();
						break;
//files
					case SHOWTEXTFILE:
						if(data.parser.isSet("buttons")==false)
							data.dbutton=QDialogButtonBox::Ok;
						retval=files.showTextFile(true);
						break;
					case GETTEXT:
						if(data.parser.isSet("buttons")==false)
							data.dbutton=QDialogButtonBox::Ok;
						retval=files.showTextFile(false);
						break;
					case SHOWIMAGEFILE:
						if(data.parser.isSet("buttons")==false)
							data.dbutton=QDialogButtonBox::Ok;
							retval=files.showImageFile();
						break;
//orphans
					case GETCOLOUR:
						retval=orphans.getColour();
						break;
					case GETFONT:
						retval=orphans.getFont();
						break;
				}
		}
	else
		{
			data.boxType=ABOUTQT;
			retval=info.showDialog();
		}

	if(data.parser.isSet("btntoerr"))
		qDebug()<<QMessageBox::StandardButton(retval);

	switch(retval)
		{
			case QMessageBox::Ok:
			case QMessageBox::Open:
			case QMessageBox::Save:
			case QMessageBox::Close:
			case QMessageBox::Apply:
			case QMessageBox::Reset:
			case QMessageBox::RestoreDefaults:
			case QMessageBox::Help:
			case QMessageBox::SaveAll:
			case QMessageBox::Yes:
			case QMessageBox::YesToAll:
			case QMessageBox::Retry:
			case QMessageBox::Ignore:

				retval=0;
				break;
			case QMessageBox::Cancel:
			case QMessageBox::No:
			case QMessageBox::NoToAll:
			case QMessageBox::Abort:
				retval=1;
				break;
			default:
				retval=1;
				break;
		}

	return(retval);
}
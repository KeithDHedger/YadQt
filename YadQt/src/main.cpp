
#include "globals.h"
#include "config.h"

int main(int argc, char **argv)
{
	QApplication			app(argc,argv);

	InfoBoxClass			info(&app);
	DataClass			data;
	InputDialogsClass	input(&app,&data);
	FormsClass			forms(&app,&data);
	ListBoxClass			list(&app,&data);
	FilesClass			files(&app,&data);

	unsigned				retval=0;

	app.setApplicationVersion(VERSION);
	data.parser.addHelpOption();
	data.parser.addVersionOption();
	data.parser.addOptions(
		{
			{{"t","title"},"Title.","YadQt"},
			{{"b","body"},"Body.","Information"},
			{{"d","default"},"Default text.",QDir::home().dirName()},
			{"width","Dialog width.","0"},
			{"height","Dialog height.","0"},
			{"opseparator","Separator for multi item output ( use \"newline\" to use '\\n' ).","|"},
			{"multiple","Select multiple items."},
			{"btntoerr","Print button to stderr."},
			{"buttons","Buttons.","Ok"},
			{"type","Box Type.","aboutqt"},
	});

	app.setWindowIcon(QIcon::fromTheme("user-info"));
	data.parser.process(app.arguments());
	data.title=data.parser.value("title");
	data.defaultText=data.parser.value("default");
	data.body=data.parser.value("body");
	data.width=data.parser.value("width").toInt();
	data.height=data.parser.value("height").toInt();
	if(data.parser.isSet("opseparator"))
		{
			if(data.parser.value("opseparator").compare("newline")==0)
				data.opsep="\n";
			else
				data.opsep=data.parser.value("opseparator");
		}
	if(data.parser.isSet("type"))
		{
			data.getBoxType();
			switch(data.boxType)
				{
//info boxes
					case ABOUT:
					case ABOUTQT:
					case WHAT:
					case INFO:
					case WARN:
					case FATAL:
						{
							data.setButtons();
							info.data=&data;
							retval=info.showDialog();
						}
						break;

//input boxes
					case GETTEXT:
						{
							retval=input.getTextInput();
						}
						break;
					case GETITEM:
						{
							retval=input.getItem();
						}
						break;
//forms
					case GETFORM:
						{
							retval=forms.getForm();
						}
						break;
//list
					case GETLIST:
						{
							retval=list.getList();
						}
						break;
//files
					case SHOWTEXTFILE:
						{
							retval=files.showTextFile();
						}
						break;
				}
		}
	else
		{
			data.boxType=ABOUTQT;
			info.data=&data;
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
				retval=0;
				break;
			case QMessageBox::Cancel:
			case QMessageBox::No:
			case QMessageBox::NoToAll:
			case QMessageBox::Abort:
			case QMessageBox::Ignore:
				retval=1;
				break;
			default:
				retval=1;
				break;
		}

	return(retval);
}
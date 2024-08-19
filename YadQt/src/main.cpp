
#include "globals.h"

int main(int argc, char **argv)
{
	QApplication			app(argc,argv);

	InfoBoxClass			info(&app);
	DataClass			data;
	InputDialogsClass	input(&app,&data);

	unsigned				retval=0;

	data.parser.addHelpOption();
	data.parser.addOptions(
		{
			{{"t","title"},"Title.","YadQt"},
			{{"b","body"},"Body.","Information"},
			{{"d","default"},"Default text.",QDir::home().dirName()},
			{"width","Dialog width.","640"},
			{"height","Dialog height.","400"},
			{"btntoerr","Print button to stderr."},
			{"buttons","Buttons.","Ok"},
			{"type","Box Type.","about"},
	});

	app.setWindowIcon(QIcon::fromTheme("user-info"));
	data.parser.process(app.arguments());
	data.title=data.parser.value("title");
	data.defaultText=data.parser.value("default");
	data.body=data.parser.value("body");
	data.width=data.parser.value("width").toInt();
	data.height=data.parser.value("height").toInt();
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
				}
		}
	else
		{
		
			qDebug()<<"You need to set a box type ...";
			return(-1);
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

#include "globals.h"

int main(int argc, char **argv)
{
	QApplication			app(argc,argv);

	InfoBoxClass			info(&app);
	DataClass			data;
	int					retval=0;

	data.parser.addHelpOption();
	data.parser.addOptions(
		{
			{{"t","title"},"Title.","YadQt"},
			{{"b","body"},"Body.","Information"},
			{"width","Dialog Width.","640"},
			{"height","Dialog Height.","400"},
			{"buttons","Buttons.","Ok"},
			{"type","Box Type.","about"},
	});

	app.setWindowIcon(QIcon::fromTheme("user-info"));
	data.parser.process(app.arguments());
	data.title=data.parser.value("title");
	data.body=data.parser.value("body");
	data.width=data.parser.value("width").toInt();
	data.height=data.parser.value("height").toInt();
	if(data.parser.isSet("type"))
		{
			data.getBoxType();
			switch(data.boxType)
				{
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
				}
		}
	else
		{
			qDebug()<<"You need to set a box type ...";
			return(-1);
		}

	qDebug()<<QMessageBox::StandardButton(retval);
	return(retval);
}
/*
 *
 * ©K. D. Hedger. Tue 20 Aug 20:21:24 BST 2024 keithdhedger@gmail.com

 * This file (OrphanDialogClass.cpp) is part of YadQt.

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

#include "OrphanDialogClass.h"

OrphanDialogClass::OrphanDialogClass(QApplication *app,DataClass *data)
{
	this->data=data;
	this->app=app;
}

OrphanDialogClass::~OrphanDialogClass()
{
}

void OrphanDialogClass::getColour(void)
{
	QColor	initcol(this->data->defaultText);
	QColor	colour;

	if(this->data->defaultText.length()>7)
		colour=QColorDialog::getColor(initcol,nullptr,this->data->title,QColorDialog::ShowAlphaChannel);
	else
		colour=QColorDialog::getColor(initcol,nullptr,this->data->title);

	if(colour.isValid()==true)
		{
			if(this->data->defaultText.length()>7)
				QTextStream(stdout) <<colour.name(QColor::HexArgb)<< Qt::endl;
			else
				QTextStream(stdout) <<colour.name()<< Qt::endl;
			this->data->retButton=QMessageBox::Ok;
			this->data->retval=0;
		}
	else
		{
			this->data->retButton=QMessageBox::Cancel;
			this->data->retval=1;
		}
}

void OrphanDialogClass::getFont(void)
{
	bool		ok;
	QFont	tfont;
	QFont	font;

	tfont.fromString(this->data->defaultText);
	font=QFontDialog::getFont(&ok,tfont,nullptr,this->data->title);
	if(ok==true)
		{
			QTextStream(stdout) <<font.toString()<< Qt::endl;
			this->data->retButton=QMessageBox::Ok;
			this->data->retval=0;
		}
	else
		{
			this->data->retButton=QMessageBox::Cancel;
			this->data->retval=1;
		}
}

void OrphanDialogClass::tailBox(void)
{
	QPlainTextEdit	*thetext;
	QVBoxLayout		*docvlayout=new QVBoxLayout;
	QString			boxtext="";
	QTextBlock		block;
	QTextCursor		cursor;
	int				available_bytes=-1;
	QTextStream		datastream(stdin);
	QString			datain="";

	this->data->theDialog=new QDialog();
	thetext=new QPlainTextEdit(nullptr);
	thetext->setReadOnly(true);

	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(thetext);
	docvlayout->addWidget(this->data->bb);
	this->data->theDialog->setLayout(docvlayout);

	this->data->theDialog->setWindowTitle(this->data->title);

	if(this->data->customSize==true)
		this->data->theDialog->resize(QSize(this->data->width,this->data->height));

	this->data->theDialog->show();
	this->data->retval=-1;

	fcntl(0,F_SETFL,fcntl(0, F_GETFL) | O_NONBLOCK);
	while(this->data->retval<0)
		{
			this->app->processEvents();
			usleep(10000);
			ioctl(0,FIONREAD,&available_bytes);
			if(available_bytes>0)
				{
    					datain=datastream.readAll();
    					if(datain.isEmpty()==false)
						{
							boxtext+=QString(datain);
							thetext->setPlainText(boxtext);
							block=thetext->document()->lastBlock();
							cursor=thetext->textCursor();
							cursor.setPosition(block.position());
							thetext->setTextCursor(cursor);
						}    				
				}
		}
}

void OrphanDialogClass::notePad(void)
{
	QPlainTextEdit	*thetext;
	QVBoxLayout		*docvlayout=new QVBoxLayout;

	this->data->theDialog=new QDialog();
	thetext=new QPlainTextEdit(nullptr);

	QFile file(this->data->defaultText);
	file.open(QFile::ReadOnly | QFile::Text);
	thetext->setPlainText(file.readAll());
	file.close();

	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(thetext);

	this->data->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Save|(unsigned int)QDialogButtonBox::Discard);
	this->data->bb->setStandardButtons(this->data->dbutton);
	docvlayout->addWidget(this->data->bb);
	this->data->theDialog->setLayout(docvlayout);

//HMmmmmm
//	if(this->data->parser.isSet("title")==false)
//		this->data->title=this->data->defaultText;

	this->data->theDialog->setWindowTitle(this->data->title);
	
	if(this->data->customSize==true)
		this->data->theDialog->resize(QSize(this->data->width,this->data->height));

	this->data->theDialog->exec();
	if(this->data->retval==0)
		{
			if(file.open(QIODevice::ReadWrite))
				{
					QTextStream(&file) << thetext->toPlainText() << Qt::endl;
					file.close();
				}
		}
}
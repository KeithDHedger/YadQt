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
#include<QColor>

OrphanDialogClass::OrphanDialogClass(QApplication *app,DataClass *data)
{
	this->data=data;
}

OrphanDialogClass::~OrphanDialogClass()
{
}

unsigned OrphanDialogClass::getColour(void)
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
			return(QMessageBox::Ok);	
		}
	return(QMessageBox::Cancel);	
}

unsigned OrphanDialogClass::getFont(void)
{
	bool		ok;
	QFont	tfont;
	QFont	font;

	tfont.fromString(this->data->defaultText);
	font=QFontDialog::getFont(&ok,tfont,nullptr,this->data->title);
	if(ok==true)
		{
			QTextStream(stdout) <<font.toString()<< Qt::endl;
			return(QMessageBox::Ok);	
		}

	return(QMessageBox::Cancel);	
}

//unsigned OrphanDialogClass::getText(void)
//{
//	QPlainTextEdit		*thetext;
//	QDialog				*theDialog;
//	QWidget				*hbox;
//	QVBoxLayout			*docvlayout=new QVBoxLayout;
//	QHBoxLayout			*hlayout;
//	QPushButton			*okbutton=new QPushButton("&Ok");
//
//	theDialog=new QDialog();
//
//	QObject::connect(okbutton,&QPushButton::clicked,[this,theDialog]()
//		{
//			theDialog->accept();
//		});
//
//	thetext=new QPlainTextEdit(nullptr);
//	thetext->setReadOnly(true);
//	thetext->setPlainText(this->data->defaultText);
//
//	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
//	docvlayout->addWidget(thetext);
//
//	hbox=new QWidget;
//	hlayout=new QHBoxLayout;
//	hlayout->setContentsMargins(0,0,0,0);
//	hbox->setLayout(hlayout);
//	hlayout->addStretch(1);
//	hlayout->addWidget(okbutton);
//
//	docvlayout->addWidget(hbox);
//
//	theDialog->setLayout(docvlayout);
//	theDialog->setWindowTitle(this->data->title);
//
//	if(this->data->customSize==true)
//		theDialog->resize(QSize(this->data->width,this->data->height));
//
//	theDialog->exec();
//	return(QMessageBox::Ok);
//}

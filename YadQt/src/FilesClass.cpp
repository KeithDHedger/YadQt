/*
 *
 * ©K. D. Hedger. Tue 20 Aug 12:07:17 BST 2024 keithdhedger@gmail.com

 * This file (FilesClass.cpp) is part of YadQt.

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

#include "FilesClass.h"

FilesClass::~FilesClass()
{
}

FilesClass::FilesClass(QApplication *app,DataClass *data)
{
	this->data=data;
}

unsigned FilesClass::showTextFile(void)
{
	QPlainTextEdit		*thetext;
	QDialog				*theDialog;
	QWidget				*hbox;
	QVBoxLayout			*docvlayout=new QVBoxLayout;
	QHBoxLayout			*hlayout;
	QPushButton			*okbutton=new QPushButton("&Ok");

	theDialog=new QDialog();

	QObject::connect(okbutton,&QPushButton::clicked,[this,theDialog]()
		{
			theDialog->accept();
		});

	thetext=new QPlainTextEdit(nullptr);
	thetext->setReadOnly(true);
	QFile file(this->data->body);
	file.open(QFile::ReadOnly | QFile::Text);
	thetext->setPlainText(file.readAll());
	file.close();

	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(thetext);

	hbox=new QWidget;
	hlayout=new QHBoxLayout;
	hlayout->setContentsMargins(0,0,0,0);
	hbox->setLayout(hlayout);
	hlayout->addStretch(1);
	hlayout->addWidget(okbutton);

	docvlayout->addWidget(hbox);

	theDialog->setLayout(docvlayout);
	theDialog->setWindowTitle(this->data->title);


	if((this->data->width!=0) || (this->data->height!=0))
		theDialog->resize(QSize(this->data->width,this->data->height));

	theDialog->exec();
	return(QMessageBox::Ok);		
}

unsigned FilesClass::showImageFile(void)
{
	QGraphicsScene		scene;
	QGraphicsView		view(&scene);
	QPixmap				pm(this->data->body);
	QGraphicsPixmapItem	item(pm);
  	QDialog				*theDialog;
	QWidget				*hbox;
	QVBoxLayout			*docvlayout=new QVBoxLayout;
	QHBoxLayout			*hlayout;
	QPushButton			*okbutton=new QPushButton("&Ok");

    scene.addItem(&item);
	theDialog=new QDialog();

	QObject::connect(okbutton,&QPushButton::clicked,[this,theDialog]()
		{
			theDialog->accept();
		});

 	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(&view);
	
	hbox=new QWidget;
	hlayout=new QHBoxLayout;
	hlayout->setContentsMargins(0,0,0,0);
	hbox->setLayout(hlayout);
	hlayout->addStretch(1);
	hlayout->addWidget(okbutton);

	docvlayout->addWidget(hbox);

	theDialog->setLayout(docvlayout);
	theDialog->setWindowTitle(this->data->title);

//	if((this->data->width!=0) || (this->data->height!=0))
	if(this->data->customSize==true)
		theDialog->resize(QSize(this->data->width,this->data->height));

	theDialog->exec();
	return(QMessageBox::Ok);
}


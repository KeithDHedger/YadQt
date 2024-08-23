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

unsigned FilesClass::showTextFile(bool file)
{
	QPlainTextEdit				*thetext;
	QDialog						*theDialog;
	QHBoxLayout					*hlayout;
	QMessageBox::StandardButton	i;
	QVBoxLayout					*docvlayout=new QVBoxLayout;
	QDialogButtonBox				bb(this->data->dbutton);

	theDialog=new QDialog();
	thetext=new QPlainTextEdit(nullptr);
	thetext->setReadOnly(true);

	if(file==true)
		{
			QFile file(this->data->defaultText);
			file.open(QFile::ReadOnly | QFile::Text);
			thetext->setPlainText(file.readAll());
			file.close();
		}
	else
		{
			QString items;
			items=QString(LFSTK_UtilityClass::LFSTK_strReplaceAllChar(this->data->defaultText.toStdString(),this->data->ipsep.toStdString(),"\n").c_str());
			thetext->setPlainText(items);
		}

	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(thetext);

	QObject::connect(&bb,&QDialogButtonBox::clicked,[this,theDialog,&bb,&i](QAbstractButton *button)
		{
			theDialog->accept();
			i=QMessageBox::StandardButton(bb.standardButton(button));
		});
	docvlayout->addWidget(&bb);
	theDialog->setLayout(docvlayout);
	theDialog->setWindowTitle(this->data->title);

	if(this->data->customSize==true)
		theDialog->resize(QSize(this->data->width,this->data->height));

	theDialog->exec();
	return(i);		
}

unsigned FilesClass::showImageFile(void)
{
	QGraphicsScene		scene;
	QGraphicsView		view(&scene);
	QPixmap				pm(this->data->defaultText);
	QGraphicsPixmapItem	item(pm);
  	QDialog				*theDialog;
	QVBoxLayout			*docvlayout=new QVBoxLayout;
	QDialogButtonBox		bb(this->data->dbutton);
	QMessageBox::StandardButton	i;

    scene.addItem(&item);
	theDialog=new QDialog();

	QObject::connect(&bb,&QDialogButtonBox::clicked,[this,theDialog,&bb,&i](QAbstractButton *button)
		{
			theDialog->accept();
			i=QMessageBox::StandardButton(bb.standardButton(button));
		});

 	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(&view);
	
	docvlayout->addWidget(&bb);

	theDialog->setLayout(docvlayout);
	theDialog->setWindowTitle(this->data->title);

	if(this->data->customSize==true)
		theDialog->resize(QSize(this->data->width,this->data->height));

	theDialog->exec();
	return(i);		
}


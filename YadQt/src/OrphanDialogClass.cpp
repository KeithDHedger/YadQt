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

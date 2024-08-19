/*
 *
 * ©K. D. Hedger. Sun 18 Aug 15:36:19 BST 2024 keithdhedger@gmail.com

 * This file (InputDialogsClass.cpp) is part of YadQt.

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

#include "InputDialogsClass.h"

InputDialogsClass::InputDialogsClass(QApplication *app,DataClass *data)
{
	this->data=data;
}

InputDialogsClass::~InputDialogsClass()
{
}

unsigned InputDialogsClass::getItem(void)
{
	QStringList	items;
	bool			ok;

	std::vector<std::string> names=LFSTK_UtilityClass::LFSTK_strTok(this->data->defaultText.toStdString(),std::string("|"));
	for(long unsigned int j=0;j<names.size();j++)
		items<<names.at(j).c_str();

	QString item=QInputDialog::getItem(nullptr,this->data->title,this->data->body,items,0,false,&ok);
		if(ok==true)
			{
				QTextStream(stdout) <<item<< Qt::endl;
				return(QMessageBox::Ok);
			}
	return(QMessageBox::Cancel);
}

unsigned InputDialogsClass::getTextInput(void)
{ 
	bool		ok;
	QString text=QInputDialog::getText(nullptr,this->data->title,this->data->body,QLineEdit::Normal,this->data->defaultText,&ok);
	if(ok==true)
		{
			QTextStream(stdout) <<text<< Qt::endl;
			return(QMessageBox::Ok);
		}
	return(QMessageBox::Cancel);
}

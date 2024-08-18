/*
 *
 * ©K. D. Hedger. Sat 17 Aug 12:29:43 BST 2024 keithdhedger@gmail.com

 * This file (InfoBoxClass.cpp) is part of YadQt.

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

#include "QT_InfoBoxClass.h"

#ifndef moc_InfoBoxClass
#include "moc_QT_InfoBoxClass.cpp"
#define moc_InfoBoxClass
#endif

InfoBoxClass::InfoBoxClass(QApplication *app)
{
}

InfoBoxClass::~InfoBoxClass()
{
}

int InfoBoxClass::showDialog(void)
{
	int retval=-1;

	switch(data->boxType)
		{
			case ABOUT:
				QMessageBox::about(nullptr,this->data->title,this->data->body);
				break;
			case ABOUTQT:
				QMessageBox::aboutQt(nullptr);
				break;
			case WHAT:
				retval=QMessageBox::question(nullptr,this->data->title,this->data->body,this->data->buttons);
				break;
			case INFO:
				retval=QMessageBox::information(nullptr,this->data->title,this->data->body,this->data->buttons);
				break;
			case WARN:
				retval=QMessageBox::warning(nullptr,this->data->title,this->data->body,this->data->buttons);
				break;
			case FATAL:
				retval=QMessageBox::critical(nullptr,this->data->title,this->data->body,this->data->buttons);
				break;			
		}
	return(retval);
}

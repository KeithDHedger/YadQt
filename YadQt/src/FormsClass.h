/*
 *
 * ©K. D. Hedger. Mon 19 Aug 12:27:27 BST 2024 keithdhedger@gmail.com

 * This file (FormsClass.h) is part of YadQt.

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


#ifndef _FORMSCLASS_
#define _FORMSCLASS_

#include "globals.h"

struct miniPrefsReturnStruct
{
	QDialog					*theDialog;
	QHash<int,QLineEdit*>	boxes;
};

class FormsClass
{
	public:
		FormsClass(QApplication *app,DataClass *data);
		~FormsClass();

		DataClass	*data;

		unsigned		getForm(void);

	private:
		miniPrefsReturnStruct	miniPrefsDialog(QStringList items);

};

#endif

/*
 *
 * ©K. D. Hedger. Mon 19 Aug 14:04:18 BST 2024 keithdhedger@gmail.com

 * This file (ListBoxClass.h) is part of YadQt.

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

#ifndef _LISTBOXCLASS_
#define _LISTBOXCLASS_

#include "globals.h"

class ListBoxClass
{
	public:
		ListBoxClass(QApplication *app,DataClass *data);
		~ListBoxClass();

	void								getList(void);

	private:
		DataClass					*data;
		QMessageBox::StandardButton	retButton;
};

#endif

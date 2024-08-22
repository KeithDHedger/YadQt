/*
 *
 * ©K. D. Hedger. Tue 20 Aug 20:21:31 BST 2024 keithdhedger@gmail.com

 * This file (OrphanDialogClass.h) is part of YadQt.

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


#ifndef _ORPHANDIALOGCLASS_
#define _ORPHANDIALOGCLASS_

#include "globals.h"

class OrphanDialogClass
{
	public:
		OrphanDialogClass(QApplication *app,DataClass *data);
		~OrphanDialogClass();

		unsigned getColour(void);
		unsigned getFont(void);
		//unsigned getText(void);

	private:
		DataClass	*data;
};

#endif

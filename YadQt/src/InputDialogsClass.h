/*
 *
 * ©K. D. Hedger. Sun 18 Aug 15:36:11 BST 2024 keithdhedger@gmail.com

 * This file (InputDialogsClass.h) is part of YadQt.

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

#ifndef _INPUTDIALOGSCLASS_
#define _INPUTDIALOGSCLASS_

#include "globals.h"

class InputDialogsClass
{
	public:
		InputDialogsClass(QApplication *app,DataClass *data);
		~InputDialogsClass();

		unsigned		getTextInput(void);
		unsigned		getItem(void);

	private:
		DataClass	*data;

};

#endif

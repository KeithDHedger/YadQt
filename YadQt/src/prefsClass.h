/*
 *
 * ©K. D. Hedger. Fri  1 Nov 13:52:32 GMT 2024 keithdhedger@gmail.com

 * This file (prefsClass.h) is part of Classes-DEV.

 * Classes-DEV is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Classes-DEV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Classes-DEV.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _PREFSCLASS_
#define _PREFSCLASS_

#include <QApplication>
#include <QtWidgets>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDialog>

#include <stdio.h>

#define RITESTRETCH 2

struct prefsReturnStruct
{
//simple
	QDialog					*theDialog=NULL;
	QHash<int,QLineEdit*>	editBoxes;
	QHash<int,QString>		editBoxesPrefsName;
	int						editBoxCnt=0;
	QHash<int,QComboBox*>	comboBoxes;
	QHash<int,QString>		comboBoxesPrefsName;
	int						comboBoxCnt=0;
	QHash<int,QCheckBox*>	checkBoxes;
	QHash<int,QString>		checkBoxesPrefsName;
	int						checkBoxCnt=0;
	QHash<int,QDoubleSpinBox*>		spinBoxes;
	QHash<int,QString>		spinBoxesPrefsName;
	int						spinBoxCnt=0;

//compound
	QHash<int,QLineEdit*>	colourBoxes;
	QHash<int,QString>		colourBoxesPrefsName;
	int						colourBoxCnt=0;
	QHash<int,QLineEdit*>	fontBoxes;
	QHash<int,QString>		fontBoxesPrefsName;
	int						fontBoxCnt=0;
	QHash<int,QLineEdit*>	fileBoxes;
	QHash<int,QString>		fileBoxesPrefsName;
	int						fileBoxCnt=0;

	bool						valid=false;
};

class prefsClass
{
	public:
		prefsClass();
		~prefsClass();

	prefsReturnStruct		dialogPrefs;
	QHash<int,QVariant>		prefsData;
	QStringList				prefsNames;
	bool						paged=false;
	void						createDialog(QString title,QStringList items,QSize sze=QSize(-1,-1));

	void						setPrefs(QStringList items);
	void						setPrefValue(QString name,QVariant val);
	QVariant					getPrefValue(QString name);
	void						writePrefs(void);
	void						readPrefs(void);

	protected:
	private:
		unsigned long		hashFromKey(QString key);
		QString				bestFontColour(QString colour);
};

#endif
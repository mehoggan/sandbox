/*
 * armylistcontainer.cpp
 *
 *  Created on: Jul 27, 2009
 *      Author: Matthew
 */

#include <QtAlgorithms>
#include "armylistcontainer.h"
#include <iostream>

using namespace std;

ArmyListContainer::ArmyListContainer()
{
	vector = new QVector<QString>();
	QString armies_Array[15] = {"Dwarfs", "Orcs & Goblins", "The Empire", "High Elves",
			"Dark Elves", "Wood Elves", "Skaven", "Beasts of Chaos",
			"Lizardmen", "Vampire Counts", "Tomb Kings", "Bretonnia", "Ogre Kingdoms",
			"Warriors of Chaos", "Daemons of Chaos"};
	for(int x = 0; x < 15; x++)
	{
		vector->insert(x, armies_Array[x]);
	}
	qSort(vector->begin(), vector->end());
}

ArmyListContainer::~ArmyListContainer()
{
}

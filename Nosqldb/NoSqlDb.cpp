/////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - key/value pair in-memory database                 //
// ver 1.2                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////

#include "NoSqlDb.h"
#include <iostream>

#ifdef TEST_NOSQLDB

using namespace NoSQLDB;
using StrData = std::string;
using intData = int;

int main()
{

	NoSqlDb<StrData> db;

	Element<StrData> elem1;
	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";

	db.saveRecord(elem1.name, elem1);

	Element<StrData> elem2;
	elem2.name = "elem2";
	elem2.category = "test";
	elem2.data = "elem2's StrData";

	db.saveRecord(elem2.name, elem2);

	Element<StrData> elem3;
	elem3.name = "elem3";
	elem3.category = "test";
	elem3.data = "elem3's StrData";

	db.saveRecord(elem3.name, elem3);

	elem1.saveChild(elem2.name);
	elem1.saveChild(elem3.name);
	elem2.saveChild(elem3.name);
	db.saveValue(elem1.name, elem1);
	db.saveValue(elem2.name, elem2);
	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}

	std::cout << "\n  Erasing element with key elem2";
	if (db.removeRecord("elem2"))
		std::cout << "\n  removed record and all children references to this record";
	std::cout << "\n  size of db = " << db.count() << "\n";
	keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
}
#endif

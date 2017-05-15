#pragma once
///////////////////////////////////////////////////////////////////
// Publisher - Define a class to generate html files             //
// Ver 1.0                                                       //
// Application: CSE687 Pr#3, Spring 2017                         //
// Platform:    Dell XPS 2720, Win 10 Pro, Visual Studio 2015   //
// Author:      Xia Hua                                         //
//              xhua02@syr.edu                                  //
/////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is to define Publisher class, it has to do the analysis and generate html files.
*
Class
---------------------------------
* Publisher

improtant functions
---------------------------------
//--------keys or key operation
void constrHtml();                                                 ------construct html file for each *.h and *.cpp
void constrBody(std::string fielname, std::string filepath);       ------construct body part of a html, read from original files
std::string addExpand(std::string s);                              ------analysis content of file, tell from comment ,"" and '', decide wether add expand part
void constrHead(std::string s);                                    ------construct head part of a html
void constrDepend(std::vector<std::string> vec, std::string s);    ------construct dependency part of a html
void constrEnd(std::string s);                                     ------construct end part of a html
void setPath(std::string path);                                    ------set path
void setFiles(std::vector<std::string> filepara);                  ------initialise files we need to generate to html
std::string  replaceSpec(std::string s);                           ------replace < and > 
std::string exeCh(std::string s, int i, std::vector<int>& vec, std::string& index);  ------tell character equals to { or } ,and add expand part
bool  isValid(std::string s);                                      ------test if the { or } belongs to class, methord and global function
void constrIndexHtml(std::vector<std::string> files);              ------construct the index html

* Required Files:
* ---------------
*   -NoSqlDb.h
*  
* Maintenance History:
* --------------------
* ver 1.0 : 2 April 2017
* - First release
*
*/
#include <iostream>
#include <fstream>
#include "../Nosqldb/NoSqlDb.h"
class Publisher
{
public:
	Publisher(NoSQLDB::NoSqlDb<std::string>* db1)
	{
		db = db1;
	}
	void constrHtml();
	void constrBody(std::string fielname, std::string filepath);
	std::string addExpand(std::string s);
	void constrHead(std::string s);
	void constrDepend(std::vector<std::string> vec, std::string s);
	void constrEnd(std::string s);
	void setPath(std::string path);
	void setFiles(std::vector<std::string> filepara);
	std::string  replaceSpec(std::string s);
	std::string exeCh(std::string s, int i, std::vector<int>& vec, std::string& index);
	bool  isValid(std::string s);
	void constrIndexHtml(std::vector<std::string> files);
	void  requirment12();
	void  requirment4567();
private:
	NoSQLDB::NoSqlDb<std::string>* db;
	std::string dirpath;
	std::vector<std::string> files;
};
//-----------------<initialise files we need to generate to html>-----------
void  Publisher::setFiles(std::vector<std::string> filepara)
{
	files.insert(files.end(), filepara.begin(), filepara.end());
}
//-----------------<set path>--------------
void Publisher::setPath(std::string path)
{
	dirpath = path;
}
//-----------------<construct html file for each *.h and *.cpp>------------
void Publisher::constrHtml()
{
	requirment12();
	std::cout <<"\n"<< "----------requirment3....---------" << "\n";
	std::cout << "----------Html files generating....---------" << "\n";
	int num = 1;
	for (auto tmp : files)
	{
		std::string a = tmp.substr(tmp.find_last_of("\\") + 1);
		constrHead(a);
		constrDepend(db->value(a).children, a);
		constrBody(a, tmp);
		constrEnd(a);
		num++;
		std::cout << a + ".html" << "\n";
	}
	constrIndexHtml(files);
	std::cout << "----------Html file has been generated in ../Html directory, the main page is Index.html---------" << "\n";
	std::cout << "----------there are "<<num<<" html files in total!---------" << "\n";
	requirment4567();
}
//-----------------<construct the index html>------------
void Publisher::constrIndexHtml(std::vector<std::string> vec)
{
	std::string a = dirpath.substr(dirpath.find_last_of("/") + 1);
	constrHead(a+" Index");
	std::ofstream outhead;
	outhead.open("../../Html/"+a+" Index.html", std::ios::app);
	if (vec.size() != 0) {
		outhead
			<< "<div class = \"indent\">" << "\n"
			<< "<h4>"+a+" Index:</h4>" << "\n";
		for (auto c : vec) {
			std::string a = c.substr(c.find_last_of("\\") + 1);
			outhead << "<a href = \"" << a + ".html" << "\">" + a + "</a>" << "\n";
		}
		outhead << "</div>" << "\n"
			<< "<hr/>" << "\n";
	}
	outhead << "<pre>" << "\n";
	outhead.close();
	constrEnd(a + " Index");
}
//-----------------<construct dependency part of a html>------------
void Publisher::constrDepend(std::vector<std::string> vec, std::string s)
{
	std::ofstream outhead;
	outhead.open("../../Html/" + s + ".html", std::ios::app);
	if (vec.size() != 0) {
		outhead
			<< "<div class = \"indent\">" << "\n"
			<< "<h4>Dependencies:</h4>" << "\n";
		for (auto c : vec) {
			outhead << "<a href = \"" << c + ".html" << "\">" + c + "</a>" << "\n";
		}
		outhead << "</div>" << "\n"
			<< "<hr/>" << "\n";
	}
	outhead << "<pre>" << "\n";
	
	outhead.close();
}
//-----------------<construct head part of a html>------------
void Publisher::constrHead(std::string s)
{
	std::ofstream outhead;

	outhead.open("../../Html/" + s + ".html");
	//std::string sourcefile;
	outhead << "<html>" << "\n" << "<head>" << "\n" << "<style>" << "\n"
		<< "body{" << "\n"
		<< "margin: 20px;" << "\n"
		<< "color: black;" << "\n"
		<< "background - color: #eee;" << "\n"
		<< "font - family: Consolas;" << "\n"
		<< "font - weight: 600;" << "\n"
		<< "font - size: 110 % ;}" << "\n";

	outhead << ".indent{ margin - left: 20px; margin - right: 20px;}" << "\n";
	outhead << "h4{margin - bottom: 3px;margin - top: 3px;}" << "\n";
	outhead << "</style>" << "\n";
	outhead << "<script src=\"Myfuc.js\">"
		<< "</script>" << "\n";
	outhead << "<style>"
		<< "div{ display:inline }"
		<< "</style>";
	outhead << "</head>" << "\n";
	outhead << "<body>" << "\n";
	outhead << "<h3>" << s << "</h3>" << "\n" << "<hr/>" << "\n";
	outhead.close();
}
//-----------------<construct end part of a html>------------
void Publisher::constrEnd(std::string s)
{
	std::ofstream outend;
	outend.open("../../Html/" + s + ".html", std::ios::app);
	outend << "</pre>" << "\n"
		<< "</body>" << "\n"
		<< "</html>" << "\n";
	outend.close();
}
//-----------------<construct body part of a html>------------
void Publisher::constrBody(std::string fielname, std::string filepath)
{

	std::ifstream in;
	in.open(filepath);
	std::string sourcefile;
	std::ofstream out;
	out.open("../../Html/" + fielname + ".html", std::ios::app);

	while (!in.eof())
	{

		char arrstr[2048];
		in.getline(arrstr, 2000);
		sourcefile.append(arrstr);
		sourcefile += '\n';
	}
	std::string nospec = replaceSpec(sourcefile);
	//std::cout << nospec;
	//std::cout << "\n" << fielname << "****************\n";
	std::string finalstr = addExpand(nospec);

	out << finalstr;
	out.close();
	in.close();

}

//-----------------<analysis content of file, tell from comment ,"" and '', decide wether add expand part>------------
std::string Publisher::addExpand(std::string s)
{
	std::string index = "a"; bool isSpec = false; bool isFirstdouble = false; bool isFirstsingle = false; std::vector<int> vec; //vec.resize(500);
	std::string s1; bool isFirstcomm = false; bool isFirstlinecomm = false;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '/'&&s[i + 1] == '/'&&isFirstdouble == false && isFirstsingle == false && isFirstcomm == false && isFirstlinecomm == false)
		{
			isSpec = true; s1 += s[i]; isFirstlinecomm = true; continue;
		}
		if (s[i] == '\n'&&isFirstdouble == false && isFirstsingle == false && isFirstcomm == false && isFirstlinecomm == true)
		{
			isSpec = false; s1 += s[i]; isFirstlinecomm = false; continue;
		}
		if (s[i] == '/'&&s[i + 1] == '*'&&isFirstdouble == false && isFirstsingle == false && isFirstcomm == false)
		{
			isSpec = true; s1 += s[i];  isFirstcomm = true; continue;
		}
		if (s[i] == '*'&&s[i + 1] == '/'&&isFirstdouble == false && isFirstsingle == false && isFirstcomm == true)
		{
			isSpec = false; s1 += s[i]; isFirstcomm = false; continue;
		}
		if (s[i] == '\''&&s[i - 1] != '\\' && isFirstdouble == false && isFirstcomm == false && isFirstlinecomm == false)
		{
			if (isFirstsingle == false)
			{isFirstsingle = true; isSpec = true;}
			else
			{isFirstsingle = false; isSpec = false;}
			s1 += s[i];continue;
		}
		if (s[i] == '\''&&s[i - 1] == '\\'&&s[i - 2] == '\\'&&isFirstdouble == false && isFirstsingle == true && isFirstcomm == false && isFirstlinecomm == false)
		{isFirstsingle = false; isSpec = false; s1 += s[i]; continue;}
		if (s[i] == '"'&&s[i - 1] != '\\'&& isFirstsingle == false && isFirstcomm == false && isFirstlinecomm == false)
		{
			if (isFirstdouble == false) { isFirstdouble = true; isSpec = true; }
			else
			{isFirstdouble = false; isSpec = false;}
			s1 += s[i];continue;
		}
		if (s[i] == '"'&&s[i - 1] == '\\'&&s[i - 2] == '\\'&&isFirstdouble == true && isFirstsingle == false && isFirstcomm == false && isFirstlinecomm == false)
		{isFirstdouble = false; isSpec = false; s1 += s[i]; continue;}
		if (isSpec == false){s1 += exeCh(s, i, vec, index);continue;}
		s1 += s[i];
	}
	return s1;
}
//-----------------<tell character equals to { or } ,and add expand part>------------
std::string  Publisher::exeCh(std::string s, int i, std::vector<int>& vec, std::string& index)
{
	std::string s2;
	switch (s[i]) {
	case '{':
	{
		std::string prefix;
		for (int a = i - 60; a < i; a++)
		{
			prefix += s[a];
		}
		if (isValid(prefix))
		{
			if (vec.size() == 0) {
				s2 += "<div class = \"wrapper\">";
				s2 += "<span  style=\"width:30px; height:20px; color:red;\"  onclick=\"ShowIt(" + index + ")\">+</span>";
				s2 += "</div><section id = \"" + index + "\">";
				s2 += s[i]; index += "a"; vec.push_back(1);
			}
			else if (vec.back() == 0) {
				vec.push_back(0); s2 += s[i];
			}
			else if (vec.back() == 1) {
				s2 += "<div class = \"wrapper\">";
				s2 += "<span  style=\"width:30px; height:20px; color:red;\"  onclick=\"ShowIt(" + index + ")\">+</span>";
				s2 += "</div><section id = \"" + index + "\">";
				s2 += s[i]; index += "a"; vec.push_back(1);
			}
		}
		else {
			vec.push_back(0); s2 += s[i];
		}
		break;
	}
	case '}':
	{
		s2 += s[i];
		if (vec.back() == 1) s2 += "</section>";
		if (vec.size()>0)vec.pop_back();
		break;
	}
	default:
		s2 += s[i];
	}
	return s2;
}
//-----------------<replace character < and > >------------
std::string  Publisher::replaceSpec(std::string s)
{
	std::string s3;
	for (int i = 0; i < s.length(); i++)
	{
		switch (s[i]) {
		case '<':
			s3 += "&lt;";
			break;
		case '>':
			s3 += "&gt;";
			break;
		default:
			s3 += s[i];
		}
	}
	return s3;
}
//-----------------<test if the { or } belongs to class, methord and global function >------------
bool  Publisher::isValid(std::string s)
{
	if (s.find("class") < 60 || s.find("namespace") < 60 || s.find("struct") < 60)
	{
		if(s.find("\"class") >200 && s.find("\"namespace") >200 && s.find("\"struct") >200)
			return true;
	}

	else if (s.find("&&") > 200 && s.find("if") > 200 && s.find("for") > 200 && s.find("catch") > 200 && s.find("enum") > 200 && s.find("while") > 200 && s.find("=") > 10 && s.find("try")>200 && s.find("else")>200)
	{
		return true;
	}
	return false;
}
//-----------------<show requirment 2 >------------
void  Publisher::requirment12()
{
	std::cout << "---------Project3 requirment--------"<<"\n";
	std::cout << "---------requirment2--------"<<"\n";
	std::cout << "For example, in AbstrSynTree.cpp, the code is as follow:"<<"\n";
	std::cout << "AbstrSynTree::~AbstrSynTree()" << "\n"
		<< "{" << "\n"
		<< "delete pGlobalNamespace_;"<<"\n"
		<< "}";

}
//-----------------<show requirment 4,5,6,7 >------------
void  Publisher::requirment4567()
{
	std::string s2;
	std::cout <<"\n"<< "---------requirment4,5--------" << "\n";
	std::cout << "Using function to determin if { belongs to class,methords and global function" << "\n";
	std::cout << "Javascript code as followed:" << "\n";
	
	std::cout
		<< "function ShowIt(id) {" << "\n"
		<< "if (id.style.display == \"block\")" << "\n"
		<< "id.style.display = \"none\";" << "\n"
		<< "else" << "\n"
		<< "id.style.display = \"block\";" << "\n"
		<< "};" << "\n";
	std::cout <<"\n"<< "Javascript link in the <head> as followed:" << "\n";
	std::cout << "<script src=\"Myfuc.js\"></script>" << "\n";
	std::cout << "\n" << "span code as followed" << "\n";
	s2 += "<div class = \"wrapper\">";
	s2 += "<span  style=\"width:30px; height:20px; color:red;\"  onclick=\"ShowIt()\">+</span>";
	s2 += "</div><section id = \"\">";
	std::cout << s2;
}
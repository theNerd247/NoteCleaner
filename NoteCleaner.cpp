/*
 * AUTHOR: Noah Harvey
 * NoteCleaner is a basic program that reads a text file
 * that is properly formatted and returns a cleaned up 
 * text file (and/or code files if plausible)
 * The format of the output is in makedown format. 
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//hold a code flag, so if "CODE:" line is found the 
//lines under it will be included in the current file
int code_flag = 0;
string code_file_path;
string code_file_text;
string file_path;

/*
 * writes the given string to the file at given path
 */
inline void writeFile(string filePath, string fileText)
{
	ofstream file (filePath.c_str());
	if(file.is_open())
	{
		file << fileText;
		file.close();
	}
	else 
		cout << "Could not write to file: " << filePath << endl;
}

void debug(string log)
{
	cout << "DEBUG: " << log << endl; 
}

//parses raw text and formats it to markdown
string& parseLine(string line)
{
	short index = 1;
	bool title_flag = true;
	string* output = new string;
	
	//check for code tags first
	if(line.find("END CODE") != string::npos)
	{
		writeFile(code_file_path,code_file_text);
		code_flag = 0;
		code_file_text.clear();
		code_file_path.clear();
		return *output = "";
	}
	else if(code_flag == 1) 
	{
		code_file_text+=line+"\n";
		return *output = "";
	}
	else if(line.find("CODE:") != string::npos)
	{
		code_flag = 1;
		code_file_path = file_path+"/"+line.substr(6);
		*output = "\n**EXAMPLE CODE** See: "+code_file_path;
		return *output;
	}

	//if the line begins with a character then it is a index 1 header. 
	//skip parsing if it is
	if(line.substr(0,1).find_first_of("abcdefghijklmopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
	{
		*output="\n#"+line+"\n";
		return *output;
	}

	if(line[0] == '\n') 
	{
		*output = "";
		return *output;
	}

	//remove index delimiters 
	while(line.find("\t-") != string::npos)
	{
		index++;
		line = line.substr(line.find("\t-")+2);
	}

	//if there is a tab then it's a title - parse it	
	if(line[0] == '\t')
	{
		index++;
		line = line.substr(1);
	}
	else
		title_flag = false;

	//remove the hyphen at the beginning of a note
	if(line[0] == '-')
		line = line.substr(1);

	if(line.find(":") != string::npos)
	{
		int colon_index = line.find(":");
		if(line.find("e.g") != string::npos)
		{
			*output = "    "+line.substr(colon_index+1);
		}
		else if(line.find(";") != string::npos)
		{
			string title = line.substr(0,colon_index);
			string list;
			line = line.substr(colon_index+1);
			while(line.find(";") != string::npos)
			{
				int	semcol_index = line.find(";");
				list+="+ "+line.substr(0,semcol_index)+"\n";
				line = line.substr(semcol_index+1);
			}
			*output = "__"+title+"__"+"\n\n"+list;
		}
		else
		{
			*output = "__"+line.substr(0,colon_index)+"__ - "
				+line.substr(colon_index+1);
		}
		*output = ">"+*output+"  ";
	}
	else if(title_flag == true)
	{
		*output=line;
		for(int i=0;i<index;i++)
			*output = "#"+*output;	
		*output = "\n"+*output+"\n";
	}
	else
	{
		*output = ">"+line+"  ";
	}

	//check for links
	if(output->find(".com") != string::npos || 
		output->find(".org") != string::npos || 
		output->find(".net") != string::npos ||
		output->find(".html") != string::npos ||
		output->find(".edu") != string::npos)
	{
		*output = "<"+*output+">  ";
	}

	return *output;
}

/*
 * returns the raw text of a file from given path
 */
string getFileText(char *filePath)
{
	//allocate a new string to hold the raw text of the file
	string rawText = "";
	//open the file and read each line; parsing the line.
	ifstream file (filePath);
	if(file.is_open())
	{
		while(file.good())
		{
			//use global getline function found in <string>
			//to get the data
			string buffer;
			getline(file,buffer);
			string newLine = parseLine(buffer);
			if(newLine != "")
			rawText+=newLine+'\n';
		}
		return rawText;
	}

	else 
	{
		cout << "file at: " << *filePath << "could not open" << endl;
	}	
}

int main(int argc, char* args[])
{
	//check to make sure that a file path was given
	//if not then terminate program
	if(argc < 2)
	{
		cout << "NoteCleaner requires an argument." <<
				"\n see NoteCleaner --help" << endl;
		return 1;
	}

	//convert the char[] to a string object
	string arg1 (args[1]);	
	if(arg1.compare("--help") == 0)
	{
		cout << "NoteCleaner file_path \n\t file_path - path to the file to clean" << endl;
		return 0;
	}

	else
	{
		file_path = arg1.substr(0,arg1.find_last_of("/"));
		if(arg1.find_last_of("/") == string::npos)
			file_path=".";
		writeFile(arg1+".mkdn",getFileText(args[1]));
	}
}



#include "precompiled.h"

#include "CConfigMgrS.h"

CConfigMgrS::~CConfigMgrS()
/*! @brief Deconstructor
*/
{
	std::map<std::string,DATA>::iterator icur = CConfigMgrS::ConfigMap.begin();

	while (icur != ConfigMap.end())
	{
		// delete any instances of string
		if (icur->second.type == eSTRING)
			delete icur->second.value.s;
		icur++;
	}
}

VALUE CConfigMgrS::GetCfgValue(std::string key)
/*! @brief Look up value in map represented by key
	@param A string that serves as an index into the map

	@return The value stored at the index key
*/
{
	if( CConfigMgrS::ConfigMap.find(key) != CConfigMgrS::ConfigMap.end() )
		return ConfigMap[key].value;
	else
	{
		VALUE vt;
		//vt.type = eINT;
		vt.i = 0;
		return vt;
	}
}

void CConfigMgrS::SetCfgValue(std::string key, DATA data)
/*! @brief Sets the value at the index key
			if the key is not found it is added to the map
			with it's value
	@param String that serves as an index into the map
	@param Structure of type DATA holds type and value
			to be set to key
*/
{
		ConfigMap[key] = data;
}

void CConfigMgrS::ParseConfig(char *configFile)
/*! @brief Parses a file into a map of key(strings) and value(DATA).
	DATA is a struct that stores the type rep by an enum
	and a union that stores the value. Values can be a string, bool,
	double or int.

	@param The location of the file to be parsed
*/

{
	std::FILE *pFile;
	nsl::stringlist vline;		// vector to hold the 'words' of a line
	char buffer [256];		// holds the line to be split into words
	char *first;			// will point to the first time chosen char appears
	DATA data;				// hold value to be stored in map
	
	if (!(pFile = std::fopen(configFile, "r")))
		return;
	else
	{
		// read a line does not include newline
		while (std::fscanf(pFile, "%[^\n]", buffer) != EOF)
		{
			// separate line into stings delimited by colons, spaces or tabs
			vline = nsl::stsplit_chr(buffer, ": \t");
			// disregard everything after #
			if (vline[0] == "#")
			{
				// throw out the newline
				std::fgetc(pFile);
				continue;
			}
			// key is always first string of vector
			std::string key = vline[0];
			// value is bool
			if(!( strcmp(vline[1].c_str(), "yes") ) || 
				!( strcmp(vline[1].c_str(), "on") ) || 
				!( strcmp(vline[1].c_str(), "true") ))
			{
				data.type = eBOOL;
				data.value.b = true;
			}
			else if (!( strcmp(vline[1].c_str(), "no") ) || 
				!( strcmp(vline[1].c_str(), "off") ) || 
				!( strcmp(vline[1].c_str(), "false") ))
			{
				data.type = eBOOL;
				data.value.b = false;
			}
			// value is a string with double quotes
			else if( strpbrk(vline[1].c_str(), "\"") != NULL)
			{
				// compact vector of strings into one string
				std::vector<std::string>::iterator icur = vline.begin();
				icur++;
				int i = 1;
				int ct = 0;
				char tempStr [256];
				
				while(icur != vline.end())
				{					
					strcpy(&tempStr[ct], vline[i].c_str());
					ct += (int)vline[i].size();
					// put spaces between words
					tempStr[ct++] = ' ';
					icur++;
					i++;
				}
				tempStr[--ct] = '\0';
				data.type = eSTRING;
				data.value.s = new std::string;
				*(data.value.s) = tempStr;
			}
			// value is an int if '.' not found
			else if ((first = strpbrk(ccast< char *>(vline[1].c_str()), ".")) == NULL)
			{
				data.type = eINT;
				data.value.i = atoi(vline[1].c_str());
			}
			// value is a double if the first found is same as the last
			else if (first == (strrchr(vline[1].c_str(), '.')))
			{
				data.type = eDOUBLE;
				data.value.d = atof(vline[1].c_str());
			}
			// value is a string, has more than one '.'
			else
			{
				data.type = eSTRING;
				data.value.s = new std::string;
				*(data.value.s) = vline[1];
			}
			SetCfgValue(key,data);//jpetrie changed to fix multiple-parse bug
			//ConfigMap.insert(std::map<std::string, DATA>::value_type(key, data));
			
			// throw newline away
			std::fgetc(pFile);
		}
	}
}
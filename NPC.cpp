#include "NPC.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/regex.hpp>
#include <cstdlib>
#include <ncurses.h>
#include <vector>

NPC::NPC()
{

}

NPC::~NPC()
{
}
char NPC::getSymbol()
{
	return this->symbol;
}
std::string NPC::getName()
{
	return this->name;
}
std::string NPC::getDescription()
{
	return this->description;
}
unsigned char NPC::getColor()
{
	return this->color;
}
unsigned int NPC::getAbilities()
{
	return this->abilities;
}
Dice NPC::getSpeed()
{
	return this->speed;
}
Dice NPC::getDamage()
{
	return this->damage;
}
Dice NPC::getHP()
{
	return this->HP;
}

void NPC::setSymbol(const char c)
{
	this->symbol = c;
	this->symbolSet = true;
}
void NPC::setName(const std::string &str)
{
	this->name = str;
	this->nameSet = true;
}
void NPC::setDescription(const std::string &str)
{
	this->description = str;
	this->descriptionSet = true;
}
void NPC::setColor(const unsigned char color)
{
	this->color = color;
	this->colorSet = true;
}
void NPC::setAbilities(const unsigned int abil)
{
	this->abilities = abil;
	this->abilitiesSet = true;
}
void NPC::setSpeed(const Dice &d)
{
	this->speed = d;
}
void NPC::setDamage(const Dice &d)
{
	this->damage = d;
}
void NPC::setHP(const Dice &d)
{
	this->HP = d;
}


std::ostream &operator<<(std::ostream &o, const NPC &npc)
{
	return o << npc.name << std::endl 
		<< npc.description
		<< npc.symbol << std::endl
		<< npc.color << std::endl//TODO don't print a number
		<< npc.speed << std::endl
		<< npc.abilities << std::endl//TODO don't print a number
		<< npc.HP << std::endl
		<< npc.damage << std::endl;
}

int main(int argc, char *argv[])
{
	std::string path;
	std::string home;
	std::string file = ".rlg229/monsterdef.txt";
	home = getenv("HOME");
	path = home + "/" + file;
	std::ifstream f(path.c_str());
	if (!f)
	{
		std::cerr << "File does not exist" << std::endl;
		return 1;
	}
	std::string line;
	std::getline(f, line);
	if (line != "RLG229 MONSTER DESCRIPTION 1")
	{
		std::cerr << "File has incorrect metadata" << std::endl;
		return 1;
	}
	vector<NPC> monsters;
	NPC monster;
	while (std::getline(f, line))
	{
		//std::cout << line << std::endl;
		std::istringstream iss(line);
		std::string word;
		iss >> word;
		//std::cout << word << " ";
		if (word == "BEGIN")
		{
			iss >> word;
			if (word != "MONSTER")
			{
				std::cerr << "Invalid BEGIN tag" << std::endl;
				continue;
			}
			monster = new NPC;
			std::cout << "New monster made" << std::endl;
		}
		else if (word == "NAME")
		{
			boost::regex regex("NAME (.*)");
			boost::cmatch matches;
			boost::regex_match(line.c_str(), matches, regex);
			std::string str(matches[1]);
			monster->setName(str);
			std::cout << "Set monster's name" << std::endl;
		}
		else if (word == "DESC")
		{
			std::string description;
			std::getline(f, line);
			while (line != ".")
			{
				description += line;
				description += "\n";
				std::getline(f, line);
			}
			monster->setDescription(description);
			std::cout << "Set monster description" << std::endl;
		}
		else if (word == "SYMB")
		{
			char c;
			iss >> c;
			monster->setSymbol(c);
			std::cout << "Set monster symbol" << std::endl;
		}
		else if (word == "COLOR")
		{
			iss >> word;
			unsigned char color;
			if(word=="BLACK") color = COLOR_BLACK;
			else if(word=="RED") color = COLOR_RED;
			else if(word=="GREEN") color = COLOR_GREEN;
			else if(word=="BLUE") color = COLOR_BLUE;
			else if(word=="CYAN") color = COLOR_CYAN;
			else if(word=="YELLOW") color = COLOR_YELLOW;
			else if(word=="MAGENTA") color = COLOR_MAGENTA;
			else if(word=="WHITE") color = COLOR_WHITE;
			monster->setColor(color);
			std::cout << "Set monster color" << std::endl;
		}
		else if (word == "SPEED")
		{
			iss >> word;
			Dice d(word);
			monster->setSpeed(d);
			std::cout << "Set monster speed" << std::endl;
		}
		else if (word == "ABIL")
		{
			unsigned int flags=0;
			while(iss >> word)
			{
				if (word=="TELE")
				{
					flags |= NPC_TELEPATH;
				}
				else if (word=="SMART")
				{
					flags |= NPC_SMART;
				}
				else if (word=="TUNNEL")
				{
					flags |= NPC_TUNNEL;
				}
				else if (word=="PASS")
				{
					flags |= NPC_PASS;
				}
				else
				{
					std::cerr << "Invalid ability: " << word << std::endl;
				}
			}
			std::cout << flags << std::endl;
			monster->setAbilities(flags);
			std::cout << "Set monster Abilities" << std::endl;

		}
		else if (word == "HP")
		{
			iss >> word;
			Dice d(word);
			monster->setHP(d);
			std::cout << "Set monster HP" << std::endl;
		}
		else if (word == "DAM")
		{
			iss >> word;
			Dice d(word);
			monster->setDamage(d);
			std::cout << "Set monster Damage" << std::endl;
		}
		else if (word == "END")
		{
			delete monster;
			if (!monster->isFinished())
			{
				//std::cout << "Monster not finished" << std::endl;
				continue;
			}
			std::cout << *monster << std::endl << std::endl;
			std::cout << "monster finished" << std::endl;
		}
		else
		{
			std::cout << "Found an unexpeded identifier: " << word << std::endl;
			break;
		}
	}
	return 0;
}

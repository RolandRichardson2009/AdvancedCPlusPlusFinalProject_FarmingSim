#include <iostream>//Required for cout statements
#include <memory>//this is required for using smart pointers
#include <fstream>//File handling
#include <string>
#include <thread>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <filesystem>
//This grants entire application to the standard library
using namespace std::literals::chrono_literals;
//This is a base class that is never instantiated.
class GameStructure
{
public:
	virtual void Help() {}
};
//This is a base class that is never instantiated.
class Character : public GameStructure
{
private:
	std::string Name;//private variable for health
	int Gold;
public:
	std::fstream myFile;
	std::string line;
	int currentIndexVar = 1;
	virtual void Help() {}//Empty Help Function
	//set function to set private variable
	virtual void setName(std::string nameVar)
	{
		Name = nameVar;
	}
	virtual void getName()
	{
		std::cout << Name << std::endl;
	}
	virtual void setGold(int goldVar)
	{
		Gold = goldVar;

		remove("playerGold.txt");

		myFile.open("playerGold.txt", std::ios::app);//write
		if (myFile.is_open())
		{
			myFile << Gold << std::endl;
			myFile.close();
		}
		
	}
	virtual int getGold()
	{
		int goldFromFile = 0;

		// creating an ifstream object named file
		std::ifstream file;

		// defining the file path
		std::string pathOfFile = "playerGold.txt";

		// attempting to open the file
		file.open(pathOfFile);
		if(!file)
		{
			// printing the success message
			//std::cout << "File does not exist" << std::endl;
			Gold = 1000;

			remove("playerGold.txt");

			myFile.open("playerGold.txt", std::ios::app);//write
			if (myFile.is_open())
			{
				myFile << Gold << std::endl;
				myFile.close();
			}
			return 1000;
		}
		else
		{
			// printing the error message
			//std::cout << "File exists" << std::endl;

			myFile.open("playerGold.txt", std::ios::in);//read
			if (myFile.is_open())
			{
				std::string line;
				while (getline(myFile, line))
				{
					//std::cout << "Entry " << currentIndexVar << ": ";
					goldFromFile = stoi(line);
					//std::cout << line << std::endl;
					currentIndexVar++;
				}
				currentIndexVar = 1;
				myFile.close();
				return goldFromFile;
			}
			//return CornSeedsVar;
			return 1000;
			//return Gold;
		}

	}
};
class Farm : public GameStructure
{
private:
	bool FarmPlotPlanted[9];
	int FarmPlotGrowthStage[9];
	int Minutes;
	bool s_Finished;//bool for controlling when thread stops
public:
	
	Farm()
	{
		for (int x = 0; x < 9; x++)
		{
			FarmPlotPlanted[x] = false;
			FarmPlotGrowthStage[x] = 0;
		}
		Minutes = 480;
		s_Finished = false;
	}
	void setFarmPlotPlanted(int index, bool farmPlotPlanted)
	{
		FarmPlotPlanted[index] = farmPlotPlanted;
	}
	bool getfarmPlotPlanted(int index)
	{
		return FarmPlotPlanted[index];
	}
	void setFarmPlotGrowthStage(int index, int farmPlotGrowthStage)
	{
		FarmPlotGrowthStage[index] = farmPlotGrowthStage;
	}
	int getFarmPlotGrowthStage(int index)
	{
		return FarmPlotGrowthStage[index];
	}
	std::string processFarmPlot(int index)
	{
		if (getfarmPlotPlanted(index))
		{
			return std::to_string(getFarmPlotGrowthStage(index));
		}
		else
		{
			return " ";
		}
	}
	void setMinutes(int minutes)
	{
		Minutes = minutes;
	}
	int getMinutes()
	{
		return Minutes;
	}
	void startClock()//Function that plays the animation
	{
		while (getThreadFinishedState() == false)
		{
			Minutes = Minutes + 1;
			std::this_thread::sleep_for(0.05s);
		}
	}
	void setThreadFinished(bool finishedState)
	{
		s_Finished = finishedState;
	}
	bool getThreadFinishedState()
	{
		return s_Finished;
	}
	void displayClock(int minutes)
	{
		std::stringstream ss;

		if (minutes < 60 && minutes >= 0)
		{
			ss << std::setw(2) << std::setfill('0') << (minutes % 60);
			std::cout << "Time: " << ((minutes) / 60) + 12 << ":" << ss.str() << " AM" << std::endl;
			ss.str("");
		}
		
		if (minutes < 720 && minutes >= 60)
		{
			ss << std::setw(2) << std::setfill('0') << (minutes % 60);
			std::cout << "Time: " << (minutes) / 60 << ":" << ss.str() << " AM" << std::endl;
			ss.str("");
		}
		if (minutes < 780 && minutes > 720)
		{
			ss << std::setw(2) << std::setfill('0') << (minutes % 60);
			std::cout << "Time: " << (minutes) / 60 << ":" << ss.str() << " PM" << std::endl;
			ss.str("");
		}
		if (minutes > 780 && minutes < 1440)
		{
			ss << std::setw(2) << std::setfill('0') << (minutes % 60);
			std::cout << "Time: " << ((minutes) / 60) - 12 << ":" << ss.str() << " PM" << std::endl;
			ss.str("");
		}
		if (minutes >= 1440)
		{
			setMinutes(0);
			if (minutes < 60 && minutes >= 0)
			{
				ss << std::setw(2) << std::setfill('0') << (minutes % 60);
				std::cout << "Time: " << ((minutes) / 60) + 12 << ":" << ss.str() << " AM" << std::endl;
				ss.str("");
			}

			if (minutes < 720 && minutes >= 60)
			{
				ss << std::setw(2) << std::setfill('0') << (minutes % 60);
				std::cout << "Time: " << (minutes) / 60 << ":" << ss.str() << " AM" << std::endl;
				ss.str("");
			}
			if (minutes < 780 && minutes > 720)
			{
				ss << std::setw(2) << std::setfill('0') << (minutes % 60);
				std::cout << "Time: " << (minutes) / 60 << ":" << ss.str() << " PM" << std::endl;
				ss.str("");
			}
			if (minutes > 780 && minutes < 1440)
			{
				ss << std::setw(2) << std::setfill('0') << (minutes % 60);
				std::cout << "Time: " << ((minutes) / 60) - 12 << ":" << ss.str() << " PM" << std::endl;
				ss.str("");
			}
		}
	}
};
//This class is for the player
class Player :public Character
{
private:
	int CornSeedsVar;
	int CornCropsVar;
public:
	std::fstream myFile;
	std::string line;
	int currentIndexVar = 1;
	//Constructor
	Player(std::string nameVar)
	{
		setName(nameVar);
		//setGold(1000);
		setGold(getGold());
		CornSeedsVar = getCornSeeds();
		CornCropsVar = getCornCrops();
	}
	void setCornSeeds(int cornSeedsVar)
	{
		CornSeedsVar = cornSeedsVar;
		
		remove("playerCornSeeds.txt");

		myFile.open("playerCornSeeds.txt", std::ios::app);//write
		if (myFile.is_open())
		{
			myFile << CornSeedsVar << std::endl;
			myFile.close();
		}
	}
	int getCornSeeds()
	{
		int cornSeedsFromFile = 0;
		myFile.open("playerCornSeeds.txt", std::ios::in);//read
		if (myFile.is_open())
		{
			std::string line;
			while (getline(myFile, line))
			{
				//std::cout << "Entry " << currentIndexVar << ": ";
				cornSeedsFromFile = stoi(line);
				//std::cout << line << std::endl;
				currentIndexVar++;
			}
			currentIndexVar = 1;
			myFile.close();
		}
		//return CornSeedsVar;
		return cornSeedsFromFile;
	}
	void setCornCrops(int cornCropsVar)
	{
		CornCropsVar = cornCropsVar;
		remove("playerCornCrops.txt");
		
		myFile.open("playerCornCrops.txt", std::ios::app);//write
		if (myFile.is_open())
		{
			myFile << CornCropsVar << std::endl;
			myFile.close();
		}
	}
	int getCornCrops()
	{
		int cornCropsFromFile = 0;
		myFile.open("playerCornCrops.txt", std::ios::in);//read
		if (myFile.is_open())
		{
			std::string line;
			while (getline(myFile, line))
			{
				//std::cout << "Entry " << currentIndexVar << ": ";
				cornCropsFromFile = stoi(line);
				//std::cout << line << std::endl;
				currentIndexVar++;
			}
			currentIndexVar = 1;
			myFile.close();
		}
		return cornCropsFromFile;
		//return CornCropsVar;
	}
};
int main()
{
	std::unique_ptr<Player> playerUniquePtr(new Player("David"));//Creates a Unique Pointer
	std::unique_ptr<Farm> farmUniquePtr(new Farm);//Creates a Unique Pointer
	std::thread thread1Var(&Farm::startClock, &*farmUniquePtr);
	std::stringstream ss;
	
	//starting screen
	std::cout << "*************************************************************************\n";
	std::cout << "*                            Description:                               *\n";
	std::cout << "*     This is a farming game where you try to earn as much money as     *\n";
	std::cout << "*  you can before year 3.                                               *\n";
	std::cout << "*                                                                       *\n";
	std::cout << "*                                                                       *\n";
	std::cout << "*                             Instructions:                             *\n";
	std::cout << "*      1. Buy seeds from the store.                                     *\n";
	std::cout << "*      2. Plant seeds and water them.                                   *\n";
	std::cout << "*      3. Harvest Crops                                                 *\n";
	std::cout << "*      4. Sell Crops                                                    *\n";
	std::cout << "*************************************************************************\n";
	system("pause");
	//end starting screen
	char userInputVar = ' ';//Place this variable outside of main loop so it can be used as an exit condition for the loop
	//The reason we are using a char instead of an int is to 
	//prevent exceptions being thrown for the user entering 
	//something other than an int.
	char userInputVar2 = ' ';
	char userInputVar3 = ' ';
	do//Begin main game loop
	{
		system("cls");//clears console for a clean view to prepare for current section.
		//Display menu to user
		farmUniquePtr->displayClock(farmUniquePtr->getMinutes());
		std::cout << "1. Visit general store." << std::endl;
		std::cout << "2. Work on farm." << std::endl;
		std::cout << "3. Sleep." << std::endl;
		std::cout << "4. Exit game." << std::endl;
		std::cin >> userInputVar;//Get User Input for menu
		switch (userInputVar)//Process user's choice and display respective menu.
		{
		case '1':
			do
			{
				system("cls");
				std::cout << "*******************************" << std::endl;
				farmUniquePtr->displayClock(farmUniquePtr->getMinutes());
				std::cout << "Gold: " << playerUniquePtr->getGold() << std::endl;
				std::cout << "Corn Seeds: " << playerUniquePtr->getCornSeeds() << std::endl;
				std::cout << "Corn Crops: " << playerUniquePtr->getCornCrops() << std::endl;
				std::cout << "*******************************" << std::endl;
				std::cout << "Welcome to my store! How can I help you?" << std::endl;
				std::cout << "1. Buy corn seeds.(-3 Gold)" << std::endl;
				std::cout << "2. Sell crops.(+30 Gold)" << std::endl;
				std::cout << "3. Leave shop." << std::endl;
				std::cin >> userInputVar2;//Get User Input for menu
				switch (userInputVar2)//Process user's choice and display respective menu.
				{
				case '1':
					if (playerUniquePtr->getGold() >= 3)
					{
						playerUniquePtr->setGold(playerUniquePtr->getGold() - 3);
						playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() + 1);
						std::cout << "That will be 3 gold, thank you!\n";
						system("pause");
					}
					else
					{
						std::cout << "Sorry, you don't have enough gold.\n";
						system("pause");
					}
					break;
				case '2':
					if (playerUniquePtr->getCornCrops() >= 1)
					{
						playerUniquePtr->setGold(playerUniquePtr->getGold() + 30);
						playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() - 1);
						std::cout << "Here you go, 30 gold!\n";
						system("pause");
					}
					else
					{
						std::cout << "Sorry, you don't have any crops.\n";
						system("pause");
					}
					break;
				case '3':
					break;
				}
			} while (userInputVar2 != '3');
			break;//Break out of case and back to main game loop
		case '2':
			std::cout << "Work on farm." << std::endl;
			do
			{
				system("cls");
				std::cout << "*******************************" << std::endl;
				farmUniquePtr->displayClock(farmUniquePtr->getMinutes());
				std::cout << "Gold: " << playerUniquePtr->getGold() << std::endl;
				std::cout << "Corn Seeds: " << playerUniquePtr->getCornSeeds() << std::endl;
				std::cout << "Corn Crops: " << playerUniquePtr->getCornCrops() << std::endl;
				std::cout << "*******************************" << std::endl;
				std::cout << "1. Plant seeds." << std::endl;
				std::cout << "2. Harvest crops." << std::endl;
				std::cout << "3. Stop work." << std::endl;
				std::cin >> userInputVar2;//Get User Input for menu
				switch (userInputVar2)//Process user's choice and display respective menu.
				{
				case '1':
					std::cout << "|---" << "-" << "-|---" << "-" << "-|---" << "-" << "-|\n";
					std::cout
						<< "|(1) " << farmUniquePtr->processFarmPlot(0)
						<< "|(2) " << farmUniquePtr->processFarmPlot(1)
						<< "|(3) " << farmUniquePtr->processFarmPlot(2)
						<< "|\n";
					std::cout << "|---" << "-" << "-|---" << "-" << "-|---" << "-" << "-|\n";
					std::cout
						<< "|(4) " << farmUniquePtr->processFarmPlot(3)
						<< "|(5) " << farmUniquePtr->processFarmPlot(4)
						<< "|(6) " << farmUniquePtr->processFarmPlot(5)
						<< "|\n";
					std::cout << "|---" << "-" << "-|---" << "-" << "-|---" << "-" << "-|\n";
					std::cout
						<< "|(7) " << farmUniquePtr->processFarmPlot(6)
						<< "|(8) " << farmUniquePtr->processFarmPlot(7)
						<< "|(9) " << farmUniquePtr->processFarmPlot(8)
						<< "|\n";
					std::cout << "|---" << "-" << "-|---" << "-" << "-|---" << "-" << "-|\n";
					std::cout << "*************************************************\n";
					std::cout << "Select which plot:(1-9)" << std::endl;
					std::cin >> userInputVar3;//Get User Input for menu

					try
					{
						if (!(userInputVar3 == '1' || 
							userInputVar3 == '2' ||
							userInputVar3 == '3' ||
							userInputVar3 == '4' ||
							userInputVar3 == '5' ||
							userInputVar3 == '6' ||
							userInputVar3 == '7' ||
							userInputVar3 == '8' ||
							userInputVar3 == '9'))
						{
							throw std::runtime_error(
								"You must select a number between 1 and 9.");
						}
					}
					catch (const std::exception& e)
					{
						// print the exception
						std::cout << "Exception " << e.what() << std::endl;
					}
					switch (userInputVar3)//Process user's choice and display respective menu.
					{
					case '1':
						if (!farmUniquePtr->getfarmPlotPlanted(0) && playerUniquePtr->getCornSeeds() > 0)
						{
							farmUniquePtr->setFarmPlotGrowthStage(0, 0);
							farmUniquePtr->setFarmPlotPlanted(0, true);
							playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() - 1);
						}
						else
						{
							std::cout << "Seeds are already here.\n";
						}
						break;
					case '2':
						if (!farmUniquePtr->getfarmPlotPlanted(1) && playerUniquePtr->getCornSeeds() > 0)
						{
							farmUniquePtr->setFarmPlotGrowthStage(1, 0);
							farmUniquePtr->setFarmPlotPlanted(1, true);
							playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() - 1);
						}
						else
						{
							std::cout << "Seeds are already here.\n";
						}
						break;
					case '3':
						if (!farmUniquePtr->getfarmPlotPlanted(2) && playerUniquePtr->getCornSeeds() > 0)
						{
							farmUniquePtr->setFarmPlotGrowthStage(2, 0);
							farmUniquePtr->setFarmPlotPlanted(2, true);
							playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() - 1);
						}
						else
						{
							std::cout << "Seeds are already here.\n";
						}
						break;
					case '4':
						if (!farmUniquePtr->getfarmPlotPlanted(3) && playerUniquePtr->getCornSeeds() > 0)
						{
							farmUniquePtr->setFarmPlotGrowthStage(3, 0);
							farmUniquePtr->setFarmPlotPlanted(3, true);
							playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() - 1);
						}
						else
						{
							std::cout << "Seeds are already here.\n";
						}
						break;
					case '5':
						if (!farmUniquePtr->getfarmPlotPlanted(4) && playerUniquePtr->getCornSeeds() > 0)
						{
							farmUniquePtr->setFarmPlotGrowthStage(4, 0);
							farmUniquePtr->setFarmPlotPlanted(4, true);
							playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() - 1);
						}
						else
						{
							std::cout << "Seeds are already here.\n";
						}
						break;
					case '6':
						if (!farmUniquePtr->getfarmPlotPlanted(5) && playerUniquePtr->getCornSeeds() > 0)
						{
							farmUniquePtr->setFarmPlotGrowthStage(5, 0);
							farmUniquePtr->setFarmPlotPlanted(5, true);
							playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() - 1);
						}
						else
						{
							std::cout << "Seeds are already here.\n";
						}
						break;
					case '7':
						if (!farmUniquePtr->getfarmPlotPlanted(6) && playerUniquePtr->getCornSeeds() > 0)
						{
							farmUniquePtr->setFarmPlotGrowthStage(6, 0);
							farmUniquePtr->setFarmPlotPlanted(6, true);
							playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() - 1);
						}
						else
						{
							std::cout << "Seeds are already here.\n";
						}
						break;
					case '8':
						if (!farmUniquePtr->getfarmPlotPlanted(7) && playerUniquePtr->getCornSeeds() > 0)
						{
							farmUniquePtr->setFarmPlotGrowthStage(7, 0);
							farmUniquePtr->setFarmPlotPlanted(7, true);
							playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() - 1);
						}
						else
						{
							std::cout << "Seeds are already here.\n";
						}
						break;
					case '9':
						if (!farmUniquePtr->getfarmPlotPlanted(8) && playerUniquePtr->getCornSeeds() > 0)
						{
							farmUniquePtr->setFarmPlotGrowthStage(8, 0);
							farmUniquePtr->setFarmPlotPlanted(8, true);
							playerUniquePtr->setCornSeeds(playerUniquePtr->getCornSeeds() - 1);
						}
						else
						{
							std::cout << "Seeds are already here.\n";
						}
						break;
					}
					system("pause");
					break;
				case '2':
					std::cout << "|---" << "-" << "-|---" << "-" << "-|---" << "-" << "-|\n";
					std::cout
						<< "|(1) " << farmUniquePtr->processFarmPlot(0)
						<< "|(2) " << farmUniquePtr->processFarmPlot(1)
						<< "|(3) " << farmUniquePtr->processFarmPlot(2)
						<< "|\n";
					std::cout << "|---" << "-" << "-|---" << "-" << "-|---" << "-" << "-|\n";
					std::cout
						<< "|(4) " << farmUniquePtr->processFarmPlot(3)
						<< "|(5) " << farmUniquePtr->processFarmPlot(4)
						<< "|(6) " << farmUniquePtr->processFarmPlot(5)
						<< "|\n";
					std::cout << "|---" << "-" << "-|---" << "-" << "-|---" << "-" << "-|\n";
					std::cout
						<< "|(7) " << farmUniquePtr->processFarmPlot(6)
						<< "|(8) " << farmUniquePtr->processFarmPlot(7)
						<< "|(9) " << farmUniquePtr->processFarmPlot(8)
						<< "|\n";
					std::cout << "|---" << "-" << "-|---" << "-" << "-|---" << "-" << "-|\n";
					std::cout << "*************************************************\n";
					std::cout << "Select which plot:(1-9)" << std::endl;
					std::cin >> userInputVar3;//Get User Input for menu
					switch (userInputVar3)//Process user's choice and display respective menu.
					{
					case '1':
						if (farmUniquePtr->getFarmPlotGrowthStage(0) == 3)
						{
							playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() + 1);
							farmUniquePtr->setFarmPlotGrowthStage(0, 0);
							farmUniquePtr->setFarmPlotPlanted(0, false);
						}
						else
						{
							std::cout << "Corn is not ready yet.\n";
						}
						break;
					case '2':
						if (farmUniquePtr->getFarmPlotGrowthStage(1) == 3)
						{
							playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() + 1);
							farmUniquePtr->setFarmPlotGrowthStage(1, 0);
							farmUniquePtr->setFarmPlotPlanted(1, false);
						}
						else
						{
							std::cout << "Corn is not ready yet.\n";
						}
						break;
					case '3':
						if (farmUniquePtr->getFarmPlotGrowthStage(2) == 3)
						{
							playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() + 1);
							farmUniquePtr->setFarmPlotGrowthStage(2, 0);
							farmUniquePtr->setFarmPlotPlanted(2, false);
						}
						else
						{
							std::cout << "Corn is not ready yet.\n";
						}
						break;
					case '4':
						if (farmUniquePtr->getFarmPlotGrowthStage(3) == 3)
						{
							playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() + 1);
							farmUniquePtr->setFarmPlotGrowthStage(3, 0);
							farmUniquePtr->setFarmPlotPlanted(3, false);
						}
						else
						{
							std::cout << "Corn is not ready yet.\n";
						}
						break;
					case '5':
						if (farmUniquePtr->getFarmPlotGrowthStage(4) == 3)
						{
							playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() + 1);
							farmUniquePtr->setFarmPlotGrowthStage(4, 0);
							farmUniquePtr->setFarmPlotPlanted(4, false);
						}
						else
						{
							std::cout << "Corn is not ready yet.\n";
						}
						break;
					case '6':
						if (farmUniquePtr->getFarmPlotGrowthStage(5) == 3)
						{
							playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() + 1);
							farmUniquePtr->setFarmPlotGrowthStage(5, 0);
							farmUniquePtr->setFarmPlotPlanted(5, false);
						}
						else
						{
							std::cout << "Corn is not ready yet.\n";
						}
						break;
					case '7':
						if (farmUniquePtr->getFarmPlotGrowthStage(6) == 3)
						{
							playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() + 1);
							farmUniquePtr->setFarmPlotGrowthStage(6, 0);
							farmUniquePtr->setFarmPlotPlanted(6, false);
						}
						else
						{
							std::cout << "Corn is not ready yet.\n";
						}
						break;
					case '8':
						if (farmUniquePtr->getFarmPlotGrowthStage(7) == 3)
						{
							playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() + 1);
							farmUniquePtr->setFarmPlotGrowthStage(7, 0);
							farmUniquePtr->setFarmPlotPlanted(7, false);
						}
						else
						{
							std::cout << "Corn is not ready yet.\n";
						}
						break;
					case '9':
						if (farmUniquePtr->getFarmPlotGrowthStage(8) == 3)
						{
							playerUniquePtr->setCornCrops(playerUniquePtr->getCornCrops() + 1);
							farmUniquePtr->setFarmPlotGrowthStage(8, 0);
							farmUniquePtr->setFarmPlotPlanted(8, false);
						}
						else
						{
							std::cout << "Corn is not ready yet.\n";
						}
						break;
					}
					system("pause");
					break;
				case '3':
					break;
				}
			} while (userInputVar2 != '3');
			break;//Break out of case and back to main game loop
		case '3':
			std::cout << "Sleep." << std::endl;
			for (int x = 0; x < 9; x++)
			{
				if (farmUniquePtr->getfarmPlotPlanted(x) && farmUniquePtr->getFarmPlotGrowthStage(x) < 3)
				{
					farmUniquePtr->setFarmPlotGrowthStage(x, farmUniquePtr->getFarmPlotGrowthStage(x) + 1);
				}
			}
			system("pause");
			break;//Break out of case and back to main game loop
		case '4':
			std::cout << "Exit game." << std::endl;
			system("pause");
			break;//Break out of case and back to main game loop
		default:
			system("cls");//clears console for a clean view to prepare for current section.
			std::cout << "That is not a valid choice. Please try again." << std::endl;
			system("pause");//system pause asking user to press any key to continue.
			break;//Break out of case and back to main game loop
		}
	} while (userInputVar != '4');//Exit game loop when user enters the character 4.
	farmUniquePtr->setThreadFinished(true);
	thread1Var.join();
	return 0;
}
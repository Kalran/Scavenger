#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<conio.h>
#include<ctime>
#include<fstream>
#include<string>
#include<Windows.h>
#include<vector>
#include<algorithm>
using namespace std;

//Variables
string Cmds;  		//Used to receive user input
char l=219;				//Used in progress bars
char d=167;				//Character for degrees

//Classes
class Building
{
public:
    string Type;
    int Xpos;
    int Ypos;
    int Level;
};

class Enemy
{
public:
    string Type;
    int Level;
    int Health;
    int Damage;
};

class Plant
{
public:
    string Type;
	int Object;
    int Xpos;
	int Ypos;
    int GrowthStage;
    int HarvestReq;
};

class Player
{
public:
	//Functions
	void LevelUp();

	//Variables
    string Name;
    int Level;
    int Health;
	int Energy;
    int Hunger;
    int Thirst;
    int Tiredness;
    int BodyTemp;

	int Xpos;
	int Ypos;

	string StartingSkill;
	
	//Skills

	//Skinning
	int SkinningLevel;
	double SkinningXp;
	double SkinningXpCap;
	double SkinningXpPercent;
	int SkinningXpInt;

	//Woodcutting
	int WoodcuttingLevel;
	double WoodcuttingXp;
	double WoodcuttingXpCap;
	double WoodcuttingXpPercent;
	int WoodcuttingXpInt;

	//Inventory
	string InventorySlot1,
		InventorySlot2,
		InventorySlot3,
		InventorySlot4,
		InventorySlot5,
		InventorySlot6,
		InventorySlot7,
		InventorySlot8,
		InventorySlot9,
		InventorySlot10;
};

class World
{
public:
	int Object;
	string ObjectType;
};

Player Character;
World World;
Plant Tree;

void gotoxy(int X, int Y)
{
	COORD coord;
	coord.X=X;
	coord.Y=Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void NewGame();
void LoadGame();
void About();
void CharacterCreation();
void ChangeName();
void ChangeStartingSkill();
void Menu();
void Build();
void Crafting();
void InventoryScreen();
void Move();
void CutTree();
void Notes();
void PauseMenu();
void RestMenu();
void Skills();
void SkinningSkill();
void WoodcuttingSkill();

int main()
{
	srand(time(NULL));

    system("cls");
    cout<<"-------------------------Scavenger---------------------------------------------\n\n"
        <<"[N]ew Game\n"
        <<"[L]oad Game\n"
        <<"[A]bout\n";
    Cmds=getch();
    
    if(Cmds=="N"||Cmds=="n")
        NewGame();
    else if(Cmds=="L"||Cmds=="l")
        LoadGame();
    else if(Cmds=="A"||Cmds=="a")
        About();
    else
        main();
}

void About()
{
    system("cls");
    cout<<"-------------------------About-------------------------------------------------\n\n"
        <<"Created by: Kalle Rantanen (Northern Ranger)\n\n"
        <<"Version: ALPHA\n";
	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		main();
	else
		About();
}

void SaveGame()
{
    ofstream Save;
    Save.open("Save.txt");
    
    //Character - Stats
    Save<<Character.BodyTemp<<endl
		<<Character.Energy<<endl
		<<Character.Health<<endl
		<<Character.Hunger<<endl
		<<Character.Level<<endl
		<<Character.Name<<endl
		<<Character.StartingSkill<<endl
		<<Character.Thirst<<endl
		<<Character.Tiredness<<endl
		<<Character.Xpos<<endl
		<<Character.Ypos<<endl;

	//Character - Skills
	Save<<Character.SkinningLevel<<endl
		<<Character.SkinningXp<<endl
		<<Character.SkinningXpCap<<endl
		<<Character.SkinningXpInt<<endl
		<<Character.SkinningXpPercent<<endl
		<<Character.WoodcuttingLevel<<endl
		<<Character.WoodcuttingXp<<endl
		<<Character.WoodcuttingXpCap<<endl
		<<Character.WoodcuttingXpInt<<endl
		<<Character.WoodcuttingXpPercent<<endl;

	//Character - Inventory
	Save<<Character.InventorySlot1<<endl
		<<Character.InventorySlot2<<endl
		<<Character.InventorySlot3<<endl
		<<Character.InventorySlot4<<endl
		<<Character.InventorySlot5<<endl
		<<Character.InventorySlot6<<endl
		<<Character.InventorySlot7<<endl
		<<Character.InventorySlot8<<endl
		<<Character.InventorySlot9<<endl
		<<Character.InventorySlot10<<endl;
    
    Save.close();

	PauseMenu();
}

void LoadGame()
{
	ifstream Load;
	Load.open("Save.txt");

	//Character - Stats
	Load>>Character.BodyTemp
		>>Character.Energy
		>>Character.Health
		>>Character.Hunger
		>>Character.Level
		>>Character.Name
		>>Character.StartingSkill
		>>Character.Thirst
		>>Character.Tiredness
		>>Character.Xpos
		>>Character.Ypos;

	//Character - Skills
	Load>>Character.SkinningLevel
		>>Character.SkinningXp
		>>Character.SkinningXpCap
		>>Character.SkinningXpInt
		>>Character.SkinningXpPercent
		>>Character.WoodcuttingLevel
		>>Character.WoodcuttingXp
		>>Character.WoodcuttingXpCap
		>>Character.WoodcuttingXpInt
		>>Character.WoodcuttingXpPercent;

	//Character - Inventory
	Load>>Character.InventorySlot1
		>>Character.InventorySlot2
		>>Character.InventorySlot3
		>>Character.InventorySlot4
		>>Character.InventorySlot5
		>>Character.InventorySlot6
		>>Character.InventorySlot7
		>>Character.InventorySlot8
		>>Character.InventorySlot9
		>>Character.InventorySlot10;

	Load.close();

	Menu();
}

void NewGame()
{
	system("cls");
	cout<<"Welcome to Scavenger\n\n"
		<<"*story*\n"<<flush;
	Sleep(2000);

	World.Object=0;

	//Character
	Character.BodyTemp=37;
	Character.Health=100;
	Character.Energy=10;
	Character.Level=0;
	Character.Hunger=0;
	Character.Thirst=0;
	Character.Tiredness=0;
	Character.Name="Player";

	Character.StartingSkill="Skinning";

	Character.SkinningLevel=0;
	Character.SkinningXp=0;
	Character.SkinningXpCap=10;

	Character.WoodcuttingLevel=0;
	Character.WoodcuttingXp=0;
	Character.WoodcuttingXpCap=10;

	//Inventory
	Character.InventorySlot1="Empty";
	Character.InventorySlot2="Empty";
	Character.InventorySlot3="Empty";
	Character.InventorySlot4="Empty";
	Character.InventorySlot5="Empty";
	Character.InventorySlot6="Empty";
	Character.InventorySlot7="Empty";
	Character.InventorySlot8="Empty";
	Character.InventorySlot9="Empty";
	Character.InventorySlot10="Empty";

	CharacterCreation();
}

void CharacterCreation()
{
	system("cls");
	cout<<"-------------------------Character Sheet---------------------------------------\n\n"
		<<"Current name   - "<<Character.Name<<"\n"
		<<"Starting skill - "<<Character.StartingSkill<<"\n\n"
		<<"[N]ame your character\n"
		<<"[C]hange starting skill\n"
		<<"\n[D]one?\n";
	Cmds=getch();

	if(Cmds=="N"||Cmds=="n")
		ChangeName();
	else if(Cmds=="C"||Cmds=="c")
		ChangeStartingSkill();
	else if(Cmds=="D"||Cmds=="d")
	{
DoneQuestion:
		system("cls");
		cout<<"\n\nAre you happy with "<<Character.Name<<"?\n       [Y]es / [N]o\n";
		Cmds=getch();

		if(Cmds=="Y"||Cmds=="y")
		{
			if(Character.StartingSkill=="Skinning")
				Character.SkinningLevel=1;
			else if(Character.StartingSkill=="Woodcutting")
				Character.WoodcuttingLevel=1;
			Menu();
		}
		else if(Cmds=="N"||Cmds=="n")
			CharacterCreation();
		else
			goto DoneQuestion;
	}
	else
		CharacterCreation();
}

void ChangeName()
{
	system("cls");
	cout<<"-------------------------Change name-------------------------------------------\n\n"
		<<Character.Name<<"     ----->     ";
	getline(cin, Character.Name);
	CharacterCreation();
}

void ChangeStartingSkill()
{
	system("cls");
	cout<<"-------------------------Change starting skill---------------------------------\n\n"
		<<"[1] - Skinning\n"
		<<"[2] - Woodcutting\n";
	Cmds=getch();

	if(Cmds=="1")
	{
		Character.StartingSkill="Skinning";
		CharacterCreation();
	}
	else if(Cmds=="2")
	{
		Character.StartingSkill="Woodcutting";
		CharacterCreation();
	}
	else
		ChangeStartingSkill();
}

void Menu()
{
	system("cls");
	cout<<"-------------------------"<<Character.Name;
	for(int i=0;i<54-Character.Name.length();i++)
		cout<<"-";
	cout<<"\n\n[B]uild\n[C]raft\n[I]nventory\n[M]ove\n[S]kills\n\n[R]est for the night\n\n[N]otes";

	gotoxy(25,2);
	cout<<"Coordinates: ("<<Character.Xpos<<","<<Character.Ypos<<")";

	gotoxy(25,3);
	cout<<"Health: "<<Character.Health;
	gotoxy(40,3);
	cout<<"Energy: "<<Character.Energy;
	gotoxy(54,3);
	cout<<"Body Temprature: "<<Character.BodyTemp<<d;

	gotoxy(25,5);
	cout<<"Hunger: "<<Character.Hunger;
	gotoxy(37,5);
	cout<<"|";
	for(int i=Character.Hunger/4; i>0; i--)
		cout<<l;
	gotoxy(62,5);
	cout<<"|";

	gotoxy(25,6);
	cout<<"Thirst: "<<Character.Thirst;
	gotoxy(37,6);
	cout<<"|";
	for(int i=Character.Thirst/4; i>0; i--)
		cout<<l;
	gotoxy(62,6);
	cout<<"|";

	gotoxy(25,7);
	cout<<"Sleep : "<<Character.Tiredness;
	gotoxy(37,7);
	cout<<"|";
	for(int i=Character.Tiredness/4; i>0; i--)
		cout<<l;
	gotoxy(62,7);
	cout<<"|";

	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		Build();
	else if(Cmds=="C"||Cmds=="c")
		Crafting();
	else if(Cmds=="I"||Cmds=="i")
		InventoryScreen();
	else if(Cmds=="M"||Cmds=="m")
		Move();
	else if(Cmds=="S"||Cmds=="s")
		Skills();
	else if(Cmds=="N"||Cmds=="n")
		Notes();
    else if(Cmds=="P"||Cmds=="p")
        PauseMenu();
	else if(Cmds=="R"||Cmds=="r")
		RestMenu();
	else
		Menu();
}

void Build()
{
	system("cls");

	cout<<"-------------------------Build-------------------------------------------------\n\n";

	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		Menu();
	else
		Build();
}

void Crafting()
{
	system("cls");

	cout<<"-------------------------Crafting----------------------------------------------\n\n";

	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		Menu();
	else
		Crafting();
}

void InventoryScreen()
{
	system("cls");

	cout<<"-------------------------Inventory---------------------------------------------\n\n"
		<<"[1] "<<Character.InventorySlot1<<endl
		<<"[2] "<<Character.InventorySlot2<<endl
		<<"[3] "<<Character.InventorySlot3<<endl
		<<"[4] "<<Character.InventorySlot4<<endl
		<<"[5] "<<Character.InventorySlot5<<endl
		<<"[6] "<<Character.InventorySlot6<<endl
		<<"[7] "<<Character.InventorySlot7<<endl
		<<"[8] "<<Character.InventorySlot8<<endl
		<<"[9] "<<Character.InventorySlot9<<endl
		<<"[0] "<<Character.InventorySlot10<<endl;

	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		Menu();
	else
		InventoryScreen();
}

void Move()
{
	system("cls");

	cout<<"-------------------------Map---------------------------------------------------\n\n"
		<<"[W] Move North\n[S] Move South\n[A] Move West\n[D] Move East";
	gotoxy(25,2);
	cout<<"X: "<<Character.Xpos;
	gotoxy(25,3);
	cout<<"Y: "<<Character.Ypos;

	if(World.Object<=50 && World.Object!=0)
	{
		gotoxy(25,5);
		
		if(World.Object>=1 && World.Object<=25)
		{
			World.ObjectType="Tree";
			Tree.Object=rand()%100+1;

			if((Tree.Object>=1 && Tree.Object<=25) && Character.WoodcuttingLevel>0)
			{
				Tree.Type="Oak";
				cout<<"You find yourself looking at an oak";
			}
			else if((Tree.Object>=26 && Tree.Object<=50) && Character.WoodcuttingLevel>=5)
			{
				Tree.Type="Birch";
				cout<<"You find yourself looking at a birch";
			}
			else
			{
				Tree.Type="Strange Tree";
				cout<<"You find yourself looking at a strange tree";
			}
		}
		else if(World.Object>=26 && World.Object<=50)
			cout<<"You find yourself looking at a lake";

		cout<<"\n[I]nteract\n";
	}

	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		Menu();
	else if(Cmds=="W"||Cmds=="w")
	{
		if(Character.Energy>0)
		{
			World.Object=rand()%100+1;

			Character.Ypos++;
			Character.Energy--;
			Character.Hunger+=rand()%5+3;
			Character.Thirst+=rand()%8+5;
			Character.Tiredness+=rand()%3+2;

			if(Character.Hunger>100)
			{
				Character.Hunger=100;
				Character.Health-=rand()%3+2;
			}
			
			if(Character.Thirst>100)
			{
				Character.Thirst=100;
				Character.Health-=rand()%4+3;
			}

			if(Character.Tiredness>100)
			{
				Character.Tiredness=100;
				Character.Health-=rand()%2+1;
			}
			


			system("cls");
			cout<<"Traveling north...\n"<<flush;
			Sleep(1000);
			Move();
		}
		else
		{
			system("cls");
			cout<<"You don't have enough energy to travel...\n"<<flush;
			Sleep(1000);
			Move();
		}
	}
	else if(Cmds=="S"||Cmds=="s")
	{
		if(Character.Energy>0)
		{
			World.Object=rand()%100+1;

			Character.Ypos--;
			Character.Energy--;
			Character.Hunger+=rand()%5+3;
			Character.Thirst+=rand()%8+5;
			Character.Tiredness+=rand()%3+2;

			if(Character.Hunger>0)
			{
				Character.Hunger=100;
				Character.Health-=rand()%3+2;
			}

			if(Character.Thirst>0)
			{
				Character.Thirst=100;
				Character.Health-=rand()%4+3;
			}

			if(Character.Tiredness>0)
			{
				Character.Tiredness=100;
				Character.Health-=rand()%2+1;
			}

			system("cls");
			cout<<"Traveling South...\n"<<flush;
			Sleep(1000);
			Move();
		}
		else
		{
			system("cls");
			cout<<"You don't have enough energy to travel...\n"<<flush;
			Sleep(1000);
			Move();
		}
	}
	else if(Cmds=="A"||Cmds=="a")
	{
		if(Character.Energy>0)
		{
			World.Object=rand()%100+1;

			Character.Xpos--;
			Character.Energy--;
			Character.Hunger+=rand()%5+3;
			Character.Thirst+=rand()%8+5;
			Character.Tiredness+=rand()%3+2;

			if(Character.Hunger>100)
			{
				Character.Hunger=100;
				Character.Health-=rand()%3+2;
			}

			if(Character.Thirst>100)
			{
				Character.Thirst=100;
				Character.Health-=rand()%4+3;
			}

			if(Character.Tiredness>100)
			{
				Character.Tiredness=100;
				Character.Health-=rand()%2+1;
			}

			system("cls");
			cout<<"Traveling West...\n"<<flush;
			Sleep(1000);
			Move();
		}
		else
		{
			system("cls");
			cout<<"You don't have enough energy to travel...\n"<<flush;
			Sleep(1000);
			Move();
		}
	}
	else if(Cmds=="D"||Cmds=="d")
	{
		if(Character.Energy>0)
		{
			World.Object=rand()%100+1;

			Character.Xpos++;
			Character.Energy--;
			Character.Hunger+=rand()%5+3;
			Character.Thirst+=rand()%8+5;
			Character.Tiredness+=rand()%3+2;

			if(Character.Hunger>100)
			{
				Character.Hunger=100;
				Character.Health-=rand()%3+2;
			}

			if(Character.Thirst>100)
			{
				Character.Thirst=100;
				Character.Health-=rand()%4+3;
			}

			if(Character.Tiredness>100)
			{
				Character.Tiredness=100;
				Character.Health-=rand()%2+1;
			}

			system("cls");
			cout<<"Traveling east...\n"<<flush;
			Sleep(1000);
			Move();
		}
		else
		{
			system("cls");
			cout<<"You don't have enough energy to travel...\n"<<flush;
			Sleep(1000);
			Move();
		}
	}
	else if(Cmds=="I"||Cmds=="i")
	{
		system("cls");

		if(World.ObjectType=="Tree")
		{
			if(Character.WoodcuttingLevel>0 && Character.Energy>0)
				CutTree();
			else
			{
				if(Character.WoodcuttingLevel==0)
					cout<<"You need\nSkill: Woodcutting\nto perform this action"<<endl;
				else
					cout<<"You don't have enough energy to perform this action"<<endl;

				Sleep(1500);
			}
		}
		else
			Move();
	}
	else
		Move();
}

void CutTree()
{
	if(Tree.Type=="Oak")
	{
		cout<<"Cutting the oak..."<<endl;
		World.Object=0;
		World.ObjectType.clear();
		Tree.Object=0;
		Tree.Type.clear();
		Sleep(1000);
		Move();
	}
	else if(Tree.Type=="Birch")
	{
		cout<<"Cutting the birch..."<<endl;
		World.Object=0;
		World.ObjectType.clear();
		Tree.Object=0;
		Tree.Type.clear();
		Sleep(1000);
		Move();
	}
	else
	{
		cout<<"You need a higher level in woodcutting to cut this tree..."<<endl;
		Sleep(1000);
		Move();
	}

	Move();
}

void Notes()
{
	system("cls");
	cout<<"-------------------------Notes-------------------------------------------------\n\n";

	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		Menu();
	else
		Notes();
}

void PauseMenu()
{
    system("cls");
    
    cout<<"-------------------------"<<Character.Name;
	for(int i=0;i<54-Character.Name.length();i++)
		cout<<"-";
    
    cout<<"\n\n[R]esume\n\n"
        <<"[S]ave Game\n[L]oad Game\n";
    
    Cmds=getch();
    
    if(Cmds=="R"||Cmds=="r")
        Menu();
    else if(Cmds=="S"||Cmds=="s")
        SaveGame();
    else if(Cmds=="L"||Cmds=="l")
        LoadGame();
    else
        PauseMenu();
}

void RestMenu()
{
	system("cls");

}

void Skills()
{
	Character.SkinningXpPercent=Character.SkinningXp/Character.SkinningXpCap;
	Character.SkinningXpInt=Character.SkinningXpPercent;

	Character.WoodcuttingXpPercent=Character.WoodcuttingXp/Character.WoodcuttingXpCap;
	Character.WoodcuttingXpInt=Character.WoodcuttingXpPercent;

	system("cls");
	cout<<"-------------------------Skills------------------------------------------------\n\n";

	cout<<"[1] Skinning";
	if(Character.SkinningLevel>0)
	{
		gotoxy(25,2);
		cout<<Character.SkinningXp<<"/"<<Character.SkinningXpCap;
		gotoxy(37,2);
		cout<<Character.SkinningXpInt<<"%";
		gotoxy(42,2);
		cout<<"|";
		for(int p=Character.SkinningXpPercent/4; p>0; p--)
			cout<<l;
		gotoxy(67,2);
		cout<<"|";
		gotoxy(70,2);
		cout<<Character.SkinningLevel<<"\n";
	}
	else
	{
		gotoxy(25,2);
		cout<<"N/A"<<endl;
	}

	cout<<"[2] Woodcutting";
	if(Character.WoodcuttingLevel>0)
	{
		gotoxy(25,3);
		cout<<Character.WoodcuttingXp<<"/"<<Character.WoodcuttingXpCap;
		gotoxy(37,3);
		cout<<Character.WoodcuttingXpInt<<"%";
		gotoxy(42,3);
		cout<<"|";
		for(int p=Character.WoodcuttingXpPercent/4; p>0; p++)
			cout<<l;
		gotoxy(67,3);
		cout<<"|";
		gotoxy(70,3);
		cout<<Character.WoodcuttingLevel<<"\n";
	}
	else
	{
		gotoxy(25,3);
		cout<<"N/A"<<endl;
	}

	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		Menu();
	else if(Cmds=="1"&&Character.SkinningLevel>0)
		SkinningSkill();
	else if(Cmds=="2"&&Character.WoodcuttingLevel>0)
		WoodcuttingSkill();
	else
		Skills();
}

void SkinningSkill()
{
	system("cls");

	cout<<"-------------------------Skinning----------------------------------------------\n\n";

	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		Skills();
	else
		SkinningSkill();
}

void WoodcuttingSkill()
{
	system("cls");

	cout<<"-------------------------Woodcutting-------------------------------------------\n\n";

	Cmds=getch();

	if(Cmds=="B"||Cmds=="b")
		Skills();
	else
		WoodcuttingSkill();
}

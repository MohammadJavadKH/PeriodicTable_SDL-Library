#include "stdafx.h"

#include "Genio.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <exception>
#include <stdio.h>
using namespace std;
#undef main
int addedelement;
struct element {
	int Z;
	int A;
	string shortname;
	string name;
	string state;
	string type;
	string Info = "Name : " + name + "\nState : " + state + "\nType : " + type + "\n";
};
element table[11][18];
void load();
void deleteelement_shortname();
void deleteelement_atomicnumber();
void searchelement_shortname();
void searchelement_atomicnumber();
void addelement();
void print_table();
void printmenu();
int main()
{
	//init
	G_InitSDL();
	G_Rect rect_window = { 30,30,900,700 };
	G_Rect rect_table = { 30,30,900,500 };
	G_Rect rect_selectedElement = {100,530,150,150 };
	G_Rect rect_InfoElement = { 300,600,550,25 };
	G_Rect rect_InfoElement_Fromfile = { 300,530,550,25 };
	G_Texture* table_image;
	G_Texture* selectedElement_image;
	G_Font* type_Geo = G_OpenFont("assets//font//type2.fon", 5);
	G_Font* type_Fix = G_OpenFont("assets//font//type2.fon", 5);
	G_Texture* Textur_type_Geo;
	G_Texture* Textur_type_Fix;
	ifstream file("assets//ElementsTextInfo.txt");
	string elementsInfoReadFromFile[118];
	if (file.is_open())
	{
		for (int i = 0; i < 118; ++i)
		{
			getline(file, elementsInfoReadFromFile[i]);
		}
	}
	load();
	bool exit = false;
	int select;
	int searchway;
	bool runWindow = true;
	int row = 0;
	int column = 3;
	int alternation;
	int group;
	while (!exit) {
		printmenu();
		scanf_s("%d", &select);
		switch (select) {
			case 1:addelement();
				break;
			case 2:
				label1:
					printf("please input your searching way\n1.search by atomic number\n2.search by short name\n");
					scanf_s("%d", &searchway);
					if (searchway == 1)
						searchelement_atomicnumber();
					else if (searchway == 2)
						searchelement_shortname();
					else
						goto label1;
					break;
			case 3:
				label2:
					printf("please input your deletingway\n1.deleting by atomic number\n2.deleting by short name\n");
					scanf_s("%d", &searchway);
					if (searchway == 1)
						deleteelement_atomicnumber();
					else {
						if (searchway == 2)
							deleteelement_shortname();
						else
							goto label2;
					}
					break;
			case 4:print_table();
				break;

			case 5:
				int x, y;
				G_CreateWindow("PeriodicTable", rect_window,255,255,255,0);
				table_image = G_LoadImage("assets\\table.jpg");
				G_Draw(table_image, &rect_table, false);
				G_Update();
				runWindow = true;
				while (runWindow) {
					switch (G_Event())
					{
					case G_QUIT:
						runWindow = false;
						SDL_DestroyWindow(window);
						break;
					case G_MOUSEMOTION:
						/*switch (G_Mouse)
						{
						case G_BUTTON_LEFT:*/
							x = G_motion.x;
							y = G_motion.y;
							string fileAdd;
							if (y > 69 && y < 370 && x > 66 && x < 895) {
								y -= 70;
								x -= 66;
								row = y / 43;
								group = column + 1;
								alternation = row + 1;
								column = x / 46;
							}
							if (x > 203 && x < 894 && y > 421 && y < 508)
							{
								x -= 204;
								y -= 422;
								column = (x / 46) + 2;
								group = 3;
								if (y < 42) {
									row = 9;
									alternation = 6;
								}
								else {
									row = 10;
									alternation = 7;
								}
							}

								try {
									element SelectedElement = table[row][column];
									string Info1_string = "Summary : A : " + to_string(SelectedElement.A) +"  Z : " + elementsInfoReadFromFile[SelectedElement.Z - 1];
									string Info2_string = "Alternation : " + to_string(alternation) + "   Group : " + to_string(group) + "   State : " + SelectedElement.state + "   Type : " + SelectedElement.type;
									const char* info1 = Info1_string.c_str();
									const char* info2 = Info2_string.c_str();
									Textur_type_Geo = G_LoadFont(type_Geo, (char*)info1, 95, 135, 210);
									Textur_type_Fix = G_LoadFont(type_Fix, (char*)info2, 100, 20, 20);
									int Z = SelectedElement.Z;
									string Z_string = to_string(Z);
									fileAdd = "assets\\elements\\" + Z_string + ".gif";
									const char* image = fileAdd.c_str();
									selectedElement_image = G_LoadImage(image);
									G_Draw(table_image, &rect_table, false);
									G_Draw(selectedElement_image, &rect_selectedElement, false);
									G_Draw(Textur_type_Fix, &rect_InfoElement, false);
									G_Draw(Textur_type_Geo, &rect_InfoElement_Fromfile, false);
									G_Update();
								}
								catch (bad_alloc &ex_bad) {
									
								}
								catch (char* e) {

								}
								catch (invalid_argument &ex) {
									
								}
								catch (exception &ex) {

								}
						//}
					}
					//G_Update();
				}
				break;
			case 6:
				system("cls");
				break;
			case 7:
				exit = true;
		}
	}
	G_QuitSDL();
	return 0;
}
void print_table() {
	for (int i = 0;i<11;i++) {
		for (int j = 0;j<18;j++) {
			if (table[i][j].Z != 0)
				cout << setw(5) << table[i][j].shortname;
			else
				cout << "     ";
		}
		cout << endl;
		for (int j = 0;j<18;j++) {
			if (table[i][j].Z != 0)
				cout << setw(5) << table[i][j].Z;
			else
				cout << "     ";
		}
		if (i != 7)
			cout << endl << endl;
		else
			cout << endl;
	}
}
void addelement() {
	element e;
	printf("please input element name.\n");
	cin >> e.name;
	printf("please input element short name.\n");
	cin >> e.shortname;
	printf("please input atomic number.\n");
	cin >> e.Z;
	printf("please input mass number.\n");
	cin >> e.A;
	printf("please input element state.\n");
	cin >> e.state;
	printf("please input element type.\n");
	cin >> e.type;
	table[7][addedelement] = e;
	addedelement++;
}
void searchelement_atomicnumber() {
	element e;
	int z;
	printf("please input atomic number.\n");
	scanf_s("%d", &z);
	for (int i = 0;i<11;i++) {
		for (int j = 0;j<18;j++) {
			if (table[i][j].Z == z) {
				e = table[i][j];
				cout << "name:" << e.name << "\natomic number:" << e.Z << "\nmass number:" << e.A << "\nstate:" << e.state << "\ntype:" << e.type << endl << endl;
				return;
			}
		}
	}
	cout << "Not Founded!" << endl << endl;
}
void searchelement_shortname() {
	element e;
	string s;
	printf("please input short name.\n");
	cin >> s;
	for (int i = 0;i<11;i++) {
		for (int j = 0;j<18;j++) {
			if (table[i][j].shortname.compare(s) == 0) {
				e = table[i][j];
				cout << "name:" << e.name << "\natomic number:" << e.Z << "\nmass number:" << e.A << "\nstate:" << e.state << "\ntype:" << e.type << endl << endl;
				return;
			}
		}
	}
	cout << "Not Founded!" << endl << endl;
}
void deleteelement_atomicnumber() {
	element e;
	int z;
	printf("please input atomic number.\n");
	scanf_s("%d", &z);
	for (int i = 0;i<11;i++) {
		for (int j = 0;j<18;j++) {
			if (table[i][j].Z == z) {
				e = table[i][j];
				table[i][j].Z = 0;
				cout << "element " << e.name << " was deleted" << endl;
				return;
			}
		}
	}
	cout << "Not Founded!" << endl << endl;
}
void deleteelement_shortname() {
	element e;
	string s;
	printf("please input short name.\n");
	cin >> s;
	for (int i = 0;i<11;i++) {
		for (int j = 0;j<18;j++) {
			if (table[i][j].shortname.compare(s) == 0) {
				e = table[i][j];
				table[i][j].Z = 0;
				cout << "element " << e.name << " was deleted" << endl;
				return;
			}
		}
	}
	cout << "Not Founded!" << endl << endl;
}
void load() {
	element e;
	e.name = "Hydrogen";e.shortname = "H";e.Z = 1;e.A = 1;e.state = "gas";e.type = "Other Nonmetal";
	table[0][0] = e;
	e.name = "Helium";e.shortname = "He";e.Z = 2;e.A = 4;e.state = "gas";e.type = "Noble Gas";
	table[0][17] = e;
	e.name = "Lithium";e.shortname = "Li";e.Z = 3;e.A = 7;e.state = "solid";e.type = "Alkaline Metal";
	table[1][0] = e;
	e.name = "Beryllium";e.shortname = "Be";e.Z = 4;e.A = 9;e.state = "solid";e.type = "Alkaline Earth Metal";
	table[1][1] = e;
	e.name = "Boron";e.shortname = "B";e.Z = 5;e.A = 11;e.state = "Solid";e.type = "Metalloid";
	table[1][12] = e;
	e.name = "Carbon";e.shortname = "C";e.Z = 6;e.A = 12;e.state = "solid";e.type = "Other Nonmetal";
	table[1][13] = e;
	e.name = "Nitrogen";e.shortname = "N";e.Z = 7;e.A = 14;e.state = "gas";e.type = "Other Nonmetal";
	table[1][14] = e;
	e.name = "Oxygen";e.shortname = "O";e.Z = 8;e.A = 16;e.state = "gas";e.type = "Other Nonmetal";
	table[1][15] = e;
	e.name = "Fluorine";e.shortname = "F";e.Z = 9;e.A = 19;e.state = "gas";e.type = "Halogen";
	table[1][16] = e;
	e.name = "Neon";e.shortname = "Ne";e.Z = 10;e.A = 20;e.state = "gas";e.type = "Noble Gas";
	table[1][17] = e;
	e.name = "Sodium";e.shortname = "Na";e.Z = 11;e.A = 23;e.state = "solid";e.type = "Alkaline Metal";
	table[2][0] = e;
	e.name = "Magnesium";e.shortname = "Mg";e.Z = 12;e.A = 24;e.state = "solid";e.type = "Alkaline Earth Metal";
	table[2][1] = e;
	e.name = "Aluminum";e.shortname = "Al";e.Z = 13;e.A = 27;e.state = "Solid";e.type = "Other Metal";
	table[2][12] = e;
	e.name = "Silicon";e.shortname = "Si";e.Z = 14;e.A = 28;e.state = "Solid";e.type = "Metalloid";
	table[2][13] = e;
	e.name = "Phosphorus";e.shortname = "P";e.Z = 15;e.A = 31;e.state = "solid";e.type = "Other Nonmetal";
	table[2][14] = e;
	e.name = "Sulfur";e.shortname = "S";e.Z = 16;e.A = 32;e.state = "solid";e.type = "Other Nonmetal";
	table[2][15] = e;
	e.name = "Chlorine";e.shortname = "Cl";e.Z = 17;e.A = 35;e.state = "gas";e.type = "Halogen";
	table[2][16] = e;
	e.name = "Argon";e.shortname = "Ar";e.Z = 18;e.A = 40;e.state = "gas";e.type = "Noble Gas";
	table[2][17] = e;
	e.name = "Potassium";e.shortname = "K";e.Z = 19;e.A = 39;e.state = "solid";e.type = "Alkaline Metal";
	table[3][0] = e;
	e.name = "Calcium";e.shortname = "Ca";e.Z = 20;e.A = 40;e.state = "solid";e.type = "Alkaline Earth Metal";
	table[3][1] = e;
	e.name = "Scandium";e.shortname = "Sc";e.Z = 21;e.A = 45;e.state = "solid";e.type = "Transition Metal";
	table[3][2] = e;
	e.name = "Titanium";e.shortname = "Ti";e.Z = 22;e.A = 48;e.state = "solid";e.type = "Transition Metal";
	table[3][3] = e;
	e.name = "Vanadium";e.shortname = "V";e.Z = 23;e.A = 51;e.state = "solid";e.type = "Transition Metal";
	table[3][4] = e;
	e.name = "Chromium";e.shortname = "Cr";e.Z = 24;e.A = 52;e.state = "solid";e.type = "Transition Metal";
	table[3][5] = e;
	e.name = "Manganese";e.shortname = "Mn";e.Z = 25;e.A = 55;e.state = "solid";e.type = "Transition Metal";
	table[3][6] = e;
	e.name = "Iron";e.shortname = "Fe";e.Z = 26;e.A = 56;e.state = "solid";e.type = "Transition Metal";
	table[3][7] = e;
	e.name = "Cobalt";e.shortname = "Co";e.Z = 27;e.A = 59;e.state = "solid";e.type = "Transition Metal";
	table[3][8] = e;
	e.name = "Nickel";e.shortname = "Ni";e.Z = 28;e.A = 58;e.state = "solid";e.type = "Transition Metal";
	table[3][9] = e;
	e.name = "Copper";e.shortname = "Cu";e.Z = 29;e.A = 64;e.state = "solid";e.type = "Transition Metal";
	table[3][10] = e;
	e.name = "Zinc";e.shortname = "Zn";e.Z = 30;e.A = 65;e.state = "solid";e.type = "Transition Metal";
	table[3][11] = e;
	e.name = "Gallium";e.shortname = "Ga";e.Z = 31;e.A = 70;e.state = "Solid";e.type = "Other Metal";
	table[3][12] = e;
	e.name = "Germanium";e.shortname = "Ge";e.Z = 32;e.A = 73;e.state = "Solid";e.type = "Metalloid";
	table[3][13] = e;
	e.name = "Arsenic";e.shortname = "As";e.Z = 33;e.A = 75;e.state = "Solid";e.type = "Metalloid";
	table[3][14] = e;
	e.name = "Selenium";e.shortname = "Se";e.Z = 34;e.A = 79;e.state = "solid";e.type = "Other Nonmetal";
	table[3][15] = e;
	e.name = "Bromine";e.shortname = "Br";e.Z = 35;e.A = 80;e.state = "liquid";e.type = "Halogen";
	table[3][16] = e;
	e.name = "Krypton";e.shortname = "Kr";e.Z = 36;e.A = 84;e.state = "gas";e.type = "Noble Gas";
	table[3][17] = e;
	e.name = "Rubidium";e.shortname = "Rb";e.Z = 37;e.A = 85;e.state = "solid";e.type = "Alkaline Metal";
	table[4][0] = e;
	e.name = "Strontium";e.shortname = "Sr";e.Z = 38;e.A = 88;e.state = "solid";e.type = "Alkaline Earth Metal";
	table[4][1] = e;
	e.name = "Yttrium";e.shortname = "Y";e.Z = 39;e.A = 89;e.state = "solid";e.type = "Transition Metal";
	table[4][2] = e;
	e.name = "Zirconium";e.shortname = "Zr";e.Z = 40;e.A = 91;e.state = "solid";e.type = "Transition Metal";
	table[4][3] = e;
	e.name = "Niobium";e.shortname = "Nb";e.Z = 41;e.A = 93;e.state = "solid";e.type = "Transition Metal";
	table[4][4] = e;
	e.name = "Molybdenum";e.shortname = "Mo";e.Z = 42;e.A = 96;e.state = "solid";e.type = "Transition Metal";
	table[4][5] = e;
	e.name = "Technetium";e.shortname = "Tc";e.Z = 43;e.A = 98;e.state = "solid";e.type = "Transition Metal";
	table[4][6] = e;
	e.name = "Ruthenium";e.shortname = "Ru";e.Z = 44;e.A = 101;e.state = "solid";e.type = "Transition Metal";
	table[4][7] = e;
	e.name = "Rhodium";e.shortname = "Rh";e.Z = 45;e.A = 103;e.state = "solid";e.type = "Transition Metal";
	table[4][8] = e;
	e.name = "Palladium";e.shortname = "Pd";e.Z = 46;e.A = 106;e.state = "solid";e.type = "Transition Metal";
	table[4][9] = e;
	e.name = "Silver";e.shortname = "Ag";e.Z = 47;e.A = 108;e.state = "solid";e.type = "Transition Metal";
	table[4][10] = e;
	e.name = "Cadmium";e.shortname = "Cd";e.Z = 48;e.A = 112;e.state = "solid";e.type = "Transition Metal";
	table[4][11] = e;
	e.name = "Indium";e.shortname = "In";e.Z = 49;e.A = 115;e.state = "Solid";e.type = "Other Metal";
	table[4][12] = e;
	e.name = "Tin";e.shortname = "Sn";e.Z = 50;e.A = 119;e.state = "Solid";e.type = "Other Metal";
	table[4][13] = e;
	e.name = "Antimony";e.shortname = "Sb";e.Z = 51;e.A = 122;e.state = "Solid";e.type = "Metalloid";
	table[4][14] = e;
	e.name = "Tellurium";e.shortname = "Te";e.Z = 52;e.A = 128;e.state = "Solid";e.type = "Metalloid";
	table[4][15] = e;
	e.name = "Iodine";e.shortname = "I";e.Z = 53;e.A = 127;e.state = "gas";e.type = "Halogen";
	table[4][16] = e;
	e.name = "Xenon";e.shortname = "Xe";e.Z = 54;e.A = 131;e.state = "gas";e.type = "Noble Gas";
	table[4][17] = e;
	e.name = "Cesium";e.shortname = "Cs";e.Z = 55;e.A = 133;e.state = "solid";e.type = "Alkaline Metal";
	table[5][0] = e;
	e.name = "Barium";e.shortname = "Ba";e.Z = 56;e.A = 137;e.state = "solid";e.type = "Alkaline Earth Metal";
	table[5][1] = e;
	e.name = "Lanthanum";e.shortname = "La";e.Z = 57;e.A = 139;e.state = "solid";e.type = "Lanthanide";
	table[5][2] = e;
	table[9][2] = e;
	e.name = "Cerium";e.shortname = "Ce";e.Z = 58;e.A = 140;e.state = "solid";e.type = "Lanthanide";
	table[9][3] = e;
	e.name = "Praseodymium";e.shortname = "Pr";e.Z = 59;e.A = 141;e.state = "solid";e.type = "Lanthanide";
	table[9][4] = e;
	e.name = "Neodymium";e.shortname = "Nd";e.Z = 60;e.A = 144;e.state = "solid";e.type = "Lanthanide";
	table[9][5] = e;
	e.name = "Promethium";e.shortname = "Pm";e.Z = 61;e.A = 145;e.state = "solid";e.type = "Lanthanide";
	table[9][6] = e;
	e.name = "Samarium";e.shortname = "Sm";e.Z = 62;e.A = 150;e.state = "solid";e.type = "Lanthanide";
	table[9][7] = e;
	e.name = "Europium";e.shortname = "Eu";e.Z = 63;e.A = 152;e.state = "solid";e.type = "Lanthanide";
	table[9][8] = e;
	e.name = "Gadolinium";e.shortname = "Gd";e.Z = 64;e.A = 157;e.state = "solid";e.type = "Lanthanide";
	table[9][9] = e;
	e.name = "Terbium";e.shortname = "Tb";e.Z = 65;e.A = 159;e.state = "solid";e.type = "Lanthanide";
	table[9][10] = e;
	e.name = "Dysprosium";e.shortname = "Dy";e.Z = 66;e.A = 163;e.state = "solid";e.type = "Lanthanide";
	table[9][11] = e;
	e.name = "Holmium";e.shortname = "Ho";e.Z = 67;e.A = 165;e.state = "solid";e.type = "Lanthanide";
	table[9][12] = e;
	e.name = "Erbium";e.shortname = "Er";e.Z = 68;e.A = 167;e.state = "solid";e.type = "Lanthanide";
	table[9][13] = e;
	e.name = "Thulium";e.shortname = "Tm";e.Z = 69;e.A = 169;e.state = "solid";e.type = "Lanthanide";
	table[9][14] = e;
	e.name = "Ytterbium";e.shortname = "Yb";e.Z = 70;e.A = 173;e.state = "solid";e.type = "Lanthanide";
	table[9][15] = e;
	e.name = "Lutetium";e.shortname = "Lu";e.Z = 71;e.A = 175;e.state = "solid";e.type = "Lanthanide";
	table[9][16] = e;
	e.name = "Hafnium";e.shortname = "Hf";e.Z = 72;e.A = 178;e.state = "solid";e.type = "Transition Metal";
	table[5][3] = e;
	e.name = "Tantalum";e.shortname = "Ta";e.Z = 73;e.A = 181;e.state = "solid";e.type = "Transition Metal";
	table[5][4] = e;
	e.name = "Tungsten";e.shortname = "W";e.Z = 74;e.A = 184;e.state = "solid";e.type = "Transition Metal";
	table[5][5] = e;
	e.name = "Rhenium";e.shortname = "Re";e.Z = 75;e.A = 186;e.state = "solid";e.type = "Transition Metal";
	table[5][6] = e;
	e.name = "Osmium";e.shortname = "Os";e.Z = 76;e.A = 190;e.state = "solid";e.type = "Transition Metal";
	table[5][7] = e;
	e.name = "Iridium";e.shortname = "Ir";e.Z = 77;e.A = 192;e.state = "solid";e.type = "Transition Metal";
	table[5][8] = e;
	e.name = "Platinum";e.shortname = "Pt";e.Z = 78;e.A = 195;e.state = "solid";e.type = "Transition Metal";
	table[5][9] = e;
	e.name = "Gold";e.shortname = "Au";e.Z = 79;e.A = 197;e.state = "solid";e.type = "Transition Metal";
	table[5][10] = e;
	e.name = "Mercury";e.shortname = "Hg";e.Z = 80;e.A = 201;e.state = "liquid";e.type = "Transition Metal";
	table[5][11] = e;
	e.name = "Thallium";e.shortname = "Tl";e.Z = 81;e.A = 204;e.state = "Solid";e.type = "Other Metal";
	table[5][12] = e;
	e.name = "Lead";e.shortname = "Pb";e.Z = 82;e.A = 207;e.state = "Solid";e.type = "Other Metal";
	table[5][13] = e;
	e.name = "Bismuth";e.shortname = "Bi";e.Z = 83;e.A = 209;e.state = "Solid";e.type = "Other Metal";
	table[5][14] = e;
	e.name = "Polonium";e.shortname = "Po";e.Z = 84;e.A = 209;e.state = "Solid";e.type = "Other Metal";
	table[5][15] = e;
	e.name = "Astatine";e.shortname = "At";e.Z = 85;e.A = 210;e.state = "Solid";e.type = "Metalloid";
	table[5][16] = e;
	e.name = "Radon";e.shortname = "Rn";e.Z = 86;e.A = 222;e.state = "gas";e.type = "Noble Gas";
	table[5][17] = e;
	e.name = "Francium";e.shortname = "Fr";e.Z = 87;e.A = 223;e.state = "solid";e.type = "Alkaline Metal";
	table[6][0] = e;
	e.name = "Radium";e.shortname = "Ra";e.Z = 88;e.A = 226;e.state = "solid";e.type = "Alkaline Earth Metal";
	table[6][1] = e;
	e.name = "Actinium";e.shortname = "Ac";e.Z = 89;e.A = 227;e.state = "solid";e.type = "Actinide";
	table[6][2] = e;
	table[10][2] = e;
	e.name = "Thorium";e.shortname = "Th";e.Z = 90;e.A = 232;e.state = "solid";e.type = "Actinide";
	table[10][3] = e;
	e.name = "Protactinium";e.shortname = "Pr";e.Z = 91;e.A = 231;e.state = "solid";e.type = "Actinide";
	table[10][4] = e;
	e.name = "Uranium";e.shortname = "U";e.Z = 92;e.A = 238;e.state = "solid";e.type = "Actinide";
	table[10][5] = e;
	e.name = "Neptunium";e.shortname = "Np";e.Z = 93;e.A = 237;e.state = "solid";e.type = "Actinide";
	table[10][6] = e;
	e.name = "Plutonium";e.shortname = "Pu";e.Z = 94;e.A = 244;e.state = "solid";e.type = "Actinide";
	table[10][7] = e;
	e.name = "Americium";e.shortname = "Am";e.Z = 95;e.A = 243;e.state = "solid";e.type = "Actinide";
	table[10][8] = e;
	e.name = "Curium";e.shortname = "Cm";e.Z = 96;e.A = 247;e.state = "solid";e.type = "Actinide";
	table[10][9] = e;
	e.name = "Berkelium";e.shortname = "Bk";e.Z = 97;e.A = 247;e.state = "solid";e.type = "Actinide";
	table[10][10] = e;
	e.name = "Californium";e.shortname = "Cf";e.Z = 98;e.A = 251;e.state = "solid";e.type = "Actinide";
	table[10][11] = e;
	e.name = "Einsteinium";e.shortname = "Es";e.Z = 99;e.A = 252;e.state = "solid";e.type = "Actinide";
	table[10][12] = e;
	e.name = "Fermium";e.shortname = "Fm";e.Z = 100;e.A = 257;e.state = "solid";e.type = "Actinide";
	table[10][13] = e;
	e.name = "Mendelevium";e.shortname = "Md";e.Z = 101;e.A = 258;e.state = "solid";e.type = "Actinide";
	table[10][14] = e;
	e.name = "Nobelium";e.shortname = "No";e.Z = 102;e.A = 259;e.state = "solid";e.type = "Actinide";
	table[10][15] = e;
	e.name = "Lawrencium";e.shortname = "Lr";e.Z = 103;e.A = 266;e.state = "solid";e.type = "Actinide";
	table[10][16] = e;
	e.name = "Rutherfordium";e.shortname = "Rf";e.Z = 104;e.A = 267;e.state = "solid";e.type = "Transition Metal";
	table[6][3] = e;
	e.name = "Dubnium";e.shortname = "Db";e.Z = 105;e.A = 268;e.state = "solid";e.type = "Transition Metal";
	table[6][4] = e;
	e.name = "Seaborgium";e.shortname = "Sg";e.Z = 106;e.A = 269;e.state = "solid";e.type = "Transition Metal";
	table[6][5] = e;
	e.name = "Bohrium";e.shortname = "Bh";e.Z = 107;e.A = 270;e.state = "solid";e.type = "Transition Metal";
	table[6][6] = e;
	e.name = "Hassium";e.shortname = "Hs";e.Z = 108;e.A = 277;e.state = "solid";e.type = "Transition Metal";
	table[6][7] = e;
	e.name = "Meitnerium";e.shortname = "Mt";e.Z = 109;e.A = 278;e.state = "solid";e.type = "Transition Metal";
	table[6][8] = e;
	e.name = "Darmstadium";e.shortname = "Ds";e.Z = 110;e.A = 281;e.state = "solid";e.type = "Transition Metal";
	table[6][9] = e;
	e.name = "Roentgenium";e.shortname = "Rg";e.Z = 111;e.A = 282;e.state = "solid";e.type = "Transition Metal";
	table[6][10] = e;
	e.name = "Copernicium";e.shortname = "Cn";e.Z = 112;e.A = 285;e.state = "solid";e.type = "Transition Metal";
	table[6][11] = e;
	e.name = "Nihonium";e.shortname = "Nh";e.Z = 113;e.A = 286;e.state = "solid";e.type = "Unknown Chemical property";
	table[6][12] = e;
	e.name = "Flerovium";e.shortname = "Fl";e.Z = 114;e.A = 289;e.state = "solid";e.type = "Unknown Chemical property";
	table[6][13] = e;
	e.name = "Moscovium";e.shortname = "Mc";e.Z = 115;e.A = 290;e.state = "solid";e.type = "Unknown Chemical property";
	table[6][14] = e;
	e.name = "Livermorium";e.shortname = "Lv";e.Z = 116;e.A = 293;e.state = "solid";e.type = "Unknown Chemical property";
	table[6][15] = e;
	e.name = "Tennessine";e.shortname = "Ts";e.Z = 117;e.A = 294;e.state = "solid";e.type = "Unknown Chemical property";
	table[6][16] = e;
	e.name = "Oganesson";e.shortname = "Og";e.Z = 118;e.A = 294;e.state = "solid";e.type = "Unknown Chemical property";
	table[6][17] = e;
}
void printmenu() {
	cout << "*************************" << endl << "1.Add element" << endl << "2.Search element" << endl << "3.Delete element" << endl << "4.print table" << endl << "5.print table(Graphical)"<<endl << "6.Clear page" << endl <<"7.Exit" << endl;
}

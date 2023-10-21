#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <WinBase.h>
#include <conio.h>
///dimensiunile chenarului
#define DIM_X 17
#define DIM_Y 27
///caracterele ASCII utilizate pentru construirea chenarului
#define CHR_STANGA_SUS 201
#define CHR_STANGA_JOS 200
#define CHR_DREAPTA_SUS 187
#define CHR_DREAPTA_JOS 188
#define CHR_BARA_VERTICALA 186
#define CHR_BARA_ORIZONTALA 205
///caracterele ASCII reprezentative 
#define CHR_PROIECTIL 248
#define CHR_OU 'O'
#define CHR_INVADER_1 254
#define CHR_INVADER_2 219
#define CHR_CORP_NAVA 202
#define CHR_COMPONENTA_CHENAR_SCOR 203
int i, j, x_nava, y_nava, x_proiectil, y_proiectil, niv_dif;
char scena[DIM_X][DIM_Y];
int aux[DIM_X][DIM_Y];
int score = 0, lives = 0, gainalovita, x_ou, y_ou, numar_nivel, nr;
///in aceasta functie se creeaza meniul introductiv al jocului, in care exista titlul jocului
///dupa care se va efectua selectarea nivelului de dificultate
/// si instructiuni cum ar fi de pe care taste se pune pauza, se misca nava, se trage cu nava
void menu();
///aceasta functie este copiata din cpp-ul laboratorului 7
void hidecursor();
/// urmatoarele 10 functii, reprezinta generarea hartii fiecaruia dintre cele 10 nivele ( 0 - 9 )
void level_0();
void level_1();
void level_2();
void level_3();
void level_4();
void level_5();
void level_6();
void level_7();
void level_8();
void level_9();
void level_infinit();
///aceasta functie este copiata din cpp-ul laboratorului 7
void gotoXY(int x, int y);
void chenarscor();
///functia cu care am creat prelungirea chenarului, in care se afla scorul si vietile
void initializare_scena();
void resetare_harta();
/// aceasta functie afiseaza harta unde are loc toata actiunea din joc
void afisare_harta();
/// aceasta functie va genera aparitia oalelor pe harta
void generare_ou();
///urmatoarele 2 functii realizeaza miscarea proiectilelor si a oualelor pe harta
void miscare_proiectil();
void miscare_oua();
///urmatoarea functie verifica daca nava a fost lovita de catre un ou
///daca aceasta a fost lovita, se va scadea o viata
int verif();
///in urmatoarea functie verific daca oul a ajuns la finalul hartii, pentru a fi sters
void verif_ouafinal();
///in proiectillovestegaina() verific daca gaina a fost atinsa de proiectil
void proiectillovestegaina();
int ouaatingmargine();
/// in aceasta functie am implementat posibilitatea miscarii navei pe cele 2 axe, posibilitatea punerii pe pauza a jocului,
/// prin intermediul tastei SPACE, lansarea proiectilelor de catre nava
/// si posibilitatea inchiderii programului, prin apasarea tastei 'p'
void miscare_nava();
int joc_castigat();
int main()
{
	int k;
	menu();
	char c;
	lives = 1;
	c = _getch();
	if (c == ' ')
	{
		hidecursor();
		initializare_scena();
		resetare_harta();
		afisare_harta();
		miscare_oua();
		chenarscor();
		while (lives)
		{

			while (verif())
			{
				if (rand() % 5 == 0)
					generare_ou();
				miscare_oua();
				chenarscor();
				for (i = 0; i < 300; i++)
					miscare_nava();
				miscare_proiectil();
				verif_ouafinal();
				resetare_harta();
				afisare_harta();
				if (joc_castigat())
				{
					numar_nivel++;
					break;
				}
			}
			for (i = 0; i < DIM_X; i++)
				for (j = 0; j < DIM_Y; j++)
					if (scena[i][j] == (char)CHR_CORP_NAVA)
					{
						k = i - 1;
						break;
					}
			for (i = 0; i < DIM_Y; i++)
				scena[k][i] = ' ';
			initializare_scena();
			resetare_harta();
			afisare_harta();
		}
		system("cls");
		printf("\n\n\n\n\n\n                        !!!GAME OVER!!!\n\n\n\n\n\n\n\n");
	}
}
void menu()
{
	char c;
	char k;


	printf("                                                  !!!  CHICKEN  !!!\n");
	printf("                                                  !!!  INVADERS !!!\n");
	printf("                                         Selectati nivelul de dificultate:\n");
	printf("                                                   1.  <EASY>\n");
	printf("                                                   2.  <MEDIUM>\n");
	printf("                                                   3.  <HARD>\n");
	printf("\n\n\n\n\n\n\n                              Pentru a naviga nava in spatiu se vor folosi tastele: W, A, S, D.");
	printf("\n\n                              Pentru a trage cu proiectile se va folosi tasta L");
	printf("\n\n                              Pentru a pune jocul pe pauza se va folosi tasta SPACE");
	printf("\n\n                              Pentru a incheia jocul se va folosi tasta P ");
	c = _getch();
	switch (c)
	{
	case '1':
	{
		niv_dif = 1;
		lives = 3;
		break;
	}
	case '2':
	{
		niv_dif = 2;
		lives = 2;
		break;
	}
	case '3':
	{
		niv_dif = 3;
		lives = 1;
		break;
	}
	}
	system("cls");
	if (niv_dif == 1)printf("         Ati selectat nivelul de dificultate <EASY>");
	if (niv_dif == 2)printf("         Ati selectat nivelul de dificultate <MEDIUM>");
	if (niv_dif == 3)printf("         Ati selectat nivelul de dificultate <HARD>");
	Sleep(2000);
	system("cls");
	printf("          Selectarea nivelului pe care doriti sa il jucati :\n\n");
	printf("0. LEVEL 0\n\n");
	printf("1. LEVEL 1\n\n");
	printf("2. LEVEL 2\n\n");
	printf("3. LEVEL 3\n\n");
	printf("4. LEVEL 4\n\n");
	printf("5. LEVEL 5\n\n");
	printf("6. LEVEL 6\n\n");
	printf("7. LEVEL 7\n\n");
	printf("8. LEVEL 8\n\n");
	printf("9. LEVEL 9\n\n");

	k = _getch();
	switch (k)
	{
	case '0':
	{
		numar_nivel = 0;
		break;
	}
	case '1':
	{
		numar_nivel = 1;
		break;
	}
	case '2':
	{
		numar_nivel = 2;
		break;
	}
	case '3':
	{
		numar_nivel = 3;
		break;
	}
	case '4':
	{
		numar_nivel = 4;
		break;
	}
	case '5':
	{
		numar_nivel = 5;
		break;
	}
	case '6':
	{
		numar_nivel = 6;
		break;
	}
	case '7':
	{
		numar_nivel = 7;
		break;
	}
	case '8':
	{
		numar_nivel = 8;
		break;
	}
	case '9':
	{
		numar_nivel = 9;
		break;
	}
	}
	system("cls");
	if (numar_nivel == 0)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	if (numar_nivel == 1)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	if (numar_nivel == 2)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	if (numar_nivel == 3)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	if (numar_nivel == 4)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	if (numar_nivel == 5)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	if (numar_nivel == 6)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	if (numar_nivel == 7)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	if (numar_nivel == 8)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	if (numar_nivel == 9)printf("\n\n\n\n\nAti selectat LEVEL %d", numar_nivel);
	Sleep(2000);
	system("cls");
	printf("\n\n\n\n\n\n  . . . Apasati tasta SPACE pentru a incepe jocul . . .");



}
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void level_0()
{
	for (i = 1; i < DIM_X - 10; i++)
		for (j = 4; j < DIM_Y - 4; j++)
			if (i == DIM_X - 11 && j % 3 == 0)
				scena[i][j] = (char)CHR_INVADER_1;
}
void level_1()
{
	for (i = 1; i < DIM_X - 10; i++)
		for (j = 4; j < DIM_Y - 4; j++)
			if (i == DIM_X - 11 && j % 2 == 0)
				scena[i][j] = (char)CHR_INVADER_1;
}
void level_2()
{
	for (i = 1; i < DIM_X - 10; i++)
		for (j = 4; j < DIM_Y - 4; j++)
			if (i == DIM_X - 11 && j % 3 == 0 || i == DIM_X - 12 && j % 3 == 0)
				scena[i][j] = (char)CHR_INVADER_1;
}
void level_3()
{
	for (i = 1; i < DIM_X - 10; i++)
		for (j = 4; j < DIM_Y - 4; j++)
			if (i == DIM_X - 11 && j % 2 == 0 || i == DIM_X - 12 && j % 2 == 0)
				scena[i][j] = (char)CHR_INVADER_1;
}
void level_4()
{
	for (i = 1; i < DIM_X - 10; i++)
		for (j = 4; j < DIM_Y - 4; j++)
			if (j % 8 == 0)
				scena[i][j] = (char)CHR_INVADER_1;
}
void level_5()
{
	for (i = 1; i < DIM_X - 10; i++)
	{
		for (j = 4; j < DIM_Y - 4; j++)
			scena[i][DIM_X - 6] = (char)CHR_INVADER_1;
		scena[i][DIM_X - 2] = (char)CHR_INVADER_1;
	}
}
void level_6()
{
	for (i = 1; i < DIM_X - 10; i++)
	{
		for (j = 4; j < DIM_Y - 4; j++)
			scena[i][DIM_X - 9] = (char)CHR_INVADER_1;
		scena[i][DIM_X - 4] = (char)CHR_INVADER_1;
		scena[i][DIM_X + 1] = (char)CHR_INVADER_1;
	}
}
void level_7()
{
	for (i = 1; i < DIM_X - 10; i++)
		for (j = 4; j < DIM_Y - 4; j++)
			if (j % 5 == 0)
				scena[i][j] = (char)CHR_INVADER_1;
}
void level_8()
{
	for (i = 1; i < DIM_X - 10; i++)
		for (j = 4; j < DIM_Y - 4; j++)
			if (j % 4 == 0)
				scena[i][j] = (char)CHR_INVADER_1;
}
void level_9()
{
	for (i = 1; i < DIM_X - 10; i++)
		for (j = 4; j < DIM_Y - 4; j++)
			if (j % 2 == 0)
				scena[i][j] = (char)CHR_INVADER_1;
}
void gotoXY(int x, int y)
{
	COORD coord = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void chenarscor() {
	gotoXY(DIM_X - 6, DIM_Y - 10);
	printf("SCORE");
	gotoXY(DIM_X - 6, DIM_Y - 7);
	printf("LIVES");
	gotoXY(DIM_X - 4, DIM_Y - 9);
	printf("%d", score);
	gotoXY(DIM_X - 4, DIM_Y - 6);
	printf("%d", lives);
	gotoXY(DIM_X - 9, DIM_Y - 11);
	printf("%c", CHR_COMPONENTA_CHENAR_SCOR);
	gotoXY(DIM_X + 1, DIM_Y - 11);
	printf("%c", CHR_COMPONENTA_CHENAR_SCOR);
	gotoXY(DIM_X - 9, DIM_Y - 10);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X + 1, DIM_Y - 10);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X - 9, DIM_Y - 9);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X + 1, DIM_Y - 9);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X - 9, DIM_Y - 8);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X + 1, DIM_Y - 8);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X - 9, DIM_Y - 7);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X + 1, DIM_Y - 7);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X - 9, DIM_Y - 6);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X + 1, DIM_Y - 6);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X - 9, DIM_Y - 5);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X + 1, DIM_Y - 5);
	printf("%c", CHR_BARA_VERTICALA);
	gotoXY(DIM_X - 9, DIM_Y - 4);
	printf("%c", CHR_STANGA_JOS);
	gotoXY(DIM_X + 1, DIM_Y - 4);
	printf("%c", CHR_DREAPTA_JOS);
	gotoXY(DIM_X - 7, DIM_Y - 4);
	printf("%c%c%c%c%c%c%c", CHR_BARA_ORIZONTALA, CHR_BARA_ORIZONTALA, CHR_BARA_ORIZONTALA, CHR_BARA_ORIZONTALA, CHR_BARA_ORIZONTALA, CHR_BARA_ORIZONTALA, CHR_BARA_ORIZONTALA);
}
void initializare_scena()
{
	system("cls");
	for (i = 1; i < DIM_X - 1; i++)
	{
		for (j = 1; j < DIM_Y - 1; j++)
			scena[i][j] = ' ';
	}
	for (j = 0; j < DIM_Y; j++)
		scena[0][j] = scena[DIM_X - 1][j] = CHR_BARA_ORIZONTALA;

	for (i = 0; i < DIM_X; i++)
		scena[i][0] = scena[i][DIM_Y - 1] = CHR_BARA_VERTICALA;

	scena[0][0] = CHR_STANGA_SUS;
	scena[0][DIM_Y - 1] = CHR_DREAPTA_SUS;
	scena[DIM_X - 1][0] = CHR_STANGA_JOS;
	scena[DIM_X - 1][DIM_Y - 1] = CHR_DREAPTA_JOS;
	scena[DIM_X - 2][DIM_Y / 2] = (char)CHR_CORP_NAVA;
	x_nava = DIM_X - 2;
	y_nava = DIM_Y / 2;
	if (numar_nivel == 0)level_0();
	if (numar_nivel == 1)level_1();
	if (numar_nivel == 2)level_2();
	if (numar_nivel == 3)level_3();
	if (numar_nivel == 4)level_4();
	if (numar_nivel == 5)level_5();
	if (numar_nivel == 6)level_6();
	if (numar_nivel == 7)level_7();
	if (numar_nivel == 8)level_8();
	if (numar_nivel == 9)level_9();
	if (numar_nivel > 9) level_infinit();
}
void resetare_harta()
{

	COORD cursorPosition;	//functie folosita pentru a curata ecranul care mentine cursivitatea jocului
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	for (i = 1; i < DIM_X - 1; i++)
		for (j = 1; j < DIM_Y - 1; j++)
			if (scena[i][j] != (char)CHR_PROIECTIL)
				if (scena[i][j] != (char)CHR_INVADER_1)
					if (scena[i][j] != (char)CHR_OU)
						scena[i][j] = ' ';

	scena[x_nava][y_nava] = (char)CHR_CORP_NAVA;
	i = 0;
	for (j = 0; j < DIM_Y; j++)
		scena[i][j] = (char)CHR_BARA_ORIZONTALA;
	scena[0][0] = CHR_STANGA_SUS;
	scena[0][DIM_Y - 1] = CHR_DREAPTA_SUS;

}
void afisare_harta()
{
	for (i = 0; i < DIM_X; i++)
	{
		for (j = 0; j < DIM_Y; j++)
			printf("%c", scena[i][j]);
		printf("\n");
	}
}
void generare_ou()
{
	int nr;
	srand(time(NULL));
	for (i = DIM_X; i >= 0; i--)
		for (j = 0; j < DIM_Y; j++)
			if (scena[i][j] == (char)CHR_INVADER_1 && scena[i + 1][j] == ' ')
			{
				if (rand() % 10 == 1)
					scena[i + 1][j] = (char)CHR_OU;
			}
}
void miscare_proiectil()
{

	for (i = DIM_X - 1; i >= 0; i--)
	{
		for (j = 0; j < DIM_Y; j++)
			if (scena[i][j] == (char)CHR_PROIECTIL)
			{
				if (scena[i - 1][j] == ' ')
				{
					scena[i][j] = ' ';
					scena[i - 1][j] = (char)CHR_PROIECTIL;
					resetare_harta();
					afisare_harta();
				}
				if (scena[i - 1][j] == (char)CHR_INVADER_1)
				{
					scena[i][j] = ' ';
					scena[i - 1][j] = ' ';
					resetare_harta();
					afisare_harta();
					score += 100;
				}
				if (scena[i - 1][j] == (char)CHR_INVADER_1 || scena[i - 1][j] == (char)CHR_BARA_ORIZONTALA)
				{
					scena[i][j] = ' ';
					resetare_harta();
					afisare_harta();
				}

			}



	}



}
void miscare_oua()
{
	for (i = DIM_X - 1; i >= 0; i--)
	{

		for (j = 0; j < DIM_Y; j++)
			if (scena[i][j] == CHR_OU)
			{

				scena[i][j] = ' ';
				scena[i + 1][j] = CHR_OU;

			}


	}
	resetare_harta();
	afisare_harta();
}
int verif()
{
	for (i = 0; i < DIM_X; i++)
		for (j = 0; j < DIM_Y; j++)
		{
			if (scena[i][j] == (char)CHR_OU && scena[i + 1][j] == (char)CHR_CORP_NAVA)
			{
				lives--;
				return 0;
			}
		}
	return 1;
}
void verif_ouafinal()
{
	for (i = 0; i < DIM_Y; i++)
		if (scena[DIM_X - 1][i] == (char)CHR_OU)
			scena[DIM_X - 1][i] = CHR_BARA_ORIZONTALA;


}
void proiectillovestegaina()
{
	for (i = 0; i < DIM_X; i++)
		for (j = 0; j < DIM_Y; j++)
			if (scena[i][j] == CHR_INVADER_1)
				if (scena[i + 1][j] == CHR_PROIECTIL)
				{
					scena[i + 2][j] = ' ';
					scena[i][j] = ' ';
				}
}
int ouaatingmargine()
{
	for (i = 0; i < DIM_Y; i++)
		if (scena[DIM_X][i] == (char)CHR_OU)
			return 0;
	return 1;
}
void miscare_nava()
{
	char c;

	if (_kbhit())
	{
		c = _getch();
		switch (c)
		{///urmatoarele 4 case-uri, fac nava sa se miste pe cele 2 axe
		case 'w':

		{  if (x_nava - 1 > 0)
			x_nava--;
		break;

		}
		case 's':
		{   if (x_nava + 1 < DIM_X - 1)
			x_nava++;
		break;
		}
		case 'a':
		{   if (y_nava - 1 > 0)
			y_nava--;
		break;
		}
		case 'd':
		{   if (y_nava + 1 < DIM_Y - 1)
			y_nava++;
		break;
		}
		case ' ':///cu ajutorul acestui case, la apasarea tastei SPACE jocul va fi pus pe pauza
		{   char s;
		while (69)
		{
			s = _getch();
			if (s == ' ') break;
		}
		break;
		}
		case 'l':///acest case face nava sa traga
		{

			scena[x_nava - 1][y_nava] = (char)CHR_PROIECTIL;
			break;

		}
		case 'p':///acest case va opri programul la apasarea tastei 'p'
		{
			exit(1);
		}

		}
	}

}
int joc_castigat()
{
	for (i = 0; i < DIM_X; i++)
		for (j = 0; j < DIM_Y; j++)
			if (scena[i][j] == (char)CHR_INVADER_1)
				return 0;
	return 1;
}
void level_infinit()
{
	for (i = 1; i < DIM_X - 10; i++)
		for (j = 4; j < DIM_Y - 4; j++)
			if (rand() % 5 == 0)
				scena[i][j] = (char)CHR_INVADER_1;
}
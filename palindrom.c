//zadanie zaliczeniowe WPI 'palindrom'
//Marta Markocka
//13 listopada 2018r.
#include <stdio.h>

#define wygral 'w'
#define wiersze 10
#define kolumny 10

void stworz_plansze ( char plansza[][kolumny], int wysokosci[] ) {
	for ( int j=0; j<8; j++ ) {
		wysokosci[j] = 0;
	}
	for ( int i=0; i<8; i++ ) {
		for ( int j=0; j<8; j++ ) {
			plansza[i][j] = '-';
		}
	}
}

void wypisz_plansze ( char plansza[][kolumny] ) {
	for ( int i=7; i>=0; i-- ) {
		for ( int j=0; j<8; j++ ) {
			printf(" %c", plansza[i][j]);
		}
		printf("\n");
	}
	printf(" a b c d e f g h\n");
}

char koniec_kolejki ( char gracz ) {
	if ( gracz == '1' ) {
		return '2';
	} else {
		return '1';
	}
}

int czy_palindrom ( char p[][kolumny], int wysokosci[], int gdzie ) {
	int wys = wysokosci[gdzie] - 1;
	int x = wys, y = gdzie;

	if ( wys >= 4 ) {
		for ( int i=0; i<=wys-4; i++ ) {
			if ( p[i][y] == p[i+4][y] && p[i+1][y] == p[i+3][y] ) {
				return 1;
			}
		}
	}

	for ( int i=0; i<4; i++ ) {
		if ( p[x][i] == p[x][i+4] && p[x][i] != '-' 
			&& p[x][i+1] == p[x][i+3] && p[x][i+1] != '-' 
			&& p[x][i+2] != '-' ) {
			return 1;
		}
	}

	while ( x > 0 && y > 0 ) {
		x--;
		y--;
	}
	while ( x < 4 && y < 4 ) {
		if ( p[x][y] == p[x+4][y+4] && p[x][y] != '-' 
			&& p[x+1][y+1] == p[x+3][y+3] && p[x+1][y+1] != '-' 
			&& p[x+2][y+2] != '-' ) {
			return 1;
		}
		x++;
		y++;
	}

	x = wys;
	y = gdzie;
	while ( x > 0 && y < 7 ) {
		x--;
		y++;
	}
	while ( x < 4 && y > 3 ) {
		if ( p[x][y] == p[x+4][y-4] && p[x][y] != '-' 
			&& p[x+1][y-1] == p[x+3][y-3] && p[x+1][y-1] != '-' 
			&& p[x+2][y-2] != '-' ) {
			return 1;
		}
		x++;
		y--;
	}

	return 0;
}

char ruch ( char dana, char plansza[][kolumny], int wysokosci[], char gracz ) {
	int gdzie = (int)dana - (int)('a');
	if ( gdzie >= 0 && gdzie < 8 && wysokosci[gdzie] < 8 ) {
		plansza [wysokosci[gdzie]] [gdzie] = gracz;
		wysokosci[gdzie] ++;

		int wygrana = czy_palindrom ( plansza, wysokosci, gdzie );

		if ( wygrana == 1 ) {
			return wygral;
		} else {
			return koniec_kolejki ( gracz );
		}
	}
	return gracz;
}

int main () {
	char plansza[wiersze][kolumny];
	int wysokosci[wiersze];
	char gracz = '1';

	stworz_plansze ( plansza, wysokosci );
	wypisz_plansze ( plansza );

	char dana = getchar ();
	while ( dana != EOF ) {
		printf("%c:\n", gracz);
		
		if ( dana == '=' ) {
			return 0;
		}
		if ( dana == '\n' || dana == '\r' ) {
			// '\n' odpowiada znakowi LF - line feed w kodzie ASCII, a '\r' CR - carriage return
			// oba powyzsze w zaleznosci od systemu sa symbolem konca linii EOL - end of line
			dana = getchar ();
			wypisz_plansze ( plansza );
			continue;
		}

		char koniec = getchar ();
		if ( koniec == '\n' ) {
			char efekt = ruch ( dana, plansza, wysokosci, gracz );
			if ( efekt == wygral ) {
				wypisz_plansze ( plansza );
				printf("%c.\n", gracz);
				return 0;
			} else {
				gracz = efekt;
			}
	
		} else {
			koniec = getchar ();
			while ( koniec != '\n' ) {
				koniec = getchar ();
			}
		}
		wypisz_plansze ( plansza );
		dana = getchar ();
	}
	printf("%c:\n", gracz);
	
	return 0;
}

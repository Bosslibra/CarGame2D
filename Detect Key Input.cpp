#include <iostream>
#include <Windows.h>
using namespace std;

const int LARGHEZZA = 99;
const int ALTEZZA =LARGHEZZA /2;
char menu[ALTEZZA][LARGHEZZA];

// Inserisce il testo nell'array bidimensionale
void addText(const char testo[], int length) {

	int tmp = 0;
	int i = ALTEZZA / 2 - 4;
	while (tmp < length - 1) {

		int j = LARGHEZZA / 2 - 9;
		while (testo[tmp] != '\n' && j < LARGHEZZA - 1) {
			menu[i][j] = testo[tmp];
			tmp++;
			j++;
		}
		i++;
		tmp++;
	}

}


void MenuDisplay(int opt) {

	// Inizializzazione a spazio vuoto
	for (int i = 0; i < ALTEZZA; i++) {
		for (int j = 0; j < LARGHEZZA; j++) {
			//Bordi sup e inf
			if (i == ALTEZZA - 1 || i == 0) {
				menu[i][j] = '-';
			} else if (j == LARGHEZZA - 1 || j == 0) {
				menu[i][j] = '|';
			} else {
				menu[i][j] = ' ';
			}
		}
	}
	// Visualizzazione del centro dello schermo (outdated)
	//menu[(ALTEZZA / 2) + 1][LARGHEZZA / 2 + 1] = 'f';

	// Inizializzazione dei vari testi per le varie opzioni del menu
	char text1[] = "_____________________\n      CAR RACING\n\n  Select an option:\n> Start new game. <\n  Continue.\n\n  Quit.\n_____________________\n";
	char text2[] = "_____________________\n      CAR RACING\n\n  Select an option:\n  Start new game.\n> Continue. <\n\n  Quit.\n_____________________\n";
	char text3[] = "_____________________\n      CAR RACING\n\n  Select an option:\n  Start new game.\n  Continue.\n\n>  Quit. <\n_____________________\n";

	// Switch per selezione del testo corretto nel menu
	switch (opt)
	{
	case 1:
		addText(text1, sizeof(text1));
		break;
	case 2:
		addText(text2, sizeof(text2));
		break;
	case 3:
		addText(text3, sizeof(text3));
		break;
	}

	// Stampa dell'array
	for (int i = 0; i < ALTEZZA; i++) {
		for (int j = 0; j < LARGHEZZA; j++) {
			cout << menu[i][j];
		}
		cout << endl;
	}
	// Spaziatura per non far vedere menu superiore
	int n_spazi = 10;
	for (int i = 0; i < n_spazi; i++) {
		cout << endl;
	}
}


// Input dalla tastiera per il menu di gioco
void KeyboardInput() {
	bool keepGoing = true; // variabile booleana per determinare se l'utente vuole rimanere sul gioco o uscirne
	int opt = 1; // opzione attiva nel menu
	int lowest_opt = 1; // prima opzione disponibile (resa a variabile rispetto a versione precedente per rendere funzione pi� generica)
	int highest_opt = 3;// ultima opzione disponibile (come sopra). Solitamente � Quit

	// Ciclo per continuare ininterrottamente gioco (si esce con ESC o selezionando Quit)
	do {
		if (GetAsyncKeyState(VK_UP)) {
			if (opt == lowest_opt) {
				opt = highest_opt;
			} else {
				opt--;
			}
			MenuDisplay(opt);
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			if (opt == highest_opt) {
				opt = lowest_opt;
			} else {
				opt++;
			}
			MenuDisplay(opt);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
		}
		if (GetAsyncKeyState(VK_LEFT)) {
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {

			cout << endl << "Exiting the game." << endl;
			keepGoing = false;
		}
		if (GetAsyncKeyState(VK_RETURN)) { // VK_RETURN � il tasto ENTER
			if (opt == 1) {
				cout << "Starting new game\n";
				// Game
				MenuDisplay(lowest_opt); //Dopo aver finito la partita si ritorna al menu iniziale
			}
			if (opt == 2) {
				cout << "Continuing game\n";
				// Game
				MenuDisplay(lowest_opt);
			}
			if (opt == 3) {
				cout << "Exiting the game. Thank you for playing\n";
				keepGoing = false;
			}
		}
	} while (keepGoing);
}



int main() {

	// Prima volta in cui viene mostrato il menu
	MenuDisplay(1);

	// Viene atteso input da tastiera (all'interno � richiamato MenuDisplay())
	KeyboardInput();

	return 0;
}
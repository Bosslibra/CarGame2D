# CarGame2D

Progetto per Esame Programmazione, corso di Laurea Informatica

- pasta e fagioli
- Gioco di corse automobilistiche
- Su più livelli
- A punteggio, senza traguardi
- Protagonista: auto controllata da tastiera
- Nel percorso l'auto incontra ostacoli (buche, chiodi) o potenziamenti (benzina, NOS) o altre auto
- Punteggio: andando avanti e prendendo potenziamenti il punteggio aumenta, finendo fuori strada o scontrandosi con un'altra auto / prendendo ostacoli ecc il punteggio diminuisce
- GAME OVER: quando il punteggio scende a 0
- La mappa viene generata su un livello alla volta dinamicamente
- La mappa viene implementata in una grafica ASCII (x es. attraverso una matrice)
- NO librerie grafiche (ogni personaggio/strumento è un simbolo diverso
- NO traguardi
- Passaggio livello successivo: un punteggio (es. 1000 punti)
- Passaggio livello precedente se si scende sotto un punteggio
- Più è alto più è difficile il gioco (livelli infiniti)

- Bisogna usare le classi
- Più file

## Classi

Game(); (E) (P)
#include <GameInterface>
 canvas[][];
 level;
 score;
 private numberOfEnemies;
 private numberOfBonuses;
 start(
every 1/60s of a second:
checkCollision(canvas)
checkLevel(score)
);

GameInterface(); (M)
#include <LevelInterface>
 car;
 const bonuses;
 const enemies;
 checkCollision(canvas);
 checkLevel(score);
 checkBounds(canvas);
 setLevel(level);
 setScore(score);

LevelInterface(); (E) (P)
 drawEnemies(numberOfEnemies, enemies, canvas);
 drawBonuses(numberOfEnemies, bonuses, canvas);
 moveCar(source,direction, canvas);
 moveBonus(source,direction, canvas);
 moveEnemy(source,direction, canvas);


KeyBoard(); (A)
 keyboard stuff

Printing(); (A)
printing stuff

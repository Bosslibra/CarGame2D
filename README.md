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

- Player (M)
  - Scontra
  - get position
- Livello (numero nemici, motiplicatore Danno, moltiplicatore bonus (?)) (A)
  - altezza statica
  - disegna
  - get punteggio
- Partita (E)
  - add livello (punteggio)
- Nemici (moltiplicatore) (E)
  - Type (lettera)
  - Danno (Player p) => p.proprietà -= danno
- Bonus (E)
  - Type
  - AddBonus (Player p) => p.proprietà += bonus
- Interfaccia di gioco (A)
  - Level stats
  - Draw map
- Sprite
  - scontra (quadrato)

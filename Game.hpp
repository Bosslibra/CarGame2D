#include "ConsoleDrawing.hpp"
#include "LevelInterface.hpp"
#include "Player.hpp"
#include <vector>
#define ENTER 9
class Game
{
private:
    ConsoleDrawing console;
    //costanti
    const int width = 60;
    const int height = 70;
    int speed;
    std::vector<std::vector<char>> canvas;

    //@param bonuses lista bonus sulla mappa
    std::vector<Bonus> bonuses;
    //@param bonuses lista nemici sulla mappa
    std::vector<Enemy> enemies;
    //danno e bonus inflitti
    int damage;
    int bonus;

    int score; //@param score score partita
    int level;

    Player *player; //giocatore
    //numero bonus/nemici nella mappa
    int nEnemy;
    int nBonus;

    int levelUpTarget;
    int prevLevel;

    //funzioni interne
    void initGame();
    /**
     * @brief muove tutte le entità nel canvas (player, enemy, bonus)
     */
    void move();
    /**
     * @brief disegna sul canvas le nuove posizioni delle varie entità
     */
    void draw();
    /**
     * @brief verfica che non vi siano state collisioni tra entità
     */
    void checkCollision();
    /**
     * @brief conotrolla lo score e nel caso aumenta il livello della partita
     */
    void checkLevel();
    /**
     * @brief cancella le vecchie posizioni delle entità dal canvas
     */
    void resetCanvas();
    /**
     * @brief aggiunge un nemico
     */
    void addEnemy(int damage);
    /**
     * @brief aggiunge un bonus
     */
    void addBonus(int bonus);
    /**
     * @brief mostra la schermata di game over e chiede se si vuole riprovare
     *
     * @return true
     * @return false
     */
    bool gameOver();
    /**
     * @brief collega il vettore delle statistiche al gioco
     *
     * @return std::vector<std::vector<char>>
     */
    std::vector<std::vector<char>> showStats();

public:
    /**
     * @brief inizializza alcuni parametri di base del gioco come numero iniziale di nemici/bonus
     *        score e la posizione del player
     */
    Game();
    ~Game();
    /**
     * @brief gestisce tutto il gioco (è un wrapper dei metodi principali)
     */
    void run();
};

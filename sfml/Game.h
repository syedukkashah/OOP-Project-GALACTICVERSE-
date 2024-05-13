#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Animation.h"
using namespace sf;
using namespace std;
class Game {
public:
    Game();
    void run();
private:
    RenderWindow window;
    void processEvents();
    void update();
    void render();
    //Sounds & Buffers
    SoundBuffer soundBuffer, soundBuffer2, soundBuffer3;
    Sound laserSound,powerUpBlast, gameOverSound;
    Music bgMusic, titleMusic;
    Texture playerTexture, bulletTexture, enemyTexture, backgroundTexture1, backgroundTexture2, blastTexture, thrusterTexture, pauseTexture, scoreTexture, coverTexture; //Textures
    RectangleShape hpBar;
    Font font;
    Sprite background1, background2, cover, scoreLogo, toggle, jet1, jet2; //Sprites
    Text text, hpText, e_HPtext, timer, scoreText; //Texts
    bool playBG, gameOverPlayed, isBlastTextVisible, pause, start, time, canBlast;
    int scoreCount, countdown, shootTimer, spawnTimer, lastBlastScore;
    float deltaTime, bgSpeed;
    Clock clock, blinkClock, jetClock; //clocks to manage spritesheets, text blinks and timers
    Time totalPausedTime, lastPauseTime;
    vector<Enemy> enemies;
    Animation animation;
    Player player;
};
#endif

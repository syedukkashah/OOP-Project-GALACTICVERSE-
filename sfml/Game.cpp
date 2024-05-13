#include "Game.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace sf;
using namespace std;
Game::Game() : window(VideoMode(1920, 1080), "GALACTICVERSE"), player(&playerTexture, &blastTexture)
{
    window.setFramerateLimit(60);
	//load all sounds
	soundBuffer.loadFromFile("Sounds/retrolasers.wav");
	laserSound.setBuffer(soundBuffer);
	laserSound.setVolume(60.f);
	soundBuffer2.loadFromFile("Sounds/ultraraygun.wav");
	powerUpBlast.setBuffer(soundBuffer2);
	powerUpBlast.setPlayingOffset(seconds(3.0f));
	soundBuffer3.loadFromFile("Sounds/gameover.wav");
	gameOverSound.setBuffer(soundBuffer3);
	bgMusic.openFromFile("Sounds/MilkyWayMusic.wav");
	titleMusic.openFromFile("Sounds/SpaceCruise.wav");
	titleMusic.setPlayingOffset(seconds(20.f));
	titleMusic.play();
    //init textures
    playerTexture.loadFromFile("Textures/ship.png");
    bulletTexture.loadFromFile("Textures/Laser Sprites/18.png");
    enemyTexture.loadFromFile("Textures/enemy.png");
    backgroundTexture1.loadFromFile("Textures/space.jpg");
	backgroundTexture2.loadFromFile("Textures/space2.jpg");
    blastTexture.loadFromFile("Textures/whirlwind.png");
    thrusterTexture.loadFromFile("Textures/thruster2.png");
    pauseTexture.loadFromFile("Textures/PNG/Pause/Header.png");
    scoreTexture.loadFromFile("Textures/PNG/You_Win/Score.png");
    coverTexture.loadFromFile("Textures/galacticverse cover.png");
    //init sprites
    background1.setTexture(backgroundTexture1);
	background2.setTexture(backgroundTexture2);
    cover.setTexture(coverTexture);
    scoreLogo.setTexture(scoreTexture);
    toggle.setTexture(pauseTexture);
    jet1.setTexture(thrusterTexture);
    jet2.setTexture(thrusterTexture);
    jet1.setScale(1.7f, 2.5f);
    jet2.setScale(1.7f, 2.5f);
    deltaTime = 0.0f;
    //init text
	if (!font.loadFromFile("Fonts/NewTitle-Regular.ttf")) throw "Could not open font";
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(Color::Cyan);
    text.setStyle(Text::Bold);
	e_HPtext.setFont(font);
	e_HPtext.setCharacterSize(36);
	e_HPtext.setFillColor(Color::White);
	//UI init 
	scoreLogo.setPosition(10.f, 15.f);
	scoreText.setStyle(Text::Bold);
	scoreText.setCharacterSize(65);
	scoreText.setFont(font);
	scoreText.setPosition(scoreLogo.getPosition().x + scoreLogo.getGlobalBounds().width + 20.f, 0.f);
	timer.setFont(font);
	timer.setPosition(940, 30);
	timer.setFillColor(Color::White);
	timer.setStyle(Text::Bold);
	timer.setCharacterSize(70);
	hpText.setFont(font);
	hpText.setCharacterSize(36);
	hpText.setFillColor(Color::White);
	hpBar.setFillColor(Color::Red);
	hpBar.setOutlineThickness(2.f);
	hpBar.setOutlineColor(Color::Yellow);
	hpBar.setSize(Vector2f((float)player.getHP() * 20.f, 20.f));
	toggle.setPosition(800, 418); //pause toggle
	playBG = false;
	gameOverPlayed = false;
    isBlastTextVisible = true;
    pause = false;
    start = false;
    time = true;
    canBlast = false;
    scoreCount = 0;
    countdown = 120;
    shootTimer = 15;
    spawnTimer = 20;
    lastBlastScore = 0;
	bgSpeed = 0.5f;
	background1.setPosition(0.f, 0.f);
	background2.setPosition(background1.getGlobalBounds().width, 0.f);
	player = Player(&playerTexture, &blastTexture);
	animation = Animation(&thrusterTexture, Vector2u(8, 8), 0.3f);
}
void Game::run() {
    Clock clock;
    Time timeSinceLastUpdate = Time::Zero;
    while (window.isOpen()) {
        Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > seconds(1.f / 60.f)) {
            timeSinceLastUpdate -= seconds(1.f / 60.f);
            processEvents();
            update();
        }
        render();
    }
}
void Game::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            window.close();
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::P)
            pause = !pause;
		if (event.type == Event::KeyPressed) {
			start = true;
			titleMusic.stop();
			if (!playBG) {
				bgMusic.play();
				playBG = true;
			}
		}
    }
}
void Game::update() {
    if (pause || !start) return; // Do not update if the game is paused or not started
    deltaTime = jetClock.restart().asSeconds();
	if (player.getHP() > 0 && time)
	{
		//player movement
		if (Keyboard::isKeyPressed(Keyboard::W))player.getSprite()->move(0.f, -5.f);
		if (Keyboard::isKeyPressed(Keyboard::A))player.getSprite()->move(-5.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::S))player.getSprite()->move(0.f, 5.f);
		if (Keyboard::isKeyPressed(Keyboard::D))player.getSprite()->move(5.f, 0.f);
		//HP setters
		hpText.setPosition(player.getSprite()->getPosition() + Vector2f(0.f, -80.f));
		hpText.setString(to_string(player.getHP()) + "/" + to_string(player.getMaxHP()));
		hpBar.setPosition(player.getSprite()->getPosition().x, player.getSprite()->getPosition().y - hpText.getGlobalBounds().height);
		//collision with window
		if (player.getSprite()->getPosition().x <= 0) player.getSprite()->setPosition(0.f, player.getSprite()->getPosition().y); //left
		if (player.getSprite()->getPosition().x >= window.getSize().x - player.getSprite()->getGlobalBounds().width)player.getSprite()->setPosition(window.getSize().x - player.getSprite()->getGlobalBounds().width, player.getSprite()->getPosition().y); //right
		if (player.getSprite()->getPosition().y <= 0) player.getSprite()->setPosition(player.getSprite()->getPosition().x, 0.f); //top
		if (player.getSprite()->getPosition().y >= window.getSize().y - player.getSprite()->getGlobalBounds().height)player.getSprite()->setPosition(player.getSprite()->getPosition().x, window.getSize().y - player.getSprite()->getGlobalBounds().height); //bottom
		animation.Update(0, deltaTime); //thruster animation
		jet1.setTextureRect(animation.uvRect);
		jet2.setTextureRect(animation.uvRect);
		jet1.setPosition(player.getSprite()->getPosition() + Vector2f(-95.f, 0.f));
		jet2.setPosition(player.getSprite()->getPosition() + Vector2f(-95.f, 60.f));
		//shooting
		if (shootTimer < 15)shootTimer++;
		if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 15)
		{
			laserSound.play();
			Vector2f shooterPos(player.getSprite()->getGlobalBounds().width + player.getSprite()->getGlobalBounds().left - 20.f, player.getSprite()->getGlobalBounds().top + player.getSprite()->getGlobalBounds().height / 2 - 30.f);
			player.getBullets().push_back(Bullet(&bulletTexture, shooterPos));
			shootTimer = 0;
		}
		//power up blast
		if (canBlast) {
			if (blinkClock.getElapsedTime().asSeconds() >= 0.5) {
				isBlastTextVisible = !isBlastTextVisible; // Toggle visibility
				blinkClock.restart(); // Reset the clock after each toggle
			}
		}
		else isBlastTextVisible = false; // Ensure it doesn't show when canBlast is false
		if (Keyboard::isKeyPressed(Keyboard::H) && canBlast) {
			Vector2f shooterPos(player.getSprite()->getGlobalBounds().width + player.getSprite()->getGlobalBounds().left, player.getSprite()->getGlobalBounds().top + player.getSprite()->getGlobalBounds().height / 2 - 25.f);
			player.getPowerUp()->getBlast()->setPosition(shooterPos);
			canBlast = false;	
			powerUpBlast.play();
		}
		player.getPowerUp()->getBlast()->move(20.f, 0.f);
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (player.getPowerUp()->getBlast()->getGlobalBounds().intersects(enemies[i].getSprite()->getGlobalBounds())) {
				scoreCount += enemies[i].getHP();
				enemies.erase(enemies.begin() + i);
			}
		}
		if (player.getPowerUp()->getBlast()->getPosition().x > window.getSize().x) {
			player.getPowerUp()->getBlast()->setPosition(-100.f, -100.f);//repositioning the power up blast sprite to move it to the unvisible area once it has been used
		}
		//Bullets
		for (size_t i = 0; i < player.getBullets().size(); i++)
		{
			//Move
			player.getBullets()[i].getBullet()->move(20.f, 0.f);

			//Out of window bounds
			if (player.getBullets()[i].getBullet()->getPosition().x > window.getSize().x)
			{
				player.getBullets().erase(player.getBullets().begin() + i);
				break;
			}
			//Enemy collision
			for (size_t k = 0; k < enemies.size(); k++)
			{
				if (player.getBullets()[i].getBullet()->getGlobalBounds().intersects(enemies[k].getSprite()->getGlobalBounds()))
				{
					if (enemies[k].getHP() <= 1)
					{
						scoreCount += enemies[k].getMaxHP();
						enemies.erase(enemies.begin() + k);
						// Check if the score has crossed the next multiple of 50 since the last blast was enabled
						if (scoreCount / 50 > lastBlastScore / 50) {
							canBlast = true;
							lastBlastScore = scoreCount;  // Update last blast score
						}
					}
					else
					{
						enemies[k].setHP(enemies[k].getHP() - 1); //enemy take damage
					}
					player.getBullets().erase(player.getBullets().begin() + i);
					break;
				}
			}
		}
		//Enemy
		if (spawnTimer < 25)spawnTimer++;
		//enemy spawn
		if (spawnTimer >= 25)
		{
			enemies.push_back(Enemy(&enemyTexture, window.getSize()));
			spawnTimer = 0; //reset timer
		}
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].getSprite()->move(-6.f, 0.f);
			if (enemies[i].getSprite()->getPosition().x <= 0 - enemies[i].getSprite()->getGlobalBounds().width)
			{
				enemies.erase(enemies.begin() + i);
				break;
			}
			if (enemies[i].getSprite()->getGlobalBounds().intersects(player.getSprite()->getGlobalBounds()))
			{
				enemies.erase(enemies.begin() + i);
				player.setHP(player.getHP() - 1); //player takes damage
				break;
			}
		}
		//UI update
		hpBar.setSize(Vector2f((float)player.getHP() * 20.f, 20.f));
		scoreText.setString(to_string(scoreCount));
		int minutes = countdown / 60;
		int seconds = countdown % 60;
		timer.setString(to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds));
		background1.move(-bgSpeed, 0.f);
		background2.move(-bgSpeed, 0.f);
		// If the first background sprite moves completely out of the window to the left
		if (background1.getPosition().x + background1.getGlobalBounds().width < 0)
		{
			// Reposition it immediately after the second sprite to create the loop
			background1.setPosition(background2.getPosition().x + background2.getGlobalBounds().width, 0.f);
		}
		// If the second background sprite moves completely out of the window to the left
		if (background2.getPosition().x + background2.getGlobalBounds().width < 0)
		{
			// Reposition it immediately after the first sprite to create the loop
			background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);
		}
	}
	// Update countdown timer
	if (clock.getElapsedTime().asSeconds() >= 1.0 && countdown > 0) {
		countdown--;
		clock.restart();
	}
}
void Game::render() {
    window.clear();
    if (!start) {
        window.draw(cover);
    }
    else {
        // DRAW GAME SCENE
        window.draw(background1);
		window.draw(background2);
        window.draw(jet1);
        window.draw(jet2);
        window.draw(*player.getSprite());
        for (size_t i = 0; i < player.getBullets().size(); i++)window.draw(*player.getBullets()[i].getBullet());
        if (!canBlast)window.draw(*player.getPowerUp()->getBlast());
        for (size_t i = 0; i < enemies.size(); i++)
        {
            e_HPtext.setString(to_string(enemies[i].getHP()) +  "/" + to_string(enemies[i].getMaxHP()));
            e_HPtext.setPosition(enemies[i].getSprite()->getPosition().x, enemies[i].getSprite()->getPosition().y - e_HPtext.getGlobalBounds().height);
            window.draw(e_HPtext);
            window.draw(*enemies[i].getSprite());
        }
        //UI 
		window.draw(hpBar);
        window.draw(hpText);
        window.draw(scoreLogo);
        window.draw(scoreText);
        window.draw(timer);
        if (canBlast && isBlastTextVisible) {
            text.setString("BLAST CHARGED");
            text.setFillColor(Color::Yellow);
            text.setStyle(Text::Bold);
            text.setPosition(window.getSize().x - 400.f, 9.f);
            window.draw(text);
        }
		if (player.getHP() >= 0 && countdown == 0)
		{
			text.setString("YOU WIN!");
			text.setStyle(Text::Bold);
			text.setFillColor(Color::Green);
			window.draw(text);
		}
		else if ((player.getHP() <= 0 || countdown == 0) && !gameOverPlayed)
		{
			bgMusic.stop();
			gameOverSound.play();
			gameOverPlayed = true;
		}
		else if (player.getHP() <= 0 || countdown == 0)
		{
			text.setString("YOU LOSE! - GAME OVER!");
			text.setFillColor(Color::Red);
			text.setPosition(750, 480);
			window.draw(text);
		}
        if (pause)window.draw(toggle);
    }
    window.display();
}
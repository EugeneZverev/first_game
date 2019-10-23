#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.hpp"
#include "functions.hpp"
#include "view.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include "StaticObject.hpp"
#include "LifeBar.hpp"  
#include "Santa.hpp"  

void drawMap(RenderWindow &window, Sprite &map);

using namespace sf;

int main(){
	RenderWindow window(VideoMode(1100, 700), "Snowman's procrastination", Style::None); 
	view.reset(FloatRect(0, 0, 1100, 700));  

	Clock clock;  

	Font font; 
	font.loadFromFile("fonts/mainfont.ttf");  

	Text counter("", font, 50);  
	Text level("", font, 50);
	Text lose("You lose..\nCongratulations!!!", font, 50);
	Text end("Coursework done\n by Eugene Zverev", font, 50);	

	Texture map;  
	map.loadFromFile("images/map.png"); 
	Sprite s_map;  
	s_map.setTexture(map);  

	StaticObject igloo1("images/igloo.png", 5150, 210);
	StaticObject lEdge1("images/leftEdge.png", 840, 490);
	StaticObject rEdge1("images/rightEdge.png", 1260, 490);
	StaticObject lEdge2("images/leftEdge.png", 2380, 490);
	StaticObject rEdge2("images/rightEdge.png", 2940, 490);
	StaticObject owl("images/owl.png", 1880, 370);
	StaticObject tree2("images/tree2.png", 0, 0);
	StaticObject tree3("images/tree3.png", 3300, 42);
	StaticObject portal("images/portal.png", 4100, 22);
	StaticObject bill("images/bill.png", 4180, 22);
	StaticObject penguin("images/penguin.png", 610, 185);
	StaticObject deer("images/deer.png", 2665, 173);
	
	StaticObject igloo("images/igloo.png", 35, 210); 
	StaticObject moon("images/moon.png", 740, 40);  
	StaticObject lEdge("images/leftEdge.png", 770, 490); 
	StaticObject rEdge("images/rightEdge.png", 1190, 490);  
	StaticObject tree("images/tree.png", 5000, 140);
	StaticObject barren("images/barren_tree.png", 2635, 140);
	StaticObject lyra("images/lyra.png", 4800, 30);
	StaticObject danger("images/danger.png", 3900, 300);
	StaticObject bag_before("images/bag_before.png", 5390, 380);
	StaticObject bag_after("images/bag_after.png", 5390, 380);
	StaticObject new_year("images/new_year.png", 5000, 140);

	LifeBar lifebar("images/life.png");

	Santa santa("images/santa.png");

	Hero snowman("snowman.png", 165, 345, 117.0, 145.0);

	Enemy zombie1("images/zombie.png", 1600, 353, 77.0, 145.0, "zombie");
	Enemy zombie2("images/zombie.png", 1700, 353, 77.0, 145.0, "zombie");
	Enemy zombie3("images/zombie.png", 4150, 60, 77.0, 145.0, "zombie");
	Enemy zombie4("images/zombie.png", 4165, 65, 77.0, 145.0, "zombie");
	Enemy zombie5("images/zombie.png", 4180, 70, 77.0, 145.0, "zombie");
	Enemy spike1("images/easyEnemy.png", 1750, 412, 77.0, 145.0, "easyEnemy");
	Enemy spike2("images/easyEnemy.png", 2050, 412, 77.0, 145.0, "easyEnemy");

	Enemy spike("images/easyEnemy.png", 2300, 412, 77.0, 145.0, "easyEnemy");
	Enemy ghost("images/ghost.png", 4400, 392, 123.0, 80.0, "hardEnemy");

	Music main_theme;  
	main_theme.openFromFile("audio/play.ogg"); 
	main_theme.play(); 
	main_theme.setLoop(true);   
	Music end_theme;
	end_theme.openFromFile("audio/end.ogg");
	Music dead_theme;
	dead_theme.openFromFile("audio/dead.ogg");

	bool m_flag = 1;
	while (window.isOpen()){
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event)){
			if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
				window.close();
		}
		snowman.update(time);

		if(snowman.level == 2 && !snowman.trans){
			for (int i = 0; i < HEIGHT_MAP; i++){
				for (int j = 0; j < WIDTH_MAP; j++){
					TileMap[i][j] = Level2[i][j];
				}
			}
			snowman.trans = true;
		}
 
		if (snowman.numLives == 0 && m_flag){
			main_theme.stop();
			dead_theme.play();
			dead_theme.setLoop(true);
			dead_theme.setVolume(50);
			m_flag = 0;
		}

		if (snowman.level == 1){
			zombie1.update(time, snowman.getplayercoordinateX());
			zombie2.update(time, snowman.getplayercoordinateX());
			zombie3.update(time, snowman.getplayercoordinateX());
			zombie4.update(time, snowman.getplayercoordinateX());
			zombie5.update(time, snowman.getplayercoordinateX());
			spike1.update(time, snowman.getplayercoordinateX());
			spike2.update(time, snowman.getplayercoordinateX());
			if (snowman.getSprite().getGlobalBounds().intersects(zombie1.getSprite().getGlobalBounds()) 
				|| snowman.getSprite().getGlobalBounds().intersects(zombie2.getSprite().getGlobalBounds()) 
				|| snowman.getSprite().getGlobalBounds().intersects(zombie3.getSprite().getGlobalBounds()) 
				|| snowman.getSprite().getGlobalBounds().intersects(zombie4.getSprite().getGlobalBounds()) 
				|| snowman.getSprite().getGlobalBounds().intersects(zombie5.getSprite().getGlobalBounds()) 
				|| snowman.getSprite().getGlobalBounds().intersects(spike1.getSprite().getGlobalBounds()) 
				|| snowman.getSprite().getGlobalBounds().intersects(spike2.getSprite().getGlobalBounds())){
				snowman.health -= 100;
			}
			if (snowman.getSprite().getGlobalBounds().intersects(penguin.getSprite().getGlobalBounds()) && zombie1.health == 0 && zombie2.health == 0){ 
				penguin.setPosition(5100, 373); 
				if (snowman.getplayercoordinateX() < 4850) snowman.friends++;
			}
			if (snowman.getSprite().getGlobalBounds().intersects(owl.getSprite().getGlobalBounds())){
				owl.setPosition(5000, 370); 
				if (snowman.getplayercoordinateX() < 4850) snowman.friends++;
			}
			if (snowman.getSprite().getGlobalBounds().intersects(deer.getSprite().getGlobalBounds()) && zombie3.health == 0 && zombie4.health == 0 && zombie5.health == 0){
				deer.setPosition(4850, 367); 
				if(snowman.getplayercoordinateX() < 4800) snowman.friends++;
			}
		}

		if(snowman.level == 2){
			if (snowman.win && m_flag){
				main_theme.stop();
				end_theme.play();
				end_theme.setLoop(true);
				end_theme.setVolume(50);
				m_flag = 0;
			}
			spike.update(time, snowman.getplayercoordinateX());
			ghost.update(time, snowman.getplayercoordinateX());
			if (snowman.getSprite().getGlobalBounds().intersects(spike.getSprite().getGlobalBounds()) 
				|| snowman.getSprite().getGlobalBounds().intersects(ghost.getSprite().getGlobalBounds())){
				snowman.health -= 100;
			}
		}
 
		lifebar.animation(snowman.numLives, view.getCenter().x - 420, view.getCenter().y - 290);
		
		if(snowman.level == 2){
			santa.animation(5180, 333, time, 175, 255, 16);
			std::ostringstream stringCounter;
			stringCounter << snowman.counter;
			counter.setString("podarochki: " + stringCounter.str());
		}

		window.setView(view);
		window.clear();
		drawMap(window, s_map);
		if(snowman.level == 1){ 
			window.draw(igloo1.getSprite()); 
			window.draw(lEdge1.getSprite());
			window.draw(rEdge1.getSprite());
			window.draw(lEdge2.getSprite());
			window.draw(rEdge2.getSprite());
			window.draw(owl.getSprite());
			window.draw(tree2.getSprite());
			window.draw(penguin.getSprite());
			window.draw(deer.getSprite());
			window.draw(tree3.getSprite());
			if (snowman.friends < 3){
				window.draw(portal.getSprite());
				window.draw(bill.getSprite());
			}
		}

		level.setPosition(view.getCenter().x + 250, view.getCenter().y - 310);
		lose.setPosition(view.getCenter().x + 70, view.getCenter().y - 310);
		if(snowman.level == 1) level.setString("Level 1"); else level.setString("Level 2");

		if(snowman.level == 2){
			counter.setPosition(view.getCenter().x - 250, view.getCenter().y - 310);
			end.setPosition(view.getCenter().x + 100, view.getCenter().y - 310);
			window.draw(igloo.getSprite());
			window.draw(moon.getSprite());
			window.draw(lEdge.getSprite());
			window.draw(rEdge.getSprite());
			if (snowman.counter < 10 || (snowman.counter == 10 && snowman.getplayercoordinateX() < 4980)) window.draw(tree.getSprite());
			else if (snowman.counter == 10 && snowman.getplayercoordinateX() > 4980) window.draw(new_year.getSprite());
			window.draw(lyra.getSprite());
			window.draw(barren.getSprite());
		}

		window.draw(lifebar.getSprite());

		if (snowman.level == 1){ 
			window.draw(zombie1.getSprite()); 
			window.draw(zombie2.getSprite());
			window.draw(zombie3.getSprite());
			window.draw(zombie4.getSprite());
			window.draw(zombie5.getSprite());
			window.draw(spike1.getSprite());
			window.draw(spike2.getSprite());
		}

		if(snowman.level == 2){
			window.draw(santa.getSprite());
			if (snowman.counter < 10 || (snowman.counter == 10 && snowman.getplayercoordinateX() < 4980)) window.draw(bag_before.getSprite());
			else if (snowman.counter == 10 && snowman.getplayercoordinateX() > 4980) window.draw(bag_after.getSprite());
			window.draw(counter);
			if (snowman.win) window.draw(end);
			window.draw(spike.getSprite());
			window.draw(ghost.getSprite());
		}

		if(!snowman.win && snowman.numLives != 0) window.draw(level);
		if(snowman.numLives == 0) window.draw(lose);
		window.draw(snowman.getSprite());
		if(snowman.level == 2) window.draw(danger.getSprite());
		window.display();
	}
	return 0;
}
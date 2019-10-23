#include <SFML/Graphics.hpp>  

using namespace sf; 

void drawMap(RenderWindow &window, Sprite &map){  
	for (int i = 0; i < HEIGHT_MAP; i++){  
		for (int j = 0; j < WIDTH_MAP; j++){  
			if (TileMap[i][j] == ' ')  map.setTextureRect(IntRect(0, 0, 70, 70));  
			if (TileMap[i][j] == 'g') map.setTextureRect(IntRect(70, 0, 70, 70));  
			if (TileMap[i][j] == '0' || TileMap[i][j] == 'e') map.setTextureRect(IntRect(140, 0, 70, 70));  
			if (TileMap[i][j] == 'w') map.setTextureRect(IntRect(350, 0, 70, 70));
			if (TileMap[i][j] == 'd') map.setTextureRect(IntRect(420, 0, 70, 70));  
			if (TileMap[i][j] == '[') map.setTextureRect(IntRect(490, 0, 70, 70));  
			if (TileMap[i][j] == '|') map.setTextureRect(IntRect(560, 0, 70, 70)); 
			if (TileMap[i][j] == ']') map.setTextureRect(IntRect(630, 0, 70, 70));  
			if (TileMap[i][j] == '1') map.setTextureRect(IntRect(700, 0, 70, 70));  
			if (TileMap[i][j] == '2') map.setTextureRect(IntRect(770, 0, 70, 70));  
			if (TileMap[i][j] == '3') map.setTextureRect(IntRect(840, 0, 70, 70));  
			if (TileMap[i][j] == '4') map.setTextureRect(IntRect(910, 0, 70, 70));  
			if (TileMap[i][j] == '5') map.setTextureRect(IntRect(980, 0, 70, 70));  
			map.setPosition(j * 70, i * 70);  
			window.draw(map);  
		}
	}
}
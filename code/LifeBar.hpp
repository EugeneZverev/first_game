class LifeBar{  
private:
	Texture texture; 
	Sprite sprite;  
public:
	LifeBar(String file){ 
		texture.loadFromFile(file);  
		sprite.setTexture(texture);  
	}
	void animation(int nLives, float x, float y){  
		sprite.setPosition(x, y);
		sprite.setTextureRect(IntRect(0, 36 * (3 - nLives), 127, 36));  
	}
	Sprite getSprite(){ 
		return sprite;
	}
};

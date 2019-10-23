class StaticObject{  
private:
	Texture texture; 
	Sprite sprite;  
public:
	StaticObject(String file, float x, float y){ 
		texture.loadFromFile(file); 
		sprite.setTexture(texture); 
		sprite.setPosition(x, y); 
	}
	Sprite getSprite(){ 
		return sprite;
	}
	void setPosition(float x, float y){
		sprite.setPosition(x, y);
	}
};
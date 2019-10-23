class Santa{
private:
	Texture texture; 
	Sprite sprite; 
	float currentFrame = 0;
public:
	Santa(String file){
		texture.loadFromFile(file); 
		sprite.setTexture(texture); 
	}
	void animation(float x, float y, float time, int h, int w, int nFrame){ 
		sprite.setPosition(x, y);
		currentFrame += 0.005*time;
		if (currentFrame > nFrame) currentFrame -= nFrame;
		sprite.setTextureRect(IntRect(w * (int(currentFrame) + 1), 0, -w, h));
	}
	Sprite getSprite(){ 
		return sprite;
	}
};
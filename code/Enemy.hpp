class Enemy{ 
private:
	float dx, dy, x, y, speed, moveTimer, coordMove, originX, originY;
	int w, h;
	bool dir;
	float currentFrame;
	enum{ left, right, idle } state;
	const float ANIMATION = 0.006;
	Texture texture;
	Sprite sprite;
	String name;
	String file;
public:
	bool move;
	int health;
	Enemy(String File, float X, float Y, int W, int H, String Name){
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0; file = File;
		originX = X; originY = Y;
		speed = 0; health = 100; dx = 0; dy = 0; currentFrame = 0;
		coordMove = 0;
		state = left;
		texture.loadFromFile(file);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
		if (name == "hardEnemy" || name == "zombie"){
			sprite.setTextureRect(IntRect(0, 0, w, h));
			move = 0;
			dir = 1;
		}
		if (name == "zombie") sprite.setTextureRect(IntRect(w, 0, -w, h));
	}
	void checkCollisionWithMap(float Dx, float Dy){
		for (int i = y / 70; i < (y + h) / 70; i++)
			for (int j = x / 70; j<(x + w) / 70; j++){
				if (x < 0) break;
				if (y > 550){
					health = 0;
					dx = 0;
					break;
				};
				if(TileMap[i][j] == '0'){
					if (Dy>0){ y = i * 70 - h + 10;  dy = 0;}
				}
			}
	}
	void update(float time, float X){
		if (name == "easyEnemy"){
			sprite.setPosition(x + w / 2, y + h / 2);
		}
		if(name == "hardEnemy"){ 
			checkCollisionWithMap(dx, 0); 
			if (move) x += dx*time;
			checkCollisionWithMap(0, dy);
			sprite.setPosition(x + w / 2, y + h / 2);  
			walkAnimation(time);	
			if (X > 3850) move = 1;
			if (X < 380){ 
				move = 0; 
				x = 4400;
			}
			if (move) dx = -0.2; 
		}
		if (name == "zombie"){
			if(dir && move == 1){
				coordMove = X;
				dir = 0;
			}
			checkCollisionWithMap(dx, 0);
			if (move) x += dx*time;
			y += dy*time;
			checkCollisionWithMap(0, dy);
			sprite.setPosition(x + w / 2, y + h / 2);
			if(move) zombieAnimation(time, X);
			if (X > x-550) move = 1;
			if (X < 380){
				move = 0;
				x = originX;
				y = originY;
				health = 100;
			}
			if(move){ 
				if (coordMove > x){
					dx = 0.13; 
					state = right;
				}
				if (state == 0 && x < coordMove + 1) dir = 1;
				if (state == 1 && x > coordMove - 1) dir = 1;
				if (coordMove < x){ 
					dx = -0.13; 
					state = left;
				}
			}
			if (X > x - 550) dy = dy + 0.0005*time;
		}
	}
	void walkAnimation(float time){
		currentFrame += ANIMATION*time;
		if(currentFrame > 15) currentFrame -= 15;
		sprite.setTextureRect(IntRect(123 * int(currentFrame), 0, 123, 80));
	}
	void zombieAnimation(float time, float X){
		currentFrame += ANIMATION*time;
		if (currentFrame > 6) currentFrame -= 6;
		if(state == 1) sprite.setTextureRect(IntRect(77 * int(currentFrame), 0, 77, 145)); 
			else if(state == 0) sprite.setTextureRect(IntRect(77 * (int(currentFrame) + 1), 0, -77, 145));
	}
	Sprite getSprite(){
		return sprite;
	}
};
class Hero{
private:
	float x, y;  
	const float GRAVITY = 0.0013;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	float w, h, dx, dy, speed, wJump;  
	float currentFrame = 0;
	bool life, isMove, isRun, onGround, game = 1, win = 0, trans;
	int dir, counter, health, numLives, runningGame;  
	enum{ left, right, jump, idle } state;
	int level;
	int friends = 0;
	Hero(String file, float X, float Y, float W, float H){  
		dx = 0;
		dy = 0;
		win = 0;
		trans = 0;
		speed = 0;
		level = 1;
		dir = 0;
		wJump = -0.55;
		counter = 0;
		health = 100;
		numLives = 3;
		runningGame = 1;
		life = true;
		onGround = false;
		isMove = false;
		isRun = false;
		state = idle;
		File = file;  
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; 
		y = Y; 
		w = W; 
		h = H; 
		sprite.setTextureRect(IntRect(0, 0, w, h));  
		sprite.setOrigin(w / 2, h / 2);
	}

	void control(float time){
		if (life && !win){
			if (Keyboard::isKeyPressed(Keyboard::LAlt)){
				isRun = true;
				wJump = -0.75;
			}
			else isRun = false;

			if (Keyboard::isKeyPressed(Keyboard::A)) {
				state = left;
				if (isRun == false && wJump > -0.56) speed = 0.19; else speed = 0.25;
				
					if (onGround == true) currentFrame += 0.006*time; 
					if (currentFrame > 9) currentFrame -= 9;
					sprite.setTextureRect(IntRect(117 * (int(currentFrame) + 1), 0, -117, 145));
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				state = right;
				if (isRun == false && wJump > -0.56) speed = 0.19; else speed = 0.25;
				if (onGround == true) currentFrame += 0.006*time; 
				if (currentFrame > 9) currentFrame -= 9;
				sprite.setTextureRect(IntRect(117 * int(currentFrame), 0, 117, 145)); 
			}

			if (Keyboard::isKeyPressed(Keyboard::W) && onGround) {
				state = jump;
				dy = wJump;
				onGround = false;
			}
		}
	}

	void update(float time){
		control(time);
		switch (state){
			case right: dx = speed; break;
			case left: dx = -speed; break;
			case jump: break;
			case idle: dy = 0;  break;		
		}
		if (dx == 0 && life) idleAnimation(time); 
			else if (!game){
				deadAnimation(time); 
			}
		if(!life){
			if (numLives != 0) numLives--;
			if(numLives > 0){
				life = true;
				state = idle;
				health = 100;
				x = 165;
				y = 345;
			}
			else runningGame = 0;
		}
		if(y > 350){
			dx = 0;
			onGround = false;
		}
		if(x > 4980){
			if(counter == 10){
				win = 1;
			}
			if(level == 1 && x > 5280 && friends >= 3){ 
				level++; 
				x = 165;
				y = 345;
			}
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);
		y += dy*time;
		if (onGround == true) {
			wJump = -0.55; 
		}
		checkCollisionWithMap(0, dy);
		if (!isMove) speed = 0;
		sprite.setPosition(x + w / 2, y + h / 2); 
		if (health <= 0 || y > 700 + h){ 
			life = false;
			if (numLives == 0){
				game = false; 
			}
			if (dy < 0) dy = 0.1;
		}
		dy = dy + GRAVITY*time*(runningGame);
		if (life) setPlayerCoordinateForView(x);
	}

	float getplayercoordinateX(){	
		return x;
	}

	float getplayercoordinateY(){	
		return y;
	}

	void setX(float X){
		x = X;
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 70; i < (y + h) / 70; i++)
			for (int j = x / 70; j<(x + w) / 70; j++)
			{
				if (y > 550){
					life = false;
					break;
				};
				if (y < 0){
					break;
				};
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == 'e')) 
				{
					if (Dy>0){ y = i * 70 - h;  dy = 0; onGround = true; }
				}
				if ((TileMap[i][j] == '[') || (TileMap[i][j] == '|') || (TileMap[i][j] == ']'))
				{
					if (Dy > 0 && y <= i * 70 - h + 20){ y = i * 70 - h + 19;  dy = 0; onGround = true;}
				}
				if (x < 0) x = 0;
				if (x > 5410) x = 5410;
				if (TileMap[i][j] == 'e'){
					wJump = -0.7;
				}
				if (TileMap[i][j] == '1' || TileMap[i][j] == '2' || TileMap[i][j] == '3' || TileMap[i][j] == '4' || TileMap[i][j] == '5'){
					TileMap[i][j] = ' ';
					counter++;
				}
			}
	}

	void idleAnimation(float time){
		currentFrame += 0.004*time;
		if (currentFrame > 7) currentFrame -= 7;
		if (state == idle || state == right) sprite.setTextureRect(IntRect(117 * int(currentFrame), 145, 117, 145));
		if (state == left) sprite.setTextureRect(IntRect(117 * (int(currentFrame) + 1), 145, -117, 145));
	}

	void deadAnimation(float time){
		currentFrame += 0.0025*time;
		if (currentFrame > 9) currentFrame = 8;
		if (state == idle || state == right) sprite.setTextureRect(IntRect(240 * int(currentFrame), 290, 240, 163));
		if (state == left) sprite.setTextureRect(IntRect(240 * (int(currentFrame) + 1), 290, -240, 163));
	}
	
	Sprite getSprite(){
		return sprite;
	}
};
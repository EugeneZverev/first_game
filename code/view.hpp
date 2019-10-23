View view; 

void setPlayerCoordinateForView(float x){ 
	float tempX = x; 
	if (x < 550) tempX = 550; 
	if (x > 4980) tempX = 4980; 
	view.setCenter(tempX, 350); 
}

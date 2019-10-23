#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 10; 
const int WIDTH_MAP = 80; 

sf::String TileMap[HEIGHT_MAP] = {
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"       [||]                         [||||]                                      ",
	"                                                                                ",
	"                                                                                ",
	"0000000000000ewwww00000000000000000ewwwwww00000000000000000000000000000000000000",
	"gggggggggggggddddddggggggggggggggggddddddddggggggggggggggggggggggggggggggggggggg",
	"gggggggggggggddddddggggggggggggggggddddddddggggggggggggggggggggggggggggggggggggg",
};

sf::String Level2[HEIGHT_MAP] = {
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                          3                      1                              ",
	"                        [||]                   [||||]                           ",
	"                                                                                ",
	"         1          2              4   5    3         4     2      3            ",
	"000000000000ewwww000000000000000000000000000000000000000000000000000000000000000",
	"ggggggggggggddddddgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
	"ggggggggggggddddddgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
};
#include "map_func.h"
#include "map_class.h"
#include "points.h"

void fill_with_punkty(punkty& punkty, const float x, const float y, const int k, const int w, const float distance) {
	for (int i = 0; i < k; i++) {
		punkty.add_punkt(x + i * distance, y);
		for (int j = 0; j < w; j++)
			punkty.add_punkt(x + i * distance, y + j * distance);
	}
}

void map1(labirynth& l, punkty& punkty)

{
	fill_with_punkty(punkty, 50, 50, 24, 13, 50);

	//ramki
	l.add_wall(0, 0, 1270, 20); // sciana pozioma gorna
	l.add_wall(0, 20, 20, 680); // sciana pionowa lewa
	l.add_wall(0, 700, 1270, 20); // sciana pozioma dolna
	l.add_wall(1250, 20, 20, 680); // sciana pionowa prawa
	//4 rogi
	//lewy gora
	l.add_wall(100, 100, 20, 220); //pionowa
	l.add_wall(120, 100, 100, 20); //pozioma
	//lewy dol
	l.add_wall(100, 400, 20, 220);//pionowa
	l.add_wall(120, 600, 100, 20);//pozioma
	//prawy gora
	l.add_wall(1150, 100, 20, 220);//pionowa
	l.add_wall(1050, 100, 100, 20);//pozioma

	//prawy dol
	l.add_wall(1150, 400, 20, 220); //pionowa
	l.add_wall(1050, 600, 100, 20); //pozioma


	//4 bolce pionowe
	l.add_wall(300, 20, 20, 100); //lewy gora
	l.add_wall(950, 20, 20, 100); //prawy gora
	l.add_wall(300, 600, 20, 100); //lewy dol
	l.add_wall(950, 600, 20, 100); //prawy dol

	//6 bolce poziome
	l.add_wall(200, 200, 120, 70); //lewy gorny
	l.add_wall(200, 350, 200, 20); //lewy srodek
	l.add_wall(200, 450, 120, 70); //lewy dol
	l.add_wall(950, 200, 120, 70); //prawy gora
	l.add_wall(870, 350, 200, 20); //prawy srodek
	l.add_wall(950, 450, 120, 70); //prawy dol

	//2 dlugie pionowe
	l.add_wall(400, 200, 20, 320);//lewy
	l.add_wall(850, 200, 20, 320);//prawy

	//2 dlugie poziome
	l.add_wall(400, 100, 470, 20);//gorny
	l.add_wall(400, 600, 470, 20);//dolny

	//srodek
	l.add_wall(500, 120, 20, 200);//pionowy gorny
	l.add_wall(500, 400, 20, 200);//pionowy dolny
	l.add_wall(750, 120, 20, 200);
	l.add_wall(750, 400, 20, 200);
	l.add_wall(600, 350, 70, 20);
	l.add_wall(600, 200, 70, 70);
	l.add_wall(600, 450, 70, 70);

}

void map2(labirynth& l, punkty& punkty)
{
	fill_with_punkty(punkty, 50, 50, 11, 13, 50);
	fill_with_punkty(punkty, 690, 50, 11, 13, 50);
	fill_with_punkty(punkty, 620, 150, 1, 2, 150);
	fill_with_punkty(punkty, 620, 400, 1, 2, 150);

	//ramki

	l.add_wall(0, 0, 1270, 20); // sciana pozioma gorna
	l.add_wall(0, 20, 20, 680); // sciana pionowa lewa
	l.add_wall(0, 700, 1270, 20); // sciana pozioma dolna
	l.add_wall(1240, 20, 30, 680); // sciana pionowa prawa
	///lewa strona
	l.add_wall(100, 600, 120, 20);//poziomy
	l.add_wall(100, 500, 20, 120);//pionowy

	l.add_wall(300, 600, 20, 100);//pionowy

	l.add_wall(400, 600, 100, 20);//poziomy
	l.add_wall(500, 500, 20, 120);//pionowy
	l.add_wall(400, 500, 20, 20);//kwadrat

	l.add_wall(200, 500, 120, 20);//poziomy cienki
	l.add_wall(200, 400, 20, 100);//pionowy 
	l.add_wall(100, 400, 100, 20);//poziomy gruby

	l.add_wall(300, 400, 120, 20);//poziomy lewy
	l.add_wall(300, 200, 20, 200);//pionowy lewy
	l.add_wall(500, 200, 20, 220);//pionowy prawy
	l.add_wall(400, 300, 100, 20);//poziomy prawy
	l.add_wall(400, 200, 20, 20);//kwadrat

	l.add_wall(20, 300, 200, 20);//gruby poziomy
	l.add_wall(200, 200, 20, 100);//pionowy dolny

	l.add_wall(100, 100, 20, 120);//pionowy gorny

	l.add_wall(120, 100, 100, 20);//poziomy gorny

	l.add_wall(300, 20, 20, 100);//pionowy samotnik
	l.add_wall(400, 100, 120, 20);//poziomy samotnik

	//srodek
	l.add_wall(600, 20, 60, 100);//gorny prostokat
	l.add_wall(600, 200, 60, 70);//gorny kwadrat 
	l.add_wall(600, 350, 60, 20);//srodkowy 
	l.add_wall(600, 450, 60, 70);//dolny kwadrat
	l.add_wall(600, 600, 60, 100);//dolny prostokat


	//prawa strona
	l.add_wall(740, 100, 120, 20);//poziomy lewy
	l.add_wall(740, 120, 20, 100);//pionowy lewy
	l.add_wall(840, 200, 20, 20);//kwadrat

	l.add_wall(940, 20, 20, 100);//pionowy samotny
	l.add_wall(1040, 100, 120, 20);//poziomy rog
	l.add_wall(1140, 110, 20, 110);//pionowy rog

	l.add_wall(940, 200, 120, 20);//poziomy
	l.add_wall(1040, 220, 20, 100);//pionowy cienki
	l.add_wall(1060, 300, 100, 20);//poziomy gruby

	l.add_wall(740, 300, 20, 220);//pionowy
	l.add_wall(760, 400, 100, 20);//poziomy
	l.add_wall(840, 300, 120, 20);//pionowy
	l.add_wall(940, 320, 20, 200);//poziomy
	l.add_wall(840, 500, 20, 20);//kwadrat

	l.add_wall(1040, 400, 200, 20);//gruby ze sciany
	l.add_wall(1040, 410, 20, 110);//pionowy

	l.add_wall(740, 600, 120, 20);//poziomy samotnik
	l.add_wall(940, 600, 20, 100);//pionowy samotnik
	l.add_wall(1040, 600, 120, 20);//poziomy
	l.add_wall(1140, 500, 20, 120);
}

void map3(labirynth& l, punkty& punkty)
{
	fill_with_punkty(punkty, 50, 50, 24, 13, 50);
	//ramki
	l.add_wall(0, 0, 1270, 20); // sciana pozioma gorna
	l.add_wall(0, 20, 20, 680); // sciana pionowa lewa
	l.add_wall(0, 700, 1270, 20); // sciana pozioma dolna
	l.add_wall(1250, 20, 20, 680); // sciana pionowa prawa

	//lewy rog
	l.add_wall(20, 500, 100, 20);//maly bolec ze sciany poziomy
	l.add_wall(300, 400, 70, 20);//samotny poziomy

	//niepelnosprawne f
	l.add_wall(100, 600, 270, 20);//poziomy z f
	l.add_wall(300, 500, 20, 100);//pionowy z f

	//odwrocona elka
	l.add_wall(200, 400, 20, 120);//pionowy z odwroconej elki
	l.add_wall(90, 400, 110, 20);//poziomy z odwroconej elki

	//kinole
	l.add_wall(400, 500, 120, 20);//kinol dolny poziome
	l.add_wall(450, 520, 20, 100);//kinol dolny pionowe

	l.add_wall(450, 320, 20, 100);//kinol pionowe gorne
	l.add_wall(400, 300, 120, 20);//kinol poziome gora

	l.add_wall(400, 100, 120, 20);//kinol najwyzszy poziome
	l.add_wall(450, 120, 20, 100);//kinol najwyzszy pionowe

	//prawy rog
	l.add_wall(900, 600, 120, 20); // poziomy dol 1
	l.add_wall(1100, 600, 70, 20);//poziomy dol 2
	l.add_wall(800, 500, 370, 20);//poziomy gora
	l.add_wall(900, 400, 20, 100);//pionowy gora
	l.add_wall(550, 400, 70, 20);
	l.add_wall(1000, 400, 170, 20);
	//niepelnosprawne f
	l.add_wall(550, 600, 270, 20);//poziomy z f
	l.add_wall(600, 500, 20, 100);//pionowy z f



	//odwr elka
	l.add_wall(700, 400, 20, 120);//pionowy z elki
	l.add_wall(720, 400, 100, 20);//poziomy z elki

	//srodek
	l.add_wall(300, 220, 20, 100);//pionowy lewy
	l.add_wall(300, 200, 70, 20);//poziomy lewy
	l.add_wall(600, 220, 20, 100);//pionowy prawy
	l.add_wall(550, 200, 70, 20);//poziomy prawy


	//lewy gora
	l.add_wall(100, 100, 20, 220);//pionowy
	l.add_wall(120, 200, 100, 20);//poziomy
	l.add_wall(200, 20, 20, 80);//pionowy lewy gora
	l.add_wall(200, 100, 120, 20);//poziomy lewy gora
	l.add_wall(200, 300, 20, 20);//kwadrat

	//prawy gora
	l.add_wall(600, 100, 120, 20);//poziomy prawy gora
	l.add_wall(700, 20, 20, 80);//pionowy prawy gora
	l.add_wall(700, 200, 100, 20);//poziomy
	l.add_wall(800, 100, 20, 220);//pionowy
	l.add_wall(700, 300, 20, 20);//kwadrat
	//kwadrat duzy
	l.add_wall(900, 100, 20, 220);//lewy bok
	l.add_wall(920, 100, 250, 20);//gora
	l.add_wall(1150, 100, 20, 220);//prawy bok
	l.add_wall(900, 300, 70, 20);//lewy dol
	l.add_wall(1050, 300, 100, 20);//prawy dol
	l.add_wall(1000, 200, 70, 20);//kwadrat w srodku
}

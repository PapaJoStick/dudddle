#include <SFML/Graphics.hpp>

#include "iostream"

using namespace std; //using namespace std; сообщает компилятору, что мы хотим использовать всё,
					 //что находится в пространстве имен std
using namespace sf;  //using namespace sf; сообщает компилятору, что мы хотим использовать всё,
					 //что находится в пространстве имен sf


#include "vector"

#include "string"

#include "ctime"

class Point          //class Point; место расположения платформы

{

public:				//puplic; список методов доступных другим функциям и объектам программы

	double x, y;

};

int main()			

{

	srand(time(0));										//srand(time(0)); помогает в генерации чисел random путем посева rand с начальным значением

	RenderWindow window(VideoMode(600, 600), "Duddle"); //создает окно 600*600 пикселей с названием "Duddle"
														//RenderWindow; окно для 2д чертежа
	window.setFramerateLimit(80);						//window.setFramerateLimit; число обновлений окна

	Font font;											//Front; позволяет использовать шрифт который лежит в папке
														
	font.loadFromFile("CyrilicOld.TTF");				//loadFromFile; путь к шрифту для программмы (в нашем случае шрифт лежит в самой программе)
														//это сделано для того чтобы не указывать полный путь к файлу (в нашем случае достаточно указать название и расширение)
	Text text;											//Text; создаем перременную текст, которую будем выводить на экран
														//в нашем случае это счетчик (в верхнем правом углу)
	text.setFont(font);									//setFront; указывает каким шрифтом(front) будет выводиться текст(text)

	text.setCharacterSize(60);							//setCharacterSize; указывает кого размера будет текст

	text.setFillColor(Color::Green);					//setFillColor; указывает кого цвета будет текст

	int Score = 0;										//задаем счетчик отскакиваний (начальное число 0)

	vector<Point> platforms;							//vector; неограниченный массив с неизвестным количесвом элементов
														//...
	Image i_back, i_platform, i_player, i_gover;		//создаем изображение которое будет выводиться на экран
													
	Texture t_back, t_platform, t_player, t_gover;		//создаем текстуру которая будет обрабатываться программой

	Sprite s_back, s_platform, s_player, s_gover;		//изображение может переремещаться по экрану

	i_back.loadFromFile("background.png");				//loadFromFile; путь к картинке для программмы

	t_back.loadFromImage(i_back);						//loadFromImage; теперь мы "записывае" эту картинку в текстуру

	s_back.setTexture(t_back);							//setTexture; теперь мы переводим эту текстуру в спрайт 

	s_back.setScale(2, 2);								//setScale; увеличиваем спрайт в 2 ао координате x и y

	i_platform.loadFromFile("platform.png");			//

	t_platform.loadFromImage(i_platform);				//

	s_platform.setTexture(t_platform);					//

	i_player.loadFromFile("doodle.png");				//

	t_player.loadFromImage(i_player);					//дальше все делается аналогично (см background)

	s_player.setTexture(t_player);						//

	i_gover.loadFromFile("game.png");					//

	t_gover.loadFromImage(i_gover);						//

	s_gover.setTexture(t_gover);						//

	double x = 300, y = 100;							//координаты нашего дудлика

	double dx = 0, dy = 0;								//записываем перемещение дудлика по координатам x и y
	
	s_player.setOrigin(40, 40);							//setOrigin; центр спрайта дудлика (спомоью setOrigin мы смещаем точку спрайта
														//из верхенго левого угла (у всех спрайтов она задана в этом углу) на 40 по y и на 40 по х (размер дудлика 80*80))
	for (int i(0); i < 10; i++)							//ограчиваем количество платформ до 10
														//и записываем координаты каждой платформы в вектор
	{

		Point point;									//обращаемся к лассу Point 

		point.x = 0 + rand() % (530 - 0 + 1);			//рандомные координаты по х (от 0 до 530) 
														//мы это делаем чтобы платформы не уходили за пределы окна
		point.y = 0 + rand() % (580 - 0 + 1);			//рандомные координаты по y (от 0 до 580)
														//мы это делаем чтобы платформы не уходили за пределы окна
		platforms.push_back(point);						//push_back; записываем в конец вектора координаты нашей платформы

	}

	while (window.isOpen())								//isOpen; пока окно открыто мы можем...		

	{

		Event event;									//Event; обработка события

		while (window.pollEvent(event))					//pollEvent; проверка на нажатие кнопки "крест"

		{

			if (event.type == Event::Closed)

				window.close();

		}												//окно закроется

		if (Keyboard::isKeyPressed(Keyboard::D))		//isKeyPressed; если на жимаем на клавишу "D"

		{

			dx = 3;										//изменение перемещения

			s_player.setScale(-1, 1);					//setScale; позволяет развернуть дудлика вправо 
					
		}

		if (Keyboard::isKeyPressed(Keyboard::A))		//

		{

			dx = -3;									//аналогично (см D)

			s_player.setScale(1, 1);					//

		}

		dy += 0.2;									
													
		if (x > 600)

		{

			x = 0;

		}

		if (x < 0)										//если координаты дудлика меньше 0
														
		{

			x = 600;									//изменяем координаты дудлика на 600

		}

		x += dx;										//перемещаем дудлика по координате х на промежуток записанный в dx

		y += dy;										//перемещаем дудлика по координате y на промежуток записанный в dy

		dx = 0;											//обнулям dx иначе дудлик будет постоянно перемещаться

		if (y < 20)										//если дудлик поднимается на координаты y меньше 20
														
		{

			y = 20;										//мы оставляем дудлика на этой координате

			for (int i(0); i < 10; i++)					//работа со всеми платформами
														
			{

				platforms[i].y -= dy;					//мы опкскаем эти платформы ровно на столько
														//на сколько дудлик должен был подняться
				if (platforms[i].y > 500)				//если координата платформы больше 500 по y

				{

					platforms[i].y = 0;					//то координата плтформы по y становится равна 0

					platforms[i].x = 0 + rand() % (530 - 0 + 1);
														//а по x спавним ее в рандомном месте (от 0 до 530)
				}

			}

		}

		s_player.setPosition(x, y);						//setPosition; прекрепляет наш спрайт к координатам x y

		for (int i(0); i < 10; i++)						//работа со всеми платформами	

		{

			if (platforms[i].x < x + 10 && x - 10 <platforms[i].x + 68 && y + 40>platforms[i].y && y + 40 < platforms[i].y + 14)
														//если дудлик касается платформы то 
			{											
														
				dy = -10;								//пермещение по y равняется -10

				Score++;								//а счетчик платформ +1

			}

		}

		string str_Score = to_string(Score);			//мы создаем перменную стринг в которую задаем переменную (наш счетчик)
														//to_string; переводит intвскую переменную в строку (string)
		text.setPosition(530, 10);						//setPosition; координаты текста

		text.setString(str_Score);						//setString; то что будем выводить (в нашем случае счетчик)

		window.clear();									//очищаем окно

		window.draw(s_back);							//заново выводим задний фон

		window.draw(s_player);							//заново выводим задний дулика

		window.draw(text);								//заново выводим задний счетчик

		for (int i(0); i < 10; i++)						//заново выводим все платформы

		{

			s_platform.setPosition(platforms[i].x, platforms[i].y);

			window.draw(s_platform);

		}

		if (y > 640)									//если координаты y дудлика больше 640 то

		{

			s_gover.setPosition(203, 200);				//задаем расположение картинки

			window.draw(s_gover);						//мы ввыводим картинку "game over"

		}

		window.display();								//окно выводит то что нарисовало

	}

	return 0;							

}
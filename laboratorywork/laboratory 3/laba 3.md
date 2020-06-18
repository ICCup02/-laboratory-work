МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
​
### Отчёт по лабораторной работе №3 <br/> по дисциплине "Программирование"
<br/>
​
студента 1 курса группы ИВТ-б-о-192(1)<br/>
Абибулаев Ремзи Энверовича<br/>
направления подготовки 09.03.01 "Информатика и Вычислительная Техника"
<br/>
​
<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)<br/></td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>
<p align="center">Симферополь, 2020</p>
<hr>

**Цель:**
1. Закрепить навыки разработки программ использующих операторы цикла;
2. Закрепить навыки разработки программ использующих массивы;
3. Освоить методы подключения сторонних библиотек.

**Ход работы:**
1. Изучение библиотеки для работы с изображением.
2. Ознакомление с побитовыми операторами
3. Разбор алгоритмов кодировки сообщения в картинку.
4. Написание кода декодировки. <br>
   
Итак, перейдем к выполнению заданий.
1. Изучил библиотеку для работы с изображением, разобрался с алгоритмами кодировки.
2. Мой исходный ключ для изображения: ``` 11r 11g 11b 01r 01g 01b 10r 10g ``` 
3. Результатом изученного материала является код, благодаря которому можно декодировать сообщение из изображения:
```cpp
#include <iostream>
#include<string>
#include "libbmp.h"
#include<fstream>
int8_t defcolor(int& x, int& y, BmpImg& img) {
	static int8_t count = 1;
	if (count == 1) {
		count = 2;
		return img.red_at(x, y);
	}
	else if (count == 2) {
		count = 3;
		return img.green_at(x, y);
	}
	count = 1;
	return img.blue_at(x, y);
};
int main()
{
	std::ofstream out;
	std::string msg;
	uint8_t letter = 0;
	BmpImg img;
	int8_t bit = 0;
	img.read("pic1.bmp");
	if (BMP_OK != img.read("pic.bmp")) { return EXIT_FAILURE; }
	for (int y = img.get_height() - 1, x; y >= 0; y--)
	{
		for (x = img.get_width() - 1; x >= 0; x--)
		{
			for (int rgb = 0; rgb < 3; rgb++) {
				letter = (letter << 1) | (defcolor(x, y, img) & 1); bit++;
				if (bit == 8) {
					if ((letter & 255) == '\0' ) {
						out.open("output.txt");
						out << msg;
						out.close();return EXIT_SUCCESS;
					}
					msg = msg + static_cast<char>(letter); bit = 0;
					letter = 0;
				}
			}
		}
	}
	return EXIT_SUCCESS;
}

```
<br>

2. Вот само изображение:
<center>
<img src="code\pic1.bmp"><br>
Рис. 1. Бендер </center>

1. А вот и сам результат кода-- декодированное сообщение:
```txt
J@orge Washington (February 22, 1732[b][c] – December 14, 1799) was an American political leader, military general, statesman, and Founding Father who served as the first president of the United States from 1789 to 1797. PrevIsµsly, he led Patriot forces to victory in the nation's War for Independence. He presided at the Constitutional Convention of 1787 which established the U.S. Constitution and a federal government. Washington has been called яяя "Father of His Country" for his manifold leadership in the formative days of the new nation.
Washington received his initial military training and command with the Virginia Regiment during the French and Indian War. He waяяяater elected to the Virginia House of Burgesses and was named a delegate to the Continental Congress, where he was appointed Commanding General of the Continental Army. He commanded American forces, allied with France, in яяя defeat and surrender of the British during the Siege of Yorktown, and resigned his commission in 1783 after the signing of the Treaty of Paris.
Washington played a key role in the adoption and ratification of the Constituяяяn and was then elected president by the Electoral College in the first two elections. He implemented a strong, well-financed national government while remaining impartial in a fierce rivalry between cabinet members Thomas яяяferson and Alexander Hamilton. During the French Revolution, he proclaimed a policy of neutrality while sanctioning the Jay Treaty. He set enduring precedents for the office of president, including the title "President of яяя United States", and his Farewell Address is widely regarded as a pre-eminent statement on republicanism.
Washington owned slaves for labor and trading, and supported measures passed by Congress protecting slavery, in ordeяяяo preserve national unity. He later became troubled with the institution of slavery and freed his slaves in a 1799 will. He endeavored to assimilate Native Americans into Western culture, but responded to their hostility iяяяimes of war. He was a member of the Anglican Church and the Freemasons, and he urged broad religious freedom in his roles as general and president. Upon his death, he was eulogized as "first in war, first in peace, and first in the hearts of his countrymen." He has been memorialized by monuments, art, geographical locations, stamps, and currency, and many scholars and polls rank him among the greatest American presidents.
```
Вот как выглядит файл output.txt:
<center>
<img src="resources\images\1.PNG"><br>
Рис. 2. декодированное сообщение</center>

**Вывод:** Таким образом все цели и задачи лабораторной работы были выполнены в полном объеме. Были получены навыки работы с побитовыми операторами. Были изучены алгоритмы кодировки и декодировки сообщения из изображения. А также закрепляются знания в работе с markdown , C++.
МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
​
### Отчёт по лабораторной работе №6 <br/> по дисциплине "Программирование"
<br/>
​
студента 1 курса группы ИВТ-192(1)<br/>
Абибулаев Ремзи Энверовича 
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

Симферополь, 2019
<br/><br/>

**Цель:**
Закрепить навыки разработки многофайловыx приложений;изучить способы работы с API web-сервиса; изучить процесс сериализации/десериализации данных.

**Ход работы:**
1. Разработка сервера на С++.
2. Работа с сервисом openweathermap.org.
3. Разработка клиента для получения информации от openweathermap.org.
4. Работа с JSON.
5. Заполнение шаблона виджета.
6. Сборка итогового проекта.
Cкриншот <br>

Итак, перейдем к выполнению заданий.
1. После исследования сервиса openweathermap.org я получил следующий API ключ:"0a35d8c8abac2913bccad956424b8479".
2. Результатом разработки серверной части, клиета, работы с JSON является данный код:
```cpp
#include <httplib/httplib.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <thread>
using namespace httplib;
using std::cin;
using std::cout;
using std::string;
using namespace nlohmann;
json answer_server;
string city;
string DIR = "/data/2.5/forecast?q=";
string API = "&units=metric&appid=0a35d8c8abac2913bccad956424b8479";
string cut_double(double a, int b) {//Функция для нормального отражения погоды;
	string Return;
	int8_t integ;
	char comma = ',';
	integ = a;
	Return = std::to_string(integ);
	int counter = 0;
	if (a > 0) {
		Return.insert(0, 1, '+');
	}
	else if ((a < 0) && (a > -1)) {
		Return.insert(0, 1, '-');
	}
	if ((a > 0) || (a < 0)) {
		Return = Return + comma;
		a = a - integ;
		comma = std::to_string(fabs(a))[2];
		return Return + comma;
	}
	return Return;
}
string edition(std::string Template,int Cur_time) {//Редактор шаблона

	Template.replace(Template.find("{city.name}"), strlen("{city.name}"), city);
	if (Cur_time == 24) { Cur_time = 0; }
	string time = answer_server["list"][NULL]["dt_txt"].get<string>();
	int counter = 0;
	int start = 0;
	char null = '0';
	string cur_time ;
	cur_time=std::to_string(Cur_time);
	while ((time[11] > null) || (time[12] > null)) {
		time = answer_server["list"][counter]["dt_txt"].get<string>();
		counter++;
	}
	counter--;
	time = answer_server["list"][0]["dt_txt"].get<string>();
	if ((time[11] <= cur_time[NULL]) && (time[12] < cur_time[1])) { start =counter-(24-Cur_time)/3; };
	Template.replace(Template.find("{list.dt}"), strlen("{list.dt}"), answer_server["list"][start]["dt_txt"].get<string>().substr(0, 16));
	Template.replace(Template.find("{list.main.temp}"), strlen("{list.main.temp}"), cut_double(answer_server["list"][NULL]["main"]["temp"], 10));
	Template.replace(Template.find("{list.weather.icon}"), strlen("{list.weather.icon}"), answer_server["list"][NULL]["weather"][NULL]["icon"].get<string>());
	
	for (int i = counter+Cur_time/3; i < counter + Cur_time / 3+25; i +=8) {
		Template.replace(Template.find("{list.dt}"), strlen("{list.dt}"), answer_server["list"][i]["dt_txt"].get<string>().substr(0, 16));
		Template.replace(Template.find("{list.main.temp}"), strlen("{list.main.temp}"), cut_double(answer_server["list"][i]["main"]["temp"], 10));
		Template.replace(Template.find("{list.weather.icon}"), strlen("{list.weather.icon}"), answer_server["list"][i]["weather"][NULL]["icon"].get<string>());
	}
	return Template;
}
int gen_response(const Request& req, Response& res) {//В этой функции формируем ответ сервера на запрос
	int time = 0;
	if (req.get_param_value("city") != "")  { 
	httplib::Client cli("api.openweathermap.org", 80);
	city = req.get_param_value("city"); 
	auto res = cli.Get((DIR + city + API).c_str());
	answer_server = json::parse(res->body);
		if (res && res->status != 200) {
			cout << "Maybe you did not write the city correctly\n";exit(NULL);
		}
	};

	string Template;
	std::ifstream inf;
	inf.open("informer.html");
	getline(inf, Template, '\0');// считывание содержимого informer.html в переменную Template;
	inf.close();

	if ((req.get_param_value("time") != "") && (atoi(req.get_param_value("time").c_str()) <= 24)) {
		time = atoi(req.get_param_value("time").c_str());
	}
	else if  (atoi(req.get_param_value("time").c_str()) > 24) {
		cout << "Maybe you did not write the time correctly\n"; exit(NULL);
	};
	res.set_content(edition(Template,time), "text/html");
	// Команда set_content задаёт ответ сервера и тип ответа:
	// edition(Template) - тело ответа
	// text/html - тип ответа (в данном случае html страничка)
}
int main() {
	cout << "Write your city:";
	cin >> city;
	httplib::Client cli("api.openweathermap.org", 80);
	auto res = cli.Get((DIR + city + API).c_str());
	if (!res || res->status != 200) {
		cout << "Maybe you did not write the city correctly\n"; return EXIT_FAILURE;
	}
	answer_server = json::parse(res->body);
	
	Server svr;						// Создаём сервер (пока-что не запущен)  
	svr.Get("/", gen_response);		// Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
	svr.listen("localhost", 3000);	// Запускаем сервер на localhost и порту 3000
	svr.stop(); 
	return EXIT_SUCCESS;
}

```
<br> 

3. А вот и сам результат кода:
<center>
<img src="resources\pictures\1.PNG"><br>
Рис. 1. Заполненый шаблон</center>

**Вывод:** Таким образом все цели и задачи лабораторной работы были выполнены в полном объеме. Были получены навыки в написании сервера и клиета. Был изучен сервис openweathermap.org, а также Json, научился работать с строками с++. А также закрепляются знания в работе с markdown , C++.
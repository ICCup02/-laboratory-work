МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
​
### Отчёт по лабораторной работе № 1<br/> по дисциплине "Программирование"
<br/>
​
студента 1 курса группы ИВТ-б-о-192(1)<br/>
Абибулаев Ремзи Энверович</br>
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

Симферополь, 2020
<br/><br/>



**Цель:**
1. Научиться работать с текстовыми файлами;
2. Закрепить навыки работы со структурами.

**Код программы:**

``` c++

#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include <variant>
#include <cassert>
using std::cin;
using std::cout;
using std::endl;
using std::string;
enum AllData {
	ADPASSENGERID,
	ADSURVIVED,
	ADPCLASS,
	ADNAME,
	ADSEX,
	ADAGE,
	ADSIBSP,
	ADPARCH,
	ADTICKET,
	ADFARE,
	ADCABIN,
	ADEMBARKED,
};
enum ForStringData {
	NAME,
	SEX,
	FARE,
	CABIN,
	EMBARKED,
};
enum ForIntData {
	PASSENGERID,
	SURVIVED,
	PCLASS,
	AGE,
	SIBSP,
	PARCH,
	TICKET,
};
struct DataPeople {
	int i = 0;
	std::vector<string> DataString;
	std::vector<int> DataInt;
	DataPeople* ptr;
	void SetData(int NumberData, string data) {
		switch (NumberData) {
		case ADNAME:DataString.push_back(data);
			break;
		case ADSEX:DataString.push_back(data);
			break;
		case ADFARE:DataString.push_back(data);
			break;
		case ADCABIN:DataString.push_back(data);
			break;
		case ADEMBARKED:DataString.push_back(data);
			break;
		default:
			DataInt.push_back(atoi(data.c_str()));
		}
	}

};
struct DataForСalculation {
	int NumberSurvivors, FirstClassSurvivors, TwoClassSurvivors, ThreeClassSurvivors,
		FemaleSurvivors, MaleSurvivors, AverageAge, AgeMale,
		AgeFemale, StateCherbourg, StateQueenstown, StateSouthampton;
	string State, IdentifiersMinors;
	DataForСalculation() {
		NumberSurvivors = 0; FirstClassSurvivors = 0; TwoClassSurvivors = 0; ThreeClassSurvivors = 0;
		FemaleSurvivors = 0; MaleSurvivors = 0; AverageAge = 0; AgeMale = 0;
		AgeFemale = 0; StateCherbourg = 0; StateQueenstown = 0; StateSouthampton = 0;
		State = "";
		IdentifiersMinors = "";

	}
};
void WriteFile(DataForСalculation& allData) {
	std::ofstream out("OutputFile.txt", std::ios::out);
	out << "Общее Число выживших: " << allData.NumberSurvivors << endl;
	out << "Число выживших из 1 класса: " << allData.FirstClassSurvivors << endl;
	out << "Число выживших из 2 класса: " << allData.TwoClassSurvivors << endl;
	out << "Число выживших из 3 класса: " << allData.ThreeClassSurvivors << endl;
	out << "Количество выживших женщин: " << allData.FemaleSurvivors << endl;
	out << "Количество выживших мужчин: " << allData.MaleSurvivors << endl;
	out << "Средний возраст пассажира / женский / мужской: " << allData.AverageAge << " "
		<< allData.AgeFemale << " " << allData.AgeMale << endl;
	out << "Штат, в котором село больше всего пассажиров: " << allData.State << endl;
	out << "Список идентификаторов несовершеннолетних: " << allData.IdentifiersMinors << endl;
	out.close();
};

DataForСalculation CalculData(std::vector<DataPeople>& dataPeople) {
	DataForСalculation calculationData;
	int counterSurv = 0, counterSurvMale = 0;
	for (int i = 0; i < dataPeople.size(); i++) {
		calculationData.NumberSurvivors = calculationData.NumberSurvivors + dataPeople[i].DataInt[SURVIVED];
		if (dataPeople[i].DataInt[AGE] > 0) {
			calculationData.AverageAge += dataPeople[i].DataInt[AGE];
			counterSurv++;
		}
		if ((dataPeople[i].DataInt[AGE] < 18) && (dataPeople[i].DataInt[AGE] > 0)) {
			calculationData.IdentifiersMinors += "," + std::to_string(dataPeople[i].DataInt[PASSENGERID]);
		}
		if (dataPeople[i].DataString[EMBARKED] == "S")calculationData.StateSouthampton++;
		if (dataPeople[i].DataString[EMBARKED] == "Q")calculationData.StateQueenstown++;
		if (dataPeople[i].DataString[EMBARKED] == "C")calculationData.StateCherbourg++;
		if ((dataPeople[i].DataInt[PCLASS] == 1) && (dataPeople[i].DataInt[SURVIVED] == 1))calculationData.FirstClassSurvivors++;
		if ((dataPeople[i].DataInt[PCLASS] == 2) && (dataPeople[i].DataInt[SURVIVED] == 1))calculationData.TwoClassSurvivors++;
		if ((dataPeople[i].DataInt[PCLASS] == 3) && (dataPeople[i].DataInt[SURVIVED] == 1))calculationData.ThreeClassSurvivors++;
		if ((dataPeople[i].DataString[SEX] == "female") && (dataPeople[i].DataInt[AGE] > 0)) calculationData.AgeFemale += dataPeople[i].DataInt[AGE];
		if ((dataPeople[i].DataString[SEX] == "male") && (dataPeople[i].DataInt[AGE] > 0)) {
			calculationData.AgeMale += dataPeople[i].DataInt[AGE];
			counterSurvMale++;
		}
		if ((dataPeople[i].DataString[SEX] == "female") && (dataPeople[i].DataInt[SURVIVED] == 1))calculationData.FemaleSurvivors++;
		if ((dataPeople[i].DataString[SEX] == "male") && (dataPeople[i].DataInt[SURVIVED] == 1))calculationData.MaleSurvivors++;

	}
	if ((calculationData.StateSouthampton > calculationData.StateQueenstown) && (calculationData.StateSouthampton > calculationData.StateCherbourg))calculationData.State = "Southampton";
	else if ((calculationData.StateQueenstown > calculationData.StateSouthampton) && (calculationData.StateQueenstown > calculationData.StateCherbourg))calculationData.State = "Queenstown";
	else calculationData.State = "Cherbourg";
	calculationData.IdentifiersMinors = calculationData.IdentifiersMinors.substr(1, calculationData.IdentifiersMinors.length() - 1);
	calculationData.AverageAge /= counterSurv;
	calculationData.AgeMale /= counterSurvMale;
	calculationData.AgeFemale /= (counterSurv - counterSurvMale);
	return calculationData;
};
int main()
{
	std::vector<DataPeople> dataPeople;
	DataPeople tempData;
	string temp = "";
	std::ifstream trainScv("train.csv");
	char ch;
	string str;
	int coutnerForQuotes = 0, counterOneData = 0;
	while (trainScv.get(ch)) {
		if (ch == '"') {
			coutnerForQuotes++;
			continue;
		}
		else if ((ch == ',') && (coutnerForQuotes != 3)) {
			//cout << counterOneData << '\n';
			tempData.SetData(counterOneData, temp);
			counterOneData++;
			temp = "";
			continue;
		}
		if (ch == '\n') {
			coutnerForQuotes = 0;
			tempData.SetData(counterOneData, temp);
			dataPeople.push_back(tempData);
			tempData.DataString.clear();
			tempData.DataInt.clear();
			counterOneData = 0;
			temp = "";
		}
		temp = temp + ch;
	}
	dataPeople.erase(dataPeople.begin());

	DataForСalculation ResultCalc = CalculData(dataPeople);
	WriteFile(ResultCalc);
	trainScv.close();
	dataPeople.clear();
	return EXIT_SUCCESS;
}

```

<a href="code/main/OutputFile.txt">Файл с результатами расчета</a>

<br/>

| Характеристика | Результат  |
|:-:|:-:|
| Общее число выживших | 342  |
| Число выживших из 1 класса | 136 |
| Число выживших из 2 класса | 87 |
| Число выживших из 3 класса | 119 |
| Количество выживших женщин | 233 |
| Количество выживших мужчин | 109 |
| Средний возраст пассажира | 29 |
| Средний возраст женский | 28 |
| Средний возраст мужчин | 31 |
| Штат, в котором село больше всего пассажиров: | Southampton |
| Список идентификаторов несовершеннолетних | 6,8,10,11,15,17,18,20,23,25,27,29,30,32,33,37,40,43,44,46,47,48,49,51,56,<br/>59,60,64,65,66,69,72,77,78,79,83,85,87,88,96,102,108,110,112,115,120,<br/>122,126,127,129,139,141,148,155,157,159,160,164,165,166,167,169,172,<br/>173,177,181,182,183,184,185,186,187,194,197,199,202,206,209,215,221,<br/>224,230,234,236,238,241,242,251,257,261,262,265,267,271,275,278,279,<br/>283,285,296,298,299,301,302,304,305,306,307,308,325,330,331,334,335,<br/>336,341,348,349,352,353,355,359,360,365,368,369,375,376,382,385,387,<br/>389,390,408,410,411,412,414,416,420,421,426,429,432,434,436,445,446,<br/>447,449,452,455,458,460,465,467,469,470,471,476,480,481,482,486,490,<br/>491,496,498,501,503,505,508,512,518,523,525,528,531,532,533,534,536,<br/>539,542,543,548,550,551,553,558,561,564,565,569,574,575,579,585,590,<br/>594,597,599,602,603,612,613,614,619,630,634,635,640,643,644,645,649,<br/>651,654,657,668,670,675,681,684,687,690,692,693,698,710,712,719,721,<br/>722,728,732,733,739,740,741,747,751,752,756,761,765,767,769,774,777,<br/>778,779,781,782,784,788,789,791,792,793,794,803,804,814,816,820,825,<br/>826,827,828,829,831,832,833,838,840,842,845,847,850,851,853,854,860,<br/>864,869,870,876,879,889 |

# Вывод
В данной работе получены навыки работы с текстовыми файлами, ознакомились с форматом ***CSV***, а также закреплены навыки работы со структурами
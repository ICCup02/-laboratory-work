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
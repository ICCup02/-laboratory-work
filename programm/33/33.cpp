#include<math.h>
#include <iostream>
#include <ctime>
#include<cmath>
enum {
	ADDFORCE,
	ADDHEALTH,
	ADDDEFENCE,
	ADDAGILITY,
	ADDCRITICAL,
};
class Fighter {
	int HealthPoints, Health, ForcePoints, DefensePoints, AgilityPoints, CriticalPoints, Points;
public:
	Fighter() {
		Health = 100;
		HealthPoints = 0;
		ForcePoints = 0;
		CriticalPoints = 0;
		DefensePoints = 0;
		AgilityPoints = 0;
		Points = 10;

	};
	Fighter(int HealthPoints, int CriticalPoints, int DefensePoints, int AgilityPoints, int ForcePoints) {
		this->HealthPoints = HealthPoints;
		this->CriticalPoints = CriticalPoints;
		this->DefensePoints = DefensePoints;
		this->ForcePoints = ForcePoints;
		this->AgilityPoints = AgilityPoints;
		Health = 100 + this->HealthPoints * 100;
		Points = 0;
	};
	bool AddHealthPoints(int points) {
		if (points <= Points) {
			HealthPoints += points;
			Health = 100 + this->HealthPoints * 100;
			Points -= points;
			return true;
		}
		else return false;
	};
	bool AddForcePoints(int points) {
		if (points <= Points) {
			ForcePoints += points;
			Points -= points;
			return true;
		}
		else return false;
	};
	bool AddCriticalPoints(int points) {
		if (points <= Points) {
			CriticalPoints += points;
			Points -= points;
			return true;
		}
		else return false;
	};
	bool AddDefensePoints(int points) {
		if (points <= Points) {
			DefensePoints += points;
			Points -= points;
			return true;
		}
		else return false;
	};
	bool AddAgilityPoints(int points) {
		if (points <= Points) {
			AgilityPoints += points;
			Points -= points;
			return true;
		}
		else return false;
	};
	double Attack() {
		return (Force() * (1 + Critical()));
	};
	double Damage(double& dmg) {
		dmg = (1 - agility()) * Defence() * dmg;
		Health -= dmg;
		return dmg;
	}
	bool IsDead() {
		return (Health <= 0);
	}
private:
	double Force() {
		return (1 + ForcePoints);
	};
	bool Critical() {

		double randomNumber;
		randomNumber = rand() % 100;
		randomNumber /= 100;
		return randomNumber > (1 / (1 + pow((CriticalPoints / 4.0), 4)));
	};
	double Defence() {
		return (1 / (1 + pow((DefensePoints / 4.0), 4)));
	};
	bool agility() {

		double randomNumber;
		randomNumber = rand() % 100;
		randomNumber /= 100;
		return randomNumber > (1 / (1 + pow((AgilityPoints / 4.0), 4)));
	}

};
void InitForBot(int& health, int& criticalDamage, int& defenseDamage, int& agility, int& force) {

	health = rand() % 10;
	criticalDamage = rand() % 10;
	defenseDamage = rand() % 10;
	agility = rand() % 10;
	force = rand() % 10;

};
void distributionofpoints(Fighter& fighter) {
	int randompointincrease = rand() % 5;
	for (int i = 0; i < 10; i++)
	{
		switch (randompointincrease) {
		case ADDFORCE:
			fighter.AddForcePoints(1);
			break;
		caseADDHEALTH:
			fighter.AddHealthPoints(1);
			break;
		case ADDDEFENCE:
			fighter.AddDefensePoints(1);
			break;
		case ADDAGILITY:
			fighter.AddAgilityPoints(1);
			break;
		case ADDCRITICAL:
			fighter.AddCriticalPoints(1);
			break;
		}
	}
}
void InitForPlayer(int& health, int& criticalDamage, int& defenseDamage, int& agility, int& force) {
	std::cout << "Write character your personage:\n"
		<< "Personage health:";
	std::cin >> health;
	std::cout << "\nPersonage criticalDamage:";
	std::cin >> criticalDamage;
	std::cout << "\nPersonage defenseDamage:";
	std::cin >> defenseDamage;
	std::cout << "\nPersonage agility:";
	std::cin >> agility;
	std::cout << "\nPersonage force:";
	std::cin >> force;
	std::cout << "\n";
};
void Game(int whoPlaysWithWhom) {
	int health, criticalDamage, defenseDamage, agility, force;
	int numberPlayer = 0;
	double dmg;
	if (whoPlaysWithWhom != 3) {
		InitForBot(health, criticalDamage, defenseDamage, agility, force);
		Fighter player1(health, criticalDamage, defenseDamage, agility, force);
		distributionofpoints(player1);
		if (whoPlaysWithWhom == 2) {
			InitForPlayer(health, criticalDamage, defenseDamage, agility, force);
			Fighter player2(health, criticalDamage, defenseDamage, agility, force);
			while ((!player1.IsDead()) && (!player2.IsDead())) {
				if (numberPlayer == 0) {
					dmg = player1.Attack();
					player2.Damage(dmg);
					numberPlayer = 1;
					std::cout << "Player received damage of " << dmg << " units" << std::endl;
				}
				else {
					dmg = player2.Attack();
					player1.Damage(dmg);
					numberPlayer = 0;
					std::cout << "Bot received damage of " << dmg << " units" << std::endl;
				}				
			}
			if (numberPlayer == 1) {
				std::cout << "Bot winner" << std::endl;
			}
			else {
				std::cout << "Player winner" << std::endl;
			}
		}
		else {
			InitForBot(health, criticalDamage, defenseDamage, agility, force);
			Fighter player2(health, criticalDamage, defenseDamage, agility, force);
			distributionofpoints(player2);
			while ((!player1.IsDead()) && (!player2.IsDead())) {
				if (numberPlayer == 0) {
					dmg = player1.Attack();
					player2.Damage(dmg);
					numberPlayer = 1;
				}
				else {
					dmg = player2.Attack();
					player1.Damage(dmg);
					numberPlayer = 0;
				}
				std::cout << "Bot " << numberPlayer + 1 << " received damage of " << dmg << " units" << std::endl;
			}
			std::cout << "Bot " << ((numberPlayer==0) ? 2:1) << " winner" << std::endl;

		}
	}
	else if (whoPlaysWithWhom == 3) {
		InitForPlayer(health, criticalDamage, defenseDamage, agility, force);
		Fighter player1(health, criticalDamage, defenseDamage, agility, force);
		InitForPlayer(health, criticalDamage, defenseDamage, agility, force);
		Fighter player2(health, criticalDamage, defenseDamage, agility, force);
		while ((!player1.IsDead()) && (!player2.IsDead())) {
			if (numberPlayer == 0) {
				dmg = player1.Attack();
				player2.Damage(dmg);
				numberPlayer = 1;
			}
			else {
				dmg = player2.Attack();
				player1.Damage(dmg);
				numberPlayer = 0;
			}
			std::cout << "User " << numberPlayer + 1 << " received damage of " << dmg << " units" << std::endl;
		}
		std::cout << "User " << ((numberPlayer == 0) ? 2 : 1) << " winner" << std::endl;

	}

};
int main() {
	srand(time(NULL));
	int whoPlaysWithWhom = 0;
	std::cout << "Select the battle mode:\n" << "1 - Bot and Bot\n" << "2 - Bot and User\n" << "3 - User and User\n";
	std::cin >> whoPlaysWithWhom;
	Game(whoPlaysWithWhom);
}


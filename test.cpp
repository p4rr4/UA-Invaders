#include <iostream>
#include <unistd.h>

using namespace std;

void initialAnimation(char &answer);
void mainMenu(int &opt, int &instr);
void printLetter();
void credits(int &opt, int &instr);
void clearbuffer();
void menuJugar(int &opt, int &instr);


int main() {
	char ans;
	int option,instr;
	char name[4];
	instr = 0;

	initialAnimation(ans);
	printLetter();

	cout << "\n\n\t\t\t\t\t\t\u001b[34mEɳƚҽɾ ყσυɾ ɳαɱҽ (3 ʅҽƚƚҽɾʂ): ";
	cin >> name;
	mainMenu(option, instr);

	while (instr==1) {
		menuJugar(option, instr);
	}
	return 0;
}

void initialAnimation(char &answer) {

	system("clear");
	cout << "\n\n\n";
	usleep(100000);
	cout << "\t\t\033[0;32m █    ██  ▄▄▄          ██▓ ███▄    █ ██▒   █▓ ▄▄▄      ▓█████▄ ▓█████  ██▀███    ██████ \n";
	usleep(100000);
	cout << "\t\t\033[0;32m ██  ▓██▒▒████▄       ▓██▒ ██ ▀█   █▓██░   █▒▒████▄    ▒██▀ ██▌▓█   ▀ ▓██ ▒ ██▒▒██    ▒ \n";
	usleep(100000);
	cout << "\t\t\033[0;32m▓██  ▒██░▒██  ▀█▄     ▒██▒▓██  ▀█ ██▒▓██  █▒░▒██  ▀█▄  ░██   █▌▒███   ▓██ ░▄█ ▒░ ▓██▄   \n";
	usleep(100000);
	cout << "\t\t\033[0;32m▓▓█  ░██░░██▄▄▄▄██    ░██░▓██▒  ▐▌██▒ ▒██ █░░░██▄▄▄▄██ ░▓█▄   ▌▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒\n";
	usleep(100000);
	cout << "\t\t\033[0;32m▒▒█████▓  ▓█   ▓██▒   ░██░▒██░   ▓██░  ▒▀█░   ▓█   ▓██▒░▒████▓ ░▒████▒░██▓ ▒██▒▒██████▒▒\n";
	usleep(500000);
	cout << "\t\t\033[0;32m░▒▓▒ ▒ ▒  ▒▒   ▓▒█░   ░▓  ░ ▒░   ▒ ▒   ░ ▐░   ▒▒   ▓▒█░ ▒▒▓  ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░\n";
	usleep(500000);
	cout << "\t\t\033[0;32m░░▒░ ░ ░   ▒   ▒▒ ░    ▒ ░░ ░░   ░ ▒░  ░ ░░    ▒   ▒▒ ░ ░ ▒  ▒  ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░\n";
	usleep(500000);
	cout << "\t\t\033[0;32m ░░░ ░ ░   ░   ▒       ▒ ░   ░   ░ ░     ░░    ░   ▒    ░ ░  ░    ░     ░░   ░ ░  ░  ░  \n";
	usleep(500000);
	cout << "\t\t\033[0;32m   ░           ░  ░    ░           ░      ░        ░  ░   ░       ░  ░   ░           ░  \n";
	usleep(500000);
	cout << "\t\t\033[0;32m                                         ░              ░                               \n";
	usleep(500000);
	
	cout << "\n\n\t\t\t\t\t\t\u001b[34mPɾҽʂʂ ENTER ƚσ ƈσɳƚιɳυҽ...";
	cin.get();
}

void mainMenu(int &opt, int &instr) {
	
	printLetter();

	opt = 0;
	instr = 0;

	do {
		clearbuffer();
		cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Pʅαყ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Iɳʂƚɾυƈƚισɳʂ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Cɾҽԃιƚʂ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Qυιƚ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
		cin>>opt;
		if (!(opt<=4 & opt>=1)) {
				cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ\n";
		}
	}while (!(opt<=4 & opt>=1));
	switch (opt) {
	case 1:
		instr = 1;
		break;
	case 2:
		//Instrucciones
		break;
	case 3:
		credits(opt, instr);
		break;
	case 4:
		cout << "\n\n\t\t\t\t\t\t\u001b[34mᎶᎧᎧᎴᏰᎩᏋ\n";
		exit(0);
	default:
		break;
	}

}

void printLetter(){
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\033[0;32m █    ██  ▄▄▄          ██▓ ███▄    █ ██▒   █▓ ▄▄▄      ▓█████▄ ▓█████  ██▀███    ██████ \n";
	cout << "\t\t\033[0;32m ██  ▓██▒▒████▄       ▓██▒ ██ ▀█   █▓██░   █▒▒████▄    ▒██▀ ██▌▓█   ▀ ▓██ ▒ ██▒▒██    ▒ \n";
	cout << "\t\t\033[0;32m▓██  ▒██░▒██  ▀█▄     ▒██▒▓██  ▀█ ██▒▓██  █▒░▒██  ▀█▄  ░██   █▌▒███   ▓██ ░▄█ ▒░ ▓██▄   \n";
	cout << "\t\t\033[0;32m▓▓█  ░██░░██▄▄▄▄██    ░██░▓██▒  ▐▌██▒ ▒██ █░░░██▄▄▄▄██ ░▓█▄   ▌▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒\n";
	cout << "\t\t\033[0;32m▒▒█████▓  ▓█   ▓██▒   ░██░▒██░   ▓██░  ▒▀█░   ▓█   ▓██▒░▒████▓ ░▒████▒░██▓ ▒██▒▒██████▒▒\n";
	cout << "\t\t\033[0;32m░▒▓▒ ▒ ▒  ▒▒   ▓▒█░   ░▓  ░ ▒░   ▒ ▒   ░ ▐░   ▒▒   ▓▒█░ ▒▒▓  ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░\n";
	cout << "\t\t\033[0;32m░░▒░ ░ ░   ▒   ▒▒ ░    ▒ ░░ ░░   ░ ▒░  ░ ░░    ▒   ▒▒ ░ ░ ▒  ▒  ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░\n";
	cout << "\t\t\033[0;32m ░░░ ░ ░   ░   ▒       ▒ ░   ░   ░ ░     ░░    ░   ▒    ░ ░  ░    ░     ░░   ░ ░  ░  ░  \n";
	cout << "\t\t\033[0;32m   ░           ░  ░    ░           ░      ░        ░  ░   ░       ░  ░   ░           ░  \n";
	cout << "\t\t\033[0;32m                                         ░              ░                               \n";
}

void credits(int &opt, int &instr) {
	char ans1;
	printLetter();
	cout << "\n\n\t\t\t\t\t\t\u001b[34mAԃɾιáɳ Tҽɳԃҽɾσ Gαɾƈíα";
	cout << "\n\n\t\t\t\t\t\t\u001b[34mAʅҽʝαɳԃɾσ Bҽɳιƚσ Mαɾƈσʂ";
	cout << "\n\n\t\t\t\t\t\t\u001b[34mJҽʂúʂ Pαɾɾα Gαɾƈíα";
	do {
		cout << "\n\n\t\t\t\t\t\t\u001b[34mExιƚ (e): ";
		cin >> ans1;
		if (ans1!='e') {
				cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ\n";
		}
	}while(ans1!='e');
	mainMenu(opt, instr);



}

void clearbuffer() {    
	char c;
	do {
		c = getchar();
	}while (c != '\n' && c != EOF);
}

void menuJugar(int &opt, int &instr) {
	opt = 0;
	instr = 1;
	printLetter();
		do {
			cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Lҽʋҽʅ 1 (Tυƚσɾιαʅ)";
			cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Lҽʋҽʅ 2 (Iɳƚҽɾɱҽԃιαƚҽ)";
			cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Lҽʋҽʅ 3 (Hαɾԃ)";
			cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Bαƈƙ";
			cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
			cin>>opt;
			if (!(opt<=4 & opt>=1)) {
				cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ\n";
			}
		} while (!(opt<=4 & opt>=1));
		switch (opt){
			case 1:
				//Instrucciones nivel 1
				break;
			case 2:
				//Instrucciones nivel 2
				break;
			case 3:
				//instrucciones nivel 3
				break;
			case 4:
				mainMenu(opt, instr);
				break;
			default:
				break;
			}
}
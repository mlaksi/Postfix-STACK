#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Node {
	int data;
	struct Node* next;
};

struct Node* top = NULL;

void push(int val) {
	struct Node* newnode = (struct Node*) malloc(sizeof(struct Node));
	newnode->data = val;
	newnode->next = top;
	top = newnode;
}

int pop() {

	int x;
	if (top == NULL) {
		cout << "ERROR: Stack Underflow" << endl;
		x = -1;
	}
	else {
		struct Node* p = top;
		top = p->next;
		x = p->data;
		delete p;
	}
	return x;
}

void display() {
	struct Node* ptr;
	if (top == NULL)
		cout << "Prazan stek!";
	else {
		ptr = top;
		cout << "Stanje steka: ";
		while (ptr != NULL) {
			cout << ptr->data << " ";
			ptr = ptr->next;
		}
	}
	cout << endl;
}

int countVariables(string pfix)
{
	int brProm=0;
	for (int i = 0; i < pfix.size(); ++i)
	{
		if (isupper(pfix[i])) ++brProm;
	}
	return brProm;
}

int* setVariables(int brProm)
{

	int* nizPromenljivih = new int[brProm];
	for (int i = 0; i < brProm; ++i)
	{
		cin >> nizPromenljivih[i]; //korisnik unosi zeljene vrednosti, koje bivaju smestene u niz
	}
	
	return nizPromenljivih;

}


void changeVariables(int indeks, int newValue, int* niz)
{
	for (int i = 0; i < indeks; ++i)
	{
		niz++;
	}

	*niz = newValue;

}

int checkInputType(char currentChar)
{
	bool uppercase = isupper(currentChar);
	if (uppercase) return 1;
	bool operacija=false;
	if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/')
		operacija = true;
	if (operacija) return 2;

	if (!uppercase || !operacija) return -1;



}

int evaluateExpression(string pfix, int* pNiz)
{
	int tipClana;
	//int* tipClana=new int[pfix.size()];
	for (int i = 0; i < pfix.size(); i++)
	{
		tipClana=checkInputType(pfix[i]);
		switch (tipClana)
		{
		case -1:
			cout << "Nedozvoljeni simbol!" << endl;
			break;
		case 1:
			push(*pNiz);
			pNiz++;
			display();
			break;
		case 2:
			int oprnd2 = pop();
			int oprnd1 = pop();
			int rezultat;

			int tipOperatora;
			if (pfix[i] == '+') { tipOperatora = 1; rezultat = oprnd1 + oprnd2; }

			if (pfix[i] == '-') { tipOperatora = 2; rezultat = oprnd1 - oprnd2; }
			if (pfix[i] == '*') { tipOperatora = 3; rezultat = oprnd1 * oprnd2; }
			if (pfix[i] == '/') { tipOperatora = 4; rezultat = oprnd1 / oprnd2; }

			push(rezultat);
			display();
			break;
		}
		
	}

	int krajRacuna = pop();
	if (top == NULL)
		return krajRacuna;
	else {
		cout << "Greska u izrazu!" << endl;
		return -1;
	}


}

int main() {
	cout << "Izaberite zeljenu opciju: " << endl << endl;
	cout << "1. Unos izraza u postfiksnoj notaciji." << endl;
	cout << "2. Unos vrednosti promenljivih." << endl;
	cout << "3. Izracunaj vrednost izraza." << endl;
	cout << "4. Promeni vrednosti promenljivih." << endl;
	cout << "5. Zavrsi." << endl;
	int izbor;
	string postfix;
	int brojPromenljivih=0;
	int racun;
	int indeksProm;
	int novaVrednost;

	while (true) {
		cin >> izbor;
		switch (izbor)
		{
		case 1:
			cout << "Unesite zeljeni izraz u ispravnom formatu: " << endl;
			cin >> postfix;
			int tipClana;
			
			for (int i = 0; i < postfix.size(); i++)
			{
				tipClana = checkInputType(postfix[i]);
				if (tipClana == -1)
				{
					cout << "Neispravan izraz!" << endl;
					exit(-1);
				}
			}
			
			
			break;
		case 2:
			cout << "Unesite zeljene vrednosti promenljivih: " << endl;
			brojPromenljivih = countVariables(postfix);
			static int* pNiz;
			pNiz=setVariables(brojPromenljivih);
			

			break;
		case 3:
			racun = evaluateExpression(postfix, pNiz);
			cout << "Vrednost unetog izraza za date vrednosti je: " << racun<<endl;
			break;
		case 4:
			cout << "Unesite indeks zeljene promenljive u izrazu: " << endl;
			cin >> indeksProm;
			cout << "Unesite novu vrednost promenljive: " << endl;
			cin >> novaVrednost;
	
			
			changeVariables(indeksProm, novaVrednost, pNiz);
			break;
		case 5:
			exit(0);
		}
	}
	
	system("pause");
	return 0;
}
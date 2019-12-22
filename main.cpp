#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <conio.h>
#include <iomanip>
using namespace std;
struct medicine{
	char name[15];
	char company_name[15];
	char expirydate[6];
	int price;
	int stock;
};
inline void displayline(int,char);
inline bool login(char []);
void changePin();
void addmedicine();
void editmedicine();
void deletemedicine();
void showlistofMedicines();
void searchMedicine();
void updateStock();

int main()
{
	char pin[5];
	cout<<"Enter Password(<5)(1 attempt left): ";
	cin.getline(pin,5);
	if(!login(pin)) exit(1);
for(;;){
	system("CLS");
	int choice;
	cout<<"\n\t\t\tPHARMECY MANAGEMENT SYSTEM\n";
	cout<<"\n\n\t\t\tChoose From the Following: \n\n";
	cout<<"1 -> Add New Medicine "<<endl;
	cout<<"2 -> Show Available Medicines "<<endl;
	cout<<"3 -> Search Medicine "<<endl;
	cout<<"4 -> Modify Medicine Name "<<endl;
	cout<<"5 -> Delete Medicine "<<endl;
	cout<<"6 -> Update Stock of Medicine "<<endl;
	cout<<"7 -> Change Login Password"<<endl;
	cout<<"8 -> Exit"<<endl;
	cout<<"\nEnter Your Choice: ";
	cin>>choice;
	switch(choice){
		case 1: addmedicine(); 			break;
		case 2: showlistofMedicines();  break;
		case 3: searchMedicine(); 		break;
		case 4: editmedicine();			break;
		case 5: deletemedicine();		break;
		case 6: updateStock();			break;
		case 7: changePin();			break;
		case 8: exit(1);
		default:
		cout<<"\nInvalid Choice, Try Again\n";
		break;
	}
	getch();
}
return 0;
}
void addmedicine(){
	cin.ignore();
	medicine temp;
	fstream file("record.txt",ios::app );
	cout<<"Enter medicine Name: ";
	cin.getline(temp.name,15);
	file<<temp.name<<"|";
	cout<<"Enter Company name: ";
	cin.getline(temp.company_name,15);
	file<<temp.company_name<<"|";
	cout<<"Enter expiry Date (mm \"-\" yy): ";
	cin>>temp.expirydate;
	file<<temp.expirydate<<"|";
	cout<<"Enter Price of medicine: ";
	cin>>temp.price;
	file<<"$"<<temp.price<<"|";
	cout<<"Enter number of Stock: ";
	cin>>temp.stock;
	file<<temp.stock<<"|\n"<<endl;
	file.close();
	cout<<"\nMedicine Added Successfully\n";
}
void showlistofMedicines(){
	displayline(80,'-');
	char temp[50];
	ifstream file("record.txt");
	while(file.getline(temp,50)){
		char * pch;
 		 pch = strtok (temp,"|");
		 while (pch != NULL){
 		   cout<<setw(15)<<pch;
 		   pch = strtok (NULL, "|");
		}
	cout<<endl;
	}
	file.close();
}
void searchMedicine(){
	char name[15],temp[50];
	int i=1; 
	cout<<"\nEnter Name of Medicine: "; 
	cin.ignore(); 
	cin.getline(name,15);
	ifstream file("record.txt");
	while(file.getline(temp,50)){
		if(strnicmp(name,temp,strlen(name))==0){
			if(i==1) displayline(80,'-');
			i++;
			char *token;
			token = strtok(temp,"|");
			while(token != NULL){
 		  	    cout<<setw(15)<<token;
 		   	    token = strtok (NULL, "|");
			}
		cout<<endl;
		}
	}
	file.close();
}
void updateStock(){
	char temp[50],find[15];
	cout<<"\nEnter The Name of The Medicine: ";
	cin.ignore();
	cin.getline(find,15);
	ifstream file("record.txt");
	ofstream tempfile("TEMP.txt");
	while(file.getline(temp,50)){
		bool check=false;
		char *token;
		token = strtok(temp,"|");
		for(int i=1;token != NULL;i++){
 		  	if(i==1 && stricmp(find,token)==0){
 	  	    	tempfile<<token<<"|";
 	  	    	check=true;
			}
			else if(i==5 && check==true){
				int stock;
				cout<<"Enter New Stock: ";
				cin>>stock;
				tempfile<<stock<<"|";
				cout<<"\nStock updated Successfully\n";
			}
			else{
				tempfile<<token<<"|";
			}
 		   	token = strtok (NULL, "|");
			}
		tempfile<<endl;
			
	}
	file.close();
	tempfile.close();
	remove("record.txt");
	rename("TEMP.txt","record.txt");
	
}
void editmedicine(){
	char temp[50],replace[15],find[15];
	cout<<"\nEnter Name of Medicine, You want to modify: ";
	cin.ignore();
	cin.getline(find,15);
	ifstream file("record.txt");
	ofstream tempfile("TEMP.txt");
	while(file.getline(temp,50)){
		char *token;
		token = strtok(temp,"|");
		while(token != NULL){
 		  	if(stricmp(find,token)==0){
 		      	cout<<"Enter the new Name: ";
 		    	cin.getline(replace,15);
 	  	    	tempfile<<replace<<"|";
 	  	    	cout<<"\nName Changed Successfully.\n";
			}
			else{
				tempfile<<token<<"|";
			}
 		   	token = strtok (NULL, "|");
			}
		tempfile<<endl;
			
	}
	file.close();
	tempfile.close();
	remove("record.txt");
	rename("TEMP.txt","record.txt");
}
void deletemedicine(){
	char temp[50],find[15];
	cout<<"\nEnter Name of Medicine, You want to delete: ";
	cin.ignore();
	cin.getline(find,15);
	ifstream file("record.txt");
	ofstream tempfile("TEMP.txt");
	while(file.getline(temp,50)){
		bool check=false;
		char *token;
		token = strtok(temp,"|");
		while(token != NULL){
 		  	if(stricmp(find,token)==0){
 	  	    	cout<<"\n"<<find<<" deleted Successfully.\n";
 	  	    	check=true;
			}
			else{
				if(!check)	tempfile<<token<<"|";
			}
 		token = strtok (NULL, "|");
		}
		if(!check)tempfile<<endl;	
	}
	file.close();
	tempfile.close();
	remove("record.txt");
	rename("TEMP.txt","record.txt");
}
bool login(char pin[5]){
	int temp[5];
	ifstream PWfile("password.txt");
	if(!PWfile.is_open()){
		ofstream file("password.txt");
		file<<"97 98 99 100";
		file.close();
	}
	PWfile.open("password.txt",ios::in);
	for(int i=0;PWfile>>temp[i];i++){
		if((char)temp[i]!=pin[i]){
			PWfile.close();
			return false;
		}
	}
	return true;
}
void changePin(){
	char temp[5];
	cout<<"Enter previous Password: ";
	cin>>temp;
	if(login(temp)==true){
		ofstream PWfile("password.txt");
		cout<<"Enter New Password(<5): ";
		for(int i=0;i<5;i++){
			temp[i]=getch();
			if(temp[i]=='\r') break;
			cout<<"*";
			PWfile<<(int)temp[i]<<" ";
		}
	PWfile.close();
	cout<<"\nPassword Changed Successfully\n";
	}
	else cout<<"Incorrect Password!";
}
void displayline(int n,char ch){
	cout<<"\n\tName \t Company Name \t    ExpiryDate  \t Price \t     ItemsLeft  \n";
	for(int i=0;i<n;i++) cout<<ch;
}

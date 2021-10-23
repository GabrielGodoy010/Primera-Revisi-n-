#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
	 #define color SetConsoleTextAttribute
using namespace std;

				void dibujarCuadro(int x1,int y1,int x2,int y2);
			void gotoxy(int x,int y);
				
struct Traductor
{
	char palabra[50];
	char traduccion[70];
	char funcion[250];
}; 	Traductor traductor;

void ingresar(){
	char continuar;
	FILE* archivo = fopen("Traducciones.dat","ab");
	string palabra,traduccion, funcion;

	do{
		system("cls");
		fflush(stdin);
		gotoxy (4,2);cout<<"Ingrese la palabra: ";
		cin>>traductor.palabra;
		cin.ignore();
		gotoxy (4,4);cout<<"Ingrese la traduccion: ";
		getline(cin,traduccion);
		strcpy(traductor.traduccion, traduccion.c_str());
		gotoxy (4,6);cout<<"Ingrese la funcion: ";
		getline(cin,funcion);
		strcpy(traductor.funcion,funcion.c_str());
		fwrite(&traductor,sizeof(Traductor),1,archivo);
		gotoxy (4,8);cout<<"\nDesea Agregar Otra palabra (s/n): ";
		cin>>continuar;
	} while(continuar=='s'||continuar=='S');

	fclose(archivo);
}

void leer(){
	FILE* archivo = fopen("Traducciones.dat","rb");
	if (!archivo){
		archivo = fopen("Traducciones.dat","w+b");;
	}
	int registro = 0;
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		gotoxy (4,0);cout<<"___________________________________________________________"<<endl;
		gotoxy (4,2);cout<<"¦id: "<<registro<<endl;
		gotoxy (4,4);cout<<"¦Palabra: "<<traductor.palabra<<endl;
		gotoxy (4,6);cout<<"¦Traduccion: "<<traductor.traduccion<<endl;
		gotoxy (4,8);cout<<"¦Funcion: "<<traductor.funcion<<endl;
		gotoxy (4,10);cout<<"___________________________________________________________"<<endl;
		fread(&traductor,sizeof(Traductor),1,archivo);
		registro+=1;
	} while (feof(archivo) ==0);
	cout<<endl;
	fclose(archivo);
}

void actualizar()
{
	FILE* archivo = fopen("Traducciones.dat","r+b");
	string palabra, traduccion, funcion;
	int id=0;
	gotoxy (4,2);cout<<"Que registro desea modificar (id): "; cin>>id;
	cin.ignore();
	fseek(archivo,id* sizeof(Traductor), SEEK_SET);
	gotoxy (4,4);cout<<"Ingrese la palabra: ";getline(cin, palabra);
	strcpy(traductor.palabra, palabra.c_str());
	gotoxy (4,6);cout<<"Ingrese nueva traduccion: ";getline(cin, traduccion);
	strcpy(traductor.traduccion, traduccion.c_str());
	gotoxy (4,8);cout<<"Ingrese la funcion: ";getline(cin, funcion);
	strcpy(traductor.funcion, funcion.c_str());
	fwrite(&traductor,sizeof(Traductor),1,archivo);
	fclose(archivo);
}

void buscar()
{
	FILE* archivo = fopen("Traducciones.dat","rb");	
	int	 indice=0,pos=0;
	char palabra[100];
	gotoxy (4,12);cout<<"Buscar palabra:";
	cin>>palabra;
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		if(strcmp(traductor.palabra,palabra)==0)
		{
			pos = indice;
		}
		fread(&traductor,sizeof(Traductor),1,archivo);
		indice+=1;
		
	} while (feof(archivo)==0);
	fseek(archivo,pos * sizeof(Traductor),SEEK_SET);
	fread(&traductor,sizeof(Traductor),1,archivo);
		
	cout<<endl<<endl<<"_____________"<<pos<<"__________________"<<endl;
	cout<<"___________________________________________________________"<<endl;
	cout<<"Palabra: "<<traductor.palabra<<endl;
	cout<<"Traduccion: "<<traductor.traduccion<<endl;
	cout<<"Funcion: "<<traductor.funcion<<endl;
	cout<<"___________________________________________________________"<<endl;
	
	fclose(archivo);	
}

void eliminar()
{
	int id;
	double total;
	char palabra [100];
	FILE * archivo=fopen("Traducciones.dat","rb");
	FILE * auxiliar=fopen("auxiliar.dat","wb");
	cout<<"Busque la palabra que desea eliminar: ";cin>>palabra;
	fread(&traductor,sizeof(Traductor),1,archivo);
	while(!feof(archivo))
	{
		fwrite(&traductor,sizeof(Traductor),1,auxiliar);
		if(strcmp(traductor.palabra,palabra)==0)
		{
			int pos=ftell(auxiliar)-sizeof(Traductor);
			fseek(auxiliar,pos,SEEK_SET);
		}
		fread(&traductor,sizeof(Traductor),1,archivo);
	}
	cout<<"Registro eliminado"<<endl;
	fclose(archivo);
	fclose(auxiliar);
	remove("Traducciones.dat");
	rename("auxiliar.dat","Traducciones.dat");
}
	

int traducir(char *token)
{
	FILE* archivo = fopen("Traducciones.dat","rb");	
	int	 indice=0,pos[20];
	int i;
 	fread(&traductor,sizeof(Traductor),1,archivo);		
	do{
		if(strcmp(traductor.palabra,token)==0)
			{
				pos[i] = indice;
				return 1;
				token=NULL;
			}
		fread(&traductor,sizeof(Traductor),1,archivo);
		indice+=1;
	} while (feof(archivo)==0);
	fclose(archivo);
}

void imprimir(char *token)
{
	FILE* archivo = fopen("Traducciones.dat","rb");	
	int	 indice=0,pos[20];
	int i;
 	fread(&traductor,sizeof(Traductor),1,archivo);		
	do{
		if(strcmp(traductor.palabra,token)==0)
			{
				pos[i] = indice;
			}
		fread(&traductor,sizeof(Traductor),1,archivo);
		indice+=1;
	} while (feof(archivo)==0);
	fseek(archivo,pos[i] * sizeof(Traductor),SEEK_SET);
	fread(&traductor,sizeof(Traductor),1,archivo);
	if(token='\0')
	{
		cout<<endl;
	}
	else
	{
	cout<<traductor.traduccion<<" ";
	}
	fclose(archivo);
}

void multilineas()
{
	int	 indice=0,pos=0;
	int i=0;
  	string parrafo[100],copia[100];
  	char test[i];
  	cout<<"Ingrese el texto a traducir, para salir escriba: salir"<<endl;
  	for(i;i<50;i++)
  	{
  	getline(cin,parrafo[i]);
  	copia[i]=parrafo[i];
  	if(parrafo[i]=="salir" || parrafo[i]=="Salir" || parrafo[i]=="SALIR")
  	{
  		i=49;
	}
	}
	cout<<"____________________________________"<<endl;
	
	
	for(i=0;i<50;i++)
	{
	int tam = copia[i].size();
	char frase[tam];
	strcpy(frase,copia[i].c_str());
	if(copia[i]=="salir" || copia[i]=="Salir" || copia[i]=="SALIR")
	{
		i=49;
	}
	char *token[100];
	token[i] = strtok(frase," ");
	while(token[i] != NULL)
  	{
  		char *palabra;
		palabra=token[i];
		traducir(palabra);
		
		if(traducir(palabra)==1)
		{
			imprimir(palabra);
		
		}
		else
		{
			cout<<palabra<<" ";
		}
  		token[i] = strtok(NULL, " ");
  	}
	}
 system("pause");
}

void menu()
{
	int opc;
			 system("mode con: cols=100 lines=29");
		dibujarCuadro(1,0,98,28);
	 	  dibujarCuadro(2,1,97,7);
	 	   dibujarCuadro(2,25,97,27);
		 setlocale(LC_ALL, "");
		 
		  HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
 SetConsoleTextAttribute(hConsole, 14);
		 		
			 {SetConsoleTitle("Proyecto ALgoritmos Fase I");}
	gotoxy(25,2);cout<<"     Universidad Mariano Gálvez De Guatemala     "<<endl;
	 gotoxy(25,4);cout<<"Facultad De Ingeniería En Sistemas De Información"<<endl;
	 gotoxy(25,6);cout<<"         Y Ciencias De La Computación        "<<endl;	 
   		 cout<<""<<endl;
   	 			color(hConsole, 15);
	string opcion;
		gotoxy (12,10);cout<<"Menú"<<endl<<endl;
			gotoxy (4,12);cout<<"1. Agregar Palabra"<<endl;
			gotoxy (4,14);cout<<"2. Ver Palabras"<<endl;
			gotoxy (4,16);cout<<"3. Buscar Palabra"<<endl;
			gotoxy (4,18);cout<<"4. Modificar Palabra"<<endl;
			gotoxy (4,20);cout<<"5. Eliminar Palabra"<<endl;
			gotoxy (4,22);cout<<"6. Traducir texto"<<endl;
	gotoxy (7,26);cout<<"Opcion: "; cin>>opc;
	switch(opc)
	{
		case 1:
			system("cls");
			ingresar();
		break;
		case 2:
			system("cls");
			leer();
		break;
		case 3:
			system("cls");
			leer();
			buscar();
		break;
		case 4:
			system("cls");
			leer();
			actualizar();
			Sleep(500);
			cout<<"\n\n------------------------- cambios realizados -------------------------"<<endl<<endl;
		break;
		case 5:
			system("cls");
			leer();
			eliminar();
			Sleep(600);
			cout<<"\n\n------------------------- cambios realizados -------------------------"<<endl<<endl;
		break;
		case 6:
			system("cls");
			multilineas();
		break;
		default:
			cout<<"Esa opcion no existe"<<endl;
		break;
	}
	cout<<"\nDesea probar otra opcion (s/n): "; cin>>opcion;
	if(opcion=="s"||opcion=="S")
	{
		system("cls");
		menu();
	}
	else
	{
		cout<<"Proceso terminado"<<endl;
	}
}

main()
{
	menu();
}

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }

void dibujarCuadro(int x1,int y1,int x2,int y2){
	int i;
	
    for (i=x1;i<x2;i++){
		gotoxy(i,y1); cout << "\304";
		gotoxy(i,y2); cout << "\304";
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i); cout <<"\263";
		gotoxy(x2,i); cout <<"\263";
	}
	
    gotoxy(x1,y1); cout<< "\332"; 
    gotoxy(x1,y2); cout<< "\300";
    gotoxy(x2,y1); cout<< "\277";
    gotoxy(x2,y2); cout<< "\331";
}

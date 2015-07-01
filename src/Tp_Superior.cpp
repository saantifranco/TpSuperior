//============================================================================
// Name        : Tp_Superior.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <iostream>
using namespace std;

typedef struct{
	long double hidrogeno;
	long double fotones;
}dato;

long double factorial(int x){
	if(x == 0) return 1;
	else return x*factorial(x-1);
}

long double funcionLineal(double ordenada, double pendiente, int x){
	long double y;
	y = pendiente*x+ordenada;
	return y;
}

int iniciarPrograma(int cantidadDatos);
dato* leerDatos(int cantidadDatos);
int verificanAmbasRectas(dato* datos, int a, int b, int c, int d, int e);
long double calcularDiferenciaCuadrados(dato* datos, int a, int i, int j, int k, int l, long double ordenadaAux, long double pendienteAux);
long double sumaX(dato* datos, int a, int b, int c, int d, int e);
long double sumaY(dato* datos, int a, int b, int c, int d, int e);
long double sumaXX(dato* datos, int a, int b, int c, int d, int e);
long double sumaXY(dato* datos, int a, int b, int c, int d, int e);

int main() {
	int cantidadDatos = 10;
	int combinaciones = 0;
	dato* datos;

	combinaciones = iniciarPrograma(cantidadDatos);
	datos = leerDatos(cantidadDatos);
	dato datoInicial1;
	datoInicial1 = datos[0];
	long double pendienteAux, ordenadaAux;
	long double sumX, sumY, sumXY, sumXX;
	long double diferenciaCuadrados = 0;

	for(int i = 2; i < 7; i++ ){
		for(int j = 3; j < 8; j++){
			if(j <= i) j++;
			else
			{
				for(int k = 4; k < 9; k++ ){
					if(k <= i || k <= j) k++;
					else
					{
						for(int l = 5; l < 10; l++){
							if(l <= i || l <= j || l <= k) l++;
							else
							{

								sumX = sumaX(datos, 0, i, j, k, l);
								sumY = sumaY(datos, 0, i, j, k, l);
								sumXX = sumaXX(datos, 0, i, j, k, l);
								sumXY = sumaXY(datos, 0, i, j, k, l);
								ordenadaAux = (sumY*sumXX - sumXY*sumX)/(5*sumXX - sumX*sumX);
								pendienteAux = (sumXY - ordenadaAux*sumX)/sumXX;
								diferenciaCuadrados = calcularDiferenciaCuadrados(datos, 0, i, j, k, l, ordenadaAux, pendienteAux);

								/*
								cout << "SumX: " << sumX << ". SumY: " << sumY << ". SumXX: " << sumXX << ". SumXY: " << sumXY << endl;
								cout << "Pendiente recta calculada: " << pendienteAux << endl;
								cout << "Ordenada recta calculada: " << ordenadaAux << endl;
								cout << "Diferencia de cuadrados: " << diferenciaCuadrados << endl;
								cout << "La diferencia de cuadrados sirve, 1 si, 0 no: " << (diferenciaCuadrados < (3/10)) << endl;
								*/
								/*
								sumX = sumaX(datos, 0, 2, 5, 7, 9);
								sumY = sumaY(datos, 0, 2, 5, 7, 9);
								sumXX = sumaXX(datos, 0, 2, 5, 7, 9);
								sumXY = sumaXY(datos, 0, 2, 5, 7, 9);
								ordenadaAux = (sumY*sumXX - sumXY*sumX)/(5*sumXX - sumX*sumX);
								pendienteAux = (sumXY - ordenadaAux*sumX)/sumXX;
								cout << "Diferencia cuadrados solucion: " << calcularDiferenciaCuadrados(datos, 0, 2, 5, 7, 9, ordenadaAux, pendienteAux) << endl;
								 */
								/*
								sumX = sumaX(datos, 1, 3, 4, 6, 8);
								sumY = sumaY(datos, 1, 3, 4, 6, 8);
								sumXX = sumaXX(datos, 1, 3, 4, 6, 8);
								sumXY = sumaXY(datos, 1, 3, 4, 6, 8);
								ordenadaAux = (sumY*sumXX - sumXY*sumX)/(5*sumXX - sumX*sumX);
								pendienteAux = (sumXY - ordenadaAux*sumX)/sumXX;
								cout << "Diferencia cuadrados otra solucion: " << calcularDiferenciaCuadrados(datos, 1, 3, 4, 6, 8, ordenadaAux, pendienteAux) << endl;
								*/

								if((diferenciaCuadrados < 0.3) && (verificanAmbasRectas(datos, 0, i, j, k, l) == 1)){
									cout << "El resto de las muestras corresponden a la otra recta:" << endl;
									cout << "X: " << datos[0].hidrogeno << " Y: " << datos[0].fotones << endl;
									cout << "X: " << datos[i].hidrogeno << " Y: " << datos[i].fotones << endl;
									cout << "X: " << datos[j].hidrogeno << " Y: " << datos[j].fotones << endl;
									cout << "X: " << datos[k].hidrogeno << " Y: " << datos[k].fotones << endl;
									cout << "X: " << datos[l].hidrogeno << " Y: " << datos[l].fotones << endl;
									//cout << "SumX: " << sumX << ". SumY: " << sumY << ". SumXX: " << sumXX << ". SumXY: " << sumXY << endl;
                                    					cout << "Pendiente recta calculada: " << pendienteAux << endl;
                                					cout << "Ordenada recta calculada: " << ordenadaAux << endl;
                                					cout << "Diferencia de cuadrados: " << diferenciaCuadrados << endl;
                                    					cout << endl;
								}
							}
						}
					}
				}
			}
		}
	}
	cout << "No hay mas combinaciones con tan poco margen de error" << endl;
	
	system("pause");
	return 0;
}

int iniciarPrograma(int cantidadDatos){
	cout << "Bienvenido, calcularemos las rectas de regresion que posea minimos cuadrados" << endl;
	cout << "segun los datos ingresados" << endl;
	cout << "Utilizaremos los datos que se encuentran en 'datos.txt' " << endl;
	cout << "Con " << cantidadDatos << " datos, tomando los 2 primeros como fijos y considerando que la mitad" << endl;
	cout << "corresponden a una muestra y la otra mitad a otra" << endl;
	double combinatoria = 0;
	double numerador, denominador;
	cantidadDatos = cantidadDatos-2;
	numerador = factorial(cantidadDatos);
	cantidadDatos = cantidadDatos/2;
	denominador = factorial(cantidadDatos) * factorial(cantidadDatos);
	combinatoria = numerador/denominador;
	cout << "se pueden obtener " << combinatoria << " combinaciones." <<endl;
	cout << endl;
	cantidadDatos = cantidadDatos*2 + 2;
	return combinatoria;
}

dato* leerDatos(int cantidadDatos){
		FILE* filePointer;
		char* buffer = NULL;
		dato* bufferDatos = NULL;
		dato datoAux;
		char c;
		int i = 0;
		int posDatos = 0;
		bufferDatos = (dato*)realloc(buffer, (cantidadDatos)*sizeof(dato));

		if((filePointer = fopen("datos.txt","r")) == NULL){
			printf("No se puedo abrir el archivo de datos \n");
			exit(-1);
		}
				  c = fgetc(filePointer);
				  while(!feof(filePointer))
				    {
				      buffer = (char*)realloc(NULL, sizeof(char));
				        i = 0;
					  while( c != ',')
					    {
					      buffer[i] = c;
					      i++;
					      buffer = (char*)realloc(buffer, (i+1)*sizeof(char));
					      c = fgetc(filePointer);
					    }
				      //printf("X: %s ", buffer);
					  datoAux.hidrogeno = atoi(buffer);
				      free(buffer);
				      buffer = (char*)realloc(NULL, sizeof(char));
				      i = 0;
				      c = fgetc(filePointer);
				      while( c != '\n')
				        {
				          buffer[i] = c;
				          i++;
				          buffer = (char*)realloc(buffer, (i+1)*sizeof(char));
				          c = fgetc(filePointer);
				        }
					  datoAux.fotones = atoi(buffer);

				      /*Agrego el \n al buffer*/
				      buffer = (char*)realloc(buffer, (i+2)*sizeof(char));
				      buffer[i] = c;
				      buffer[i+1] = '\0';
				      /*Trabajar con el buffer*/
				      //printf("Y: %s", buffer);
				      free(buffer);
				      c = fgetc(filePointer);
				      bufferDatos[posDatos] = datoAux;
				      posDatos++;
				    }
				   fclose(filePointer);

				   /*for(i = 0; i<10; i++){
					   cout<< "Dato X: " << bufferDatos[i].hidrogeno << " Dato Y: " << bufferDatos[i].fotones << endl;
				   }*/
	return bufferDatos;
}

int verificanAmbasRectas(dato* datos, int a, int b, int c, int d, int e){
	long double pendienteAux, ordenadaAux;
	long double sumX, sumY, sumXY, sumXX;
	long double diferenciaCuadrados = 0;
	int inicial,i,j,k,l,p, cont;
	inicial = 1-a;
	i = 0;
	j = 0;
	k = 0;
	l = 0;
	p = 2;
	cont = 0;

	while(p<10){
		if(p!=b && p!=c && p!=d && p!=e){
			switch(cont){
				case 0:
					i = p;
					cont ++;
					break;
				case 1:
					j = p;
					cont ++;
					break;
				case 2:
					k = p;
					cont ++;
					break;
				case 3:
					l = p;
					cont ++;
					break;
				default:
					break;
			}
		}
		p++;

	}

	sumX = sumaX(datos, inicial, i, j, k, l);
	sumY = sumaY(datos, inicial, i, j, k, l);
	sumXX = sumaXX(datos, inicial, i, j, k, l);
	sumXY = sumaXY(datos, inicial, i, j, k, l);
	ordenadaAux = (sumY*sumXX - sumXY*sumX)/(5*sumXX - sumX*sumX);
	pendienteAux = (sumXY - ordenadaAux*sumX)/sumXX;
	diferenciaCuadrados = calcularDiferenciaCuadrados(datos, inicial, i, j, k, l, ordenadaAux, pendienteAux);

	if(diferenciaCuadrados < 0.3){
		cout << "Las muestras que corresponden a la primer recta son: " << endl;
		cout << "X: " << datos[inicial].hidrogeno << " Y: " << datos[inicial].fotones << endl;
		cout << "X: " << datos[i].hidrogeno << " Y: " << datos[i].fotones << endl;
		cout << "X: " << datos[j].hidrogeno << " Y: " << datos[j].fotones << endl;
		cout << "X: " << datos[k].hidrogeno << " Y: " << datos[k].fotones << endl;
		cout << "X: " << datos[l].hidrogeno << " Y: " << datos[l].fotones << endl;
		//cout << "SumX: " << sumX << ". SumY: " << sumY << ". SumXX: " << sumXX << ". SumXY: " << sumXY << endl;
		cout << "Pendiente recta calculada: " << pendienteAux << endl;
		cout << "Ordenada recta calculada: " << ordenadaAux << endl;
		cout << "Diferencia de cuadrados: " << diferenciaCuadrados << endl;
		cout << endl;
		return 1;
	}
	else
		return 0;

}

long double calcularDiferenciaCuadrados(dato* datos, int a, int i, int j, int k, int l, long double ordenadaAux, long double pendienteAux){
	long double diferenciaCuadrados = 0;
	diferenciaCuadrados = diferenciaCuadrados + (datos[a].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[a].hidrogeno))*(datos[a].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[a].hidrogeno));
	diferenciaCuadrados = diferenciaCuadrados + (datos[i].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[i].hidrogeno))*(datos[i].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[i].hidrogeno));
	diferenciaCuadrados = diferenciaCuadrados + (datos[j].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[j].hidrogeno))*(datos[j].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[j].hidrogeno));
	diferenciaCuadrados = diferenciaCuadrados + (datos[k].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[k].hidrogeno))*(datos[k].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[k].hidrogeno));
	diferenciaCuadrados = diferenciaCuadrados + (datos[l].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[l].hidrogeno))*(datos[l].fotones - funcionLineal(ordenadaAux, pendienteAux, datos[l].hidrogeno));
	return diferenciaCuadrados;
}

long double sumaX(dato* datos, int a, int b, int c, int d, int e){
	long double suma;
	suma = datos[a].hidrogeno;
	suma = suma + datos[b].hidrogeno;
	suma = suma + datos[c].hidrogeno;
	suma = suma + datos[d].hidrogeno;
	suma = suma + datos[e].hidrogeno;
	return suma;
}
long double sumaY(dato* datos, int a, int b, int c, int d, int e){
	long double suma;
	suma = datos[a].fotones;
	suma = suma + datos[b].fotones;
	suma = suma + datos[c].fotones;
	suma = suma + datos[d].fotones;
	suma = suma + datos[e].fotones;
	return suma;
}
long double sumaXX(dato* datos, int a, int b, int c, int d, int e){
	long double suma;
	suma = datos[a].hidrogeno * datos[a].hidrogeno;
	suma = suma + datos[b].hidrogeno * datos[b].hidrogeno;
	suma = suma + datos[c].hidrogeno * datos[c].hidrogeno;
	suma = suma + datos[d].hidrogeno * datos[d].hidrogeno;
	suma = suma + datos[e].hidrogeno * datos[e].hidrogeno;
	return suma;
}
long double sumaXY(dato* datos, int a, int b, int c, int d, int e){
	long double suma;
	suma = datos[a].hidrogeno * datos[a].fotones;
	suma = suma + datos[b].hidrogeno * datos[b].fotones;
	suma = suma + datos[c].hidrogeno * datos[c].fotones;
	suma = suma + datos[d].hidrogeno * datos[d].fotones;
	suma = suma +  datos[e].hidrogeno * datos[e].fotones;
	return suma;
}




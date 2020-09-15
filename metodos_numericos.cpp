#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <cmath>
#include <bits/stdc++.h>

#define PRECISION 6

using namespace std;

typedef union
{
    bool Salir;
    bool Regresar;
}CONDICIONAL;

void Biseccion(void);
void LeerEcuacion(double *x, double *y, unsigned int N);
double f(double *x, double *y, unsigned int N, double val);
void imprimePuntos(double a, double b, double *x, double *y, unsigned int N);

unsigned int Menu(string titulo, string opciones[], unsigned int n);
void MostrarCursor(bool visible, double tamanio);
void gotoxy(unsigned int x, unsigned int y);
int WhereX(void);
int WhereY(void);

void LeerMatriz(double **x, unsigned int nFilas, unsigned int nColumnas);
void LeerVector(double *x, unsigned int nElementos);
void CapturarInt(int *valor);
void CapturarUnsignedInt(unsigned int *valor);
void CapturarFloat(float *valor);
void CapturarUnsignedFloat(float *valor);
void CapturarDouble(double *valor);
void CapturarUnsignedDouble(double *valor);

double funcion(double x,double y);
double funcion2(double x,double y);
double derivadaparcialx(double x,double y);
double derivadaparcialy(double x,double y);
double derivadaparcialx_2(double x,double y);
double derivadaparcialy_2(double x,double y);
void leerFuncion();
void leerFuncion2();
void impresion();
double det();
void NewtonRapshon(void);

double** CrearMatriz(unsigned int N, unsigned int M);
void EliminacionGaussiana(void);
void EliminarMatriz(double **x, unsigned int nFilas);

float **memoria(int f,int c);
void capturar(int f,int c,float **m);
float **operacion(int f,int c,float **m,float **v);
float **normalizacion(int f,int c,float **v);
void mostrar1(int f,int c,float **v);
void liberar(int f,int c,float **m);
void EigenValoresyEigenVectores(void);

void FalsaPosicion(void);

void InterpolacionPorDiferenciasDivididas(void);
float Multiplicacion();
void funcionR();

int a1,b1,a2,b2,c;
int a1_2,b1_2,a2_2,b2_2,c_2;
double Jacobiano[3][3];
double auxJacobiano[3][3];

float x[1000],y[1000], mostrar[1000][1000],diagonal[1000], M0[1000],resultado_m[1000];
float M1[2],s,r[1000];
int TamDiagonal=1,n,iteracion;

int main()
{
    CONDICIONAL cond;
    string opciones[] = {"Soluci¢n de ecuaciones de una variable", "Soluci¢n de sistemas de ecuaciones", "C lculo de Eigenvalores y Eigenvectores", "M‚todos de aproximaci¢n de funciones", "Salir"};
    string opciones2[] = {"Lineal", "No Lineal", "Regresar"};
    string opciones3[] = {"Bisecci¢n", "Falsa Posici¢n", "Regresar"};

    cond.Salir = false;

    do
    {
        system("cls");
        MostrarCursor(false, 25);

        switch (Menu("Men£", opciones, 5))
        {
        case 1:
            cond.Regresar = false;
            do
            {
                system("cls");
                MostrarCursor(false, 25);

                switch (Menu("Men£", opciones3, 3))
                {
                case 1:
                    MostrarCursor(true, 25);
                    system("cls");
                    cout << endl << "\tM" << char(130) << "todo empleado: Bisecci" << char(162) << "n" << endl;
                    Biseccion();
                    cout << endl;
                    system("pause");
                    break;
                case 2:
                    MostrarCursor(true, 25);
                    system("cls");
                    cout << endl << "\tM" << char(130) << "todo empleado: Falsa posici" << char(162) << "n" << endl;
                    FalsaPosicion();
                    cout << endl;
                    system("pause");
                    break;
                case 3:
                    cond.Regresar = true;
                    break;
                }
            }while(!cond.Regresar);
            cond.Salir = false;
            break;
        case 2:
            cond.Regresar = false;
            do
            {
                system("cls");
                MostrarCursor(false, 25);

                switch (Menu("Men£", opciones2, 3))
                {
                case 1:
                    MostrarCursor(true, 25);
                    system("cls");
                    EliminacionGaussiana();
                    cout << endl << endl;
                    system("pause");
                    break;
                case 2:
                    MostrarCursor(true, 25);
                    system("cls");
                    cout << endl << "\tM" << char(130) << "todo empleado: Newton - Raphson" << endl;
                    NewtonRapshon();
                    cout << endl;
                    system("pause");
                    break;
                case 3:
                    cond.Regresar = true;
                    break;
                }
            }while(!cond.Regresar);
            cond.Salir = false;
            break;
        case 3:
            MostrarCursor(true, 25);
            system("cls");
            cout << endl << "\tM" << char(130) << "todo empleado: M" << char(130) << "todo de las potencias" << endl;
            EigenValoresyEigenVectores();
            cout << endl;
            system("pause");
            break;
        case 4:
            MostrarCursor(true, 25);
            system("cls");
            cout << endl << "\tM" << char(130) << "todo empleado: Interpolaci" << char(162) << "n por Diferencias Divididas" << endl << endl;
            InterpolacionPorDiferenciasDivididas();
            cout << endl;
            system("pause");
            break;
        case 5:
            cond.Salir = true;
            break;
        }
    }while(!cond.Salir);

    return 0;
}

void Biseccion(void)
{
    cout << setprecision(PRECISION);

    unsigned int N;
   double a, b, tolerancia, *coef, *exponen;


   cout << "\nIngrese la cantidad de t" << char(130) << "rminos: ";
   CapturarUnsignedInt(&N);

   coef = new double[N];
   exponen = new double[N];

   LeerEcuacion(coef, exponen, N);



   cout << "\nIngrese el intervalo inicial [a, b]" << endl;
   cout << "\na = ";
   cin >> a;
   cout << "b = ";
   cin >> b;


   imprimePuntos(a, b, coef, exponen, N);

   cout << "\nEscoja el intervalo adecuado" << endl;
   cout << "\na = ";
   cin >> a;

   cout << "b = ";
   cin >> b;

   // [a, b]
   float xr; // raiz de la función


   if (f(coef, exponen, N, a) * f(coef, exponen, N, b) > 0) {

      cout << "\nNo se puede aplicar el metodo de la biseccion\n";
      cout << "porque f(" << a << ") y f(" << b << ") tienes el mismo signo" << endl;

   } else {
      cout << "Tolerancia = ";
      cin >> tolerancia;
      cout << "\na\tb\tx\tf(a)\t\tf(b)\t\tf(x)\n" << endl;
      do {
         xr = (a + b) / 2.0;
         cout << a << "\t" << b << "\t" << xr << "\t";
         cout << f(coef, exponen, N, a) << "\t" << f(coef, exponen, N, b) << "\t" << f(coef, exponen, N, xr) << endl;

         // Vemos si cumple o no cumple
         if (abs(f(coef, exponen, N, xr)) <= tolerancia) { // xr sería la raiz de f

            cout << "\n\nPara una tolerancia " << tolerancia << " la raiz de f es " << xr << endl;

            break;

         } else {
            if (f(coef, exponen, N, xr) * f(coef, exponen, N, a) > 0) {
               a = xr;
            } else if (f(coef, exponen, N, xr) * f(coef, exponen, N, b) > 0) {
               b = xr;
            }
         }

      } while (1);
   }

   delete coef;
   delete exponen;
   return;
}

void LeerEcuacion(double *x, double *y, unsigned int N)
{
    for (unsigned int i = 0; i < N; i++)
    {
        cout << endl << "Ingrese coeficiente del t" << char(130) << "rmino " << i + 1 << ": ";
        CapturarDouble(x + i);
        cout << "Ingrese exponente del t" << char(130) << "rmino " << i + 1 << ": ";
        CapturarDouble(y + i);
    }

    return;
}

double f(double *x, double *y, unsigned int N, double val)
{
    double resp = 0.0;

    for (unsigned int i = 0; i < N; i++)
        resp += *(x + i) * pow(val, *(y + i));

    return resp;
}

#define INTERVALOS 10
void imprimePuntos(double a, double b, double *x, double *y, unsigned int N)
{
   int puntos = INTERVALOS + 1;

   double ancho = (b - a) / INTERVALOS;

   cout << "\n";
   cout << "\tx\tf(x)\n" << endl;
   for (int i = 0; i < puntos; i++) {
      cout << "\t" << a << "\t" << f(x, y, N, a) << endl;
      a = a + ancho;
   }
}

unsigned int Menu(string titulo, string opciones[], unsigned int n)
{
    unsigned int tecla, opcionseleccionada = 1;

    gotoxy(15, 2);
    cout << titulo;

    for (unsigned int i = 0; i < n; i++)
    {
        gotoxy(10, 4 + i);
        cout << i + 1 << ") " << opciones[i];
    }

    while (true)
    {
        gotoxy(5, 3 + opcionseleccionada);
        cout << "==>";

        do
        {
            tecla = getch();
        }
        while (tecla != 72 && tecla != 80 && tecla != 13);

        if (tecla != 13)
        {
            gotoxy(5, 3 + opcionseleccionada);
            cout << "   ";
        }

        switch (tecla)
        {
        case 72:
            opcionseleccionada--;

            if (opcionseleccionada < 1)
                opcionseleccionada = n;

            break;
        case 80:
            opcionseleccionada++;

            if (opcionseleccionada > n)
                opcionseleccionada = 1;

            break;
        case 13:
            gotoxy(0, 4 + n);
            return opcionseleccionada;
        }
    }
}

void LeerMatriz(double **x, unsigned int nFilas, unsigned int nColumnas)
{
    for (unsigned int i = 0; i < nFilas; i++)
    {
        cout << endl << "\tFila " << i + 1 << endl << endl;

        for (unsigned int j = 0; j < nColumnas; j++)
        {
            cout << "\tDato [" << i + 1 << "][" << j + 1 << "]: ";
            CapturarDouble((*(x + i) + j));
        }
    }

    return;
}

void LeerVector(double *x, unsigned int nElementos)
{
    for (unsigned int i = 0; i < nElementos; i++)
    {
        cout << endl << "\tDato " << i + 1 << ": ";
        CapturarDouble(x + i);
    }

    return;
}

void CapturarInt(int *valor)
{
    unsigned int x = WhereX(), y = WhereY();
    string numero = "";
    char aux;

    while (true)
    {
        aux = getch();

        switch (aux)
        {
        case 8:
            if (numero.length())
            {
                gotoxy(--x, y);
                cout << " ";
                numero = numero.substr(0, numero.length() - 1);
                gotoxy(x, y);
            }
            break;
        case 45:
            if (!numero.length())
            {
                cout << aux;
                numero.push_back(aux);
                x++;
            }
            break;
        case 13:
            if (!numero.length())
                cout << 0;

            *valor = atoi(numero.c_str());
            cout << endl;
            return;
        default:
            if (aux > 47 && aux < 58)
            {
                cout << aux;
                numero.push_back(aux);
                x++;
            }
            break;
        }
    }

}

void CapturarUnsignedInt(unsigned int *valor)
{
    unsigned int x = WhereX(), y = WhereY();
    string numero = "";
    char aux;

    while (true)
    {
        aux = getch();

        switch (aux)
        {
        case 8:
            if (numero.length())
            {
                gotoxy(--x, y);
                cout << " ";
                numero = numero.substr(0, numero.length() - 1);
                gotoxy(x, y);
            }
            break;
        case 13:
            if (!numero.length())
                cout << 0;

            *valor = atoi(numero.c_str());
            cout << endl;
            return;
        default:
            if (aux > 47 && aux < 58)
            {
                cout << aux;
                numero.push_back(aux);
                x++;
            }
            break;
        }
    }

}

void CapturarFloat(float *valor)
{
    unsigned int x = WhereX(), y = WhereY();
    string numero = "";
    char aux;
    bool punto = false;

    while(true)
    {
        aux = getch();

        switch (aux)
        {
        case 8:
            if (numero.length())
            {
                gotoxy(--x, y);
                cout << " ";

                if (numero[numero.length() - 1] == 46)
                    punto = false;

                numero = numero.substr(0, numero.length() - 1);
                gotoxy(x, y);
            }
            break;
        case 45:
            if (!numero.length())
            {
                cout << aux;
                numero.push_back(aux);
                x++;
            }
            break;
        case 46:
            if (!punto)
            {
                if (numero.length() > ((numero[0] == 45)? 1 : 0))
                {
                    cout << aux;
                    numero.push_back(aux);
                    x++;
                    punto = true;
                }
            }
            break;
        case 13:
            if (!numero.length() || numero.length() == 1 && numero[0] == 45 || numero[numero.length() - 1] == 46)
                cout << 0;

            *valor = atof(numero.c_str());
            cout << endl;
            return;
            break;
        default:
            if (aux > 47 && aux < 58)
            {
                cout << aux;
                numero.push_back(aux);
                x++;
            }
            break;
        }
    }
}

void CapturarUnsignedFloat(float *valor)
{
    unsigned int x = WhereX(), y = WhereY();
    string numero = "";
    char aux;
    bool punto = false;

    while(true)
    {
        aux = getch();

        switch (aux)
        {
        case 8:
            if (numero.length())
            {
                gotoxy(--x, y);
                cout << " ";

                if (numero[numero.length() - 1] == 46)
                    punto = false;

                numero = numero.substr(0, numero.length() - 1);
                gotoxy(x, y);
            }
            break;
        case 46:
            if (!punto)
            {
                if (numero.length() > 0)
                {
                    cout << aux;
                    numero.push_back(aux);
                    x++;
                    punto = true;
                }
            }
            break;
        case 13:
            if (!numero.length() || numero[numero.length() - 1] == 46)
                cout << 0;

            *valor = atof(numero.c_str());
            cout << endl;
            return;
            break;
        default:
            if (aux > 47 && aux < 58)
            {
                cout << aux;
                numero.push_back(aux);
                x++;
            }
            break;
        }
    }
}

void CapturarDouble(double *valor)
{
    unsigned int x = WhereX(), y = WhereY();
    string numero = "";
    char aux;
    bool punto = false;

    while(true)
    {
        aux = getch();

        switch (aux)
        {
        case 8:
            if (numero.length())
            {
                gotoxy(--x, y);
                cout << " ";

                if (numero[numero.length() - 1] == 46)
                    punto = false;

                numero = numero.substr(0, numero.length() - 1);
                gotoxy(x, y);
            }
            break;
        case 45:
            if (!numero.length())
            {
                cout << aux;
                numero.push_back(aux);
                x++;
            }
            break;
        case 46:
            if (!punto)
            {
                if (numero.length() > ((numero[0] == 45)? 1 : 0))
                {
                    cout << aux;
                    numero.push_back(aux);
                    x++;
                    punto = true;
                }
            }
            break;
        case 13:
            if (!numero.length() || numero.length() == 1 && numero[0] == 45 || numero[numero.length() - 1] == 46)
                cout << 0;

            *valor = atof(numero.c_str());
            cout << endl;
            return;
            break;
        default:
            if (aux > 47 && aux < 58)
            {
                cout << aux;
                numero.push_back(aux);
                x++;
            }
            break;
        }
    }
}

void CapturarUnsignedDouble(double *valor)
{
    unsigned int x = WhereX(), y = WhereY();
    string numero = "";
    char aux;
    bool punto = false;

    while(true)
    {
        aux = getch();

        switch (aux)
        {
        case 8:
            if (numero.length())
            {
                gotoxy(--x, y);
                cout << " ";

                if (numero[numero.length() - 1] == 46)
                    punto = false;

                numero = numero.substr(0, numero.length() - 1);
                gotoxy(x, y);
            }
            break;
        case 46:
            if (!punto)
            {
                if (numero.length() > 0)
                {
                    cout << aux;
                    numero.push_back(aux);
                    x++;
                    punto = true;
                }
            }
            break;
        case 13:
            if (!numero.length() || numero[numero.length() - 1] == 46)
                cout << 0;

            *valor = atof(numero.c_str());
            cout << endl;
            return;
            break;
        default:
            if (aux > 47 && aux < 58)
            {
                cout << aux;
                numero.push_back(aux);
                x++;
            }
            break;
        }
    }
}

double funcion(double x,double y)
{
    double r;
    r = (a1)*pow(x,2) + (a2)*pow(y,2) + (b1)*x + (b2)*y + c;
    return r;
}

double funcion2(double x,double y)
{
    double r;
    r = (a1_2)*pow(x,2) + (a2_2)*pow(y,2) + (b1_2)*x + (b2_2)*y + c_2;
    return r;
}

double derivadaparcialx(double x,double y)
{
    double h = 1e-8,r;
    r = (funcion(x+h,y)-funcion(x,y))/h;
    return r;
}

double derivadaparcialy(double x,double y)
{
    double h = 1e-8,r;
    r = (funcion(x,y+h)-funcion(x,y))/h;
    return r;
}

double derivadaparcialx_2(double x,double y)
{
    double h = 1e-8,r;
    r = (funcion2(x+h,y)-funcion2(x,y))/h;
    return r;
}

double derivadaparcialy_2(double x,double y)
{
    double h = 1e-8,r;
    r = (funcion2(x,y+h)-funcion2(x,y))/h;
    return r;
}

void leerFuncion()
{

    cout << "Los polinomios no lineales validos para este programa son (a1)x^2 + (a2)y^2 + b1x + b2y + c = 0";
    cout << "\nIngrese los valores de los coeficientes 'a1', 'a2', 'b1', 'b2' y 'c'";
    cout << "\nValor de a1: ";
    cin >> a1;
    cout << "\Valor de a2: ";
    cin >> a2;
    cout << "Valor de b1: ";
    cin >> b1;
    cout << "Valor de b2: ";
    cin >> b2;
    cout << "Valor de c: ";
    cin >> c;
    cout << "El polinomio ingresado es: " << a1 << "x^2 + (" << a2 << ")y^2 + (" << b1 << ")x + (" << b2 << ")y + (" << c << ") = 0" << endl;
}

void leerFuncion2()
{

    cout << "Los polinomios no lineales validos para este programa son (a1)x^2 + (a2)y^2 + b1x + b2y + c = 0";
    cout << "\nIngrese los valores de los coeficientes 'a1', 'a2', 'b1', 'b2' y 'c'";
    cout << "\nValor de a1: ";
    cin >> a1_2;
    cout << "\Valor de a2: ";
    cin >> a2_2;
    cout << "Valor de b1: ";
    cin >> b1_2;
    cout << "Valor de b2: ";
    cin >> b2_2;
    cout << "Valor de c: ";
    cin >> c_2;
    cout << "El polinomio ingresado es: " << a1_2 << "x^2 + (" << a2_2 << ")y^2 + (" << b1_2 << ")x + (" << b2_2 << ")y + (" << c_2 << ") = 0" << endl;
}

void impresion()
{
    cout << "\n\t\t\t-----";
    cout << "\n";
    cout << (char) 244 << "f" << "\t" << (char) 244 << "f" << "\t\t|" << endl;
    cout << "--\t--" << "\t\t|\t" << Jacobiano[0][0] << "\t\t" << Jacobiano[0][1] << endl;
    cout << (char) 244 << "x" << "\t" << (char) 244 << "y" << "\t\t|"<< endl;
    cout << "\t\t=\t|\n";
    cout << (char) 244 << "g" << "\t" << (char) 244 << "g" << "\t\t|\t" << Jacobiano[1][0] << "\t\t" << Jacobiano[1][1] << endl;
    cout << "--\t--" << "\t\t|" << endl;
    cout << (char) 244 << "x" << "\t" << (char) 244 << "y" << "\t\t|" << "\n\t\t\t-----\n";
}

double det()
{
    double determinante;
    determinante = Jacobiano[0][0]*Jacobiano[1][1]-(Jacobiano[1][0]*Jacobiano[0][1]);
    return determinante;
}

void NewtonRapshon(void)
{
    int i,j,cont=0,vectoraux=3;
    double x,y,h,k,valordet,resfun,resfun2;
    cout << "\nEste programa solo es valido para sistemas de ecuaciones de segundo orden del tipo (a1)x^2 + (a2)y^2 + b1x + b2y + c = 0" << endl;
    cout << "Ingrese 0 en los coeficientes que no necesite para su funcion" << endl;
    system("pause");
    system("cls");
    cout << "\tPrimer polinomio:\n";
    leerFuncion();
    system("pause");
    system("cls");
    cout << "\tSegundo polinomio:" << endl;
    leerFuncion2();
    system("pause");
    system("cls");
    cout << "\tIngrese aproximacion inicial" << endl;
    cout << "Valor para x: ";
    cin >> x;
    cout << "Valor para y: ";
    cin >> y;
    funcion(x,y);
    ///Para la primera funcion
    Jacobiano[0][0] = derivadaparcialx(x,y);
    Jacobiano[0][1] = derivadaparcialy(x,y);
    funcion2(x,y);
    ///Para la segunda funcion
    Jacobiano[1][0] = derivadaparcialx_2(x,y);
    Jacobiano[1][1] = derivadaparcialy_2(x,y);
    cout << "\nEl jacobiano tiene la siguiente forma:\n";
    impresion();
    double xaux[vectoraux], yaux[vectoraux];
    xaux[0] = rand() % 32768;
    xaux[1] = rand() % 32768;
    yaux[0] = rand() % 32768;
    yaux[1] = rand() % 32768;
    ///Aqui comienza el proceso iterativo
    while(xaux[vectoraux-2]!=xaux[vectoraux-3] && yaux[vectoraux-2]!=yaux[vectoraux-3])
    {
        cout << "\nIteracion " << cont << endl;
//        cout << "vectoraux vale " << vectoraux << endl;
//        cout << xaux[vectoraux-2] << " =? " << xaux[vectoraux-3] << endl;
//        cout << yaux[vectoraux-2] << " =? " << yaux[vectoraux-3] << endl;
        cout.precision(4);
        valordet = det();
        cout << "El determinante del Jacobiano es: " << valordet << endl;
        ///Evaluando funcion
        cout << "\nEvaluando la aproximacion inicial en la funcion f(x0,y0) para obtener f0" << endl;
        resfun = funcion(x,y);
        cout << resfun << endl;
        ///Evaluando funcion2
        cout << "\nEvaluando la aproximacion inicial en la funcion g(x0,y0) para obtener g0" << endl;
        resfun2 = funcion2(x,y);
        cout << resfun2 << endl;
        ///Almacenamos valores en auxiliares
        auxJacobiano[0][0] = Jacobiano[0][0];
        auxJacobiano[0][1] = Jacobiano[0][1];
        auxJacobiano[1][0] = Jacobiano[1][0];
        auxJacobiano[1][1] = Jacobiano[1][1];
        ///Ahora obtenemos h
        Jacobiano[0][1] = auxJacobiano[0][1];
        Jacobiano[1][1] = auxJacobiano[1][1];
        Jacobiano[0][0] = -(funcion(x,y));
        Jacobiano[1][0] = -(funcion2(x,y));
        h = (1/valordet)*(det());
        impresion();
        cout << "\nEl valor de h es: " << h;
        ///Ahora obtenemos k
        Jacobiano[0][0] = auxJacobiano[0][0];
        Jacobiano[1][0] = auxJacobiano[1][0];
        Jacobiano[0][1] = -(funcion(x,y));
        Jacobiano[1][1] = -(funcion2(x,y));
        k = (1/valordet)*(det());
        impresion();
        cout << "\nEl valor de k es: " << k;
        x = x + h;
        y = y + k;
        cout << "\n\nEl valor de x" << cont << " es: " << x;
        cout << "\nEl valor de y" << cont << " es: " << y;
        cout << "\n\n";
        for(int i=vectoraux-1;i<vectoraux;i++)
            {
//                cout << "x vale " << x << ", y vale " << y << endl;
                xaux[i] = x;
                yaux[i] = y;
//                cout << "xaux[" << i << "] = " << xaux[i] << ", yaux["<< i << "]= " << yaux[i] << endl;
            }

        funcion(x,y);
        ///Para la primera funcion
        Jacobiano[0][0] = derivadaparcialx(x,y);
        Jacobiano[0][1] = derivadaparcialy(x,y);
        funcion2(x,y);
        ///Para la segunda funcion
        Jacobiano[1][0] = derivadaparcialx_2(x,y);
        Jacobiano[1][1] = derivadaparcialy_2(x,y);
        cout << "\nEl jacobiano tiene la siguiente forma:\n";
        impresion();
        cont++;
//        cout << "vectoraux vale: " << vectoraux << endl;
//        cout << "xaux[vectoraux-2] que vale: " << xaux[vectoraux-2] << " =? xaux[vectoraux-3] que vale: " << xaux[vectoraux-3] << endl;
//        cout << "yaux[vectoraux-2] que vale: " << yaux[vectoraux-2] << " =? yaux[vectoraux-3] que vale: " << yaux[vectoraux-3] << "\n\n";
        system("pause");
        vectoraux++;
    }
    cout << "\nEl metodo termino en " << cont << " iteraciones" << endl;
    cout << "Resultado" << endl;
    cout << "x" << cont << " = " << x << endl;
    cout << "y" << cont << " = " << y << endl;

    return;
}

void EigenValoresyEigenVectores(void)
{
	cout<<"\nIngresa el tama" << char(164) << "o de tu matriz [nxn]: ";
	int n,n2=1;
	cin>>n; cin.ignore(256,'\n');
	float **matriz;
	matriz=memoria(n,n);
	float **vector;
	vector=memoria(n,n2);

	cout<<"\tCapturando la matriz"<<endl;
	capturar(n,n,matriz);

	cout<<"\tCapturando el vector inicial"<<endl;
	capturar(n,n2,vector);
	cout<<endl;

	for(int i=0;i<30;i++)
	{
		cout<<"Iteracion "<<i+1<<":"<<endl;
		vector=operacion(n,n2,matriz,vector);
		vector=normalizacion(n,n2,vector);
		mostrar1(n,n2,vector);
		cout<<endl;
	}

	liberar(n,n,matriz);
	liberar(n,n2,vector);

	return;
}

double** CrearMatriz(unsigned int N, unsigned int M)
{
    double **x = new double*[N];

    for (unsigned int i = 0; i < N; i++)
        x[i] = new double[M];

    return x;
}

void EliminacionGaussiana(void)
{
    double **x;
    unsigned int nFilas, nColumnas;

    do
    {
        cout << endl << "\tM" << char(130) << "todo empleado: Eliminaci" << char(162) << "n Gaussiana" << endl;
        cout << endl << "\tIngrese la cantidad de ecuaciones: ";
        CapturarUnsignedInt(&nFilas);
        cout << endl << "\tIngrese la cantidad de inc" << char(162) << "gnitas: ";
        CapturarUnsignedInt(&nColumnas);

        if (!nFilas && !nColumnas)
        {
            system("cls");
            MostrarCursor(false, 25);
            cout << endl << "\tLa cantidad de ecuaciones y la cantidad de inc" << char(162) << "gnitas no puede ser cero" << endl;
            Sleep(4500);
            MostrarCursor(true, 25);
            system("cls");
        }
        else if (nFilas != nColumnas)
        {
            system("cls");
            MostrarCursor(false, 25);
            cout << endl << "\tLa cantidad de ecuaciones debe ser igual a la cantidad de inc" << char(162) << "gnitas" << endl;
            Sleep(4500);
            MostrarCursor(true, 25);
            system("cls");
        }
    }while((nFilas != nColumnas) || (!nFilas && !nColumnas));

    nColumnas++;

    x = CrearMatriz(nFilas, nColumnas);

    LeerMatriz(x, nFilas, nColumnas);

    for (unsigned int i = 0; i < (nFilas - 1); i++)
    {
        if (!(*(*(x + i) + i)))
        {
            for (unsigned int j = i + 1; j < nFilas; j++)
            {
                if (*(*(x + j) + i))
                {
                    for (unsigned int k = 0; k < nColumnas; k++)
                    {
                        double aux = *(*(x + j) + k);
                        *(*(x + j) + k) = *(*(x + i) + k);
                        *(*(x + i) + k) = aux;
                    }
                    break;
                }
            }
        }

        for (unsigned int j = i + 1; j < nFilas; j++)
        {
            if (*(*(x + i) + i))
            {
                double piv = (*(*(x + j) + i) / *(*(x + i) + i));

                for (unsigned int k = i; k < nColumnas; k++)
                    *(*(x + j) + k) -= piv * (*(*(x + i) + k));
            }
        }
    }

    double det = 1;

    for (unsigned int i = 0; i < nFilas; i++)
        det *= *(*(x + i) + i);

    if (det)
    {
        for (int i = nFilas - 1; i > -1; i--)
        {
            for (int j = i - 1; j > -1; j--)
            {
                double piv = (*(*(x + j) + i)) / (*(*(x + i) + i));

                for (int k = nColumnas - 1; k > (j - 1); k--)
                    *(*(x + j) + k) -= piv * (*(*(x + i) + k));
            }
        }

        for (unsigned int i = 0; i < nFilas; i++)
            *(*(x + i) + nColumnas - 1) /= *(*(x + i) + i);

        for (unsigned int i = 0; i < nFilas; i++)
            cout << endl << "\t" << char(91 - nFilas + i) << " = " << *(*(x + i) + nColumnas - 1);
    }
    else
    {
        system("cls");
        cout << endl << "\tEl sistema de ecuaciones no tiene soluci" << char(162) << "n" << endl;
        Sleep(4500);
        system("cls");
    }

    EliminarMatriz(x, nFilas);
    return;
}

void EliminarMatriz(double **x, unsigned int nFilas)
{
    for (unsigned int i = 0; i < nFilas; i++)
        delete x[i];

    delete x;
    return;
}

float **memoria(int f,int c)
{
	float **m;
	m=new float*[f];
	for(int i=0;i<f;i++)
	{
		m[i]=new float[c];
	}
	return m;
}

void capturar(int f,int c,float **m)
{
	for(int i=0;i<f;i++)
	{
		for(int j=0;j<c;j++)
		{
			cout<<"Ingrese el dato["<<i<<"]["<<j<<"]: ";
			cin>>m[i][j]; cin.ignore(256,'\n');
		}
	}
}

float **operacion(int f,int c,float **m,float **v)
{
	float **vec;
	vec=new float*[f];
	for(int i=0;i<f;i++)
	{
		vec[i]=new float[c];
	}
	for(int i=0;i<f;i++)
	{
		for(int j=0;j<c;j++)
		{
			vec[i][j]=0;
			for(int k=0;k<f;k++)
			{
				vec[i][j]+=(m[i][k]*v[k][j]);
			}
		}
	}
	return vec;
}

float **normalizacion(int f,int c,float **v)
{
	float mayor=0.0;
	for(int i=0;i<f-1;i++)
	{
		for(int j=0;j<c;j++)
		{
			if(v[i][j]>v[i+1][j])
			{
				mayor=v[i][j];
			}
		}
	}
	for(int i=0;i<f;i++)
	{
		for(int j=0;j<c;j++)
		{
			v[i][j]/=mayor;
		}
	}
	cout<<"Variable normalizada: "<<mayor<<endl;
	return v;
}

void mostrar1(int f,int c,float **v)
{
	for(int i=0;i<f;i++)
	{
		for(int j=0;j<c;j++)
		{
			cout<<"Vector["<<i<<"]["<<j<<"]= "<<v[i][j]<<endl;
		}
	}
}

void liberar(int f,int c,float **m)
{
	for(int i=0;i<f;i++)
	{
		delete[]m[i];
	}
	delete[]m;
}

void FalsaPosicion(void)
{
    cout << setprecision(PRECISION);

    unsigned int N;
    double a, b, tolerancia, *coef, *exponen;


   cout << "\nIngrese la cantidad de t" << char(130) << "rminos: ";
   CapturarUnsignedInt(&N);

   coef = new double[N];
   exponen = new double[N];

   LeerEcuacion(coef, exponen, N);

   cout << "\nIngrese el intervalo inicial [a,b]:" << endl;
    cout << "\na = ";
    cin >> a;

    cout << "b = ";
    cin >> b;

    imprimePuntos(a, b, coef, exponen, N);

    cout << "\nEscoja el intervalo adecuado" << endl;
    cout << "\na = ";
    cin >> a;

    cout << "b = ";
    cin >> b;

    double xr;
    double xa = 0;

    if (f(coef, exponen, N, a) * f(coef, exponen, N, b) > 0) {
        cout << "\nNo se puede aplicar el metodo de la falsa posicion\n";
        cout << "porque f(" << a << ") y f(" << b << ") tienen el mismo signo" << endl;

    } else {
        cout << "Tolerancia = ";
        cin >> tolerancia;

        cout << "\na\tb\tx\tf(a)\t\tf(b)\t\tf(x)\n" << endl;
        do {
            xr = b - f(coef, exponen, N, b) * ((b - a) / (f(coef, exponen, N, b) - f(coef, exponen, N, a)));

            cout << a << "\t" << b << "\t" << xr << "\t" << f(coef, exponen, N, a) << "\t" << f(coef, exponen, N, b) << "\t" << f(coef, exponen, N, xr) << endl;

            // if (fabs(f(xr)) <= tolerancia) {
            if (fabs(xr - xa) / fabs(xr) <= tolerancia) {
                cout << "\n\nPara una tolerancia de " << tolerancia << " la raiz de f es: " << xr << endl;
                break;

            } else {
                xa = xr; // Se guarda el valor de la aproximación anterior
                if (f(coef, exponen, N, xr) * f(coef, exponen, N, a) > 0) {
                    a = xr;

                } else if (f(coef, exponen, N, xr) * f(coef, exponen, N, b) > 0) {
                    b = xr;
                }
            }

        } while (true);
    }

    delete coef;
    delete exponen;
    return;
}

void InterpolacionPorDiferenciasDivididas(void)
{
    int n,aux=0,xmostrar=1,ymostrar=2,Xo=0,Yo=1,contador;
    float operacion;
    cout<<"ingrese el valor de n:\n";
    cin>>n;
    cout<<"ingrese los valores para los puntos Xi y Yi respectivamente separados por un espacio\n";

    diagonal[n];

    for(int i=0; i<=n; i++)
    {
        cin>>x[i]>>y[i];
        mostrar[i][0]=x[i];
        mostrar[i][1]=y[i];
    }
    cout<<endl;
    cout<<"Los datos ingresados son:\n";
    cout<<"i\tXi\tY"<<endl;
    for(int i=0; i<=n; i++)
    {
        cout<<i<<"\t"<<x[i]<<"\t"<<y[i]<<endl;
    }

    for(int veces=0; veces<=n-1; veces++)               ///sería 1 a n, pero le reduje 1 a ambos lados para hacer genérico el código
    {
        //contador=0
        for(int k=0; k<=n-veces; k++)
        {
            operacion=(mostrar[xmostrar+k-1][ymostrar-1]-mostrar[xmostrar+k][ymostrar-1])/(mostrar[k][0]-mostrar[k+veces+1][0]);
            mostrar[xmostrar+k][ymostrar]=operacion;
        }
        ymostrar++;
        xmostrar++;
    }

///esto me va a servir para mostrar mi tabla
cout<<endl<<"Tabla de resultados:\n\n";
cout<<"i\tXi\tYi\tOperaciones\n";
for(int i=0; i<=n;i++)
{
    cout<<i<<"\t";
    for(int j=0; j<=n+1; j++)
    {
        if(mostrar[i][j]<0)
        {
            cout.precision(4);
            cout<<mostrar[i][j]<<"\t";
        }
        else
        {
            cout.precision(4);
            cout<<"+"<<mostrar[i][j]<<"\t";
        }
    }
    cout<<endl;
}

cout<<"\nNuestro polinomio resultante es: \n";

///imprime el polinomio en orden como sale y se mueve en la tabla
cout<<"\nP"<<n<<"(x)= "<<mostrar[0][1];
int xpos=n,ypos=n+1;                        ///ver si si sirven o no

for(int m=xpos; m>=1; m--)
{
    cout<<"+("<<mostrar[m][m+1]<<")";
    for(int j=m-1;j>=0;j--)
    {
        cout<<"(x-("<<x[j]<<"))";
    }
}

cout<<"\n\nFactorizando obtenemos:\n\n";
cout<<"P"<<n<<"(x)= "<<mostrar[0][1]<<" + (x-("<<mostrar[0][0]<<")) [ ";
int x_pos=1;
for(int m=x_pos; m<=n; m++)
{
    if(m!=n)
    {
        cout<<mostrar[m][m+1]<<" + (x-("<<mostrar[m][0]<<"))";
        if(m<n-1)     cout<<"[ ";
    }
    else
    {
        cout<<"("<<mostrar[m][m+1]<<")";
        for(int i=1; i<n;i++)
        {
            cout<<" ]";
         }
    }
}

    ///Valores para el arreglo de la diagonal de la tabla

    for(int i=0; i<=n; i++)
    {
        diagonal[i]=mostrar[i][i+1];
    }

    M0[0]=1;
    r[0]+=diagonal[0];
    iteracion++;
    for(int num=0; num<n; num++)
    {
        M1[0]=(-1)*x[num];
        M1[1]=1;
        Multiplicacion();
        funcionR();
        iteracion++;
    }
cout<<"\n\nResolviendo obtenemos: \n\n";

cout<<"P"<<n<<"(x)= ";

    for(int i=0; i<=n; i++)
    {
        if(r[i]<0)
        {
            cout<<"- "<<abs(r[i])<<" ";
        }
        else
        {
            cout<<"+ "<<r[i]<<" ";
        }
        if(i!=0)    cout<<"x^"<<i<<" ";
    }

cout<<endl;

return;
}

void funcionR()
{
    int contador=0;
    float aux=0;

        for(int j=0; j<TamDiagonal; j=j+1)
        {
            r[j]+=M0[j]*diagonal[iteracion];
        }
        contador++;
}

float Multiplicacion()
{
    int contador=0;
    float aux;
    for(int i=0; i<2; i=i+1)
    {
        for(int j=0; j<TamDiagonal; j=j+1)
        {
            aux=M1[i]*M0[j];
            resultado_m[j+i]=resultado_m[j+i]+aux;
        }
        contador++;
    }
    TamDiagonal++;
    for(int i=0; i<TamDiagonal; i++)
    {
        M0[i]=resultado_m[i];
        resultado_m[i]=0;
    }
}

void MostrarCursor(bool visible, double tamanio)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = tamanio;
    cci.bVisible = visible;

    SetConsoleCursorInfo(hCon,&cci);
}

void gotoxy(unsigned int x, unsigned int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

//Funcion para saber la coordenada X del cursor en pantalla
int WhereX(void)
{
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &sbi);
    return sbi.dwCursorPosition.X;
}

//Funcion para saber la coordenada Y del cursor en pantalla
int WhereY(void)
{
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &sbi);
    return sbi.dwCursorPosition.Y;
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

/*FUNCIONES DE PREPROCESADOR*/

/*variables globales*/
int numCliente1;
char nombre [15];
char apePat [15];
char apeMat [15];
char contrasena [15];

int numCuenta;
int numCliente2;
double saldoDeudor;

char opcion;

/*funciones*/
/*funciones que muestran menús*/
void menuCliente();
void menuAdmin();

/*funciones de administración*/
void registrarCliente();
void registrarCuenta();
bool existeCliente(int numCliente); //esta función comprueba que un cliente exista
void verClientes();
void verCuentas();


/*funciones de cliente*/
void registrarDeposito();
void registrarPrestamo();
void verSaldoCuentas();

/*función que valida que el usuario ingrese una opción adecuada*/
void validarOpc(int limInf, int limSup);

/*función para salir*/
void salir();



int main()
{
    system("cls");
    printf("MENU PRINCIPAL\n");
    printf("\n1. Administracion");
    printf("\n2. Cliente");
    printf("\n3. Salir");

    validarOpc(1, 3);

    switch(opcion)
    {
        case '1':
            menuAdmin();
            break;

        case '2':
            menuCliente();
            break;

        case '3':
            salir();
            break;

        default:
            printf("Error");
            break;
    }

    getch();
    return 0;
}

//Esta función lee y valida que opción sea un número y se encuentre entre dos números
void validarOpc(int limInf, int limSup)
{
    /*
    limInf = límite inferior
    limSup = límite Superior
    */

    printf("\nIngrese una opcion: ");
    scanf(" %c", &opcion);

    while(!isdigit(opcion) || opcion-'0'<limInf || opcion-'0'>limSup)
    {
        printf("Ingrese una opcion correcta (un numero del %d al %d): ", limInf, limSup);
        scanf(" %c", &opcion);
    }

}

void menuAdmin()
{
    system("cls");
    printf("ADMINISTRACION\n");
    printf("\n1. Registrar un cliente");
    printf("\n2. Registrar una cuenta (Crédito)");
    printf("\n3. Ver clientes");
    printf("\n4. Ver cuentas");
    printf("\n5. Salir");

    validarOpc(1, 5);

    switch(opcion)
    {
        case '1':
            registrarCliente();
            break;

        case '2':
            registrarCuenta();
            break;

        case '3':
            //verClientes();
            break;

        case '4':
            //verCuentas();
            break;

        case '5':
            salir();
            break;

        default:
            printf("Error");
            break;
    }
}

void menuCliente()
{
    system("cls");
    printf("CLIENTE\n");
    printf("\n1. Registrar un deposito");
    printf("\n2. Registrar un prestamo");
    printf("\n3. Ver saldo de cuentas");
    printf("\n4. Salir");

    validarOpc(1, 4);

    switch(opcion)
    {
        case '1':
            //registrarDeposito();
            break;

        case '2':
            //registrarPrestamo();
            break;

        case '3':
            //verSaldoCuentas();
            break;

        case '4':
            salir();
            break;

        default:
            printf("Error");
            break;
    }
}

void registrarCliente()
{
    FILE *fp;
    fp = fopen("Clientes.txt", "r+t");

    if(fp == NULL)
    {
        fp = fopen("Clientes.txt", "w+t");
        fprintf(fp, "%d ", 1);
    }
    else
    {
        fclose(fp);
        fp = fopen("Clientes.txt", "a+t");

        while(!feof(fp))
        {
            fscanf(fp, "%d %s %s %s %s\n", &numCliente1, &nombre, &apePat, &apeMat, &contrasena);
        }

        fclose(fp);
        numCliente1++;
    }

    system("cls");
    printf("Nombre: ");
    scanf(" %s",nombre);

    printf("Apellido paterno: ");
    scanf(" %s",apePat);

    printf("Apellido materno: ");
    scanf(" %s",apeMat);

    printf("Contrasenia: ");
    scanf(" %s",contrasena);

    fp = fopen("Clientes.txt", "a+t");
    fprintf(fp, "%d ", numCliente1);
    fprintf(fp, "%s ", nombre);
    fprintf(fp, "%s ", apePat);
    fprintf(fp, "%s ", apeMat);
    fprintf(fp, "%s ", contrasena);
    fputs("\n", fp);

    fclose(fp);

    printf("Cliente registrado exitosamente. ID: %d", numCliente1);

}

void registrarCuenta()
{
    FILE *fp;
    fp = fopen("Cuentas.txt", "r+t");
    bool primerRegistro = true;

    if(fp == NULL)
    {
        fp = fopen("Cuentas.txt", "w+t");
        numCuenta = 1;
        fprintf(fp, "%d ", numCuenta);
        fclose(fp);
    }
    else
    {
        primerRegistro = false;
        fclose(fp);
        fp = fopen("Cuentas.txt", "a+t");

        while(!feof(fp))
        {
            fscanf(fp, "%d %d %d\n", &numCuenta, &numCliente2, &saldoDeudor);
        }

        fclose(fp);
        numCuenta++;
    }

    system("cls");
    printf("Ingrese el ID del cliente que desea obtener una cuenta: ");
    scanf("%d", &numCliente2);

    //----------Buscando si el cliente existe

    if(existeCliente(numCliente2))
    {
        fp = fopen("Cuentas.txt", "a+t");
        if(!primerRegistro) fprintf(fp, "%d ", numCuenta);
        fprintf(fp, "%d ", numCliente2);
        fprintf(fp, "%d ", 5000);
        fputs("\n", fp);

        fclose(fp);
        printf("La cuenta fue otorgada con exito al cliente No. %d", numCliente2);
    }
    else
    {
        printf("ERROR. No existe un cliente con ese ID.");
    }

    fclose(fp);

}

bool existeCliente(int numCliente)
{
    FILE *fp;
    fp = fopen("Clientes.txt", "r+t");
    bool existe = false;

    if(fp == NULL)
    {
        fp = fopen("Clientes.txt", "w+t");
        fprintf(fp, "%d ", 1);
    }
    else
    {
        fclose(fp);
        fp = fopen("Clientes.txt", "a+t");


        while(!feof(fp))
        {
            fscanf(fp, "%d %s %s %s %s\n", &numCliente1, &nombre, &apePat, &apeMat, &contrasena);

            if(numCliente1 == numCliente)
            {
                existe = true;
            }
        }
    }

    fclose(fp);

    return existe;
}

void registrarDeposito ()
{
    FILE *fp;
    //fp = fopen
}

void salir(){
    exit(-1);
}

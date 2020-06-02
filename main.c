#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

/*FUNCIONES DE PREPROCESADOR*/

/*variables globales*/
int numClienteSesion;
char contrasenaSesion [15];

struct Domicilio
{
    char calle [15];
    int numeroInt;
    int numeroExt;
    char colonia [15];
    char alcaldia [15];
    char ciudad [15];
};

struct Cliente
{
    int numCliente1;
    char nombre [15];
    char apePat [15];
    char apeMat [15];
    int edad;
    struct Domicilio domicilioCliente;
    char contrasena [15];
} miCliente;

bool logueado = false;

struct Cuenta
{
    int numCuenta;
    int numCliente2;
    double saldoDeudor;
} miCuenta;

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
void iniciarSesion();
void registrarDeposito();
void registrarPrestamo();
void verSaldoCuentas(int cliente);

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
            iniciarSesion();
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
    printf("\n5. Regresar");

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
            verClientes();
            break;

        case '4':
            verCuentas();
            break;

        case '5':
            main();
            break;

        default:
            printf("Error");
            break;
    }
}

void iniciarSesion(){


    printf("Inicie sesion.\n\n");
    printf("No. de cliente: ");
    scanf("%d", &numClienteSesion);
    printf("Contrasenia: ");
    scanf("%s", contrasenaSesion);
}

void menuCliente()
{

    FILE *fp;

    fp = fopen("Clientes.txt", "r+t");

    /*----------------------Se lee el archivo de Clientes---------------------*/
    if(fp == NULL)
    {
        printf("No hay clientes registrados.");
    }
    else
    {
        fclose(fp);
        fp = fopen("Clientes.txt", "a+t");

        while(!feof(fp))
        {
            fscanf(fp, "%d %s %s %s %s\n", &miCliente.numCliente1, &miCliente.nombre, &miCliente.apePat, &miCliente.apeMat, &miCliente.contrasena);
            if(numClienteSesion == miCliente.numCliente1 && strcmp(contrasenaSesion, miCliente.contrasena)==0)
            {
                logueado = true;
                break;
            }
        }

        fclose(fp);
        miCliente.numCliente1++;

    }

    if(logueado)
    {
        system("cls");
        printf("CLIENTE\n");
        printf("\n1. Registrar un deposito");
        printf("\n2. Registrar un prestamo");
        printf("\n3. Ver saldo de cuentas");
        printf("\n4. Regresar");

        validarOpc(1, 4);

        switch(opcion)
        {
            case '1':
                registrarDeposito();
                break;

            case '2':
                registrarPrestamo();
                break;

            case '3':
                verSaldoCuentas(1);
                break;

            case '4':
                main();
                break;

            default:
                printf("Error");
                break;
        }
    }
    else printf("Datos incorrectos");
}

void registrarCliente()
{
    system("cls");

    struct Cliente miCliente;
    FILE *fp;
    FILE *fp2;

    fp = fopen("Clientes.txt", "r+t");
    fp2 = fopen("Domicilio.txt", "r+t");

    /*----------------------Se lee el archivo de Clientes---------------------*/
    if(fp == NULL)
    {
        fp = fopen("Clientes.txt", "w+t");
        fprintf(fp, "%d ", 1);
        miCliente.numCliente1 = 1;
    }
    else
    {
        fclose(fp);
        fp = fopen("Clientes.txt", "a+t");


        while(!feof(fp))
        {
            fscanf(fp, "%d %s %s %s %s\n", &miCliente.numCliente1, &miCliente.nombre, &miCliente.apePat, &miCliente.apeMat, &miCliente.contrasena);
        }

        fclose(fp);
        miCliente.numCliente1++;

    }

    /*----------------------Se lee el archivo de Domicilio---------------------*/
    if(fp2 == NULL)
    {
        fp2 = fopen("Domicilio.txt", "w+t");

    }
    else
    {
        fclose(fp2);
        fp2 = fopen("Domicilio.txt", "a+t");

        fclose(fp2);
    }

    printf("DATOS PERSONALES: \n");

    printf("Nombre: ");
    scanf(" %[^\n]", miCliente.nombre);

    printf("Apellido paterno: ");
    scanf(" %[^\n]", miCliente.apePat);

    printf("Apellido materno: ");
    scanf(" %[^\n]", miCliente.apeMat);

    printf("Edad: ");
    scanf(" %[^\n]", &miCliente.edad);

    printf("\nDOMICILIO: \n");

    printf("Calle: ");
    scanf(" %[^\n]", miCliente.domicilioCliente.calle);

    printf("Numero Interior: ");
    scanf(" %d", &miCliente.domicilioCliente.numeroInt);

    printf("Numero Exterior: ");
    scanf(" %d", &miCliente.domicilioCliente.numeroExt);

    printf("Colonia: ");
    scanf(" %[^\n]", miCliente.domicilioCliente.colonia);

    printf("Alcaldia: ");
    scanf(" %[^\n]", miCliente.domicilioCliente.alcaldia);

    printf("Ciudad: ");
    scanf(" %[^\n]", miCliente.domicilioCliente.ciudad);

    printf("Contrasenia: ");
    scanf(" %s", miCliente.contrasena);


    fp = fopen("Clientes.txt", "a+t");
    fp2 = fopen("Domicilio.txt", "a+t");
    fprintf(fp, "%d ", miCliente.numCliente1);
    fprintf(fp, "%s ", miCliente.nombre);
    fprintf(fp, "%s ", miCliente.apePat);
    fprintf(fp, "%s ", miCliente.apeMat);
    fprintf(fp2, "%d ", miCliente.numCliente1);
    fprintf(fp2, "[%s] ", miCliente.domicilioCliente.calle);
    fprintf(fp2, "%d ", miCliente.domicilioCliente.numeroInt);
    fprintf(fp2, "%d ", miCliente.domicilioCliente.numeroExt);
    fprintf(fp2, "[%s] ", miCliente.domicilioCliente.colonia);
    fprintf(fp2, "[%s] ", miCliente.domicilioCliente.alcaldia);
    fprintf(fp2, "[%s] ", miCliente.domicilioCliente.ciudad);
    fprintf(fp, "%s ", miCliente.contrasena);
    fputs("\n", fp);
    fputs("\n", fp2);

    fclose(fp);
    fclose(fp2);

    printf("Cliente registrado exitosamente. ID: %d", miCliente.numCliente1);
}

void registrarCuenta()
{
  FILE *fp;
  fp = fopen("Cuentas.txt", "r+t");
  bool primerRegistro = true;

  if(fp == NULL)
  {
      fp = fopen("Cuentas.txt", "w+t");
      //miCuenta.numCuenta = 1;
      //fprintf(fp, "%d ", miCuenta.numCuenta);
      fclose(fp);
  }
  else
  {
      primerRegistro = false;
      fclose(fp);
      fp = fopen("Cuentas.txt", "a+t");

      while(!feof(fp))
      {
          fscanf(fp, "%d %d %d\n", &miCuenta.numCuenta, &miCuenta.numCliente2, &miCuenta.saldoDeudor);
      }

      fclose(fp);
      miCuenta.numCuenta++;
  }

  system("cls");
  printf("Ingrese el ID del cliente que desea obtener una cuenta: ");
  scanf("%d", &miCuenta.numCliente2);

  //----------Buscando si el cliente existe

  if(existeCliente(miCuenta.numCliente2))
  {
      fp = fopen("Cuentas.txt", "a+t");
      if(primerRegistro)
          fprintf(fp, "%d ", 1);
      else
          fprintf(fp, "%d ", miCuenta.numCuenta);
      fprintf(fp, "%d ", miCuenta.numCliente2);
      fprintf(fp, "%d ", 5000);
      fputs("\n", fp);

      fclose(fp);
      printf("La cuenta fue otorgada con exito al cliente No. %d", miCuenta.numCliente2);
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
          fscanf(fp, "%d %s %s %s %s\n", &miCliente.numCliente1, miCliente.nombre, miCliente.apePat, miCliente.apeMat, miCliente.contrasena);

          if(miCliente.numCliente1 == numCliente)
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
    system("cls");

    FILE *fp = fopen( "Cuentas.txt" , "r+t" );
    if (fp == NULL) //Si no hay un archivo es porque aún no tiene una cuenta
    {
        fclose(fp);
        char registro;
        printf("No tienes una cuenta todavía. ¿Deseas registrar una? \n");
        scanf("%c", &registro);
        if (registro == 's') registrarCuenta();
        else menuCliente();
    }

    printf("Cuentas en existencia\n\n");
    while (!feof(fp))
    {
        fscanf( fp, "%d %d %d\n", &miCuenta.numCuenta, &miCuenta.numCliente2, &miCuenta.saldoDeudor);
        if(numClienteSesion == miCuenta.numCliente2)printf("Cuenta: %d\tAdeudo: %d\n\n", miCuenta.numCuenta, miCuenta.saldoDeudor);
    }
    fclose(fp);

    fp = fopen( "Cuentas.txt" , "r+t" );
    bool depositar = false;
    int cuentaDepositar;
    printf("\n\nSeleccione la cuenta a depositar: ");
    scanf("%d", &cuentaDepositar);

    double deposito;
    printf("Monto del Deposito: ");
    scanf("%ld", &deposito);

    while (!feof(fp))
    {
        fscanf(fp, "%d %d %d\n", &miCuenta.numCuenta, &miCuenta.numCliente2, &miCuenta.saldoDeudor);
        if(numClienteSesion == miCuenta.numCliente2 && cuentaDepositar == miCuenta.numCuenta)
            depositar = true; //la variable depositar nos permite saber si el cliente metió una cuenta que le corresponde
    }

    if(depositar)
    {
        //modificar saldo actual
        FILE *fpTemporal;
        fpTemporal = fopen("CuentasTemporal.txt", "a+t");
        rewind(fp);

        while (!feof(fp))
        {
            fscanf(fp, "%d %d %d\n", &miCuenta.numCuenta, &miCuenta.numCliente2, &miCuenta.saldoDeudor);

            fprintf(fpTemporal, "%d ", miCuenta.numCuenta);
            fprintf(fpTemporal, "%d ", miCuenta.numCliente2);

            if(numClienteSesion == miCuenta.numCliente2 && cuentaDepositar == miCuenta.numCuenta)
                fprintf(fpTemporal, "%d", miCuenta.saldoDeudor-deposito);
            else
                fprintf(fpTemporal, "%d", miCuenta.saldoDeudor);

            fprintf(fpTemporal, "\n");
        }

        rewind(fp);
        rewind(fpTemporal);

        while (!feof(fpTemporal))
        {
            fscanf(fpTemporal, "%d %d %d\n", &miCuenta.numCuenta, &miCuenta.numCliente2, &miCuenta.saldoDeudor);

            fprintf(fp, "%d ", miCuenta.numCuenta);
            fprintf(fp, "%d ", miCuenta.numCliente2);
            fprintf(fp, "%d ", miCuenta.saldoDeudor);
            fprintf(fp, "\n");
        }

        fclose(fpTemporal);
        remove("CuentasTemporal.txt");
    }


    fclose(fp);
    menuCliente();

}
void registrarPrestamo()
{
        system("cls");

    FILE *fp = fopen( "Cuentas.txt" , "r+t" );
    if (fp == NULL) //Si no hay un archivo es porque aún no tiene una cuenta
    {
        fclose(fp);
        char registro;
        printf("No tienes una cuenta todavía. ¿Deseas registrar una? \n");
        scanf("%c", &registro);
        if (registro == 's') registrarCuenta();
        else menuCliente();
    }

    printf("Cuentas en existencia\n\n");
    while (!feof(fp))
    {
        fscanf( fp, "%d %d %d\n", &miCuenta.numCuenta, &miCuenta.numCliente2, &miCuenta.saldoDeudor);
        printf("Cuenta: %d\tAdeudo: %d\n\n", miCuenta.numCuenta, miCuenta.saldoDeudor);
    }
    printf("Seleccione la opcion que desea realizar\n\n");
    printf("1. Realizar un prestamo\n");
    printf("2. Regresar");
    validarOpc(1,2);
    fclose(fp);
    menuCliente();
}

void verClientes(){
    system("cls");
    FILE *fp=fopen("Clientes.txt","r+t");
    char a;
    if (fp==NULL)
    {
        printf("No hay clientes registrados");
        fclose(fp);
        menuAdmin();
    }
    printf("ID:\tNombre:\t\t\t\tContrasenia:\n");

    while (!feof(fp))
    {
        fscanf( fp, "%d %s %s %s %s\n", &miCliente.numCliente1, miCliente.nombre, miCliente.apePat, miCliente.apeMat, miCliente.contrasena);
        printf("\n%d\t%s %s %s\t\t%s\n",miCliente.numCliente1,miCliente.nombre,miCliente.apePat,miCliente.apeMat,miCliente.contrasena);
    }
    printf("\n1. Regresar");
    validarOpc(1,1);
    fclose(fp);
    menuAdmin();
}

void verCuentas()
{
  system("cls");

  FILE *fp = fopen( "Cuentas.txt" , "r+t" );
  if (fp == NULL) {         //Si no hay un archivo es porque aún no se han registrado Cuentas
    fclose(fp);
    char registro;
    printf("No se ha registrado una cuenta todavía. ¿Deseas registrar una? (s/n)\n");
    scanf("%c", &registro);
    if (registro == 's') registrarCuenta();
    else menuAdmin();
  }

  while (!feof(fp)) {         //cada dato que esté en el archivo se muestra con el ciclo
    fscanf( fp, "%d %d %d\n", &miCuenta.numCuenta, &miCuenta.numCliente2, &miCuenta.saldoDeudor);
    printf("Cliente %d:\n\n\tNo. Cuenta: %d\tDeuda: %d\n\n", miCuenta.numCliente2, miCuenta.numCuenta, miCuenta.saldoDeudor);
  }

  printf("1. Regresar");
  validarOpc(1,1);
  fclose(fp);
  menuAdmin();
}

void verSaldoCuentas(int cliente) {
  system("cls");

  FILE *fp = fopen( "Cuentas.txt" , "r+t" );
  if (fp == NULL) {         //Si no hay un archivo es porque aún no tiene una cuenta
    fclose(fp);
    char registro;
    printf("No tienes una cuenta todavía. ¿Deseas registrar una con un asesor? (s/n)\n");
    scanf("%c", &registro);
    if (registro == 's') registrarCuenta();
    else menuCliente();
  }

  printf("Usted tiene los siguentes numeros de cuenta:\n\n");
  while (!feof(fp)) {
    fscanf( fp, "%d %d %d\n", &miCuenta.numCuenta, &miCuenta.numCliente2, &miCuenta.saldoDeudor);
    if (cliente == miCuenta.numCliente2) {        //
      printf("No. Cuenta: %d\tDeuda: %d\n\n", miCuenta.numCuenta, miCuenta.saldoDeudor);
    }
  }

  printf("1. Regresar");
  validarOpc(1,1);
  fclose(fp);
  menuCliente();
}

void salir(){
    exit(-1);
}

#include <iostream> 
#include <string>  
#include <fstream> 
using namespace std;

// Declaramos los arreglos para almacenar la información de los productos
int codigo[100];   
string nombre[100];
float precio[100]; 
int cantidadStock[100]; 
int ubicacionAlmacen[100];

int main() {

     // Inicialización de los productos de ejemplo
     codigo[0] = 101;
     codigo[1] = 102;
     codigo[2] = 103;
     codigo[3] = 104;
     codigo[4] = 105;
 
     nombre[0] = "Martillo";
     nombre[1] = "Destornillador";
     nombre[2] = "Taladro";
     nombre[3] = "Sierra";
     nombre[4] = "Llave inglesa";
 
     precio[0] = 15.99;
     precio[1] = 7.49;
     precio[2] = 45.00;
     precio[3] = 22.75;
     precio[4] = 12.30;
 
     cantidadStock[0] = 1;
     cantidadStock[1] = 2;
     cantidadStock[2] = 3;
     cantidadStock[3] = 4;
     cantidadStock[4] = 5;

    int opcion = 0; //  Opción del menú seleccionada por el usuario

    // Leer el archivo inventario.txt
    string line;
    ifstream archivo("inventario.txt");
    if (archivo.is_open()) {
        int i = 0;
        while (getline(archivo, line)) {
            cout << line << '\n';
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo inventario.txt. Se usarán datos predeterminados.\n";
    }

    // Bucle que mantiene el menú activo hasta que el usuario elija salir 
    while (opcion != 6) {
        // Mostramos el menú principal
        cout << "--- Bienvenido al Sistema de Inventario de 'El Martillo' ---\n";
        cout << "\nSeleccione una opcion:\n";
        cout << "1. Consultar producto\n";
        cout << "2. Actualizar inventario por ubicación\n";
        cout << "3. Registrar nuevo producto\n";
        cout << "4. Generar reporte de bajo stock\n";
        cout << "5. Encontrarel producto más barato\n";
        cout << "6. Guardar y Salir\n";

        cin >> opcion; 

        switch (opcion) {
            case 1: {
                // Consultar producto por código
                int c;
                cout << "Ingrese el código del producto a consultar: \n";
                cin >> c;
                bool encontrado = false; // Bandera para saber si el producto se encontró

                for (int i = 0; i < 5; i++) {
                    if (codigo[i] == c) {
                        cout << "Información del Producto:\n";
                        cout << "Código: " << codigo[i] << "\n";
                        cout << "Nombre: " << nombre[i] << "\n";
                        cout << "Precio unitario: $" << precio[i] << "\n";
                        cout << "Cantidad en inventario: " << cantidadStock[i] << "\n";
                        encontrado = true;
                        break; // Ya lo encontramos, no seguimos buscando
                    }
                }

                if (!encontrado) {
                    cout << "Producto no encontrado.\n";
                }
                break; 
            }

            case 2: {
                // Actualizar inventario por ubicación
                int ubi;
                cout << "Ingrese la ubicación del producto a actualizar: \n";
                cin >> ubi;
                bool encontrado = false;

                // Leer el archivo
                string line;
                ifstream archivo ("inventario.txt");
                if (archivo.is_open())
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (ubicacionAlmacen[i] == ubi) {
                            cout << "Ingrese la cantidad a agregar/quitar (+/-): ";
                            int cambio;
                            cin >> cambio;
                            if (cantidadStock[i] + cambio >= 0) { // Validamos que no quede negativo
                                cantidadStock[i] += cambio;
                                cout << "Inventario actualizado. Nueva cantidad: " << cantidadStock[i] << "\n";
                            } else {
                                cout << "Error: la cantidad no puede quedar negativa.\n";
                            }
                            encontrado = true;
                            break;
                        }
                    }  
                }else
                {
                    cout << "No se pudo abrir el archivo inventario.txt para actualizar.\n";
                }
                if (!encontrado) {
                    cout << "Producto no encontrado en la ubicación especificada.\n";
                }
                break;

            }

            case 3:{
                // Registrar nuevo producto
                int nuevoCodigo;
                string nuevoNombre;
                float nuevoPrecio;
                int nuevaCantidad;
                int nuevaUbicacion;

                cout << "Ingrese el código del nuevo producto: ";
                cin >> nuevoCodigo;
                cout << "Ingrese el nombre del nuevo producto: ";
                cin >> nuevoNombre;
                cout << "Ingrese la cantidad en inventario del nuevo producto: ";
                cin >> nuevaCantidad;
                cout << "Ingrese el precio del nuevo producto: ";
                cin >> nuevoPrecio;
                cout << "Ingrese la ubicación en el almacén del nuevo producto: ";
                cin >> nuevaUbicacion;

                // Guardar en el archivo inventario.txt
                ofstream archivo("inventario.txt");
                if (archivo.is_open()) {
                    archivo << nuevoCodigo << ","
                            << nuevoNombre << ","
                            << nuevaCantidad << ","
                            << nuevoPrecio << ","
                            << nuevaUbicacion << "\n";
                    archivo.close();
                    cout << "Producto registrado y guardado en inventario.txt.\n";
                } else {
                    cout << "No se pudo abrir el archivo inventario.txt para guardar el producto.\n";
                }

                break;
            }

            case 4:{
                // Generar reporte de bajo stock
                int limiteBajoStock;
                cout << "Ingrese el límite para considerar bajo stock: ";
                cin >> limiteBajoStock;

                cout << "<-- Reporte de productos con Bajo Stock ---";
                bool hayBajoStock = false;

                for (int i = 0; i < 5; i++) { 
                    if (cantidadStock[i] < limiteBajoStock) {
                        cout << "Nombre: " << nombre[i] << " Stock: " << cantidadStock[i] << "\n";
                        hayBajoStock = true;
                    }
                }

                if (!hayBajoStock)
                {
                    cout << "No hay bajo stock";
                }
                break;
            }

            case 5: {
                // Mostrar el producto con el precio más bajo
                float menorPrecio = precio[0];
                int indiceMenor = 0;
                for (int i = 1; i < 5; i++) {
                    if (precio[i] < menorPrecio) {
                        menorPrecio = precio[i];
                        indiceMenor = i;
                    }
                }
                cout << "Producto más bajo:\n";
                cout << "Código: " << codigo[indiceMenor] << "\n";
                cout << "Nombre: " << nombre[indiceMenor] << "\n";
                cout << "Precio unitario: $" << precio[indiceMenor] << "\n";
                cout << "Cantidad en inventario: " << cantidadStock[indiceMenor] << "\n";
                break;
            }

            case 6: {
                cout << "Saliendooooo y guardandooooo\n";
                break;
            }

            default:
                cout << "Opción no válida.\n";
                break;
            
        }
    }

    return 0;
}

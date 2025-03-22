#include <iostream>
#include <limits>
using namespace std;

// Nodo para la lista de calificaciones
struct NodoCalificacion {
    float calificacion;
    NodoCalificacion* siguiente;
    
    NodoCalificacion(float calif) : calificacion(calif), siguiente(nullptr) {}
};

// Nodo para la lista de estudiantes
struct NodoEstudiante {
    int id;
    string nombre;
    float promedio;
    NodoCalificacion* calificaciones;
    NodoEstudiante* siguiente;
    
    NodoEstudiante(int _id, string _nombre, float _promedio) : id(_id), nombre(_nombre), promedio(_promedio), calificaciones(nullptr), siguiente(nullptr) {}
};

class ListaEstudiantes {
private:
    NodoEstudiante* cabeza;

public:
    ListaEstudiantes() : cabeza(nullptr) {}
    
	//Verifica si existe un ID digitado
bool idExiste(int id) {
	NodoEstudiante* actual = cabeza;
	while (actual) {
	    if (actual->id == id) return true;
	    actual = actual->siguiente;
	    }
	    return false;
	}

    void agregarEstudiante(int id, string nombre, float promedio) {
        if (id <= 0 || idExiste(id)) {
            cout << "Error: ID invalido o duplicado.\n";
            return;
        } 
		if (id <= 0 || nombre.empty()) {
            cout << "Error: Nombre vacio.\n";
            return;
        }     
        NodoEstudiante* nuevo = new NodoEstudiante(id, nombre, promedio);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cout << "Estudiante agregado.\n";
    }

//Mostrar estudiante
    void mostrarEstudiantes() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        NodoEstudiante* actual = cabeza;
        while (actual) {
            cout << "ID: " << actual->id << " | Nombre: " << actual->nombre << " | Promedio: " << actual->promedio << "\n";
            actual = actual->siguiente;
        }
    }
//Buscar al estudiante
    void buscarEstudiante(int id) {
        NodoEstudiante* actual = cabeza;
        while (actual) {
            if (actual->id == id) {
                cout << "Estudiante encontrado: ID: " << actual->id << " | Nombre: " << actual->nombre << " | Promedio: " << actual->promedio << "\n";
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante no encontrado.\n";
    }
//Eliminar estudiante
    void eliminarEstudiante(int id) {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        if (cabeza->id == id) {
            NodoEstudiante* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cout << "Estudiante eliminado.\n";
            return;
        }
        NodoEstudiante* actual = cabeza;
        while (actual->siguiente && actual->siguiente->id != id) {
            actual = actual->siguiente;
        }
        if (!actual->siguiente) {
            cout << "Estudiante no encontrado.\n";
            return;
        }
        NodoEstudiante* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        cout << "Estudiante eliminado.\n";
    }
//Actualizar promedio
    void actualizarPromedio(int id, float nuevoPromedio) {
        if (nuevoPromedio < 0.0 || nuevoPromedio > 5.0) {
            cout << "Error: El promedio debe estar entre 0.0 y 5.0.\n";
            return;
        }
        NodoEstudiante* actual = cabeza;
        while (actual) {
            if (actual->id == id) {
                actual->promedio = nuevoPromedio;
                cout << "Promedio actualizado correctamente.\n";
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante no encontrado.\n";
    }
//Mejor promedio
    void mostrarMejorEstudiante() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        NodoEstudiante* mejor = cabeza;
        NodoEstudiante* actual = cabeza;
        while (actual) {
            if (actual->promedio > mejor->promedio) {
                mejor = actual;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante con mejor promedio: ID: " << mejor->id << " | Nombre: " << mejor->nombre << " | Promedio: " << mejor->promedio << "\n";
    }
};

// Función para validar entrada de un número entero positivo
int leerId() {
    int numero;
    while (true) {
        cout << "Ingrese el numero de identificacion del estudiante: ";
        cin >> numero;

        if (cin.fail() || numero <= 0) {
            cout << "Error: Debe ingresar un numero entero positivo valido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }
    }
}

// Función para validar entrada de un promedio entre 0.0 y 5.0
float leerPromedioValido() {
    float promedio;
    while (true) {
        cout << "Ingrese el promedio del estudiante (0.0 - 5.0): ";
        cin >> promedio;

        if (cin.fail() || promedio < 0.0 || promedio > 5.0) {
            cout << "Error: Debe ingresar un valor promedio valido entre 0.0 y 5.0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return promedio;
        }
    }
}

int leerOpcionValida(int min, int max) {
    int opcion;
    while (true) {
        cout << "Ingrese una opcion (" << min << "-" << max << "): ";
        cin >> opcion;

        if (cin.fail() || opcion < min || opcion > max) {
            cout << "Error: Debe ingresar un valor numerico valido entre " << min << " y " << max << ".\n";
            cin.clear();  // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta la entrada incorrecta
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpia el buffer de entrada
            return opcion;
        }
    }
}

int main() {
    ListaEstudiantes registro;
    int opcion, id;
    string nombre;
    float promedio;

    cout << "\n     PLATAFORMA ESTUDIANTIL"<<endl;
    do {
        cout << "\n        Menu Principal" << endl;
        cout << "Seleccione la opcion a realizar: " << endl;
        cout << "1. Agregar estudiante." << endl;
        cout << "2. Mostrar el listado de estudiantes." <<endl;
        cout << "3. Buscar un estudiante (ID)." <<endl;
        cout << "4. Eliminar estudiante (ID)." << endl;
        cout << "5. Actualizar promedio del estudiante." << endl;
        cout << "6. Estudiante con el mejor promedio." << endl;
        cout << "7. Salir." <<endl;
        opcion = leerOpcionValida (1, 7);

        switch (opcion) {
            case 1:
            	cout << "\n        Agregar Estudiante" <<endl;
                do {
                	id = leerId ();
                	
                	if (id <= 0) {
                		cout << "Error: El ID ingresado debe ser positivo." <<endl;
					} else if (registro.idExiste(id)) {
						cout << "Error: El ID ingresado ya se encuentra registrado."<<endl;
					}
            	} while (id <= 0 || registro.idExiste(id));
            	
                cout << "Ingrese el nombre del estudiante: ";
				cin.ignore();
				getline(cin, nombre);
                promedio = leerPromedioValido();
                registro.agregarEstudiante(id, nombre, promedio);
                break;

            case 2:
            	cout << "\n        Listado completo de estudiantes"<<endl;
                registro.mostrarEstudiantes();
                break;

            case 3:
            	cout << "\n        Buscar estudiante"<<endl;
                id = leerId ();
                registro.buscarEstudiante(id);
                break;

            case 4:
            	cout << "\n        Eliminar estudiante" << endl;
				id = leerId ();
                registro.eliminarEstudiante(id);
                break;

            case 5:
            	cout << "\n        Actualizar promedio"<<endl;
				id = leerId ();
				promedio = leerPromedioValido ();
                registro.actualizarPromedio(id, promedio);
                break;

            case 6:
            	cout <<"\n        Mejor Promedio" <<endl;
                registro.mostrarMejorEstudiante();
                break;

            case 7:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 7);
}

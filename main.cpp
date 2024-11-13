#include <iostream>

using namespace std;

struct Paciente {
    int edad;
    int documento_cc;
    Paciente *izq;
    Paciente *der;
};

Paciente *raiz = NULL;
Paciente *aux, *aux2, *padre;

void posicionar() {
    if (aux->edad < aux2->edad) {
        if (aux2->izq == NULL) {
            aux2->izq = aux;
        } else {
            aux2 = aux2->izq;
            posicionar();
        }
    } else {
        if (aux2->der == NULL) {
            aux2->der = aux;
        } else {
            aux2 = aux2->der;
            posicionar();
        }
    }
}

void registrar() {
    aux = (Paciente*) malloc(sizeof(Paciente));
    cout << "Digite la edad del paciente: ";
    cin >> aux->edad;
    cout << "Digite el documento de identidad del paciente: ";
    cin >> aux->documento_cc;
    aux->izq = aux->der = NULL;

    if (!raiz) {
        raiz = aux;
    } else {
        aux2 = raiz;
        posicionar();
    }
    aux = NULL;
}

void ordenarPacientes(Paciente *a) {
    if (a != NULL) {
        ordenarPacientes(a->der);
        cout << "Edad: " << a->edad << ", documento de identidad: " << a->documento_cc << endl;
        ordenarPacientes(a->izq);
    }
}

void mostrar() {
    if (raiz) {
        ordenarPacientes(raiz);
    } else {
        cout << "No hay pacientes registrados." << endl;
    }
}

int ubicar(Paciente *a, int numero_identificacion) {
    if(a->documento_cc == numero_identificacion) {
        aux2 = a;
        return 0;
    } else {
        if(a->izq != NULL) {
            ubicar(a->izq, numero_identificacion);
        } 
        if(a->der != NULL) {
            ubicar(a->der, numero_identificacion);
        }         
    }
    return 0;
}

int buscar(int numero_identificacion) {
    aux = NULL;
    if(raiz != NULL) {
        aux = raiz;
        ubicar(aux, numero_identificacion);
    }
    return 0;
}

int pedir_documentode_identidad() {
    aux2 = NULL;
    int numero_identificacion;
    cout << "Ingrese el documento de identidad del paciente: ";
    cin >> numero_identificacion;
    buscar(numero_identificacion);
    if(aux2) {
        cout << "Paciente encontrado:" << endl;
        cout << "Documento de identidad: " << aux2->documento_cc << endl;
        cout << "Edad: " << aux2->edad << endl;
    } else {
        cout << "El paciente no existe" << endl;
    }
    return 0;
}

void ubicarPadre(Paciente *a) {
    if ((a->izq == aux2) || (a->der == aux2)) {
        padre = a;
    } else {
        if (a->izq != NULL) {
            ubicarPadre(a->izq);
        } 
        if (a->der != NULL) {
            ubicarPadre(a->der);
        }
    }
}

// Valor mínimo en el subárbol derecho
Paciente* encontrarMinimo(Paciente* a) {
    while (a->izq != NULL) {
        a = a->izq;
    }
    return a;
}

void eliminarPaciente() {
    int numero_identificacion;
    cout << "Ingrese el documento de identidad del paciente a eliminar: ";
    cin >> numero_identificacion;
    buscar(numero_identificacion);
    if (aux2) {
        cout << "Paciente encontrado y eliminado." << endl;
        // Caso 1: Nodo sin hijos
        if (aux2->izq == NULL && aux2->der == NULL) {
            if (aux2 != raiz) {
                ubicarPadre(raiz);
                if (padre->izq == aux2) {
                    padre->izq = NULL;
                } else {
                    padre->der = NULL;
                }
            } else {
                raiz = NULL;
            }
            free(aux2);
        }
        // Caso 2: Nodo con un solo hijo
        else if (aux2->izq == NULL || aux2->der == NULL) {
            Paciente* hijo = (aux2->izq != NULL) ? aux2->izq : aux2->der;
            if (aux2 != raiz) {
                ubicarPadre(raiz);
                if (padre->izq == aux2) {
                    padre->izq = hijo;
                } else {
                    padre->der = hijo;
                }
            } else {
                raiz = hijo;
            }
            free(aux2);
        }
        // Caso 3: Nodo con dos hijos
        else {
            Paciente* sucesor = encontrarMinimo(aux2->der);
            int edadSucesor = sucesor->edad;
            int documentoSucesor = sucesor->documento_cc;
            eliminarPaciente();  
            aux2->edad = edadSucesor;
            aux2->documento_cc = documentoSucesor;
        }
    } else {
        cout << "El paciente no existe" << endl;
    }
}

int main() {
    int opc;
    do {
        cout << "\n-----------MENU---------" << endl;
        cout << "1. Registrar nuevo paciente" << endl;
        cout << "2. Mostrar pacientes en orden de edad" << endl;
        cout << "3. Buscar por documento" << endl;
        cout << "4. Eliminar paciente" << endl;
        cout << "5. Hasta luego, mi estimado" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc) {
            case 1: registrar(); break;
            case 2: mostrar(); break;
            case 3: pedir_documentode_identidad(); break;
            case 4: eliminarPaciente(); break;
        }
    } while (opc != 5);

    return 0;
}




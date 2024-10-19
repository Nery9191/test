#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Cursos {
    string nombrec;
    string codigo;
    string creditos;
    int cursosAsignados = 0; 
};

struct Estudiante {
    int codigo;
    string nombre;
    string apellido;
    string departamento;
    string municipio;
    int telefonope;
    int telefonoca;
    int telefonoem;
};

struct Nota {
    int codigoEstudiante; // Código del estudiante
    string codigoCurso;   // Código del curso
    float notaParcial1;
    float notaParcial2;
    float notaFinal;
    string estado;
};

vector<Estudiante> estudiantes;
vector<Cursos> cursos; // Cambiado a vector de Cursos
vector<Nota> notas;

vector<vector<string>> departamentos = {
    {"Guatemala", "Guatemala", "Mixco", "Villa Nueva"},
    {"Alta Verapaz", "Coban", "San Pedro Carcha", "Tucuru"},
    {"Baja Verapaz", "Salama", "San Miguel Chicaj", "Rabinal"},
    {"Chimaltenango", "Chimaltenango", "San Jose Poaquil", "Tecuaco"},
    {"Escuintla", "Escuintla", "Santa Lucia Cotzumalguapa", "La Democracia"},
    {"Santa Rosa", "Cuilapa", "Barberena", "San Juan Tecuaco"},
    {"Solala", "Solola", "San Jose Chacaya", "Santa Catarina Palopo"},
    {"Totonicapan", "Totonicapán", "San Francisco El Alto", "Momostenango"},
    {"Quetzaltenango", "Quetzaltenango", "Colomba", "San Carlos Sija"},
    {"San Marcos", "San Marcos", "Tecoanapa", "San Miguel Ixtahuacán"},
    {"Huehuetenango", "Huehuetenango", "Chiantla", "Cuilco"},
    {"El Progreso", "Guastatoya", "San Antonio La Paz", "Sanarate"},
    {"Jalapa", "Jalapa", "Mataquescuintla", "San Pedro Pinula"},
    {"Zacapa", "Zacapa", "La Union", "Estanzuela"},
    {"Chiquimula", "Chiquimula", "Esquipulas", "San Jose La Arada"},
    {"Peten", "Flores", "San Benito", "Santa Elena"},
    {"Izabal", "Puerto Barrios", "Morales", "El Estor"},
};

void inicializarCursos() {
    cursos = {
        {"Algoritmos", "001", "5"},
        {"Matematica Discreta", "002", "5"},
        {"Algebra lineal", "003", "5"},
        {"Contabilidad", "004", "5"},
        {"Precalculo", "005", "5"},
    };
}

int generarCodigo() {
    static int codigo = 1; 
    return codigo++;
}

void AsignarCursos() {
    int codigoEstudiante;
    cout << "Ingrese el codigo del estudiante: ";
    cin >> codigoEstudiante;

    // Verificar si el estudiante existe
    bool estudianteEncontrado = false;
    for (const auto& estudiante : estudiantes) {
        if (estudiante.codigo == codigoEstudiante) {
            estudianteEncontrado = true;
            break;
        }
    }

    if (!estudianteEncontrado) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    cout << "Ingrese el codigo del curso (numero):" << endl;
    for (size_t i = 0; i < cursos.size(); i++) {
        cout << i + 1 << ". " << cursos[i].nombrec << endl;
    }

    int Codindice;
    cin >> Codindice;

    if (Codindice < 1 || Codindice > cursos.size()) {
        cout << "Curso no valido.\n";
        return;
    }

    Cursos& asigcurso = cursos[Codindice - 1];

    const int LIMITE_CURSOS = 5; // Define el límite de cursos que un estudiante puede tener
    if (asigcurso.cursosAsignados >= LIMITE_CURSOS) {
        cout << "Limite de cursos alcanzado. No se pueden asignar mas cursos.\n";
        return;
    }

    asigcurso.cursosAsignados++; // Incrementar el número de cursos asignados
    cout << "Curso " << asigcurso.nombrec << " asignado correctamente al estudiante.\n";
}

void mostrarDyM(Estudiante &nuevoEstudiante) {
    int dptoIndice;
    while (true) {
        cout << "Seleccione un departamento:\n";
        for (size_t i = 0; i < departamentos.size(); i++) {
            cout << i + 1 << ". " << departamentos[i][0] << endl;
        }
        cin >> dptoIndice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no valida. Por favor, ingrese un numero.\n";
            continue;
        }

        if (dptoIndice > 0 && dptoIndice <= departamentos.size()) {
            nuevoEstudiante.departamento = departamentos[dptoIndice - 1][0];

            cout << "Municipios en " << nuevoEstudiante.departamento << ":\n";
            for (size_t i = 1; i < departamentos[dptoIndice - 1].size(); i++) {
                cout << i << ". " << departamentos[dptoIndice - 1][i] << endl;
            }

            int muniIndice;
            cout << "Seleccione un municipio:\n";
            cin >> muniIndice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada no valida. Por favor, ingrese un numero.\n";
                continue;
            }

            if (muniIndice > 0 && muniIndice < departamentos[dptoIndice - 1].size()) {
                nuevoEstudiante.municipio = departamentos[dptoIndice - 1][muniIndice];
                break; // Salir del bucle al ingresar correctamente
            } else {
                cout << "Indice de municipio no valido.\n";
            }
        } else {
            cout << "Indice de departamento no valido.\n";
        }
    }
}

void registroEstudiantes() {
    Estudiante nuevoEstudiante;
    nuevoEstudiante.codigo = generarCodigo();
    
    cout << "Ingrese el nombre del estudiante: " << endl;
    cin.ignore();
    getline(cin, nuevoEstudiante.nombre);
    
    cout << "Ingrese los apellidos del estudiante: " << endl;
    getline(cin, nuevoEstudiante.apellido);
    
    mostrarDyM(nuevoEstudiante);
    
    cout << "Ingrese el telefono personal del estudiante (max 8 num.): " << endl;
    cin >> nuevoEstudiante.telefonope;
    
    cout << "Ingrese el telefono de casa del estudiante (max 8 num.): " << endl;
    cin >> nuevoEstudiante.telefonoca;
    
    cout << "Ingrese el telefono de emergencia del estudiante (max 8 num.): " << endl;
    cin >> nuevoEstudiante.telefonoem;
    
    estudiantes.push_back(nuevoEstudiante);
}

void asignarNotas() {
    Nota nuevaNota;
    cout << "Ingrese el codigo del estudiante: ";
    cin >> nuevaNota.codigoEstudiante;

    // Verificar que el estudiante exista
    bool estudianteEncontrado = false;
    for (const auto& estudiante : estudiantes) {
        if (estudiante.codigo == nuevaNota.codigoEstudiante) {
            estudianteEncontrado = true;
            break;
        }
    }
    
    if (!estudianteEncontrado) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    cout << "Seleccione un curso:\n";
    for (size_t i = 0; i < cursos.size(); i++) {
        cout << i + 1 << ". " << cursos[i].nombrec << endl;
    }
    
    int cursoIndice;
    cin >> cursoIndice;

    if (cursoIndice < 1 || cursoIndice > cursos.size()) {
        cout << "Curso no valido.\n";
        return;
    }

    nuevaNota.codigoCurso = cursos[cursoIndice - 1].codigo;

    cout << "Ingrese nota parcial 1: ";
    cin >> nuevaNota.notaParcial1;

    cout << "Ingrese nota parcial 2: ";
    cin >> nuevaNota.notaParcial2;

    nuevaNota.notaFinal = (nuevaNota.notaParcial1 + nuevaNota.notaParcial2);

    nuevaNota.estado = (nuevaNota.notaFinal >= 60) ? "Aprobado" : "Reprobado";

    notas.push_back(nuevaNota);
    cout << "Notas asignadas correctamente para el curso " << nuevaNota.codigoCurso << endl;
}

void reporteEstudiante() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "\n--- Reporte de Estudiantes ---\n";
    for (const auto& estudiante : estudiantes) {
        cout << "ID: " << estudiante.codigo << endl;
        cout << "Nombre: " << estudiante.nombre << endl;
        cout << "Apellidos: " << estudiante.apellido << endl;
        cout << "Departamento: " << estudiante.departamento << endl;
        cout << "Municipio: " << estudiante.municipio << endl;
        cout << "Telefono personal: " << estudiante.telefonope << endl;
        cout << "Telefono de casa: " << estudiante.telefonoca << endl;
        cout << "Telefono de emergencia: " << estudiante.telefonoem << endl;
    }
}

void reporteCursos() {
    if (cursos.empty()) {
        cout << "No hay cursos registrados.\n";
        return;
    }

    cout << "\n--- Reporte de Cursos ---\n";
    for (const auto& curso : cursos) {
        cout << "Curso: " << curso.nombrec << endl;
        cout << "Codigo de curso: " << curso.codigo << endl;
        cout << "Creditos curso: " << curso.creditos << endl;
        cout << "Estudiantes asignados: " << curso.cursosAsignados << endl;
    }
}

void reporteNotas() {
    if (notas.empty()) {
        cout << "No hay notas registradas.\n";
        return;
    }

    cout << "\n--- Reporte de Notas ---\n";
    for (const auto& nota : notas) {
        cout << "Codigo Estudiante: " << nota.codigoEstudiante << endl;
        cout << "Codigo Curso: " << nota.codigoCurso << endl;
        cout << "Nota Final: " << nota.notaFinal << endl;
        cout << "Estado: " << nota.estado << endl;
        cout << endl;
    }
}

int main() {
    inicializarCursos(); // Inicializar los cursos al inicio
    int opcion;
    do {
        cout << "\n--- Sistema de Gestion de Estudiantes ---\n";
        cout << "1. Registro de Estudiantes\n";
        cout << "2. Asignacion de cursos\n";
        cout << "3. Control de notas\n";
        cout << "4. Reportes Academicos\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registroEstudiantes();
                break;
            case 2:
                AsignarCursos();
                break;
            case 3:
                asignarNotas();
                break;
            case 4:
                int reporteOpcion;
                do {
                    cout << "\nSeleccione el tipo de reporte:\n";
                    cout << "1. Reporte de Estudiantes\n";
                    cout << "2. Reporte de Cursos\n";
                    cout << "3. Reporte de Notas\n";
                    cout << "4. Volver al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> reporteOpcion;

                    switch (reporteOpcion) {
                        case 1:
                            reporteEstudiante();
                            break;
                        case 2:
                            reporteCursos();
                            break;
                        case 3:
                            reporteNotas();
                            break;
                        case 4:
                            cout << "Volviendo al menu principal...\n";
                            break;
                        default:
                            cout << "Opcion no valida.\n";
                    }
                } while (reporteOpcion != 4);
                break;
            case 5:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
    
    return 0;
}

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

//crea una matriz 9x9
int sudoku[9][9] = {0};

//crea casillas para colocar numeros en la partida
void imprimirSudoku() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      //imprime espacios ij como matriz
      cout << sudoku[i][j] << " "; 
    }
    cout << endl;
  }
}

//analiza las filas para que no se repita num
bool validarFila(int fila, int num) {
  for (int col = 0; col < 9; col++) {
    if (sudoku[fila][col] == num) return false;
  }
  return true;
}

//analiza las columnas para que no se repita num
bool validarColumna(int col, int num) {
  for (int fila = 0; fila < 9; fila++) {
    if (sudoku[fila][col] == num) return false;
  }
  return true;
}

//verifica que las casillas 3x3 esten sin num repetidos 
bool validarCasilla(int iniciarFila, int iniciarColumna, int num) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (sudoku[iniciarFila + i][iniciarColumna + j] == num) return false;
    }
  }
  return true;
}

//verifica que los bools anteriores esten correctos
bool esValido(int fila, int col, int num) {
  return validarFila(fila, num) && validarColumna(col, num) &&
  //verifica que ninguno de los 3 bools tengan num repetidos
  validarCasilla(fila - fila % 3, col - col % 3, num);
}

//genera numeros aleatorios del 1 al 9 en el arreglo numeros
void obtenerNumerosAleatorios(int numeros[]) {
  //bucle for con los valores 1-9
  for (int i = 0; i < 9; i++) numeros[i] = i + 1;

  for (int i = 8; i > 0; i--) {
    //generador random
    int j = rand() % (i + 1);
    int temp = numeros[i];
    numeros[i] = numeros[j];
    //desordena el arreglo numeros
    numeros[j] = temp;
  }
}

//utiliza backtracking para resolver celdas vacias
bool resolverSudoku() {
  int fila = -1, col = -1;
  bool estaVacio = true;
  //busca celdas con ceros
  for (int i = 0; i < 9 && estaVacio; i++) {
    for (int j = 0; j < 9; j++) {
      if (sudoku[i][j] == 0) {
        fila = i;
        col = j;
        //detiene la busqueda si encuentra ceros
        estaVacio = false;
        break;
      }
    }
  }
  //retorna true si no hay celdas vacias
  if (estaVacio) return true;

  //genera una lista de numeros 1-9 random 
  int numeros[9];
  obtenerNumerosAleatorios(numeros);

  for (int k = 0; k < 9; k++) {
    int num = numeros[k];
    //condiciona si es valido o no fila y col
    if (esValido(fila, col, num)) {
      sudoku[fila][col] = num;
      
      //intenta resolver lo que falte de forma recursiva
      if (resolverSudoku()) return true;
      //retrocede si no funciona, de paso vacia la celda
      sudoku[fila][col] = 0;
      }
    }
  //retorna falso si no puede resolverse
  return false;
}

//función para generar el tablero completo
void generarSudokuCompleto() {
  //usa el solucionador para crear un tablero lleno
  resolverSudoku();
}

//función para vaciar celdas de forma random
void hacerHuecos(int cantidadHuecos) {
  int vacios = 0;

  while (vacios < cantidadHuecos) {
    int fila = rand() % 9;
    int col = rand() % 9;
    //vacia una celda si no esta vacia
    if (sudoku[fila][col] != 0) {
      sudoku[fila][col] = 0;
      vacios++;
    }
  }
}

int main() {
  //semilla de números aleatorios
  srand(time(0));
    
  //crea un Sudoku completamente completo
  generarSudokuCompleto();
    
  //vacía 72 celdas aleatorias para crear un rompecabezas
  hacerHuecos(64);
    
  // Imprime el Sudoku generado
  imprimirSudoku();
  cout << "resolviendo Sudoku..." << endl;
    
  //resuelve el sudoku y verifica si tiene solucion
  if (resolverSudoku()) {
    cout << "solución encontrada:" << endl;
    //imprime el sudoku solucionado
    imprimirSudoku();
  } else {
      cout << "no tiene solucion" << endl;
    }
  return 0;
}

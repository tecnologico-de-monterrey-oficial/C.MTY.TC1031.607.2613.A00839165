#Julio Eduardo Rodriguez Ruiz A00839165
# Act 2.1 - Listas encadenadas

## Prompts utilizados
- "Revisar LinkedList.h, Node.h, Fraction.h e implementar las operaciones con manejo de excepciones std::out_of_range, sobrecarga de operadores y menú genérico interactivo."

## Reflexión sobre el uso de IA
### 1. ¿Qué parte del código te propuso la IA que aceptaste tal cual y por qué era correcta?
La plantilla de la sobrecarga de `operator[]` en sus dos versiones (`const` y no `const`) y el método de duplicación profunda `operator=`, ya que liberaba la memoria existente con `clear()` para evitar fugas y replicaba secuencialmente cada nodo.

### 2. ¿Qué parte modificaste y cómo verificaste que tu cambio era mejor?
Se ajustó el método de `insert` para validar estrictamente que el índice ingresado no fuera menor a 0 ni mayor o igual a `size`, asegurando que inserte exactamente **después** del índice indicado sin provocar accesos nulos.

### 3. ¿Dónde se equivocó la IA (si ocurrió) y cómo lo detectaste?
En la propuesta inicial que utilizaba `std::unique_ptr`, el operador de copia (`operator=`) provocaba conflictos porque los apuntadores únicos no pueden duplicarse por asignación trivial. Se resolvió estructurando nodos con apuntadores directos y control explícito en el destructor.

### 4. ¿Qué harías diferente si no tuvieras Copilot/ChatGPT?
Habría implementado primero las pruebas unitarias para cada caso borde (lista vacía, borrar el primer nodo, borrar el último nodo, e índices fuera de rango) antes de codificar la interfaz por consola, verificando con `valgrind` la liberación de memoria en cada paso.
# 🌿 Gardeneer Simulator

This document outlines not only how to play and test the **Gardeneer Simulator**, but also details the underlying code architecture, highlighting the application of Object-Oriented Programming (OOP) concepts.

## 🎮 Tutorial: How to Play and Test

The Gardeneer Simulator is a text-based grid game. Below is a step-by-step guide to starting your first garden and testing the core mechanics.

### Step 1: Create the Garden and Spawn

To begin, you need to define the size of your garden and place your gardener (`*`) on the map. Coordinates are represented by letters (e.g., `a`, `b`, `c`...).

1. `jardim 5 5` (Creates a garden with 5 rows and 5 columns. The simulator will automatically spawn random tools on the ground).
2. `entra a a` (The gardener enters the garden at row A and column A).

### Step 2: Explore and Pick Up Tools

As you walk over a tool, the gardener automatically picks it up if there is space in the backpack.

1. `move d` (Move **d**ireita/right to explore).
2. `move b` (Move **b**aixo/down).
3. `lferr` (Lists the tools the gardener has picked up and currently holds in the backpack).

### Step 3: Plant and Fast-Forward Time

Let's plant a rose and fast-forward time to watch nature take its course.

1. `planta b b r` (Plants a Rose `r` at coordinates `b b`. You can also try `c` for Cactus or `x` for Passionfruit).
2. `avanca 3` (Advances 3 turns. The rose will consume water and nutrients from the soil. If it meets the right conditions, it might even reproduce!).
3. `lsolo b b` (Inspects the soil at coordinate `b b` to see how much water and nutrients are left).

### Step 4: Save Your Progress

1. `grava meu_jardim` (Saves the exact current state of the simulation).
2. You can keep playing or test dangerous things. If you want to go back, just type: `recupera meu_jardim`.

## 📜 Full Command List

*Note: The actual commands are in Portuguese to match the C++ engine parser.*

### General Management and Time

* `jardim <rows> <columns>`: Creates the garden map (e.g., `jardim 10 10`).
* `avanca [n]`: Advances time by `n` turns (if `n` is omitted, advances 1 turn).
* `grava <name>`, `recupera <name>`, `apaga <name>`: Manages save states (Save, Load, Delete).
* `fim`: Exits the simulator.

### Gardener and Actions

* `entra <row> <column>`: Spawns the gardener at a specific coordinate (e.g., `entra a a`).
* `sair`: Removes the gardener from the garden.
* `move <direction>`: Moves the gardener **c**ima (up), **b**aixo (down), **e**squerda (left), or **d**ireita (right) (e.g., `move c`).
* `planta <row> <column> <type>`: Plants a seed. Available types: `c` (Cactus), `r` (Rose), `e` (Weed), `x` (Passionfruit).
* `colhe <row> <column>`: Harvests the plant at the specified position.

### Tools and Information

* `lferr`: Lists carried tools.
* `usa <id>`: Uses the tool with the specified ID.
* `lsolo <row> <column> [radius]`: Shows soil details (water, nutrients, etc.).
* `lplanta <row> <column>`: Shows specific details of a plant (e.g., Beauty, Health).
* `lplantas`: Lists all plants currently on the map.
* `larea`: Lists all non-empty cells (containing tools, plants, or the gardener).

## 🧬 Architecture & Applied OOP Concepts

### 1. Inheritance

Inheritance was used to create logical taxonomies and avoid code duplication:

* **Plants:** The `Planta` class defines the base structure (water levels, nutrients, living state). Classes like `Roseira` (Rose), `Cacto` (Cactus), and `Maracuja` inherit from this base, sharing the same attributes but implementing their own unique survival rules.
* **Commands:** The abstract base class `Comandos` defines the properties of a text input. All game commands (e.g., `Apaga`, `Plantar`, `Avanca`) inherit from this class.

### 2. Polymorphism

Polymorphism allows the simulator to treat different objects generically, triggering the correct behavior at runtime:

* **In the Ecosystem (`atualizar()`):** The `Jardim` (Garden) has a matrix of `Solo` (Soil), and each soil cell holds a pointer to the base class `Planta`. When the turn advances, the engine generically calls `planta->atualizar(solo)`. If the plant is a `Roseira`, it invokes its exclusive rules (e.g., dying if all 8 neighbors are occupied).
* **In Tools (`funcionalidade_ferramenta()`):** The executed code depends on the instantiated tool (a `Regador`/Watering Can increases water, a `TesouraDePodar`/Pruning Shears interacts with the plant).
* **Design Pattern (Command & Factory):** The static method `Comandos::criaComando` reads the input and polymorphically instantiates the correct command subclass (`Apaga`, `Move`, etc.), returning a generic pointer that the engine uses to call the `executa()` method.

## 🏗️ Main Class Dictionary

* **`Simulador`**: The "Brain" or Game Manager. Manages turns, processes commands, manages the gardener's inventory, and maintains the save/load system using a `std::map`.
* **`Jardim`**: The game grid. Randomly spawns tools across the map and invokes the update cycle for all cells every turn.
* **`Solo`**: The unit cell of the Garden. Acts as a container that can simultaneously hold a pointer to a `Planta`, a `Ferramenta` (Tool), and the `Jardineiro` (Gardener).
* **`Comandos`**: Interface/Superclass to encapsulate all user inputs into an Object-Oriented structure.

## 📊 Classes Relational Diagrams

Below there are some relationships diagrams representing inheritance relation between the classes. 

```shell
=============================================================
               1. MANAGEMENT & ENVIRONMENT
=============================================================

 +-------------------+                 +-------------------+
 |     Simulador     | 1 -------- 1    |      Jardim       |
 +-------------------+   manages  ->   +-------------------+
           |                                     |
           |                                     | is composed of
      has access                                 | (1 : *)
           |                                     v
 +-------------------+                 +-------------------+
 |     Comandos      |                 |       Solo        |
 +-------------------+                 +-------------------+
 | - simulacao       |                   |               |
 | + criaComando()   |          contains |               | contains
 | + executa()       |            (0..1) |               | (0..1)
 +-------------------+                   v               v
      ^ ^ ^ ^                      +----------+    +--------------+
     /  | |  \                     |  Planta  |    |  Ferramenta  |
    /   | |   \                    +----------+    +--------------+
 Apaga ... Move                      (see part 2)    (see part 3)

================================================================
                 2. PLANT INHERITANCE
================================================================

                     +------------------------+
                     |         Planta         |
                     +------------------------+
                     | # int agua             |
                     | # int nutrientes       |
                     | # bool viva            |
                     | + atualizar(Solo&)     |
                     +------------------------+
                       ^      ^      ^      ^
                       |      |      |      |
          +------------+      |      |      +-------------+
          |                   |      |                    |
     +---------+          +-------+ +-----------+    +----------+
     | Roseira |          | Cacto | |ErvaDaninha|    | Maracuja |
     +---------+          +-------+ +-----------+    +----------+

=================================================================
                 3. TOOL INHERITANCE
=================================================================

                     +--------------------------------+
                     |           Ferramenta           |
                     +--------------------------------+
                     | + funcionalidade_ferramenta()  |
                     +--------------------------------+
                       ^      ^         ^          ^
                       |      |         |          |
           +-----------+      |         |          +-----------+
           |                  |         |                      |
      +---------+         +-------+  +-------+        +----------------+
      | Regador |         | Adubo |  | Drone |        | TesouraDePodar |
      +---------+         +-------+  +-------+        +----------------+
```
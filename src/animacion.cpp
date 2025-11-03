#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <Dibujo.hpp>
#include <GestorDibujos.hpp>
#include <cmath> // Para la función std::sin()
#include <chrono> 
#include <thread> 

using namespace ftxui;

int main()
{
    // Crear la ventana con dimensiones fijas.
    auto screen = Screen::Create(
        Dimension::Fixed(80),
        Dimension::Fixed(24));

    // --- Definición de Figuras ASCII ---
    
    // Figura del Avión (Tu diseño)
    // Se ha ajustado ligeramente el padding para que el dibujo sea consistente.
    const std::vector<std::u32string> avion = {
        U"           _    ",
        U"         -=\\`\\  ",
        U"     | ____\\_\\__",
        U"   -=\\c`\"\"\"\"\"\" \"`)",
        U" jgs `~~~~~/ /~~`",
        U"        -==/ /  ",
        U"          '-'   "
    };
    
    // Figura de la Nube (Obstáculo)
    const std::vector<std::u32string> nube = {
        U"   _   _  ",
        U" (  ` ) ) ",
        U"(___(_(_)"
    };
    
    // --- Inicialización de Elementos ---
    
    GestorDibujos gestor;
    
    // Avión: Posicionado cerca del borde izquierdo (Índice 0)
    // Se ajusta la Y inicial para que esté centrado.
    gestor.Agregar(Dibujo(2, 10, avion, ftxui::Color::YellowLight)); 
    
    // Nubes: Serán los obstáculos que se desplazan (Índices 1, 2, 3...)
    gestor.Agregar(Dibujo(40, 5, nube, ftxui::Color::White));      // Nube 1 (Índice 1)
    gestor.Agregar(Dibujo(65, 15, nube, ftxui::Color::White));     // Nube 2 (Índice 2)
    gestor.Agregar(Dibujo(90, 10, nube, ftxui::Color::White));     // Nube 3 (Índice 3)
    
    // --- Bucle de Animación ---
    
    for (int frame = 0; true; ++frame) 
    {
        screen.Clear();

        // 1. MOVIMIENTO DEL AVIÓN (Vertical Oscilatorio)
        // El avión se mueve arriba y abajo simulando turbulencia.
        // 10 es la posición Y central. 5 es la amplitud del movimiento.
        gestor.dibujos[0].y = 10 + 5 * std::sin(frame / 7.0); 

        // 2. MOVIMIENTO DE LAS NUBES (Scroll Horizontal)
        for (size_t i = 1; i < gestor.dibujos.size(); ++i) {
            
            // Mover la nube un paso a la izquierda
            gestor.dibujos[i].x -= 1; 
            
            // Si la nube sale completamente de la pantalla, la reubicamos a la derecha.
            if (gestor.dibujos[i].x + nube[0].size() < 0) {
                 // Reiniciar la posición X fuera de la pantalla a la derecha
                 gestor.dibujos[i].x = screen.dimx();
                 
                 // Nueva posición Y aleatoria (1 a 15)
                 gestor.dibujos[i].y = 1 + (frame % 15); 
            }
        }

        // Dibujar todos los elementos: primero el avión, luego las nubes para que parezca que pasan cerca.
        // Si quieres que el avión parezca pasar por encima, debes dibujarlo al final.
        gestor.DibujarTodos(screen); 

        // Imprime la pantalla
        std::cout << screen.ToString();
        
        // Pausa para controlar la velocidad
        std::this_thread::sleep_for(std::chrono::milliseconds(80)); 
    }
    
    return 0;
}
#pragma once

#include <vector>
#include "Dibujo.hpp" // Depende de la clase Dibujo

/**
 * @brief Administra una colección de objetos Dibujo.
 * Facilita la adición y el dibujo de todos los elementos de la escena.
 */
class GestorDibujos {
public:
    std::vector<Dibujo> dibujos;

    GestorDibujos() = default;

    /**
     * @brief Añade un objeto Dibujo a la colección.
     * @param dibujo El objeto Dibujo a añadir.
     */
    void Agregar(const Dibujo& dibujo) {
        dibujos.push_back(dibujo);
    }

    /**
     * @brief Dibuja todos los objetos de la colección en la pantalla.
     * @param screen El objeto ftxui::Screen donde se dibujarán.
     */
    void DibujarTodos(ftxui::Screen& screen) const {
        for (const auto& dibujo : dibujos) {
            dibujo.Dibujar(screen);
        }
    }
    
    // NOTA: Para el control de animación visto en el ejemplo,
    // es útil acceder al vector directamente: gestor.dibujos[indice].x = nuevo_valor;
};
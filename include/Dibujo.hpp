#pragma once
#include <vector>
#include <string>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

/**
 * @brief Representa un objeto dibujable en la pantalla ASCII.
 * Es la unidad básica de la animación.
 */
class Dibujo {
public:
    int x; // Coordenada X (horizontal) de la esquina superior izquierda.
    int y; // Coordenada Y (vertical) de la esquina superior izquierda.
    std::vector<std::u32string> figura; // El arte ASCII (una línea por string).
    ftxui::Color color; // El color para dibujar la figura.

    /**
     * @brief Constructor de la clase Dibujo.
     * @param x_ Coordenada X inicial.
     * @param y_ Coordenada Y inicial.
     * @param figura_ La figura ASCII.
     * @param color_ El color.
     */
    Dibujo(int x_, int y_, const std::vector<std::u32string>& figura_, ftxui::Color color_ = ftxui::Color::White)
        : x(x_), y(y_), figura(figura_), color(color_) {}

    /**
     * @brief Dibuja el objeto en el buffer de la pantalla.
     * @param screen El objeto ftxui::Screen donde se dibujará.
     */
    void Dibujar(ftxui::Screen& screen) const {
        for (size_t i = 0; i < figura.size(); ++i) {
            // Recorrer cada carácter de cada línea de la figura
            for (size_t j = 0; j < figura[i].size(); ++j) {
                
                // Calcular la posición absoluta en la pantalla
                int px = x + j;
                int py = y + i;

                // Asegurarse de que el pixel esté dentro de los límites de la pantalla
                if (px >= 0 && px < screen.dimx() && py >= 0 && py < screen.dimy()) {
                    // Obtener el carácter y el objeto Pixel de FTXUI
                    ftxui::Pixel& pixel = screen.PixelAt(px, py);
                    
                    // Asignar el carácter y el color
                    // ⬇️ CORRECCIÓN AQUÍ: Convertir char32_t a char y luego a std::string de longitud 1.
                    pixel.character = std::string(1, (char)figura[i][j]);
                    
                    pixel.foreground_color = color;
                }
            }
        }
    }
};
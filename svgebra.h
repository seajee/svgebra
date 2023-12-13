#pragma once

#include <string>

// Valori predefiniti
#define DEFAULT_SVG_WIDTH 1024
#define DEFAULT_SVG_HEIGHT 768

#define DEFAULT_PLANE_SCALE g_width / 20
#define ARROW_LENGTH 10
#define PARABOLA_DX 20

// Funzioni di controllo dell'immagine SVG
void svg_inizio(int width, int height);
void svg_inizio();
void svg_fine();

// Primitive grafiche
void svg_linea(int x1, int y1, int x2, int y2);
void svg_triangolo(int x1, int y1, int x2, int y2, int x3, int y3);
void svg_quadrato(int x, int y, int l);
void svg_rettangolo(int x, int y, int width, int height);
void svg_cerchio(int x, int y, int r);

// Testo
void svg_testo(int x, int y, const std::string& text);

// Funzioni di controllo di un piano cartesiano
void svg_piano_cartesiano_inizio(int scale);
void svg_piano_cartesiano_inizio();
void svg_piano_cartesiano_fine();

// Funzioni applicate al piano cartesiano
void svg_retta(float m, float q);
void svg_parabola(float a, float b, float c);

#include "svgebra.h"

int main(void)
{
    // Configuro l'immagine SVG impostanto la risoluzione
    svg_inizio(800, 800);

    // Qui renderizzo il piano cartesiano con il rispettivo reticolo
    //   e imposto il sistema di coordinate adeguato.
    // Questa funzione può avere come parametro opzionale la dimensione
    //   dell'unità in relazione alla risoluzione dell'immagine
    svg_piano_cartesiano_inizio();

    // Variabili per la retta (y = m*x + q)
    float m = 2.0f;
    float q = 3.0f;

    // Variabili per la parabola (y = a*x*x + b*x + c)
    float a = -2.0f;
    float b =  5.0f;
    float c =  4.5f;

    // Renderizzo gli elementi interessati
    svg_retta(m, q);
    svg_parabola(a, b, c);

    // Ripristino il sistema di coordinate per poter renderizzare
    //   correttamente altre eventuali primitive
    svg_piano_cartesiano_fine();

    // Fine immagine SVG
    svg_fine();

    return 0;
}

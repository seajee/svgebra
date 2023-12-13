#include "svgebra.h"

#include <iostream>
#include <cassert>

// Variabili globali statiche,
//   visibili solo da questo file sorgente

// Dimensione immagine SVG
static int g_width = DEFAULT_SVG_WIDTH;
static int g_height = DEFAULT_SVG_HEIGHT;

// Scala del piano cartesiano
static int g_scale = 1;

void svg_inizio(int width, int height)
{
    // Header immagine SVG
    std::cout
        << "<svg version=\"1.1\" "
        << "width=\"" << width << "\" "
        << "height=\"" << height << "\" "
        << "xmlns=\"http://www.w3.org/2000/svg\">";

    // Inizializzo variabili globali
    g_width = width;
    g_height = height;
}

void svg_inizio()
{
    // Inizializzazione dell'immagine SVG con valori predefiniti
    svg_inizio(DEFAULT_SVG_WIDTH, DEFAULT_SVG_HEIGHT);
}

void svg_fine()
{
    // Racchiudo l'immagine SVG
    std::cout << "</svg>" << std::endl;
}

void svg_linea(int x1, int y1, int x2, int y2)
{
    // Per la linea, si usa il tag '<line>' direttamente
    //   passando i paramentri senza elaborazione
    std::cout
        << "<line "
        << "x1=\"" << x1 << "\" "
        << "y1=\"" << y1 << "\" "
        << "x2=\"" << x2 << "\" "
        << "y2=\"" << y2 << "\" "
        << "style=\"stroke:rgb(0,0,0);stroke-width:1\" />";
}

void svg_triangolo(int x1, int y1, int x2, int y2, int x3, int y3)
{
    // Si compone il triangolo con i tre lati distinti
    svg_linea(x1, y1, x2, y2);
    svg_linea(x2, y2, x3, y3);
    svg_linea(x3, y3, x1, y1);
}

void svg_quadrato(int x, int y, int l)
{
    // Un quadrato è anche un rettangolo
    svg_rettangolo(x, y, l, l);
}

void svg_rettangolo(int x, int y, int width, int height)
{
    // Per i rettangoli, si usa il tag '<rect>' direttamente
    //   passando i paramentri senza elaborazione
    std::cout
        << "<rect "
        << "x=\"" << x << "\" "
        << "y=\"" << y << "\" "
        << "width=\"" << width << "\" "
        << "height=\"" << height << "\" "
        << "stroke=\"black\" fill=\"transparent\" stroke-width=\"1\"/>";
}

void svg_cerchio(int x, int y, int r)
{
    // Per le circonferenze, si usa il tag '<circle>' direttamente
    //   passando i paramentri senza elaborazione
    std::cout
        << "<circle "
        << "cx=\"" << x << "\" "
        << "cy=\"" << y << "\" "
        << "r=\"" << r << "\" "
        << "fill=\"white\" "
        << "stroke=\"black\" />";
}

void svg_testo(int x, int y, const std::string& text)
{
    // Per il testo, si usa il tag '<text>' direttamente
    //   passando i paramentri senza elaborazione
    std::cout
        << "<text "
        << "x=\"" << x << "\" "
        << "y=\"" << y << "\" "
        << "font-size=\"0.6em\">"
        << text << "</text>";
}

void svg_piano_cartesiano_inizio(int scale)
{
    // Prima di inizializzare il piano cartesiano si fa un controllo
    //   sulla risoluzione dell'immagine SVG. Si ha bisogno di un immagine
    //   quadrata per evitare errori nel rendering di funzioni quadratiche
    assert(g_width == g_height && "ERROR: L'immagine SVG non è quadrata. Impostare la risoluzione in svg_inizio(int, int)");

    // Imposto la variabile globale di fattore di
    //   scala dell'unità del piano cartesiano
    g_scale = scale;

    // Definisci un pattern con id #grid per semplificare la generazione
    //   di reticoli generici
    std::cout
        << "<defs>"
        << "<pattern id=\"grid\" "
        << "width=\"" << g_scale << "\" "
        << "height=\"" << g_scale << "\" "
        << "patternUnits=\"userSpaceOnUse\">"
        << "<path d=\"M 100 0 L 0 0 0 100\" fill=\"none\" stroke=\"gray\" stroke-width=\"1\"/></pattern>"
        << "</defs>"

        // Crea il reticolo seguendo il pattern definito
        << "<rect fill=\"url(#grid)\" "
        << "height=\"" << g_height << "\" "
        << "width=\"" << g_width << "\" "
        << "y=\"0\""
        << "></rect>";

    // Assi cartesiani
    svg_linea(0, g_height / 2, g_width, g_height / 2);
    svg_linea(g_width / 2, 0, g_width / 2, g_height);

    // Freccie degli assi
    svg_linea(g_width / 2, 0,
            g_width / 2 - ARROW_LENGTH, ARROW_LENGTH); // x left
    svg_linea(g_width / 2, 0,
            g_width / 2 + ARROW_LENGTH, ARROW_LENGTH); // x right

    svg_linea(g_width, g_height / 2,
            g_width - ARROW_LENGTH, g_height / 2 - ARROW_LENGTH); // y up
    svg_linea(g_width, g_height / 2,
            g_width - ARROW_LENGTH, g_height / 2 + ARROW_LENGTH); // y down

    // Testo con unità del reticolo sugli assi
    int ux = g_width / g_scale; // Dimensione dell'unità x in pixel

    for (int x = 0; x < ux; ++x) {
        int u = x - (ux / 2); // Il carattere da renderizzare
        svg_testo(x * g_scale, g_height / 2 + 10, std::to_string(u));
    }

    int uy = g_height / g_scale; // Dimensione dell'unità y in pixel

    for (int y = 0; y < uy; ++y) {
        int u = uy - y - (uy / 2); // Il carattere da renderizzare

        // Il carattere '0' per l'origine è già stato
        //   renderizzato prima
        if (u == 0)
            continue;

        svg_testo(g_width / 2 - 10, y * g_scale, std::to_string(u));
    }

    // Imposta il sistema di coordinate per il piano cartesiano
    //   spostando l'origine al centro dell'immagine, ossia nell'
    //   intersezione dei due assi cartesiani
    // -,+ | +,+
    // ----|----
    // -,- | +,-
    std::cout
        << "<g transform=\"translate("
        << g_width / 2 << ", " << g_height / 2 << ") "
        << "scale(1,-1)\">";
}

void svg_piano_cartesiano_inizio()
{
    // Inizializzazione del piano cartesiano con
    //   fattore di scala predefinito
    svg_piano_cartesiano_inizio(DEFAULT_PLANE_SCALE);
}

void svg_piano_cartesiano_fine()
{
    // Ripristina sistema di coordinate
    std::cout << "</g>";
}

void svg_retta(float m, float q)
{
    // y = m * x + q

    // Strategia:
    //   Si ricavano due punti che sporgono dall'immagine
    //   finale, ottenendo così l'effetto di una retta infinita

    // Primo punto
    int x1 = -g_width / 2;
    int y1 = m*x1 + q;

    // Secondo punto
    int x2 = g_width / 2;
    int y2 = m*x2 + q;

    // Si renderizza tenendo conto del fattore di scala
    svg_linea(x1 * g_scale, y1 * g_scale, x2 * g_scale, y2 * g_scale);
}

void svg_parabola(float a, float b, float c)
{
    // y = a*x*x + b*x + c

    // Strategia:
    //   Data la natura della funzione quadratica, si possono
    //   sfruttare le funzioni fondamentali delle immagini vettoriali che
    //   caratterizzano la rappresentazione mediante funzioni delle figure.
    //
    //   Si ottengono i dati necessari per renderizzare una curva di bezier
    //   quadratica mediante la sostituzione delle variabili nella formula
    //   della parabola.
    //
    //   Si ha bisogno di minimo 3 punti per definire la curva:
    //
    //   1) dx <- PARABOLA_DX (Macro con un valore di default.
    //                       Può essere qualsiasi numero dato che
    //                       il resto della curva viene adattata)
    //
    //      y <- f(dx)        Con dx si ricava la corrispettiva y
    //
    //   2) V(vx, vy)         Il vertice della parabola
    //
    //   3) Il terzo punto può corrispondere al primo punto specchiato
    //      rispetto all'asse di simmetria. Si può fare questa operazione
    //      sfruttando il vertice della parabola già ricavato.

    // Per evitare errori nella definizione di parabole
    //   e per evitare divisioni per zero, si genera un errore se
    //   la componente 'a' equivale a zero
    assert(a != 0 && "ERRORE: Con le parabole, 'a' non può equivalere a zero");

    // Si ricavano i principali dati della parabola
    float delta = b*b - 4*a*c;
    float vx = (-b / (2*a)); // X del vertice
    float vy = (-delta / (4*a)); // Y del vertice

    // Punto estremo. Si usa per ricavare il suo corrispondente
    //   dall'asse di simmetria
    int dx = PARABOLA_DX;
    int y = a*dx*dx + b*dx + c;

    // Si utilizza il tag '<path>' per definire la curva di bezier con i
    //   suoi tre punti
    std::cout
        << "<path "
        // Traslazione secondo il vertice della parabola
        << "transform=\"translate(" << vx * g_scale << ", " << vy * g_scale << ")\" "
        // Curva di Bezier quadratica
        << "d=\""
        << "M" << -dx * g_scale << "," << y * g_scale << " "
        << "Q" << 0 << "," << -y * g_scale << " "
        <<        dx * g_scale << "," << y * g_scale << "\" "
        << "fill=\"transparent\" stroke=\"black\" stroke-width=\"1\" />";
}

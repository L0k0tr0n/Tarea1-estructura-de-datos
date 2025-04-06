#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>

using namespace std;

struct Imagen {
    unsigned char* data;
    int width, height, channels;
};

// Cargar imagen desde archivo
Imagen* load(const char* filename) {
    Imagen* img = new Imagen();
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    return img;
}

// Guardar imagen en archivo
void save(Imagen* img, const char* filename) {
    stbi_write_png(filename, img->width, img->height, img->channels, img->data, img->width * img->channels);
    cout << "Imagen guardada como: " << filename << endl;
}

// Operación 1: Efecto espejo horizontal
void espejo(Imagen* img) {
    int ancho = img->width;
    int alto = img->height;
    int canales = img->channels;

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho / 2; x++) {
            int i1 = (y * ancho + x) * canales;
            int i2 = (y * ancho + (ancho - 1 - x)) * canales;

            for (int c = 0; c < canales; c++) {
                unsigned char temp = img->data[i1 + c];
                img->data[i1 + c] = img->data[i2 + c];
                img->data[i2 + c] = temp;
            }
        }
    }

    cout << "Efecto espejo aplicado.\n";
}

// Operación 2: Atenuar imagen (solo R, G, B)
void atenuar(Imagen* img, float alpha) {
    int ancho = img->width;
    int alto = img->height;
    int canales = img->channels;

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            int index = (y * ancho + x) * canales;

            for (int c = 0; c < 3 && c < canales; c++) {
                float nuevo = img->data[index + c] * alpha;
                if (nuevo > 255) nuevo = 255;
                if (nuevo < 0) nuevo = 0;
                img->data[index + c] = static_cast<unsigned char>(nuevo);
            }
        }
    }

    cout << "Imagen atenuada con alpha = " << alpha << endl;
}

int main() {
    Imagen* img = load("Pikachu.png");

    if (img->data == nullptr) {
        cout << "Error al cargar la imagen." << endl;
        return 1;
    }

    while (true) {
        cout << "\n--- MENÚ DE OPERACIONES ---" << endl;
        cout << "1. Aplicar efecto espejo" << endl;
        cout << "2. Atenuar imagen" << endl;
        cout << "3. Salir del programa" << endl;
        cout << "Seleccione una opción (1-3): ";

        int opcion;
        cin >> opcion;

        // Validar si la entrada fue un número
        if (cin.fail()) {
            cin.clear(); // limpiar estado de error
            cin.ignore(10000, '\n'); // limpiar entrada anterior
            cout << "Entrada inválida. Debe ingresar un número del 1 al 3." << endl;
            continue;
        }

        if (opcion == 1) {
            espejo(img);
            save(img, "output_espejo.png");
        } 
        else if (opcion == 2) {
            float alpha;
            cout << "Ingrese valor de atenuación (entre 0.0 y 1.0): ";
            cin >> alpha;

            if (cin.fail() || alpha < 0.0f || alpha > 1.0f) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Valor inválido para atenuación. Debe estar entre 0.0 y 1.0.\n";
                continue;
            }

            atenuar(img, alpha);
            save(img, "output_atenuada.png");
        } 
        else if (opcion == 3) {
            cout << "Saliendo del programa...\n";
            break;
        } 
        else {
            cout << "Opción fuera de rango. Ingrese 1, 2 o 3.\n";
        }
    }

    // Liberar memoria
    stbi_image_free(img->data);
    delete img;

    return 0;
}


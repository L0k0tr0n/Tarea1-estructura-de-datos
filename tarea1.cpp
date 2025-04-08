#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

// Importacion de librerias. Los archivos correspondientes deben estar en el mismo directorio que el .cpp.
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Struct que almacena la data de una imagen
struct Imagen{
    unsigned char* data;
    int width, height, channels;
};

// Abrir imagen desde memoria local
Imagen* load(const char* filename) {
    Imagen* img = new Imagen();
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    return img;
}

// Guardar imagen en memoria local
void save(Imagen* img, const char* filename) {
    stbi_write_png(filename, img->width, img->height, img->channels, img->data, img->width * img->channels);
    cout << "Imagen guardada:  " << filename << "\n";
}


/* ****
* TipoFunción: Función N°1, Hacer efecto "espejo"
******
* Resumen: Esta función recorrera cada fila de la imagen y dentro de cada fila se intercambiaran los pixeles de la izquierda, con sus respectivos pixeles de la derecha
generando asi el efecto "espejo"
******
* Input :Esta función no recibe parametros
* 
* .......
******
* Returns: función tipo void, no retorna.
* 
**** */
void operacion1() {
    Imagen *img = load("Pikachu.png");
    
    int width = img->width;
    int height = img->height;
    int channels = img->channels;
    unsigned char* data = img->data;

    for (int fila = 0; fila < height; fila++) {
        for (int col = 0; col < width / 2; col++) {
            int col_opuesta = width - col - 1;

            int indice_izquierdo = (fila * width + col) * channels;
            int indice_derecho = (fila * width + col_opuesta) * channels;

            for (int ch = 0; ch < channels; ch++) {
                swap(data[indice_izquierdo + ch], data[indice_derecho + ch]);
            }
        }
    }
    Imagen *imagen_espejo = new Imagen();
    imagen_espejo->data = data;
    imagen_espejo->width = width;
    imagen_espejo->height = height;
    imagen_espejo->channels = channels;

    save(imagen_espejo, "PikachuEspejo.png");
    stbi_image_free(img->data);
    delete img;
    delete imagen_espejo;


}


/* ****
* TipoFunción: Función N°2, Rotar90° horario
******
* Resumen: Esta función va procesar la imagen y la rotara en 90° horarios.
******
* Input :Esta función no recibe parametros
* 
* .......
******
* Returns: función tipo void, no retorna.
* 
**** */

void operacion2(){

    Imagen *img = load("Pikachu.png");

    int anchooriginal = img->width;
    int largooriginal = img->height;
    int channels = img->channels;


    //Nuevos datos para que la imagen rote en 90°
    int largonuevo = anchooriginal;
    int anchonuevo = largooriginal;

    //reservamos memoria para los nuevos datos
    unsigned char *datosnuevos = new unsigned char[largonuevo * anchonuevo * channels];

    //Hacemos un bucle para recorrer pixel por pixel de la imagen original y asignarlo a indice correspondiente
    for  (int fila = 0; fila < largooriginal; fila++){
        for (int columna = 0; columna < anchooriginal; columna ++){

            //calculamos indice el indice de los pixeles originales
            int indiceoriginal = (fila * anchooriginal + columna) * channels;
            
            //trasnformamos la posicion para hacer efectiva la rotacion de 90°
            int nuevafila = columna;
            int nuevacolumna = largooriginal -1 - fila;
            
            //calculamos los indices de la imagen rotada
            int indicenuevo = (nuevafila * anchonuevo + nuevacolumna) * channels;
            
            //copiamos todos los canales
            for (int chn = 0; chn < channels; chn ++){
                datosnuevos[indicenuevo + chn] = img->data[indiceoriginal+chn];

            }
        }
    }
    
    //Guardamos los datos de la nueva imagen rotada
    Imagen *Imagen_rotada = new Imagen();
    Imagen_rotada->data = datosnuevos;
    Imagen_rotada->width = anchonuevo;
    Imagen_rotada->height = largonuevo;
    Imagen_rotada->channels = channels;

    //guardamos
    save(Imagen_rotada, "Pikachu_rotado_90°.png");

    //liberamos memoria
    stbi_image_free(img->data);
    delete img;
    stbi_image_free(Imagen_rotada->data);
    delete Imagen_rotada;


}

/* ****
* TipoFunción: Función N°3, Atenuar imagen
******
* Resumen: Esta función va procesar todos los pixeles de la imagen, para posteriormente multiplicarlos por un parametro float, y asi encontrar el efecto de "atenuacion"
******
* Input :Esta función recibe un parametro del tipo float, que nos indicara el grado de "atenuacion"
* 
* .......
******
* Returns: función tipo void, no retorna.
* 
**** */
void operacion3(float alpha) {
    Imagen *img = load("Pikachu.png");
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
    Imagen *imagen_atenuada = new Imagen();
    imagen_atenuada->data = img->data;  
    imagen_atenuada->width = ancho;
    imagen_atenuada->height = alto;
    imagen_atenuada->channels = canales;

    save(imagen_atenuada, "PikachuAtenuado.png");
    stbi_image_free(img->data);
    delete img;
    delete imagen_atenuada;

}


/* ****
* TipoFunción: Función N°4, Blanco y Negro
******
* Resumen: Esta función va procesar la imagen mediante un parametro
el cual indicara un limite en el que los pixeles se vuelven blanco o negros
******
* Input :Esta función recibe un unico parametro de tipo entero el cual como ya mencionado anteriormente
marcara un limite en el cual los pixeles se volveran blancos o negros.
* 
* .......
******
* Returns: función tipo void, no retorna.
* 
**** */
void operacion4(int lim){
    Imagen *img = load("Pikachu.png");

    int anchooriginal = img->width;
    int largooriginal = img->height;
    int channels = img->channels;
    int pixeles = largooriginal * anchooriginal;

    
    //recorremos cada pixel para aplicar la logica de volver blanco y negro
    for(int i = 0; i < pixeles; i++){

        
        int ind = i * channels;

        //sumamos los valores de cada canal del pixel (RGB)
        int suma = 0;
        for (int chn = 0; chn < channels; chn ++){
            suma += img->data[ind + chn];
        }

        //calculamos el promedio de la intensidad
        int intensidad = suma/channels;

        //evaluamos si se supera el "lim" y asignamos blanco o negro segun corresponda ? 255:0
        unsigned char nw = (intensidad >= lim) ? 255:0;

        //por ultimo, asignamos el valor blanco o negro a todos los pixels con su respectivo canal.
        for (int chn = 0; chn < channels; chn++){
            img->data[ind + chn] = nw;
        }
    }
    
    //guardamos
    save(img, "Pikachu_blanco_negro.png");

    //liberamos memoria
    stbi_image_free(img->data);
    delete img;
}

void operacion5(){
    Imagen *img = load("Pikachu.png");

    int ancho = img->width;
    int alto = img->height;
    int channels = img->channels;

    //convertimo la imagen a escala de grises
    unsigned char *gray = new unsigned char[ancho * alto];
    for (int y = 0;y < alto; y++){
        for (int x = 0; x < ancho;x++){
            int indice = (y * ancho + x) * channels;
            int intensidad = 0;

            for (int c = 0; c < 3 && c < channels; c++){
                intensidad += img->data[indice + c];


            }
            intensidad /= 3;

            gray[y * ancho + x] = static_cast<unsigned char>(intensidad);

        }

    }
    //abrimos el archivo para escribir los caracteres
    const char *ascii_chars = "@%#*+=-:. ";
    int num_chars = strlen(ascii_chars);
    ofstream archivo_salida("Pikachu_ASCII.txt");

    //convertimos pixeles a caracter ascii
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            int intensidad = gray[y * ancho + x];
            int indice_ascii = (intensidad * (num_chars - 1)) / 255;
            archivo_salida << ascii_chars[indice_ascii];
        }
        archivo_salida << '\n';


    }
    //liberamos memoria
    archivo_salida.close();
    delete[] gray;
    stbi_image_free(img->data);
    delete img;
}


int main() {
    operacion1();
    operacion2();
    operacion3(0.5);
    operacion4(120);
    operacion5();
    return 0;
    
}
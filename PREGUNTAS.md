Pregunta N°1: ¿Por que si los pixeles de la imagen son números enteros ∈ [0, 255], utilizamos el tipo de dato
unsigned char?

Pregunta N°2: ¿Cuales serían las diferencias entre usar unsigned int versus unsigned char? Responder
cuantitativamente para una imagen RGB de dimensiones (N,N,3)

Pregunta N°3: Usando este esquema de almacenamiento unidimensional: ¿Cuál sería el índice del primer
pixel del canal azul?

Pregunta N°4: ¿Cómo podemos convertir una imagen RGB a escala de grises?


Respuesta P°1: Básicamente es por la optimizacion de memoria. "Unsigned Char", garantiza maxima eficiencia en memoria y rendimiendo, ya que ocupa 1 byte de memoria
y su rango de [0 , 255] cubre los 256 valores posibles de un canal de 8 bits, en cambio al utilizar "int" ocupamos 4 bytes, lo que se traduce a 4 veces mas que "Unsigned Char"
(https://learn.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-170)
 

Respuesta P°2: Como se especifica en la documentacion de c++ (https://learn.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-170) el tamaño en memoria de "Unsigned Int" es de
4 bytes, es decir, cuatro veces mayor que el de "Unsigned Char" (1 byte)

Analisis Cuantitativo Pregunta N°2: Con "Unsigned Char" cada "canal" (R, G, B) ocupa 1 byte,
 y para verlo de una forma mas practica, haremos un ejemplo con una imagen con resolucion de 1920 x 1080

 Memoria = 1920 x 1080 x 3(R,G,B) x 1byte = 5.93 MB aprox

 en cambio si ocupamos "Unsigned Int" nos quedaria:

 Memoria = 1920 x 1080 x 3 x 4byte = 23.73 MB aprox

 en conclusion; estariamos malgastando 4 veces mas memoria que si ocuparamos "Unsigned Char"


 Respues N°3: Segun la documentacion de "stb_image"(https://github.com/nothings/stb/blob/master/stb_image.h) el índice del primer pixel de canal azul (B) en el array unidimensional
 seria 2 debido a que en el array, estan ordenandos de la siguiente forma [R G B R G B R G B......], y como partimos del del 0, el BLUE queda en en el índice = 2



Respuesta N°4: Segun "Solarian Programmer", para convertirar una imagen RGB a gris debemos acceder a cada pixel mediante un bucle(ciclo for en este caso)
multiplicando sus componentes R, G y B por 0.299, 0.587 y 0.114 respectivamente, la suma de estos valores hace que los pixels de la imagen se vean grises en su totalidad
que se almacenaran en un nuevo array y de un solo canal. 

La función en especifico:
void rgb_to_grayscale(const unsigned char* rgb, unsigned char* gray, int width, int height) {
    for (int i = 0; i < width * height; ++i) {
        // Fórmula de luminancia BT.601
        gray[i] = 0.299f * rgb[3*i] + 0.587f * rgb[3*i + 1] + 0.114f * rgb[3*i + 2];
    }
}
Respuesta 6: Puede ser que el programa no está identificando bien, cuáles son los píxeles que deben mantenerse negros. de modo que se estén revisando mal los valores de color, como por ejemplo que no se esté preguntando si R, G y B son igual a 0 al mismo tiempo. Entonces, en vez de dejar solo los píxeles negros, termina dejando los blancos o los de color. También podría ser que el programa simplemente deja todo igual porque no hay una condición que cambie el valor cuando no es negro. Quizás habría que asegurarse de que si el píxel no es negro, se reemplace por blanco o por algún valor específico. 
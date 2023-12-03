#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <vector>

using namespace cv;
using namespace std;

void processPixels(Mat& image, int startRow, int endRow) {
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            // Acceder a los componentes B, G y R del píxel
            Vec3b& pixel = image.at<Vec3b>(i, j);

            // Realizar alguna manipulación en los valores de los píxeles
            pixel[0] = 0.11 * pixel[0]; // Blue
            pixel[1] = 0.59 * pixel[1]; // Green
            pixel[2] = 0.30 * pixel[2]; // Red
        }
    }
}

int main() {
    // Carpeta que contiene las imágenes de entrada
    string folderName = "Imagenes";

    // Pedir al usuario el nombre de la imagen de entrada
    cout << "Ingrese el nombre de la imagen de entrada (con extension): ";
    string inputName;
    cin >> inputName;

    // Pedir al usuario el nombre de la imagen de salida
    cout << "Ingrese el nombre de la imagen de salida (con extension): ";
    string outputName;
    cin >> outputName;

    // Construir las rutas completas de los archivos de entrada y salida
    string inputPath = folderName + "/" + inputName;
    string outputPath = "imagenesConvertidas/" + outputName;

    // Cargar la imagen desde el archivo de entrada
    Mat image = imread(inputPath);

    //Mostrar la imagen original
    imshow("Imagen Original", image);

    // Obtener las dimensiones de la imagen
    int height = image.rows;
    int width = image.cols;

     // Solicitar al usuario que ingrese el número de hilos
    int numThreads;
    cout << "Ingrese el número de hilos: ";
    cin >> numThreads;

    // Calcular el número de filas por hilo
    int rowsPerThread = height / numThreads;

    // Vector para almacenar los hilos
    vector<thread> threads;

    // Crear hilos y procesar diferentes partes de la matriz
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? height : (i + 1) * rowsPerThread;
        threads.emplace_back(processPixels, ref(image), startRow, endRow);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    // Mostrar la imagen con los cambios en su matriz de pixeles
    imshow("Imagen Original", image);
    imwrite(outputPath, image);
    waitKey(0);

    // Guardar la imagen en escala de grises en el archivo de salida


    cout << "Imagen en escala de grises (Luminosidad) guardada en: " << outputPath << endl;
    return 0;
}

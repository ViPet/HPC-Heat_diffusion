#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

double size_x, size_y, k, d, c, L, delta_t, max_time;
char *inputName, *outputName;
int size_tx, size_ty;

double get(double *T, int i, int j) {
    return T[(j * size_tx) + i];
}

void set(double *T, int i, int j, double val) {
    T[(j * size_tx) + i] = val;
}

void compute(double *T, double *T_new) {
    double p = k / (d * c);
    double discr = delta_t / (L * L);
    for (int i = 1; i <= size_tx - 2; i++) {
        for (int j = 1; j <= size_ty - 2; j++) {
            double val =
                    get(T, i, j) * (1 - 4 * discr * p) +
                    discr * p * (get(T, i - 1, j) + get(T, i + 1, j) + get(T, i, j - 1) + get(T, i, j + 1));

            set(T_new, i, j, val);
        }
    }
}

/*
 * DIFFERENCES between cpu and gpu only in this function
 */
double *startComputation(double *T, double *T_new) {
    int i = 0;
    for (i = 0; i * delta_t < max_time; i++) {
        if (i % 2 == 1 ) {
            compute(T_new, T);
        } else {
            compute(T, T_new);
        }
    }
// Return the latest matrix
    if (i % 2 == 1) {
        return T_new;
    } else {
        return T;
    }
}

int main(int argc, char **args) {
    if (argc < 10) {
        cout << "Missing parameters" << endl;
    }
    size_x = strtod(args[1], NULL);
    size_y = strtod(args[2], NULL);

    k = strtod(args[3], NULL);
    d = strtod(args[4], NULL);
    c = strtod(args[5], NULL);
    L = strtod(args[6], NULL);
    delta_t = strtod(args[7], NULL);
    max_time = strtod(args[8], NULL);

    inputName = args[9];
    outputName = args[10];

    size_tx = (int) ceil(size_x / L);
    size_ty = (int) ceil(size_y / L);

    double *T = new double[size_tx * size_ty];
    double *T_new = new double[size_tx * size_ty];

    freopen(inputName, "r", stdin);
    freopen(outputName, "w", stdout);

    for (int i = 0; i != size_tx * size_ty; i++) {
        int x, y;
        float temp;
        scanf("%d %d %f", &x, &y, &temp);
        set(T, x, y, temp);
    }

    for (int i=0; i<size_tx; i++){
        T_new[i] = T[i];
        T_new[(size_ty-1)*size_tx + i ] = T[(size_ty-1)*size_tx + i];
    }

    for (int j=0; j<size_ty; j++) {
        T_new[size_tx*j] = T[size_tx*j];
        T_new[(size_tx*j)+size_tx-1] = T[(size_tx*j)+size_tx-1];
    }

    double *result = startComputation(T, T_new);

    
    /*OUTPUT matrice*/
    for (int i=0; i<size_tx; i++) 
        for (int j=0; j<size_ty; j++)
            printf("%d %d %.2f\n", i, j, result[(j * size_tx) + i]);
   
    return 0;

}

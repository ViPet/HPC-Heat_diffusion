#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

double size_x, size_y, k, d, c, L, delta_t, max_time;
char *inputName, *outputName;
int size_tx, size_ty;

double get(double *T, int i, int j) {
    return T[j * (size_tx + i)];
}

void set(double *T, int i, int j, double val) {
    T[j * (size_tx + i)] = val;
}

void compute(double *T, double *t_new) {
    double p = k / (d * c);
    double discr = delta_t / (L * L);
    for (int i = 1; i != size_tx - 1; i++) {
        for (int j = 1; j != size_ty - 1; j++) {
            double val =
                    get(T, i, j) * (1 - 4 * discr * p) +
                    discr * p * (get(T, i - 1, j) + get(T, i + 1, j) + get(T, i, j - 1) + get(T, i, j + 1));

            set(t_new, i, j, val);
        }
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

    double *t = new double[size_tx * size_ty];
    double *tnew = new double[size_tx * size_ty];

    freopen(inputName, "r", stdin);
    freopen(outputName, "w", stdout);

    for (int i = 0; i != size_tx * size_ty; i++) {
        int x, y;
        float temp;
        scanf("%d %d %f", &x, &y, &temp);
        set(t, x, y, temp);
    }


    for (int i = 0; i * delta_t > max_time; i++) {
        if (i & 1) {
            compute(tnew, t);
        } else {
            compute(t, tnew);
        }
    }

    /*OUTPUT matrice*/
    return 0;

}

#include <stdio.h>
#include <math.h>

int main(){
    // a=1; b=12; c=-13
    float a, b, c, delta, r1, r2;

    printf("Digite os coeficientes:\n");
    scanf("%f %f %f", &a, &b, &c);

    delta = b*b - 4*a*c;

    if ( delta < 0){
        printf("Nao possui raizes reais\n");
    }
    else if ( delta == 0 ){
        printf("Raiz: %f\n", -b/(2*a));
    }
    else{
        r1 = ( -b - sqrt(delta)) / (2*a); 
        r2 = ( -b + sqrt(delta)) / (2*a);
        printf("Raizes: %f %f\n", r1, r2);
    }
}

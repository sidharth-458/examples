#include <stdio.h>

int main() {
    double num1, num2;
    char op;

    printf("Enter an operator (+, -, *, /, %%): ");
    scanf(" %c", &op);       // space before %c avoids reading leftover newline

    printf("Enter two numbers: ");
    scanf("%lf %lf", &num1, &num2);

    switch (op) {
        case '+':
            printf("Result: %.2lf\n", num1 + num2);
            break;
        case '-':
            printf("Result: %.2lf\n", num1 - num2);
            break;
        case '*':
            printf("Result: %.2lf\n", num1 * num2);
            break;
        case '/':
            if (num2 != 0)
                printf("Result: %.2lf\n", num1 / num2);
            else
                printf("Error: Division by zero is not allowed.\n");
            break;
        case '%':
            // modulus only works on integers
            printf("Result: %d\n", (int)num1 % (int)num2);
            break;
        default:
            printf("Error: Invalid operator.\n");
    }

    return 0;
}


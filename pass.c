#include <stdio.h>

/**
 * factorial - To calculate the factorial of a number
 * @n: The number
 *
 * Return: The factorial of n
 */
unsigned int factorial(unsigned int n)
{
	if (n == 0)
		return (1);

	return (n * factorial(n - 1));
}

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	unsigned int number = 5;
	unsigned int result;

	result = factorial(number);

	printf("The factorial of %u is: %u\n", number, result);

	return (0);
}

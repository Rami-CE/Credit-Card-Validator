#include <stdio.h>
#include <stdbool.h>

int sumDigits(int);
int countDigits(long);
int getFirstDigits(long, int);
bool isValid(long);
bool isAMEX(long);
bool isMasterCard(long);
bool isVisa(long);

int main(void)
{
    long credit;
    printf("Enter your credit card's number: ");
    
    if(scanf("%li", &credit) != 1)
    {
        printf("Error: Enter numbers only!\n");
        return 1;
    }

    if(isValid(credit))
    {
        if (isAMEX(credit))
            printf("AMEX\n");
        else if (isVisa(credit))
            printf("VISA\n");
        else if (isMasterCard(credit))
            printf("MASTERCARD\n");
        else printf("Unknown\n");
    }
    else printf("INVALID\n");

    return 0;
}

int sumDigits(int n)
{
    int sum = 0;

    while(n != 0)
    {
        sum += (n % 10);
        n /= 10;
    }

    return sum;
}

int countDigits(long n)
{
    int digitCount = 0;

    if (n == 0)
        return 1;
    else if(n < 0)
        return -1;

    while(n != 0)
    {
        digitCount++;
        n /= 10;
    }

    return digitCount;
}

int getFirstDigits(long number, int amount)
{
    int length = countDigits(number);

    if(amount > length || amount < 1) return -1;

    for(int i = 0; i < length - amount; i++)
    {
        number /= 10;
    }

    return number;
}

bool isValid(long n) // Luhn's Algorithm
{
    if(n < 0) return 0;
    
    int digit;
    int checksum = n % 10; 

    n /= 10; // exclude last digit

    for (int i = 0; n != 0; i++)
    {
        digit = n % 10; // extract a digit
        n /= 10;

        if(i % 2 == 0) // even index
        {
            digit *= 2; // multiply by 2
            if(digit > 9)
            {
                digit = sumDigits(digit);
            }
            checksum += digit;   
        }
        else // odd index
        {
            checksum += digit;
        }
    }

    return checksum % 10 == 0;
}

bool isAMEX(long n) // 15 digits, start with 34 or 37
{
    int length = countDigits(n);

    int firstTwoDigits = getFirstDigits(n, 2);

    // check for beginning with 34 or 37 & length = 15

    if(((firstTwoDigits == 34 || firstTwoDigits == 37) && length == 15) == 1) 
        return true;
    return false;
}

bool isMasterCard(long n) // 16 digits, start with 51 or 52 or 53 or 54 or 55
{
    int digitCount = countDigits(n);
    int firstTwoDigits = getFirstDigits(n, 2);
    
    if(((firstTwoDigits >= 51 && firstTwoDigits <= 55) && digitCount == 16) == 1) 
        return true;
    return false;
}

bool isVisa(long n) // 13 or 16 digits, start with 4
{
    int digitCount = countDigits(n);
    int firstDigit = getFirstDigits(n, 1);

    if(((firstDigit == 4) && (digitCount == 13 || digitCount == 16)) == 1)
        return true;
    return false;
}
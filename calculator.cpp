// calculator.cpp
#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <windows.h>

#define MAX_SIZE 1000

extern "C" __declspec(dllexport) char* calculate(const char* expression);

void printProgressBar(float percentage) {
    int barWidth = 50;
    std::cout << "[";
    int pos = barWidth * percentage;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(percentage * 100.0) << "%" << "\r";
    std::cout.flush();
}

void clearProgressBar() {
    std::cout << std::string(60, ' ') << "\r"; // Clear the line where the progress bar was printed
    std::cout.flush();
}

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void addStrings(const char *num1, const char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = (len1 > len2) ? len1 : len2;
    int carry = 0;
    result[maxLen + 1] = '\0';

    for (int i = 0; i <= maxLen; i++) {
        int digit1 = (i < len1) ? num1[len1 - i - 1] - '0' : 0;
        int digit2 = (i < len2) ? num2[len2 - i - 1] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result[i] = (sum % 10) + '0';
    }

    if (carry != 0) {
        result[maxLen] = carry + '0';
    } else {
        result[maxLen] = '\0';
    }

    reverseString(result);
}

void subtractStrings(const char *num1, const char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int borrow = 0;
    result[len1 + 1] = '\0';

    for (int i = 0; i < len1; i++) {
        int digit1 = num1[len1 - i - 1] - '0';
        int digit2 = (i < len2) ? num2[len2 - i - 1] - '0' : 0;
        int diff = digit1 - digit2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[i] = diff + '0';
    }

    result[len1] = '\0';
    reverseString(result);

    // Remove leading zeros
    while (*result == '0' && *(result + 1) != '\0') {
        memmove(result, result + 1, strlen(result));
    }
}

void multiplyStrings(const char *num1, const char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int product[MAX_SIZE] = {0};

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + product[i + j + 1];
            product[i + j + 1] = sum % 10;
            product[i + j] += sum / 10;
        }
    }

    int index = 0;
    while (index < len1 + len2 - 1 && product[index] == 0) {
        index++;
    }

    int k = 0;
    while (index < len1 + len2) {
        result[k++] = product[index++] + '0';
    }
    result[k] = '\0';
}

void divideStrings(const char *num1, const char *num2, char *quotient) {
    if (strcmp(num2, "0") == 0) {
        strcpy_s(quotient, sizeof(quotient), "error");
        return;
    }

    char remainder[MAX_SIZE] = "";
    strcpy_s(remainder, sizeof(remainder), num1);

    quotient[0] = '\0';
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    for (int i = 0; i < len1; i++) {
        strncat_s(remainder, sizeof(remainder), &num1[i], 1);
        int divisor = atoi(num2);
        int dividend = atoi(remainder);
        int q = dividend / divisor;
        char qChar = q + '0';
        strncat_s(quotient, sizeof(quotient), &qChar, 1);
        sprintf_s(remainder, sizeof(remainder), "%d", dividend % divisor);
    }

    // Remove leading zeros
    while (*quotient == '0' && *(quotient + 1) != '\0') {
        memmove(quotient, quotient + 1, strlen(quotient));
    }
}

void moduloStrings(const char *num1, const char *num2, char *result) {
    if (strcmp(num2, "0") == 0) {
        strcpy_s(result, sizeof(result), "error");
        return;
    }

    char remainder[MAX_SIZE] = "";
    strcpy_s(remainder, sizeof(remainder), num1);

    int len1 = strlen(num1);
    int len2 = strlen(num2);

    for (int i = 0; i < len1; i++) {
        strncat_s(remainder, sizeof(remainder), &num1[i], 1);
        int divisor = atoi(num2);
        int dividend = atoi(remainder);
        sprintf_s(remainder, sizeof(remainder), "%d", dividend % divisor);
    }

    strcpy_s(result, sizeof(result), remainder);
}

void bitwiseAndStrings(const char *num1, const char *num2, char *result) {
    unsigned long long int val1 = strtoull(num1, nullptr, 10);
    unsigned long long int val2 = strtoull(num2, nullptr, 10);
    unsigned long long int res = val1 & val2;
    sprintf_s(result, sizeof(result), "%llu", res);
}

void bitwiseOrStrings(const char *num1, const char *num2, char *result) {
    unsigned long long int val1 = strtoull(num1, nullptr, 10);
    unsigned long long int val2 = strtoull(num2, nullptr, 10);
    unsigned long long int res = val1 | val2;
    sprintf_s(result, sizeof(result), "%llu", res);
}

void bitwiseXorStrings(const char *num1, const char *num2, char *result) {
    unsigned long long int val1 = strtoull(num1, nullptr, 10);
    unsigned long long int val2 = strtoull(num2, nullptr, 10);
    unsigned long long int res = val1 ^ val2;
    sprintf_s(result, sizeof(result), "%llu", res);
}

void leftShiftStrings(const char *num1, const char *num2, char *result) {
    unsigned long long int val1 = strtoull(num1, nullptr, 10);
    unsigned long long int shift = strtoull(num2, nullptr, 10);
    unsigned long long int res = val1 << shift;
    sprintf_s(result, sizeof(result), "%llu", res);
}

void rightShiftStrings(const char *num1, const char *num2, char *result) {
    unsigned long long int val1 = strtoull(num1, nullptr, 10);
    unsigned long long int shift = strtoull(num2, nullptr, 10);
    unsigned long long int res = val1 >> shift;
    sprintf_s(result, sizeof(result), "%llu", res);
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '&':
        case '|':
        case '^':
            return 3;
        case '<':
        case '>':
            return 4;
        default:
            return 0;
    }
}

void applyOp(char *a, char *b, char *result, char op) {
    switch (op) {
        case '+': 
            addStrings(a, b, result);
            break;
        case '-': 
            subtractStrings(a, b, result);
            break;
        case '*': 
            multiplyStrings(a, b, result);
            break;
        case '/': 
            divideStrings(a, b, result);
            break;
        case '%': 
            moduloStrings(a, b, result);
            break;
        case '&': 
            bitwiseAndStrings(a, b, result);
            break;
        case '|': 
            bitwiseOrStrings(a, b, result);
            break;
        case '^': 
            bitwiseXorStrings(a, b, result);
            break;
        case '<': 
            leftShiftStrings(a, b, result);
            break;
        case '>': 
            rightShiftStrings(a, b, result);
            break;
    }
}

bool isValidExpression(const char* tokens) {
    bool lastWasOperator = true;

    for (size_t i = 0; i < strlen(tokens); i++) {
        if (tokens[i] == ' ')
            continue;

        if (isdigit(tokens[i])) {
            lastWasOperator = false;
        } else if (strchr("+-*/%&|^<>", tokens[i])) {
            if (lastWasOperator || i == 0 || i == strlen(tokens) - 1) {
                return false;
            }
            lastWasOperator = true;
        } else if (tokens[i] == '(') {
            if (!lastWasOperator && i != 0) {
                return false;
            }
            lastWasOperator = true;
        } else if (tokens[i] == ')') {
            if (lastWasOperator) {
                return false;
            }
            lastWasOperator = false;
        } else {
            return false;
        }
    }

    return !lastWasOperator;
}

char* evaluate(const char* tokens) {
    if (!isValidExpression(tokens)) {
        return strdup("error");
    }

    std::stack<std::string> values;
    std::stack<char> ops;

    size_t totalSteps = strlen(tokens);
    size_t currentStep = 0;

    for (currentStep = 0; currentStep <= totalSteps; currentStep++) {
        printProgressBar(static_cast<float>(currentStep) / totalSteps);
        Sleep(50); // Sleep for 50 milliseconds to simulate processing time
    }

    clearProgressBar();

    for (size_t i = 0; i < strlen(tokens); i++) {
        if (tokens[i] == ' ')
            continue;

        if (isdigit(tokens[i])) {
            std::string val;
            while (i < strlen(tokens) && isdigit(tokens[i])) {
                val += tokens[i];
                i++;
            }
            values.push(val);
            i--;
        } else if (tokens[i] == '(') {
            ops.push('(');
        } else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                std::string val2 = values.top(); values.pop();
                std::string val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();

                char result[MAX_SIZE] = "";
                applyOp(&val1[0], &val2[0], result, op);
                values.push(result);
            }
            if (!ops.empty() && ops.top() != '(')
                return strdup("error");
            else
                ops.pop();
        } else if (strchr("+-*/%&|^<>", tokens[i])) {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                std::string val2 = values.top(); values.pop();
                std::string val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();

                char result[MAX_SIZE] = "";
                applyOp(&val1[0], &val2[0], result, op);
                values.push(result);
            }

            ops.push(tokens[i]);
        } else {
            return strdup("error");
        }
    }

    while (!ops.empty()) {
        std::string val2 = values.top(); values.pop();
        std::string val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();

        char result[MAX_SIZE] = "";
        applyOp(&val1[0], &val2[0], result, op);
        values.push(result);
    }

    if (!values.empty()) {
        char* finalResult = new char[strlen(values.top().c_str()) + 1];
        strcpy(finalResult, values.top().c_str());
        return finalResult;
    }

    return strdup("error");
}

extern "C" __declspec(dllexport) char* calculate(const char* expression) {
    return evaluate(expression);
}
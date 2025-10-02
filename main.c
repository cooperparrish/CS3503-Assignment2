#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


void oct_to_bin(const char* oct, char* out);
void oct_to_hex(const char* oct, char* out);
void hex_to_bin(const char* hex, char* out);

void to_sign_magnitude(int32_t n, char* out);
void to_ones_complement(int32_t n, char* out);
void to_twos_complement(int32_t n, char* out);


int main(void)
{
    FILE* file = fopen("a2_test.txt", "r");
    if (!file)
        return 1;

    char line[256];
    int total = 0, passed = 0;
    int test_num = 1;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0 || line[0] == '#') continue;

        char func[20];
        char input[100];
        char expected[65], got[65];
        int input_int;

        memset(func, 0, sizeof(func));
        memset(input, 0, sizeof(input));
        memset(expected, 0, sizeof(expected));
        memset(got, 0, sizeof(got));

        
        if (sscanf(line, "%19s", func) != 1)
            continue;
        func[19] = '\0';  

        if (strcmp(func, "oct_to_bin") == 0)
        {
            if (sscanf(line, "%*s %99s %64s", input, expected) == 2)
            {
                input[99] = '\0';
                expected[64] = '\0';

                oct_to_bin(input, got);

                total++;
                printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                    test_num++, func, input, expected, got,
                    strcmp(got, expected) == 0 ? "PASS" : "FAIL");
                if (strcmp(got, expected) == 0) passed++;
            }
        }
        else if (strcmp(func, "oct_to_hex") == 0)
        {
            if (sscanf(line, "%*s %99s %64s", input, expected) == 2)
            {
                input[99] = '\0';
                expected[64] = '\0';

                oct_to_hex(input, got);

                total++;
                printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                    test_num++, func, input, expected, got,
                    strcmp(got, expected) == 0 ? "PASS" : "FAIL");
                if (strcmp(got, expected) == 0) passed++;
            }
        }
        else if (strcmp(func, "hex_to_bin") == 0)
        {
            if (sscanf(line, "%*s %99s %64s", input, expected) == 2)
            {
                input[99] = '\0';
                expected[64] = '\0';

                hex_to_bin(input, got);

                total++;
                printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                    test_num++, func, input, expected, got,
                    strcmp(got, expected) == 0 ? "PASS" : "FAIL");
                if (strcmp(got, expected) == 0) passed++;
            }
        }
        else if (strcmp(func, "to_sign_magnitude") == 0)
        {
            if (sscanf(line, "%*s %d %64s", &input_int, expected) == 2)
            {
                expected[64] = '\0';

                to_sign_magnitude(input_int, got);

                total++;
                printf("Test %d: %s(%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                    test_num++, func, input_int, expected, got,
                    strcmp(got, expected) == 0 ? "PASS" : "FAIL");
                if (strcmp(got, expected) == 0) passed++;
            }
        }
        else if (strcmp(func, "to_ones_complement") == 0)
        {
            if (sscanf(line, "%*s %d %64s", &input_int, expected) == 2)
            {
                expected[64] = '\0';

                to_ones_complement(input_int, got);

                total++;
                printf("Test %d: %s(%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                    test_num++, func, input_int, expected, got,
                    strcmp(got, expected) == 0 ? "PASS" : "FAIL");
                if (strcmp(got, expected) == 0) passed++;
            }
        }
        else if (strcmp(func, "to_twos_complement") == 0)
        {
            if (sscanf(line, "%*s %d %64s", &input_int, expected) == 2)
            {
                expected[64] = '\0';

                to_twos_complement(input_int, got);

                total++;
                printf("Test %d: %s(%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                    test_num++, func, input_int, expected, got,
                    strcmp(got, expected) == 0 ? "PASS" : "FAIL");
                if (strcmp(got, expected) == 0) passed++;
            }
        }
    }

    fclose(file);

    printf("\nSummary: %d/%d tests passed\n", passed, total);
    return 0;
}

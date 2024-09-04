/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** main.c
*/

#include "../include/sbml.h"

static void helper(void)
{
    FILE *fd = fopen(HELPER_PATH, "r");
    char file[HELPER_LEN];

    if (!fd)
        exit(84);
    fread(file, HELPER_LEN, 1, fd);
    printf("%s", file);
    fclose(fd);
    exit(0);
}

static char *get_buffer(const char *path)
{
    struct stat sb;
    FILE *fd;
    char *buffer;

    fd = fopen(path, "r");
    if (stat(path, &sb) == -1 || !fd)
        exit(84);
    buffer = malloc(sizeof(char) * sb.st_size);
    fread(buffer, sb.st_size, 1, fd);
    fclose(fd);
    return (buffer);
}

static void init_flags(sbml_t *sbml, int argc, char **argv)
{
    short i_counter = 0;
    short e_counter = 0;
    short json_counter = 0;

    for (int x = 2; x < argc; x++) {
        if (strcmp(argv[x], "-i") == 0) {
            i_counter++;
            sbml->flags[0] = '1';
        }
        if (strcmp(argv[x], "-e") == 0) {
            e_counter++;
            sbml->flags[1] = '1';
        }
        if (strcmp(argv[x], "-json") == 0) {
            json_counter++;
            sbml->flags[2] = '1';
        }
        if (i_counter > 1 || e_counter > 1 || json_counter > 1)
            exit(84);
    }
}

static sbml_t *init_sbml(int ac, char **av)
{
    sbml_t *sbml = malloc(sizeof(sbml_t));

    sbml->buffer = get_buffer(av[1]);
    sbml->buffer_array = my_str_to_word_array_sep(sbml->buffer, '\n');
    if (sbml->buffer_array == NULL)
        exit(84);
    strcpy(sbml->flags, "000\0");
    init_flags(sbml, ac, av);
    return (sbml);
}

void printer(extract_t *res, char *search)
{
    if (res->print_type == COMPARTMENT_PRINT)
        compartment_print(res, search);
    if (res->print_type == SPECIES_PRINT)
        species_print(res, search);
    if (res->print_type == REACTION_PRINT)
        reaction_print(res, search);
    if (res->print_type == CHEMICALS_PRINT)
        chemical_print(res);
}

static void launch_flag(sbml_t *sbml, char *search)
{
    extract_t extract = {NULL, NULL, NONE, NO_PRINT};

    extract = *extract_data(search, sbml->tags, &extract);
    if (strcmp(sbml->flags, "100\0") == 0)
        printer(&extract, search);
    if (strcmp(sbml->flags, "101\0") == 0) {
        json_print(&extract);
    }
    if (strcmp(sbml->flags, "000\0") == 0) {
        simple_parser(sbml->tags);
        print_simple_parser(sbml->tags);
    }
}

int main(int argc, char **argv)
{
    sbml_t *sbml = NULL;

    if (argc == 1 || argc > 6)
        return (84);
    if (argc == 2 && strcmp(argv[1], "-h") == 0)
        helper();
    sbml = init_sbml(argc, argv);
    parser(sbml);
    launch_flag(sbml, argv[argc - 1]);
    return (0);
}

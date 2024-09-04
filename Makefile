##
## EPITECH PROJECT, 2024
## my_rpg
## File description:
## Makefile
##

TARGET			=	SBMLparser
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -g
BUILD_DIR 		=	build
OBJS			=	${addprefix ${BUILD_DIR}/, ${SRCS:.c=.o}}

SRCS			=	src/main.c									\
					src/simple_parser.c							\
					src/data_extraction/extract_chemicals.c		\
					src/data_extraction/extract_compartment.c	\
					src/data_extraction/extract_reaction.c		\
					src/data_extraction/extract_species.c		\
					src/data_extraction/extract_struct.c		\
					src/data_extraction/extraction.c			\
					src/parser/alpha_sort.c						\
					src/parser/clean_str.c						\
					src/parser/formater.c						\
					src/parser/dependencies.c					\
					src/parser/my_str_to_word_array_sep.c		\
					src/parser/parser.c							\
					src/parser/struct.c							\
					src/parser/tags.c							\
					src/print/alpha_extract.c					\
					src/print/eq_print.c						\
					src/print/extract_print.c					\
					src/print/json_print.c						\
					requirement.c								\


all:	${BUILD_DIR} ${TARGET}

${BUILD_DIR}:
	mkdir -p $@

${BUILD_DIR}/%.o: %.c
	mkdir -p ${dir $@}
	${CC} -c $< -o $@ ${LDFLAGS} ${CPPFLAGS}

${TARGET}:	${OBJS}
	${CC} ${CFLAGS} -o ${TARGET} ${OBJS}

re:	fclean all

clean:
	rm -rf ${BUILD_DIR}

fclean:	clean
	rm -f ${TARGET}

.PHONY: all re clean fclean

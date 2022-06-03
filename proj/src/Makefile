# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = proj.c graphics.c objects.c menu.c game.c snake.c timer.c keyboard.c utils.c mouse.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
# CFLAGS += -pedantic -D__LCOM_OPTIMIZED__
CFLAGS += -pedantic
# list of library dependencies (for Lab 5, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>

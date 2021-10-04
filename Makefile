IMPL_CFLAGS = 	-std=c99 -D_XOPEN_SOURCE=600 \
	        	-D_DEFAULT_SOURCE \
				-pedantic \
				-Wall \
				-W \
				-Wmissing-prototypes \
				-Wno-sign-compare \
				-Wimplicit-fallthrough \
				-Wno-unused-parameter

ifeq ($(CC),clang)
	IMPL_CFLAGS += 	-Wno-uninitialized \
				   	-Wno-infinite-recursion \
		       		-Wno-format-pedantic
endif

CFLAGS = ${IMPL_CFLAGS}
RM = rm -f
EXE = danglink

all : ${EXE}

clean :
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

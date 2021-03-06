###################################################################
#
# freeman.justin@gmail.com 
#
##################################################################

CC=	gcc

CSRC=	./src/

CFLAGS=	-O3

INC=	-I./include \
	-I./include/colormaps

LFLAGS=	-lnetcdf -lm

COBJ=	$(CSRC)main.o \
	$(CSRC)netcdfIO.o \
	$(CSRC)fail.o \
	$(CSRC)jutil.o \
	$(CSRC)colormap.o \
	$(CSRC)geo2pixel.o \
	$(CSRC)search.o \
	$(CSRC)drawmap.o

OBJ=	$(COBJ) 

EXEC=	./bin/nc2image

$(EXEC):$(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LFLAGS)

$(COBJ) : %.o : %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm $(COBJ)
	rm $(EXEC)

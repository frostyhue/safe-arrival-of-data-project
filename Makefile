EPN=encoder_run
CPN=channel
DPN=decoder


SHARED=	product/encoder.c product/converters.c
	                         
TEST=$(SHARED) \
             ../Unity/unity.c 

all: 
	gcc product/$(EPN).c $(SHARED) -lm -o encoder && gcc $(CFLAGS) product/$(CPN).c $(SHARED) -lm -o $(CPN) && gcc $(CFLAGS) product/$(DPN).c $(SHARED) -lm -o $(DPN) 
   
clean:
	rm -rf $(EPN)Test $(EPN) 
	rm -rf $(CPN)Test $(CPN) 
	rm -rf $(DPN)Test $(DPN) 

valgrind: 
	valgrind ./$(EPN)
	valgrind ./$(CPN)
	valgrind ./$(DPN)

.PHONY: clean test valgrind
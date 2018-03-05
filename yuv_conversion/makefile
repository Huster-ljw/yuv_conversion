OBJECT=main.o yuv_type_conversion.o

yuv_conversion:$(OBJECT)
	g++ -o yuv_conversion $(OBJECT)

main.o:main.cpp
	g++ -c main.cpp
yuv_type_conversion.o:yuv_type_conversion.cpp
	g++ -c  yuv_type_conversion.cpp

.PYONY:clean
clean:
	rm -rf *.o
	rm -rf *_*.yuv

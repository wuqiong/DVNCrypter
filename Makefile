default:
	g++ -g -w  -o DVNCrypter DVNCrypter.cpp  DVNCrypto.cpp -I$(HOME)/local/include -L$(HOME)/local/lib -lssl -lcrypto


clean:
	rm -rf *.o *.dSYM 

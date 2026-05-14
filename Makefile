main:CAPI_test.cpp
	g++ -o $@ $^ -lmysqlclient
.PHONY:clean
clean:
	rm -rf main
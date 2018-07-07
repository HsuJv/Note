CC = gcc

CFLAGS = -O2 -Wall -I$(HADOOP_HOME)/include
LDLIBS = -lpthread -lm -L$(HADOOP_HOME)/lib/native -lhdfs


demo: app.o upload.o download.o fs.o
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

app.o: app.c upload.h download.h
	$(CC) -c $(CFLAGS) $< $(LDLIBS)

upload.o: upload.c upload.h
	$(CC) -c $(CFLAGS) $< $(LDLIBS)

download.o: download.c download.h
	$(CC) -c $(CFLAGS) $< $(LDLIBS)

fs.o: fs.c fs.h
	$(CC) -c $(CFLAGS) $< $(LDLIBS)

clean:
	rm -f demo *.o *~


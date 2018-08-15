
SERVICE = echo_service
CLIENT = echo_client

SERVICE_SOURCES = echo_service.o

CLIENT_SOURCES = echo_client.o

CFLAGS = -std=c99

LDFLAGS = 

%.o: %.c
	gcc -c $< -o $@ $(CFLAGS)

all: $(SERVICE) $(CLIENT)

$(SERVICE): $(SERVICE_SOURCES)
	gcc $< -o $@ $(LDFLAGS)

$(CLIENT): $(CLIENT_SOURCES)
	gcc $< -o $@ $(LDFLAGS)

clean: 
	rm $(SERVICE) $(CLIENT) *.o


.PHONY: clean
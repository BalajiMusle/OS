
TARGET=asm_write

CC=gcc
AS=as

ASFLAGS=-ggdb3
LDFLAGS=

$(TARGET): $(TARGET).o
	$(CC) $(LDFLAGS) -o $@ $<

$(TARGET).o: $(TARGET).s
	$(AS) $(ASFLAGS) -o $@ $< 

clean:
	rm -f $(TARGET).o $(TARGET)


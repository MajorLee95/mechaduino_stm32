// *** STM32F401 PORT ***
// Stub minimal pour FlashStorage (RAM only). À remplacer par vraie EEPROM si besoin.

#ifndef FlashStorage_stub_h
#define FlashStorage_stub_h

template<typename T>
class FlashStorageClass {
public:
    FlashStorageClass(const char *name) { (void)name; }
    void write(const T &value) { stored = value; }
    void read(T &value) { value = stored; }
private:
    T stored;
};

#define FlashStorage(name, type) FlashStorageClass<type> name(#name)

class FlashClass {
public:
    void erase(const void* addr, size_t size) {}
    void write(const void* addr, const void* data, size_t size) {}
};

extern FlashClass flash;

#endif

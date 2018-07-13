#pragma once

#include "Debug.hpp"
#include <stdint.h>

class BitArray {
  public:
    BitArray(uint8_t size) : bufferLength((size + 7) / 8) {
        buffer = new uint8_t[bufferLength]();
    }

    ~BitArray() { delete[] buffer; }

    bool get(uint8_t bitIndex) {
        return buffer[getBufferIndex(bitIndex)] & getBufferMask(bitIndex);
    }

    void set(uint8_t bitIndex) {
        buffer[getBufferIndex(bitIndex)] |= getBufferMask(bitIndex);
    }

    void clear(uint8_t bitIndex) {
        buffer[getBufferIndex(bitIndex)] &= ~getBufferMask(bitIndex);
    }

    void set(uint8_t bitIndex, bool state) {
        if (state)
            set(bitIndex);
        else
            clear(bitIndex);
    }

    uint8_t safeIndex(uint8_t byteIndex) const {
        if (byteIndex >= getBufferLength()) {
            DEBUGFN(F("Error: index out of bounds (")
                    << (unsigned int)byteIndex << F(", length is ")
                    << (unsigned int)getBufferLength() << ')');
            ERROR(return getBufferLength() - 1);
        }
        return byteIndex;
    }

    inline uint8_t getByte(uint8_t byteIndex) const {
        return buffer[byteIndex];
        // return buffer[safeIndex(byteIndex)];
    }

    uint8_t getBufferLength() const { return bufferLength; }

  private:
    inline uint8_t getBufferIndex(uint8_t bitIndex) const {
        return safeIndex(bitIndex >> 3); // bitIndex / 8
    }
    inline uint8_t getBufferBit(uint8_t bitIndex) const {
        return bitIndex & 0b111; // bitIndex % 8
    }
    inline uint8_t getBufferMask(uint8_t bitIndex) const {
        return 1 << getBufferBit(bitIndex);
    }

    const uint8_t bufferLength;
    uint8_t *buffer;
};
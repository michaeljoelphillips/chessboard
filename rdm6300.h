#include "rfid_reader.h"
#include <Stream.h>

class RDM6300: public RFIDReader {
  public:
    RDM6300(Stream *stream);
    unsigned long read();

  private:
    /*
     * RFID Data Frame:
     *   1 byte head (value: 2)
     *   2 byte version
     *   8 byte data
     *   2 byte checksum
     *   1 byte tail (value: 3)
     */
    static const int BUFFER_SIZE = 14;

    /*
     * The buffer storing data from the RFID serial connection.
     */
    int buffer[BUFFER_SIZE];

    /*
     * The current index of RFID buffer
     */
    int buffer_index = 0;

    Stream *stream;

    unsigned long decode_tag();
    bool verify_checksum();
};

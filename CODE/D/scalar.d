module base.scalar;

// -- TYPES

union SCALAR
{
    bool
        Boolean;
    char
        Character;
    ubyte
        Natural8;
    ushort
        Natural16;
    uint
        Natural32;
    ulong
        Natural64;
    byte
        Integer8;
    short
        Integer16;
    int
        Integer32;
    long
        Integer64;
    float
        Real32;
    double
        Real64;
    ubyte[ 1 ]
        OneByteArray;
    ubyte[ 2 ]
        TwoByteArray;
    ubyte[ 4 ]
        FourByteArray;
    ubyte[ 8 ]
        EightByteArray;
}

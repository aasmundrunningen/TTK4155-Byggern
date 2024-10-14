
#pragma once

#include <stdint.h>

// Struct with bit timing information
// See `can_init` for usage example
typedef struct CanInit CanInit;
__attribute__((packed)) struct CanInit {
    union {
        struct {
            uint32_t phase2:4;  // Phase 2 segment (PHASE SEG2) (phase2 + 1)
            uint32_t propag:4;  // Propagation time segment (PROP SEG) (propag + 1)
            uint32_t phase1:4;  // Phase 1 segment (PHASE SEG1) (phase1 + 1)
            uint32_t sjw:4;     // Synchronization jump width (to what extent we can shorten or lengthen phase segments)
            uint32_t brp:8;     // Baud rate prescaler Allowed: [1, 0x7F]
            uint32_t smp:8;     // Sampling mode (0: sample once, 1: sample three times and average)
        };
        uint32_t reg;
    };
};
CanInit initRegister;

initRegister.phase2 = 1;
initRegister.propag = 0;
initRegister.phase1 = 1;
initRegister.sjw = 1; // ??
initRegister.brp = 68;
initRegister.smp = 1;


/*
NODE 1--------------------------------------------------------------
        BRP (baud rate prescaler) = 0
        => TQ = 2/f_osc = 2/2.45MHz = 820nS
        =>T_can = Bit_time * TQ = 6*82uS = 4.9uS
        =>f_can = 1/T_can = 200kHz
        Bit time = 6TQ
            syncseg = 1TQ
            propseg = 1TQ
            PS1 = 2TQ
            PS2 = 2TQ
----------------------------------------------------------------------

NODE 2 ---------------------------------------------------------------

t_bit = t_csc + t_prs + t_phs1 + t_phs2
t_csc = (BRP +1)/MCK 
    -> BRP = t_csc*MCK -1 = 820*10^-9 * 84*10^6 -1 = 67.88


----------------------------------------------------------------------
*/


// Initialize CAN bus, with bit timings and optional interrupt
// If `rxInterrupt` is not 0, an interrupt will be triggered when a message is received.
// (See can.c for an example interrupt handler)
// Example:
//    can_init((CanInit){.brp = F_CPU/2000000-1, .phase1 = 5, .phase2 = 1, .propag = 6}, 0);
void can_init(CanInit init, uint8_t rxInterrupt);


// Strict-aliasing-safe reinterpret-cast
#define union_cast(type, x) \
    (((union { \
        typeof(x) a; \
        type b; \
    })x).b)


// Dummy type for use with `union_cast`, see below
typedef struct Byte8 Byte8;
struct Byte8 {
    uint8_t bytes[8];
};


// CAN message data type
// Data fields have 3 access methods (via union):
//  8 bytes
//  2 double words (32-bit ints)
//  1 Byte8 dummy struct
// The dummy struct allows for convenient construction of a CAN message from another type
//
// Example:
//    typedef struct {
//        uint16_t  a;
//        uint8_t   b;
//        float     c;
//    } __attribute__((packed)) YourStruct ;
//    
//    CanMsg m = (CanMsg){
//        .id = 1,
//        .length = sizeof(YourStruct),
//        .byte8 = union_cast(Byte8, ((YourStruct){
//            .a = 10,
//            .b = 20,
//            .c = -30.0,
//        })),
//    };
//    can_printmsg(m);
//    // Should print: CanMsg(id:1, length:7, data:{10, 0, 20, 0, 0, 240, 193})
typedef struct CanMsg CanMsg;
struct CanMsg {
    uint8_t id;
    uint8_t length;
    union {
        uint8_t     byte[8];
        uint32_t    dword[2];
        Byte8       byte8;
    };    
};

// Send a CAN message on the bus. 
// Blocks if the bus does not receive the message (typically because one of the 
// receiving nodes has not cleared a buffer)
void can_tx(CanMsg m);

// Receive a CAN message.
// Does not block. Returns 0 if there is no message, 1 otherwise
uint8_t can_rx(CanMsg* m);

// Print a CAN message (using `printf`)
void can_printmsg(CanMsg m);






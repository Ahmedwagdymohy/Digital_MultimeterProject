/*
 * bit_ops.h
 *
 * Created: 2/24/2024 4:23:53 AM
 *  Author: asus
 */ 


#ifndef BIT_OPS_H_
#define BIT_OPS_H_

#define bitset(byte,nbit)   ((byte) |=  (1<<(nbit)))
#define bitclear(byte,nbit) ((byte) &= ~(1<<(nbit)))
#define bitflip(byte,nbit)  ((byte) ^=  (1<<(nbit)))
#define bitcheck(byte,nbit) ((byte & (1<<nbit))>>nbit)



#endif /* BIT_OPS_H_ */
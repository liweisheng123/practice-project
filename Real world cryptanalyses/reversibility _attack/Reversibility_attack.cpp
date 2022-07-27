#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "meow_hash_x64_aesni.h"
using namespace std;
const char* Msg = "Weisheng Li 202000460106";
const char* Hashed_Msg = "sdu_cst_20220610";

#define movdqu(A, B)	    A = _mm_loadu_si128((__m128i *)(B))
#define movq(A, B)          A = _mm_set_epi64x(0, B);
#define aesenc(A, B)	    A = _mm_aesenc_si128(A, B)
#define pshufb(A, B)        A = _mm_shuffle_epi8(A, B)
#define pxor(A, B)	        A = _mm_xor_si128(A, B)
#define psubq(A, B)	        A = _mm_sub_epi64(A, B)
#define pand(A, B)          A = _mm_and_si128(A, B)
#define palignr(A, B, i)    A = _mm_alignr_epi8(A, B, i)
#define pxor_clear(A, B)	A = _mm_setzero_si128(); 
// NOTE(casey): pxor_clear is a nonsense thing that is only here because compilers don't detect xor(a, a) is clearing a :(

#define INSTRUCTION_REORDER_BARRIER _ReadWriteBarrier()
#define MEOW_MIX_REG(r1, r2, r3, r4, r5,  i1, i2, i3, i4) \
pxor(r4, i4);                \
psubq(r5, i3);               \
aesenc(r2, r4);              \
INSTRUCTION_REORDER_BARRIER; \
pxor(r2, i2);                \
psubq(r3, i1);               \
aesenc(r1, r2);              \
INSTRUCTION_REORDER_BARRIER;
//The original operation is as follows :
//#define MEOW_MIX_REG(r1, r2, r3, r4, r5,  i1, i2, i3, i4) \
//aesdec(r1, r2); \
//INSTRUCTION_REORDER_BARRIER; \
//paddq(r3, i1); \
//pxor(r2, i2); \
//aesdec(r2, r4); \
//INSTRUCTION_REORDER_BARRIER; \
//paddq(r5, i3); \
//pxor(r4, i4);

#define MEOW_INV_SHUFFLE(r0, r1, r2, r4, r5, r6) \
pxor(r1, r2);     \
aesenc(r4, r1);   \
psubq(r5, r6);    \
pxor(r4, r6);     \
psubq(r1, r5);    \
aesenc(r0, r4);
//The original operation is as follows:
//#define MEOW_SHUFFLE(r1, r2, r3, r4, r5, r6) \
//aesdec(r1, r4); \
//paddq(r2, r5); \
//pxor(r4, r6); \
//aesdec(r4, r2); \
//paddq(r5, r6); \
//pxor(r2, r3)
static void PrintKey(meow_u128 Hash1, meow_u128 Hash2) 
{
	printf("\t%08X%08X%08X%08X%08X%08X%08X%08X\n",
		MeowU32From(Hash1, 3),
		MeowU32From(Hash1, 2),
		MeowU32From(Hash1, 1),
		MeowU32From(Hash1, 0),
		MeowU32From(Hash2, 3),
		MeowU32From(Hash2, 2),
		MeowU32From(Hash2, 1),
		MeowU32From(Hash2, 0));
}

static void ReverseOperationForKey(meow_umm Len, void* Hashed_Msg, void* Msg) 
{
	/*This part of the principle is not fully learned,
	most of the process directly copied from "meow_hash_x64_aesni"*/
	meow_u128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
	// NOTE(casey): xmm0-xmm7 are the hash accumulation lanes
	meow_u128 xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15;
	// NOTE(casey): xmm8-xmm15 hold values to be appended (residual, length)

	//
	// NOTE(casey): Seed the eight hash registers
	//
	meow_u8* rcx = (meow_u8*)Hashed_Msg;
	movdqu(xmm0, rcx + 0x00); 
	movdqu(xmm1, rcx + 0x10); 
	movdqu(xmm2, rcx + 0x20); 
	movdqu(xmm3, rcx + 0x30); 
	movdqu(xmm4, rcx + 0x40); 
	movdqu(xmm5, rcx + 0x50); 
	movdqu(xmm6, rcx + 0x60); 
	movdqu(xmm7, rcx + 0x70); 

	psubq(xmm0, xmm4);
	pxor(xmm0, xmm1);
	pxor(xmm4, xmm5);
	psubq(xmm0, xmm2);
	psubq(xmm1, xmm3);
	psubq(xmm4, xmm6);
	psubq(xmm5, xmm7);

	MEOW_INV_SHUFFLE(xmm3, xmm4, xmm5, xmm7, xmm0, xmm1);
	MEOW_INV_SHUFFLE(xmm2, xmm3, xmm4, xmm6, xmm7, xmm0);
	MEOW_INV_SHUFFLE(xmm1, xmm2, xmm3, xmm5, xmm6, xmm7);
	MEOW_INV_SHUFFLE(xmm0, xmm1, xmm2, xmm4, xmm5, xmm6);
	MEOW_INV_SHUFFLE(xmm7, xmm0, xmm1, xmm3, xmm4, xmm5);
	MEOW_INV_SHUFFLE(xmm6, xmm7, xmm0, xmm2, xmm3, xmm4);
	MEOW_INV_SHUFFLE(xmm5, xmm6, xmm7, xmm1, xmm2, xmm3);
	MEOW_INV_SHUFFLE(xmm4, xmm5, xmm6, xmm0, xmm1, xmm2);
	MEOW_INV_SHUFFLE(xmm3, xmm4, xmm5, xmm7, xmm0, xmm1);
	MEOW_INV_SHUFFLE(xmm2, xmm3, xmm4, xmm6, xmm7, xmm0);
	MEOW_INV_SHUFFLE(xmm1, xmm2, xmm3, xmm5, xmm6, xmm7);
	MEOW_INV_SHUFFLE(xmm0, xmm1, xmm2, xmm4, xmm5, xmm6);

	//
	// NOTE(casey): Load any less-than-32-byte residual
	//

	pxor_clear(xmm9, xmm9);
	pxor_clear(xmm11, xmm11);

	// TODO(casey): I need to put more thought into how the end-of-buffer stuff is actually working out here,
	// because I _think_ it may be possible to remove the first branch (on Len8) and let the mask zero out the
	// result, but it would take a little thought to make sure it couldn't read off the end of the buffer due
	// to the & 0xf on the align computation.

	// NOTE(casey): First, we have to load the part that is _not_ 16-byte aligned
	meow_u8* Last = (meow_u8*)Msg + (Len & ~0xf);
	int unsigned Len8 = (Len & 0xf);
	if (Len8) 
	{
		// NOTE(casey): Load the mask early
		movdqu(xmm8, &MeowMaskLen[0x10 - Len8]);

		meow_u8* LastOk = (meow_u8*)((((meow_umm)(((meow_u8*)Msg) + Len - 1)) | (MEOW_PAGESIZE - 1)) - 16);
		int Align = (Last > LastOk) ? ((int)(meow_umm)Last) & 0xf : 0;
		movdqu(xmm10, &MeowShiftAdjust[Align]);
		movdqu(xmm9, Last - Align);
		pshufb(xmm9, xmm10);

		// NOTE(jeffr): and off the extra bytes
		pand(xmm9, xmm8);
	}

	// NOTE(casey): Next, we have to load the part that _is_ 16-byte aligned
	if (Len & 0x10) 
	{
		xmm11 = xmm9;
		movdqu(xmm9, Last - 0x10);
	}

	//
	// NOTE(casey): Construct the residual and length injests
	//

	xmm8 = xmm9;
	xmm10 = xmm9;
	palignr(xmm8, xmm11, 15);
	palignr(xmm10, xmm11, 1);

	// NOTE(casey): We have room for a 128-bit nonce and a 64-bit none here, but
	// the decision was made to leave them zero'd so as not to confuse people
	// about hwo to use them or what security implications they had.
	pxor_clear(xmm12, xmm12);
	pxor_clear(xmm13, xmm13);
	pxor_clear(xmm14, xmm14);
	movq(xmm15, Len);
	palignr(xmm12, xmm15, 15);
	palignr(xmm14, xmm15, 1);


	// Append the length, to avoid problems with our 32-byte padding
	MEOW_MIX_REG(xmm1, xmm5, xmm7, xmm2, xmm3, xmm12, xmm13, xmm14, xmm15);

	// To maintain the mix-down pattern, we always Meow Mix the less-than-32-byte residual, even if it was empty
	MEOW_MIX_REG(xmm0, xmm4, xmm6, xmm1, xmm2, xmm8, xmm9, xmm10, xmm11);

	PrintKey(xmm0, xmm1);
	PrintKey(xmm2, xmm3);
	PrintKey(xmm4, xmm5);
	PrintKey(xmm6, xmm7);
	return;
}

int main() {

	int MsgLen = strlen(Msg); 
	char* message = new char[MsgLen + 1];
	int Hashed_MsgLen = strlen(Hashed_Msg);
	char* Hashed_message = new char[Hashed_MsgLen + 1];

	memset(message, 0, MsgLen + 1);
	memcpy(message, Msg, MsgLen);
	memset(Hashed_message, 0, Hashed_MsgLen + 1);
	memcpy(Hashed_message, Hashed_Msg, Hashed_MsgLen);
	
	/*Msg = "Weisheng Li 202000460106";
	Hashed_Msg = "sdu_cst_20220610";*/
	cout << "Msg: " << message << "   Hashed Msg: " << Hashed_message << endl;

	cout << "Key:" << endl;
	//Each fill content is different, resulting in different results
	ReverseOperationForKey(MsgLen, Hashed_message, message); 
	cout << endl;

	return 0;
}
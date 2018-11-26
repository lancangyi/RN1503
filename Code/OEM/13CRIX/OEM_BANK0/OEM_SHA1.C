#include "CORE_INCLUDE.H"
#include "OEM_INCLUDE.H"

#if SHA1_Support

//===================================================================
// Step 1. generate new challenge
//===================================================================
void Initialize_H(void)
{
	// 2. initial a~e = H0~4
	SHA1_a = H0 = 0x67452301;
   	SHA1_b = H1 = 0xEFCDAB89;
   	SHA1_c = H2 = 0x98BADCFE;
 	SHA1_d = H3 = 0x10325476;
   	SHA1_e = H4 = 0xC3D2E1F0;
}

void SetNewChallenge(void)
{
	// 1. create W
	Clear_RAM_Range(0x0200,0x3F);
	// --- TI default
	SHA1_W[0] = 0x01234567;
	SHA1_W[1] = 0x89abcdef;
	SHA1_W[2] = 0xfedcba98;
	SHA1_W[3] = 0x76543210;
	// --- PEGA key
/*	SHA1_W[0] = 0x65716980;
	SHA1_W[1] = 0x78798284;
	SHA1_W[2] = 0x84656645;
	SHA1_W[3] = 0x32323284;*/

	SHA1_W[4] = 0x20212223;
	SHA1_W[5] = 0x24252627;
	SHA1_W[6] = 0x28292A2B;
	SHA1_W[7] = 0x2C2D2E2F;
	SHA1_W[8] = 0x30313233;

	SHA1_W[9] = 0x80000000;
	SHA1_W[15] = 0x00000120;
}

//===================================================================
// Step 2. send new challenge to battery
//===================================================================
// inverse a string high/low, for Little/Big Endian
void inverse(XBYTE *head, XBYTE *tail)
{
	while( (head!=tail) && (head<tail) ) {
		ITempB01 = *head;
		*head = *tail;
		*tail = ITempB01;
		head++;
		tail--;
	}
}

BYTE SendChallengeToBat(void)
{
	BYTE SMBus_work;
	inverse(&Challenge_L, &Challenge_H);
	SMBus_work = bWSMBusBlock(SMbusChA, SMbusWBK, BatteryAddress, SHA1_CMD, &SHA1_W[4], 20, TRUE);
	inverse(&Challenge_L, &Challenge_H);
	if( SMBus_work ) return TRUE;
	return FALSE;
}

//===================================================================
// Step 3. Cale. key value
//===================================================================
void CalECRespones(void)
{
	LWORD WS_temp;
	LWORD SHA1_t, SHA1_k;

	SHA1_t = SHA1_k = 0x00;
	// 3. for cale.
	for(ITempB03=0;ITempB03<2;ITempB03++) {
		if( ITempB03 == 0x01 ) {
			// second time initialize
			SetNewChallenge();
			// move first time result to challenge
			SHA1_W[4]=H0;
			SHA1_W[5]=H1;
			SHA1_W[6]=H2;
			SHA1_W[7]=H3;
			SHA1_W[8]=H4;
			Initialize_H();
		}
		for(ITempB01=0;ITempB01<=79;ITempB01++) {
			ITempB02 = ITempB01 & SHA1_MASK;
			if( ITempB01 >= 16 ) {
				WS_temp = SHA1_W[(ITempB02+13)&SHA1_MASK] ^ SHA1_W[(ITempB02+8)&SHA1_MASK] ^ SHA1_W[(ITempB02+2)&SHA1_MASK] ^ SHA1_W[ITempB02];
				SHA1_W[ITempB02] = (WS_temp<<1) | (WS_temp>>31);
			}
			SHA1_t = (SHA1_a<<5) | (SHA1_a>>27);
			if( (ITempB01>=0) && (ITempB01<=19) ) {
				SHA1_k = 0x5A827999;
				WS_temp = (SHA1_b&SHA1_c) ^ ((~SHA1_b)&SHA1_d);
			}else if( (ITempB01>=20) && (ITempB01<=39) ) {
				SHA1_k = 0x6ED9EBA1;
				WS_temp = SHA1_b ^ SHA1_c ^ SHA1_d;
			}else if( (ITempB01>=40) && (ITempB01<=59) ) {
				SHA1_k = 0x8F1BBCDC;
				WS_temp = (SHA1_b&SHA1_c) ^ (SHA1_b&SHA1_d) ^ (SHA1_c&SHA1_d);
			}else if( (ITempB01>=60) && (ITempB01<=79) ) {
				SHA1_k = 0xCA62C1D6;
				WS_temp = SHA1_b ^ SHA1_c ^ SHA1_d;
			}
			SHA1_t = SHA1_t + WS_temp + SHA1_e + SHA1_k + SHA1_W[ITempB02];
			SHA1_e = SHA1_d;
			SHA1_d = SHA1_c;
			SHA1_c = (SHA1_b>>2) | (SHA1_b<<30);
			SHA1_b = SHA1_a;
			SHA1_a = SHA1_t;
		}

		// 4. coompute H
		H0 += SHA1_a;
		H1 += SHA1_b;
		H2 += SHA1_c;
		H3 += SHA1_d;
		H4 += SHA1_e;
	}
}

//===================================================================
// Step 5. read back key from battery
//===================================================================
BYTE GetChallengeFromBat(void)
{
	if( bRSMBusBlock(SMbusChA, SMbusRBK, BatteryAddress, SHA1_CMD, &BAT_Response, 20, TRUE) ) return TRUE;
	return FALSE;
}

//===================================================================
// Step 6. compare EC and BAT key
//===================================================================
BYTE Compare_data(XBYTE *buf1, XBYTE *buf2, BYTE count)
{
	do {
		if( *buf1 != *buf2 ) return FALSE;
		buf1++;
		buf2++;
		count--;
	}while(count);
	return TRUE;
}

void Compare_Auth_Result(void)
{
	// inverse result for compare
	inverse(&Hvalue_L, &Hvalue_H);
	if(	Compare_data(&Hvalue_L, &BAT_Response, 20) )
		SET_MASK(Bat1_Type,BIT(7));
	else
		CLEAR_MASK(Bat1_Type,BIT(7));
}

//===================================================================
// Service Authentication when 500ms timer
//===================================================================
void OEM_BAT_Authentication(void)
{
	if( IS_MASK_CLEAR(EC_PWRSRC,BIT(1)) ) return;

	switch(Service_Auth_Step)
	{
		case 1 :	// generate challeng
			SetNewChallenge();
			Initialize_H();
			Service_Auth_Step=2;
			break;
		case 2 :	// send challeng
			if( !SendChallengeToBat() ) return;;
			Service_Auth_Step=3;
			break;
		case 3 :	// calc. key
			CalECRespones();
			Service_Auth_Step=5;
			break;
		case 4 :	// wait 1 slot
			Service_Auth_Step=5;
			break;
		case 5 :	// read challeng
			if( !GetChallengeFromBat() ) return;
			Service_Auth_Step=6;
			break;
		case 6 :	// compare key
			Compare_Auth_Result();
			Service_Auth_Step=7;
			// --- finish ---
		default :
			break;
		case 0 :	// wait for service
			if( IS_MASK_SET(BATAUTNCTRL,BIT(7)) ) Service_Auth_Step=1;
	}
}

#endif
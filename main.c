#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include <openssl/sha.h>

#include <ec_field.h>
#include <ec_curve.h>
#include <ec_crypt.h>
#include <ec_param.h>
#include <ec_vlong.h>

void hash_to_vlong( uint32_t * mac, vlPoint V )
{
  uint32_t x;
  uint8_t i;

  V[0] = (SHA_DIGEST_LENGTH ) / sizeof(V[0]);
  for (i=0;i<(SHA_DIGEST_LENGTH / sizeof(mac[0]));i+=1)
  {
    x = mac[i];
    V[i*2+1] = (uint16_t) x;
    V[i*2+2] = (uint16_t) (x>>16);
  }
}


vlPoint private_key = { 1, 0x1337};
vlPoint k = {3 , 0x0123, 0x4567, 0x89};

int main(void) {
    uint8_t i;
    ecPoint ecPub;
    vlPoint vlPub;
    vlPoint vlMac;
    cpPair sig0;

    gfInit();

    char message0[] = "Hello, world!";
    char message1[] = "Hello, world!";
    unsigned char hash0[SHA_DIGEST_LENGTH];
    unsigned char hash1[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)message0, strlen(message0), hash0);
    SHA1((unsigned char*)message1, strlen(message1), hash1);


    printf("SHA1: ");
    for(i = 0; i < SHA_DIGEST_LENGTH; i++) {
       printf("%02x", hash0[i]);
    }
    printf("\n");
    hash_to_vlong((uint32_t *)hash0,vlMac);

    ecCopy(&ecPub, &curve_point);
    ecMultiply(&ecPub, private_key);
    ecPack(&ecPub, vlPub);
    vlPrint(stdout, "vlPub: ", vlPub);
    vlPrint(stdout, "vlMac: ", vlMac);

    cpSign(private_key,k, vlMac , &sig0);
    vlPrint(stdout, "r: ", sig0.r);
    vlPrint(stdout, "s: ", sig0.s);

    gfSelfTest(1000);
    ecSelfTest(100);

    gfQuit();
    return EXIT_SUCCESS;
}

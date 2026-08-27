#include "hashing.h"
#include "mbedtls/md.h"

void hashRecord(const uint8_t *payload, size_t payloadLength, uint8_t *output) {
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
  mbedtls_md_starts(&ctx);
  mbedtls_md_update(&ctx, payload, payloadLength);
  mbedtls_md_finish(&ctx, output);
  mbedtls_md_free(&ctx);
}

void hashToHex(const uint8_t *hash, char *hexOut) {
  for (int i = 0; i < HASH_SIZE; i++) {
    sprintf(hexOut + (i * 2), "%02x", hash[i]);
  }
  hexOut[HASH_SIZE * 2] = '\0';
}
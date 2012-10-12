#ifndef HEADER_GUARD_H
# define HEADER_GUARD_H

# include <stdint.h>
# include <stdlib.h>
# include "../lib-c/archive.h"

typedef struct
{
  int32_t suce;
  uint8_t bande;
} teton;

inline uint32_t nuntio_teton_size(teton* value)
{
  return 1 + 4 + 1;
}

inline void nuntio_teton_serialize(teton* value, t_nuntio_archive* archive)
{
  archive->size = nuntio_teton_size(value);
  archive->buffer = malloc(archive->size);
  nuntio_int32_serialize(value->suce, archive);
  nuntio_uint8_serialize(value->bande, archive);
}

inline void nuntio_teton_extract(t_nuntio_archive* archive, teton* value)
{
  nuntio_int32_extract(archive, &value->suce);
  nuntio_uint8_extract(archive, &value->bande);
}

#endif /* !HEADER_GUARD_H */

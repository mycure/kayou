#ifndef NUNTIO_ARCHIVE_H
# define NUNTIO_ARCHIVE_H

typedef struct
{
  void* buffer;
  unsigned int size;
  unsigned int offset;
} t_nuntio_archive;

/*
 * serialize
 */

inline void nuntio_uint8_serialize(uint8_t value,
				   t_nuntio_archive* archive)
{
  *((uint8_t*)(archive->buffer + archive->offset)) = value;

  archive->offset += sizeof(uint8_t);
}

inline void nuntio_int32_serialize(int32_t value,
				   t_nuntio_archive* archive)
{
  *((int32_t*)(archive->buffer + archive->offset)) = value;

  archive->offset += sizeof(int32_t);
}

inline void nuntio_uint32_serialize(uint32_t value,
				    t_nuntio_archive* archive)
{
  *((uint32_t*)(archive->buffer + archive->offset)) = value;

  archive->offset += sizeof(uint8_t);
}

inline void nuntio_meta_serialize(int endianness,
				 int stringuinness,
				 t_nuntio_archive* archive)
{
  uint8_t value = 0;

  value |= endianness & 1;
  value |= (stringuinness & 3) << 1;

  nuntio_uint8_serialize(value, archive);
}

/*
 * extract
 */

inline void nuntio_uint8_extract(t_nuntio_archive* archive,
				 uint8_t* value)
{
  *value = *((uint8_t*)(archive->buffer + archive->offset));

  archive->offset += sizeof(uint8_t);
}

inline void nuntio_int32_extract(t_nuntio_archive* archive,
				 int32_t* value)
{
  *value = *((int32_t*)(archive->buffer + archive->offset));

  archive->offset += sizeof(int32_t);
}

inline void nuntio_uint32_extract(t_nuntio_archive* archive,
				  uint32_t* value)
{
  *value = *((uint32_t*)(archive->buffer + archive->offset));

  archive->offset += sizeof(uint32_t);
}

inline void nuntio_meta_extract(t_nuntio_archive* archive,
				int* endianness,
				int* stringuinness)
{
  uint8_t value;

  nuntio_uint8_extract(archive, &value);

  *endianness = value & 1;
  *stringuinness = (value << 1) & 3;
}

#endif /* !ARCHIVE_H */

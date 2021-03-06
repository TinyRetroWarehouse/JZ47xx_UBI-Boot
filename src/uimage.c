/*
 * uImage: U-Boot image format
 *
 * http://www.denx.de/wiki/U-Boot/
 */

#include "include/jz.h"
#include "include/uimage.h"
#include "include/utils.h"

#include <endian.h>

#define UIMAGE_MAGIC       0x27051956 /* Image magic number */

#define UIMAGE_OS_LINUX    5 /* Linux */

#define UIMAGE_ARCH_MIPS   5 /* MIPS (32-bit) */

#define UIMAGE_TYPE_KERNEL 2 /* OS kernel image */

#define UIMAGE_COMP_NONE   0 /*  No compression */

struct uimage_header {
	/* Note: All fields are big endian. */
	uint32_t magic;    /* Magic number (UIMAGE_MAGIC) */
	uint32_t hcrc;     /* Image header CRC */
	uint32_t time;     /* Image creation timestamp */
	uint32_t size;     /* Image data size */
	uint32_t load;     /* Data load address */
	uint32_t ep;       /* Entry point address */
	uint32_t dcrc;     /* Image data CRC */
	uint8_t os;        /* Operating system */
	uint8_t arch;      /* CPU architecture */
	uint8_t type;      /* Image type */
	uint8_t comp;      /* Compression type */
	uint8_t name[32];  /* Image name */
};

static int check_uimage(struct uimage_header *header) {
	if(be32toh(header->magic) != UIMAGE_MAGIC) {
		return -1;
	}
	
	if(header->os != UIMAGE_OS_LINUX) {
		return -1;
	}
	
	if(header->arch != UIMAGE_ARCH_MIPS) {
		return -1;
	}
	
	if(header->type != UIMAGE_TYPE_KERNEL) {
		return -1;
	}
	
	if(header->comp != UIMAGE_COMP_NONE) {
		return -1;
	}
	
	return 0;
}

void *process_uimage_header(struct uimage_header *header, void **exec_addr, unsigned int data_size) {
	if(check_uimage(header)) {
		return NULL;
	} else {
		void *ld_addr = (void *) KSEG1ADDR(be32toh(header->load));
		void *body = (void *) header + sizeof(struct uimage_header);
		size_t move_size = data_size - sizeof(struct uimage_header);
		*exec_addr = (void *) be32toh(header->ep);
		memmove(ld_addr, body, move_size);
		return ld_addr + move_size;
	}
}

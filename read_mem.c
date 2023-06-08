#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main()
{
    int fd;
    void *cfg;
    char *name = "/dev/mem";
    const int num_locations = 10;

    // Prompt the user to input the starting address
    uint32_t start_address;
    printf("Enter the starting address (in hexadecimal): ");
    scanf("%x", &start_address);

    if((fd = open(name, O_RDWR)) < 0) {
        perror("open");
        return 1;
    }

    cfg = mmap(NULL, num_locations * sizeof(uint32_t), /* map the memory */
                PROT_READ, MAP_SHARED, fd, start_address);

    if (cfg == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    uint32_t *mem = (uint32_t *) cfg;

    for (int i = 0; i < num_locations; i++) {
        printf("Memory location 0x%x: %u\n", start_address + i*sizeof(uint32_t), mem[i]);
    }

    munmap(cfg, num_locations * sizeof(uint32_t));
    close(fd);
    return 0;
}

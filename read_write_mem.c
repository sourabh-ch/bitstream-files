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
                PROT_READ | PROT_WRITE, MAP_SHARED, fd, start_address);

    if (cfg == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    uint32_t *mem = (uint32_t *) cfg;

    // Ask the user for the data to write
    printf("Enter data to write to the first 10 memory locations (decimal values):\n");
    for (int i = 0; i < 10; i++) {
        printf("Data for memory location 0x%x: ", start_address + i*sizeof(uint32_t));
        scanf("%u", &mem[i]);
    }

    for (int i = 0; i < num_locations; i++) {
        printf("Memory location 0x%x: %u\n", start_address + i*sizeof(uint32_t), mem[i]);
    }

    munmap(cfg, num_locations * sizeof(uint32_t));
    close(fd);
    return 0;
}

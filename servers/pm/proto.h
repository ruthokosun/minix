#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <minix/ipc.h>

int main() {
    message_timing_t timing_data[MAX_TIMING_DATA];
    int count = get_message_timing_data(timing_data, MAX_TIMING_DATA);

    FILE *file = fopen("timing_data.csv", "w");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    fprintf(file, "source,destination,send_time,recv_time\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%d,%ld.%06ld,%ld.%06ld\n",
                timing_data[i].src, timing_data[i].dst,
                (long)timing_data[i].send_time.tv_sec, (long)timing_data[i].send_time.tv_usec,
                (long)timing_data[i].recv_time.tv_sec, (long)timing_data[i].recv_time.tv_usec);
    }
    fclose(file);

    printf("Message timing data saved to timing_data.csv\n");
    return 0;
}

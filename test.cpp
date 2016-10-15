#include <soxr.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>

int main(int argc, char** argv) {
    soxr_error_t error;
    soxr_quality_spec_t quality = soxr_quality_spec(SOXR_VHQ, SOXR_LINEAR_PHASE);
    soxr_t soxr = soxr_create(44100, 192000, 1, &error, nullptr, &quality, nullptr);
    size_t odone = 0;

    // 256 samples
    float input  [256];
    float output [1115];
    time_t t1, t2;
    size_t cnt = 0;
    time(&t1);

    printf("Engine: %s\n", soxr_engine(soxr));

    for (int i = 0; i < 256; i++) {
        input[i] = (i/256.0f)-0.5f;
    }

    for (int i = 0; i < 100000; i++) {
        size_t idone;
        soxr_process(soxr, input, 256, &idone, output, 1115, &odone);
        time(&t2);
        cnt++;
        if (t1 != t2) {
            t1 = t2;
            printf("%d / sec\n", (int) cnt);
            cnt = 0;
        }
    }

    soxr_delete(soxr);
}

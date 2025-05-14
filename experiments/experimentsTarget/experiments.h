/**
* Macros for experiments
*/

// experiment 1 -- increments (32)
#ifdef INCREMENT
#define EXPERIMENT_NAME "Increment experiment:"
#define asmExperiment(val) \
__asm__ volatile( \
        "ldi %0, 0x00"     "\n\t" /* set output register to 0 */ \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
)
#define EXPECTED_RESULT 32
#endif

// experiment 2 -- direct jump to address
#ifdef JUMP
#define EXPERIMENT_NAME "Jump experiment:"
#define asmExperiment(val) \
__asm__ volatile ( \
        "ldi %0, 0x00"      "\n\t" /* set output register to 0 */ \
        "nop"               "\n\t" /* add some NOPs (required ammount depends on the instruction delay of attacking HW) */ \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "rjmp a%="          "\n\t" /* target instruction we want to skip */ \
        "ldi %0, 0xFF"      "\n\t" /* if target instruction is skipped, output will be changed to 0xFF */ \
        "a%=:"              "\n\t" \
        "nop"               "\n\t" \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
)
#define EXPECTED_RESULT 0
#endif

// experiment 3 -- load constant into register
#ifdef LOAD
#define EXPERIMENT_NAME "Load experiment:"
#define asmExperiment(val) \
__asm__ volatile ( \
        "ldi %0, 0x00"      "\n\t" /* set output register to 0 */ \
        "nop"               "\n\t" /* add some NOPs (required ammount depends on the instruction delay of attacking HW) */ \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "ldi %0, 0x55"      "\n\t" /* target instruction we want to skip -- if target instruction is skipped, output won't be changed (defaults to 0x00) */ \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
)
#define EXPECTED_RESULT 85
#endif
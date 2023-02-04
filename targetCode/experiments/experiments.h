void increment() {
    uint8_t val;
    __asm__ volatile( \
        "ldi %0, 0x00"     "\n\t" \
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
    );
    Serial.print("Increment result: ");
    Serial.println(val);
}

void jump() {
    uint8_t val;
    __asm__ volatile ( \
        "ldi %0, 0x00"      "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "rjmp a%="          "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "ldi %0, 0xFF"      "\n\t" \
        "a%=:"              "\n\t" \
        "nop"               "\n\t" \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
    );
    Serial.print("Jump result: ");
    Serial.println(val);
}

void load() {
    uint8_t val;
    __asm__ volatile ( \
        "ldi %0, 0x00"      "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "ldi %0, 0x55"      "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
    );
    Serial.print("Load result: ");
    Serial.println(val);
}
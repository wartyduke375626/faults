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
    delay(1);
    Serial.print("Increment result: ");
    Serial.println(val);
}
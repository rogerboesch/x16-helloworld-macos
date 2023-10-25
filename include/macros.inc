
;Calculate register value for the given sample rate.
;   To calculate the value needed for a given sample rate, we use this equation:
;   rate(x) = min(round(x * (65536/25000000)), 128)
;   So for example, for 8KHz sample rate: rate(8000) = 20.97152 = 21 in the AUDIO_RATE register.
;   Since there is no 'round' function macro, we just add 1 to round up (might be slightly wrong)
.define SAMPLERATE(srate) .min((srate * 65536 / 25000000 + 1), $80)

;Call the debugger in the x16 emulator
.define debugger .byte $db

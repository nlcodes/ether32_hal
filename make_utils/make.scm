; Build script for gambit scheme on unix systems
; Works with swd
; After installing gambit scheme, run with "gsi make.scm"

; Define run command function
(define (run_cmd cmd)
  (shell-command cmd))

; Define make function
(define (make)

  ; Runs each command in order
  (run_cmd "make clean")
  (run_cmd "make")
  (run_cmd "arm-none-eabi-objcopy -O binary test.elf test.bin")
  (run_cmd "st-flash write test.bin 0x8000000"))

; Call make function
(make)

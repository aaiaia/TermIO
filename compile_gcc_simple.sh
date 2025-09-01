#!/bin/bash
INCLUDE_OPT=""
INCLUDE_OPT="${INCLUDE_OPT} -ITermIO/inc"
INCLUDE_OPT="${INCLUDE_OPT} -ITermIO/inc/ascii"
INCLUDE_OPT="${INCLUDE_OPT} -IDriver/inc/mcu/s12x"
INCLUDE_OPT="${INCLUDE_OPT} -IDriver/inc/os/linux"

OUT_FILE="term"

echo "include path:" $INCLUDE_OPT

if [ -e $OUT_FILE ]; then
    echo "Previous outfile is removed:" $OUT_FILE
    rm $OUT_FILE
fi

gcc -c TermIO/src/tool_term_io.c $INCLUDE_OPT
gcc -c TermIO/src/tool_data_io.c $INCLUDE_OPT
gcc -c TermIO/src/tool_form_io.c $INCLUDE_OPT
gcc -c TermIO/src/tool_menu_io.c $INCLUDE_OPT
gcc -c TermIO/src/tool_conv_io.c $INCLUDE_OPT
gcc -c Driver/src/mcu/s12x/drv_s12x_uart.c $INCLUDE_OPT
gcc -c Driver/src/os/linux/drv_linux_term.c $INCLUDE_OPT
gcc -c main.c $INCLUDE_OPT

gcc main.o tool_conv_io.o tool_menu_io.o tool_form_io.o tool_data_io.o tool_term_io.o drv_s12x_uart.o drv_linux_term.o -o term
rm *.o

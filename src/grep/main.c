#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "options.h"

int main(int argc, char* argv[]) {
    GrepOptions options;
    initialize_options(&options);

    // Обработка флагов. optarg принимает в себя первое значение после флага
    int opt;
    while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
        switch (opt) {
            case 'e':
                handle_e_flag(&options, optarg);
                break;
            case 'i':
                handle_i_flag(&options);
                break;
            case 'v':
                handle_v_flag(&options);
                break;
            case 'c':
                handle_c_flag(&options);
                break;
            case 'l':
                handle_l_flag(&options);
                break;
            case 'n':
                handle_n_flag(&options);
                break;
            case 'h':
                handle_h_flag(&options);
                break;
            case 's':
                handle_s_flag(&options);
                break;
            case 'f':
                handle_f_flag(&options, optarg);
                break;
            case 'o':
                handle_o_flag(&options);
                break;

            default:
                cleanup_options(&options);
                return 1;
        }
    }

    process_arguments(&options, argc, argv);
    cleanup_options(&options);

    return 0;
}
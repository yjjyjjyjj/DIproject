#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    printf("╭");
    for(int i=0;i<120;i++)
    {
        printf("─");
    }
    printf("╮\n");
    printf("│\t\x1b[34m                        .:::.         ..                     ......                                              \x1b[0m│\n"); 
    printf("│\t\x1b[34m                        ^~~!!?J!!!!!!^!!                  ~7~~~~~!!!.             7:                             \x1b[0m│\n"); 
    printf("│\t\x1b[34m                             7?  .... 7!                  ?!                      Y:                             \x1b[0m│\n"); 
    printf("│\t\x1b[34m                             J~       ?!                  77                      Y:                             \x1b[0m│\n"); 
    printf("│\t\x1b[34m             .~~!!~~~^^.     Y^       J! .:.   :^^^.      !Y~!!!!!!...   ..       Y^^ !!~~~^^:                   \x1b[0m│\n"); 
    printf("│\t\x1b[34m              .:::^^^^^:     Y^       ?!!7!J^ !J^:~J.     7?....... ^? ~7!?~ .7!!~5^. ::^^^^^:                   \x1b[0m│\n"); 
    printf("│\t\x1b[34m                             Y:       ?P~  :Y^P!~~7!      7?        .J!7. .J^J! .~G^                             \x1b[0m│\n"); 
    printf("│\t\x1b[34m                            .5:       J7    J7?!::.       7? .       YP.   ~J!?:. Y!                             \x1b[0m│\n"); 
    printf("│\t\x1b[34m                             7:       7:    :: ^!7~       ^J777!!!!~.~7    .~ :!!!?^                             \x1b[0m│\n"); 
    printf("│\t\x1b[34m                                                                                                                 \x1b[0m│\n"); 
    printf("│\t\x1b[33m                       ..                                                                              .:        \x1b[0m│\n"); 
    printf("│\t\x1b[33m   .^~!!!^      :!     7~          .                               :~~~^:    :.     .~~~!7 ~!!?        ~J        \x1b[0m│\n"); 
    printf("│\t\x1b[33m   :~~^~~~^     7!     ?~  :^:     ?:  ^~~!^   :~       .?!!!!!?~  :^^~~^.   J:         !J   :Y        ~J        \x1b[0m│\n"); 
    printf("│\t\x1b[33m   .:^^5J^:   .^57:.   ?^.7!~!7.   J^ ?!:..7!  ~J       ^Y     ??  :!77!^::^~Y.         ^^   :7        ~J        \x1b[0m│\n"); 
    printf("│\t\x1b[33m   ^!!~~~~!: :!~.^!~.  ?^?~   ?~   Y~ ?7:::7~  ~J       :Y~~~~~Y!  77::!7 ^^!5.      ^~~~~~~~~~:       ~J        \x1b[0m│\n"); 
    printf("│\t\x1b[33m .^^^^^^^^^^:          ~:Y.   J^   Y~  :^^^:   ~?        :::7:::.  ~7~~7~   :?        ^~~~~~~~~.       ~J        \x1b[0m│\n"); 
    printf("│\t\x1b[33m  ^~^^:^5^^^: ^!!!!!!!7. ~?^:!?    Y^......... !?          :Y       ^?7!!!!~7^        ?J~~~~~^^:                 \x1b[0m│\n"); 
    printf("│\t\x1b[33m  .J    !            .5:  .~!~     J:^~~~~!!!~ ~7      :!!!7Y!!!!~. !J    . Y!        ~5~~~~~~~:      :JJ^       \x1b[0m│\n"); 
    printf("│\t\x1b[33m  J7~~~~~~^.         J:           :.          ..      ...........  .J!!!!!!J:        :Y~~~~~~~^      .7?:        \x1b[0m│\n"); 
    printf("│\t\x1b[33m   .::::::..          .                                               ....             .........                 \x1b[0m│\n"); 
    printf("╰");
    for(int i=0;i<120;i++)
    {
        printf("─");
    }
    printf("╯\n");
    
    sleep(1);

    for(int i=0; i<4; i++)
    {
        system("clear");
         printf("                   &&&                           GPGB                                \n");   
        printf("                &Y7\x1b[33m~~~\x1b[0m!?J?7~^^^:::::::::::::^^^~!~^\x1b[33m:::\x1b[0m^!G                            \n"); 
        printf("               &7:\x1b[33m:::::::::::::::\x1b[0m^^^^^^^^^\x1b[33m::::::::::^::\x1b[0m:^#                           \n"); 
        printf("               P^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:J#                          \n"); 
        printf("             &P!^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:~Y#                        \n"); 
        printf("            B7::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:::~5                       \n"); 
        printf("           5^::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^::J&                     \n"); 
        printf("          Y::\x1b[33m^^^^^^^^^^^^^\x1b[0m::::\x1b[33m^^^^^^^^^^^^^^\x1b[0m::::\x1b[33m^^^^^^^^^^^^^\x1b[0m^::7&                    \n"); 
        printf("         5::\x1b[33m^^^^^^^^^^^^^\x1b[0m:^~~\x1b[0m::\x1b[33m^^^^^^^^^^^^\x1b[0m:~7!^\x1b[0m:\x1b[33m^^^^^^^^^^^^^^\x1b[0m^:?                    \n"); 
        printf("        #~:\x1b[33m^^^^^^^^^^^^\x1b[0m::!B&&P^\x1b[0m:\x1b[33m^^^^^^^^^^\x1b[0m:?&@@B!\x1b[0m:::::\x1b[33m^^^^^^^^^\x1b[0m^:^P                   \n"); 
        printf("        ?::\x1b[33m^^^^^^^\x1b[0m:::::::!#&&G^\x1b[0m::::::::::::~PBBJ^\x1b[0m:^^^^:::\x1b[33m^^^^^^^\x1b[0m^:!                   \n"); 
        printf("       #!:\x1b[33m^^^^^^^\x1b[0m::\x1b[35m^^~~~~^^\x1b[0m~^:::^!7?JJJ?7!^::::^~~\x1b[35m!!!!~~\x1b[0m^::\x1b[33m^^^^^\x1b[0m^:~#                  \n"); 
        printf("       #~:\x1b[33m^^^^^^\x1b[0m:^\x1b[35m~!!!!!!!\x1b[0m?J!^75BPYYJJJYYPB5!75P?\x1b[35m!!!!!!!!~\x1b[0m^^\x1b[33m^^^^\x1b[0m^:^B                  \n"); 
        printf("       #~:\x1b[33m^^^^^\x1b[0m:^\x1b[35m!!!!!!!!!\x1b[0m?PG#&J:         ^P #YJ7\x1b[35m!!!!!!!!!\x1b[0m^:\x1b[33m^^^^\x1b[0m^:^B                  \n"); 
        printf("       #!:\x1b[33m^^^^\x1b[0m^:~\x1b[35m!!!!!!!!!!!!\x1b[0m&G     .:     ~ #?7\x1b[35m!!!!!!!!!!\x1b[0m^:\x1b[33m^^^^\x1b[0m^:^#                  \n"); 
        printf("        7::\x1b[33m^^^^\x1b[0m:^\x1b[35m!!!!!!!!!\x1b[0m?GBB#57!!?B#P?7?JBGYGBJ\x1b[35m!!!!!!!!\x1b[0m~^^\x1b[33m^^^^\x1b[0m^:~&                  \n"); 
        printf("        B^:\x1b[33m^^^^^\x1b[0m:^\x1b[35m~!!!!!!!\x1b[0m7?~:~?5P& PYG BJ?!::^~~~\x1b[35m!!!!~\x1b[0m~^::\x1b[33m^^^^^\x1b[0m^:5                   \n"); 
        printf("         Y::\x1b[33m^^^^\x1b[0m::^^^~~~~^^:::::::!GBGB5~::::\x1b[33m^:::\x1b[0m^^^^^:::\x1b[33m^^^^\x1b[0m:::? &    &######&      \n"); 
        printf("          J::\x1b[33m^^^^^::::::::::\x1b[33m^^^^^^::^~^::^^^^^^^^::::::^^^\x1b[0m:::^!Y&&GPY?!~^^^^^^!JB    \n"); 
        printf("           5^::\x1b[33m^^^^^^^^^^^^^^^^^^^^:::::^^^^^^^^^^^^^^^\x1b[0m:::^7YGG5?~^::::\x1b[33m:::::::\x1b[0m::^P   \n"); 
        printf("            #?^:::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m:::!5BBY!^::::\x1b[33m^^^^^^^^^^^^^\x1b[0m:~B  \n"); 
        printf("              BY!^:::\x1b[33m:::^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m::::^?GB5!^::::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::!B  \n"); 
        printf("                &B5?!^^::::\x1b[33m::::::::::::::::::::\x1b[0m:::^!YBG?^:::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::::^?B   \n"); 
        printf("                   & BGPYJ?7!!~~~~^^^^~~~~!!7??J5PGBP!:::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::::^!YB     \n"); 
        printf("                  #P?~~7JJYYPPGBBGGGGGGBBGGP5YYJ?!~^:::\x1b[33m^^^^^^^^^^^^^^\x1b[0m::::~75#        \n"); 
        printf("               #P?~:::\x1b[33m::::::::^^^^^^^^^^^^:::::::::::\x1b[33m^^^^^^^^^^^^^^\x1b[0m:::~JP&           \n"); 
        printf("       &##BGPJ7^:::\x1b[33m:^^^^^^^::::::::::::::::::^^^^^^^^^^^^^^^^^^^\x1b[0m:::~?P&              \n"); 
        printf("  B5J?!~^^^:::\x1b[33m:::^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m::~5#                 \n"); 
        printf("B7^:::::\x1b[33m:::::^^^^^^::::^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m:^Y&                   \n"); 
        printf("?::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m:^77^:^\x1b[33m^^^^:::::::::::::::::::::::::::::::\x1b[0m::~G                     \n"); 
        printf("J::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m:!#P^::\x1b[33m:::::^^^^^^~~~~~~~~~~~~~~~~~~~^^^^^\x1b[0m^^G                      \n"); 
        printf("#?^:::\x1b[33m:::::::::::\x1b[0m::7 5~~!!!777?JJJJJJJJJJJJJJJJJJJJJJJJJJJJJ?5&                      \n"); 
        printf("  BY7~^^::\x1b[33m:::\x1b[0m^^^~775 PJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJG                       \n"); 
        printf("     &#GGGPGGGB#&    PJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJB                       \n"); 
        printf("                     GJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJYB                       \n"); 
        printf("                     GJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJB                       \n"); 
        printf("                     #JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ5#                       \n"); 
        printf("                     &GGPP5YYYYYYYYYYYYYYYYYYYYY55PGGGBB##&&                         \n");     

        usleep(250000);
        system("clear");
         printf("                             &&&                           GPGB                                \n");   
        printf("                          &Y7\x1b[33m~~~\x1b[0m!?J?7~^^^:::::::::::::^^^~!~^\x1b[33m:::\x1b[0m^!G                            \n"); 
        printf("                         &7:\x1b[33m:::::::::::::::\x1b[0m^^^^^^^^^\x1b[33m::::::::::^::\x1b[0m:^#                           \n"); 
        printf("                         P^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:J#                          \n"); 
        printf("                       &P!^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:~Y#                        \n"); 
        printf("                      B7::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:::~5                       \n"); 
        printf("                     5^::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^::J&                     \n"); 
        printf("                    Y::\x1b[33m^^^^^^^^^^^^^\x1b[0m::::\x1b[33m^^^^^^^^^^^^^^\x1b[0m::::\x1b[33m^^^^^^^^^^^^^\x1b[0m^::7&                    \n"); 
        printf("                   5::\x1b[33m^^^^^^^^^^^^^\x1b[0m:^~~\x1b[0m::\x1b[33m^^^^^^^^^^^^\x1b[0m:~7!^\x1b[0m:\x1b[33m^^^^^^^^^^^^^^\x1b[0m^:?                    \n"); 
        printf("                  #~:\x1b[33m^^^^^^^^^^^^\x1b[0m::!B&&P^\x1b[0m:\x1b[33m^^^^^^^^^^\x1b[0m:?&@@B!\x1b[0m:::::\x1b[33m^^^^^^^^^\x1b[0m^:^P                   \n"); 
        printf("                  ?::\x1b[33m^^^^^^^\x1b[0m:::::::!#&&G^\x1b[0m::::::::::::~PBBJ^\x1b[0m:^^^^:::\x1b[33m^^^^^^^\x1b[0m^:!                   \n"); 
        printf("                 #!:\x1b[33m^^^^^^^\x1b[0m::\x1b[35m^^~~~~^^\x1b[0m~^:::^!7?JJJ?7!^::::^~~\x1b[35m!!!!~~\x1b[0m^::\x1b[33m^^^^^\x1b[0m^:~#                  \n"); 
        printf("                 #~:\x1b[33m^^^^^^\x1b[0m:^\x1b[35m~!!!!!!!\x1b[0m?J!^75BPYYJJJYYPB5!75P?\x1b[35m!!!!!!!!~\x1b[0m^^\x1b[33m^^^^\x1b[0m^:^B                  \n"); 
        printf("                 #~:\x1b[33m^^^^^\x1b[0m:^\x1b[35m!!!!!!!!!\x1b[0m?PG#&J:         ^P #YJ7\x1b[35m!!!!!!!!!\x1b[0m^:\x1b[33m^^^^\x1b[0m^:^B                  \n"); 
        printf("                 #!:\x1b[33m^^^^\x1b[0m^:~\x1b[35m!!!!!!!!!!!!\x1b[0m&G     .:     ~ #?7\x1b[35m!!!!!!!!!!\x1b[0m^:\x1b[33m^^^^\x1b[0m^:^#                  \n"); 
        printf("                  7::\x1b[33m^^^^\x1b[0m:^\x1b[35m!!!!!!!!!\x1b[0m?GBB#57!!?B#P?7?JBGYGBJ\x1b[35m!!!!!!!!\x1b[0m~^^\x1b[33m^^^^\x1b[0m^:~&                  \n"); 
        printf("                  B^:\x1b[33m^^^^^\x1b[0m:^\x1b[35m~!!!!!!!\x1b[0m7?~:~?5P& PYG BJ?!::^~~~\x1b[35m!!!!~\x1b[0m~^::\x1b[33m^^^^^\x1b[0m^:5                   \n"); 
        printf("       &######&    & ?:::\x1b[33m^^^^:::^^^^^:::^::::~5BGBG!:::::::^^~~~~^^^::^^^^\x1b[0m::Y             \n");
        printf("     BJ!^^^^^^~!?YPG&&Y!^:::\x1b[33m^^^::::::^^^^^^^^::^~^::^^^^^^::::::::::^^^^^\x1b[0m::J              \n");
        printf("    P^::\x1b[33m::::::::\x1b[0m:::^~?5GGY7^:::\x1b[33m^^^^^^^^^^^^^^^:::::^^^^^^^^^^^^^^^^^^^^\x1b[0m::^5               \n");
        printf("   B~:\x1b[33m^^^^^^^^^^^^^\x1b[0m::::^!YBB5!:::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m:::^?#                \n");
        printf("   B!::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::::^!5BG?^::::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^:::\x1b[0m:::^!YB                  \n");
        printf("    B?^::::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m:::^?GBY!^::::\x1b[33m:::::::::::::::::::\x1b[0m::::^^!?5B&                    \n");
        printf("      BY!^::::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m:::!PBGP5J??7!!~~~~^^^^~~~~!!7?JYPGB &                       \n");
        printf("         #57~::::\x1b[33m^^^^^^^^^^^^^^\x1b[0m:::^~!?JYY5PGGBBGGGGGGBBGPPYYJJ7~~?P#                      \n");
        printf("            &PJ~:::\x1b[33m^^^^^^^^^^^^^^\x1b[0m:::::::::::^^^^^^^^^^^^::::::::\x1b[0m:::~?P#                   \n");
        printf("               &P?~:::\x1b[33m^^^^^^^^^^^^^^^^^^^::::::::::::::::::^^^^^^^:\x1b[0m:::^7JPGB##&           \n");
        printf("                  #5~::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^:::\x1b[0m:::^^^~!?J5B      \n");
        printf("                    &Y^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^::::^^^^^^:::::\x1b[0m:::::^7B    \n");
        printf("                      G~::\x1b[33m:::::::::::::::::::::::::::::::^^^^\x1b[0m^:^77^:\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::?    \n");
        printf("                       G^^\x1b[33m^^^^^~~~~~~~~~~~~~~~~~~~^^^^^^:::::\x1b[0m::^P#!:\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::J    \n");
        printf("                       &5?JJJJJJJJJJJJJJJJJJJJJJJJJJJJJ?777!!!~~5 7::\x1b[33m:::::::::::::\x1b[0m:^?#    \n");
        printf("                        GJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJP 577~^^^\x1b[33m:::::\x1b[0m^^~7YB      \n");
        printf("                        BJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJP    &#BGGGPGGG#&         \n");
        printf("                        BYJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJG                         \n");
        printf("                        BJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJG                         \n");
        printf("                        #5JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ#                         \n");
        printf("                          &&##BBGGGP55YYYYYYYYYYYYYYYYYYYYY5PPGG&                         \n");  
        usleep(250000);      
}       
    
    sleep(1);
    system("clear");
    printf("╭");
    for(int i=0;i<120;i++)
    {
        printf("─");
    }
    printf("╮\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");    
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│\t\t\t\t\t\t      - 만든 사람 -                                                      │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│\t\t\t\t\t\t양  정  주( ♥  공 주 ♥  )                                                │\n");
    usleep(50000);
    printf("│\t\t\t\t\t\t이  시  영(  시  녀  1  )                                                │\n");
    usleep(50000);
    printf("│\t\t\t\t\t\t유  미  유(  시  녀  2  )                                                │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);

    printf("╰");
    for(int i=0;i<120;i++)
    {
        printf("─");
    }
    printf("╯\n");

    return 0;
}

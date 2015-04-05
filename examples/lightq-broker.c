/* 
 * File:   main.c
 * Author: Rohit Joshi <rohit.c.joshi@gmail.com>
 *
 * Created on April 2, 2015, 9:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "lightq_api.h"
/*
 * start broker
 */
int main(int argc, char** argv) {
    
    int c;
    char *admin_userid = "lightq_admin";
    char *admin_password = "T0p$3cr31";
    char *bind_ip = "*";
    unsigned bind_port = 5500;
    char *transport = "tcp";
    char *loglevel = "event";
    
   
    while ((c = getopt (argc, argv, "hu:p:i:b:t:l:")) != -1) {
    switch (c)
      {
      case 'h':
        printf("Usage: [%s] [-u admin_userid[%s]] [-p admin_password[%s]] [-i bind_ip[%s]] [-b bind_port[%d]] [-t transport[%s]] [-l loglevel[event]]\n", 
                argv[0], admin_userid, admin_password, bind_ip, bind_port, transport);
        return 1;
      case 'u':
        admin_userid = optarg;
        break;
      case 'p':
        admin_password = optarg;
        break;
      case 'i':
        bind_ip = optarg;
        break;
     
      case 'b':
        bind_port = atoi(optarg);
        if(bind_port == 0) {
            printf("Invalid bindport 0\n");
            return -1;
        }
        break;
        
       case 'l':
        loglevel = optarg;
        break;
      
      case 't':
        transport = optarg;
        if((strcmp("tcp", transport) != 0) && (strcmp("ipc", transport) != 0) && (strcmp("inproc", transport) != 0)) {
            printf("Invalid transport %s. Must be one of 'tcp', 'ipc', 'inproc\n");
            return -1;
        }
        break;
      case '?':
        if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        break;
      }
    }
    
     printf("[-u admin_userid[%s]] [-p admin_password[%s]] [-i bind_ip[%s]] [-b bind_port[%d]] [-t transport[%s]] [-l loglevel[%s]]\n", 
                argv[0], admin_userid, admin_password, bind_ip, bind_port, transport, logleve);

    lightq_loglevel level = str_to_loglevel(loglevel);
    init_log(argv[0], level);
    
    lightq_broker_mgr* p_broker =  init_broker(admin_userid, admin_password, transport, bind_ip, bind_port);
    
    if(p_broker) {
        run_broker(p_broker, true);
    }else {
      printf("Failed to initialize broker");
    }
      
   return (EXIT_SUCCESS);
    }
}


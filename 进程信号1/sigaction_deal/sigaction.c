   #include <signal.h>  
   #include <stdio.h>  
   #include <unistd.h>  
     
     
   void ouch(int sig)  
   {  
       printf("oh, got a signal %d\n", sig);  
     
      int i = 0;  
      for (i = 0; i < 5; i++)  
      {  
         printf("signal func %d\n", i);  
          sleep(1);  
      }  
  }  
      
  int main()  
  {  
     struct sigaction act;  
      act.sa_handler = ouch;  
      sigemptyset(&act.sa_mask);  
      sigaddset(&act.sa_mask, SIGQUIT);  
      // act.sa_flags = SA_RESETHAND;  
      // act.sa_flags = SA_NODEFER;  
      act.sa_flags = 0;  
    
     sigaction(SIGINT, &act, 0);     
   
      struct sigaction act_2;  
      act_2.sa_handler = ouch;  
      sigemptyset(&act_2.sa_mask);  
     act.sa_flags = 0;  
      sigaction(SIGQUIT, &act_2, &act);     
        while(1)  
        {  
            printf("linux_68\n");
             sleep(1);  
        }  
      return 0;  
  
    }  

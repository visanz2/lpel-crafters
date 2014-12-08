#ifndef __L1_CPP_TASK_H__
#define __L1_CPP_TASK_H__

extern "C"
{
    #include<L1_Types.h>
}

class L1_CPP_Task
{
 public:
  virtual void run(void) = 0;
  
};

#endif /* !__L1_CPP_TASK_H__ */



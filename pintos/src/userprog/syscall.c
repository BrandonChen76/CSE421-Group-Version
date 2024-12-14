#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

#include "userprog/process.h"
#include "devices/shutdown.h"

static void syscall_handler (struct intr_frame *);

void halt (void);
void exit (int status);
pid_t exec (const char *cmd_line);
int wait (pid_t pid);
bool create (const char *file, unsigned initial_size);
bool remove (const char *file);
int open (const char *file);
int filesize (int fd);
int read (int fd, void *buffer, unsigned size);
int write (int fd, const void *buffer, unsigned size);
void seek (int fd, unsigned position);
unsigned tell (int fd);
void close (int fd);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  //get pointer
  void *stack = f->esp;

  //get argument number
  int call = *(int*)stack;

  //switch case for all calls
  switch (call)
  {
    // NOT DONE, fix input
    case 0:
      halt();
      break;

    case 1:
      exit(int status);
      break;

    case 2:
      exec(const char *cmd_line);
      break;

    case 3:
      wait();
      break;

    case 4:
      create(const char *file, unsigned initial_size);
      break;

    case 5:
      remove(const char *file);
      break;

    case 6:
      open(const char *file);
      break;

    case 7:
      filesize(int fd);
      break;
    
    case 8:
      read(int fd, void *buffer, unsigned size);
      break;
    
    case 9:
      write();
      break;

    case 10:
      seek(int fd, unsigned position);
      break;
    
    case 11:
      tell(int fd);
      break;

    case 12:
      close(int fd);
      break;

  }
  thread_exit ();
}

//exactly like documentation
void halt (void){
  shutdown_power_off();
}

//IDK
void exit (int status){
  if(status == 0){
    fprint("good");
  }

  thread_exit();
}

//Done?
pid_t exec (const char *cmd_line){
  return process_execute(cmd_line);
}

//Done?
int wait (pid_t pid){
  return process_wait(pid);
}

//Done?
bool create (const char *file, unsigned initial_size){
  return filesys_create(file, initial_size);
}

//Done?
bool remove (const char *file){
  return filesys_remove(file);
}

//
int open (const char *file){

}

//
int filesize (int fd){

}

//
int read (int fd, void *buffer, unsigned size){

}

int write (int fd, const void *buffer, unsigned size){
  //console
  if(fd = 1){
    putbuf(buffer, size);
    return size;
  }
  //file write

  //error
  return -1;
}

//
void seek (int fd, unsigned position){

}

//
unsigned tell (int fd){

}

//
void close (int fd){
  
}
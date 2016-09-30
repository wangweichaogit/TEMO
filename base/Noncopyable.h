/*
noncopable用于对象语义
*/
#ifndef _TEMO_NONCOPYABLE_H_
#define _TEMO_NONCOPYABLE_H_

class noncopyable
{
 protected:
  noncopyable() {}

 private:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;
};

class copyable
{
};


#endif
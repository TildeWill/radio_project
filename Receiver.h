#ifndef Receiver_h
#define Receiver_h

class Receiver {
   public:
      virtual void checkButtons();
      virtual void volumeUp(int amount);
      virtual void volumeDown(int amount);
};

#endif
#ifndef Receiver_h
#define Receiver_h

class Receiver {
   public:
      virtual void checkButtons();
      virtual String getCurrentSong();
};

#endif
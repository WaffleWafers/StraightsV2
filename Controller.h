#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <gtkmm.h>

class Model;

class Controller {
public:
   Controller( Model* );
   void nextButtonClicked();
   void resetButtonClicked();
private:
   Model *model_;
};


#endif
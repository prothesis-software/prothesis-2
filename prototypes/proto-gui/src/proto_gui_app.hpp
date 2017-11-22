#ifndef PROTO_GUI_APP
#define PROTO_GUI_APP

class ProtoGuiApp: public wxApp {
public:
  virtual bool OnInit();
};

DECLARE_APP(ProtoGuiApp)

#endif

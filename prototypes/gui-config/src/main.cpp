// -*- C++ -*-
//
// generated by wxGlade 0.8.0a8 on Tue Nov 21 20:13:41 2017
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

// This is an automatically generated file.
// Manual changes will be overwritten without warning!

#include <wx/wx.h>
#include <wx/image.h>
#include "MyFrame.h"


class MyApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    MyFrame* frame = new MyFrame(NULL, wxID_ANY, wxEmptyString);
    SetTopWindow(frame);
    frame->Show();

    wxButton* button_2 = new wxButton(frame, wxID_ANY, wxT("DYNAMIC BTN LEL"));
    frame->sizer_6->Add(button_2, 0, 0, 0);
    frame->SetSizer(frame->sizer_6);
    frame->sizer_6->Fit(frame);
    frame->Layout();
    frame->Fit();
    
    return true;
}

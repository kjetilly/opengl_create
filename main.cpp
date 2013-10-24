#define GLX_GLXEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

int main(int argc, char** argv) {
  
  
  std::vector<std::string> displayStrings = {":0.0", ":0.1"};
  for(auto displayString : displayStrings) {
    auto display = XOpenDisplay( displayString.c_str() );
    auto screenNumber = DefaultScreen( display );
    int glx_fb_configs_N;
    int fb_attrib[] = {
      GLX_RENDER_TYPE,    GLX_RGBA_BIT,
      GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
      GLX_RED_SIZE,       1,
      GLX_GREEN_SIZE,     1,
      GLX_BLUE_SIZE,      1,
      None,
      None
    };
    auto glx_fb_configs = glXChooseFBConfig( display,
					     screenNumber,
					     fb_attrib,
					     &glx_fb_configs_N );
    
    auto screen_number = DefaultScreen( display );
    PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB_f = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddressARB((GLubyte *) "glXCreateContextAttribsARB");
    
    
    std::vector<int> attribs;
    attribs.push_back( None );
    
    // Try direct and not direct
    
    auto m_create_context_error = false;

    
    std::cerr << "Before create context" << std::endl;
    std::cerr << "Display is " << displayString << std::endl;
    std::cerr << "glXCreateContextAttribsARB_f = " << (void*)glXCreateContextAttribsARB_f << std::endl;
    std::cerr << "Scren Number is " << screenNumber << std::endl;
    auto context = glXCreateContextAttribsARB_f( display,
						 glx_fb_configs[0],
						 NULL,
						 GL_TRUE,
						 NULL );
    
    
    std::cout << "After" << std::endl;
    XFree(glx_fb_configs);
    glXDestroyContext(display, context);
    XCloseDisplay(display);
    
    
  } 
  
}

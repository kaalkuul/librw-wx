#pragma once

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <rw.h>
#include <wx/glcanvas.h>

class wxRwGLContext;

class wxRwCanvas : public wxGLCanvas
{
    wxDECLARE_EVENT_TABLE();

public:
	wxRwCanvas(wxWindow* parent);
	virtual ~wxRwCanvas();

	bool InitRw();

protected:
	virtual wxRwGLContext* InitContext() = 0;
	virtual void InitRwResources() = 0;
	virtual void Render() = 0;

private:
    void OnPaint(wxPaintEvent& event);
	void OnResized(wxSizeEvent& evt);

private:
	wxRwGLContext* m_glContext;
};

class wxRwGLContext : public wxGLContext
{
public:
    wxRwGLContext(wxGLCanvas* canvas);
    virtual ~wxRwGLContext();

    bool InitialiseRw(wxGLCanvas* canvas);
    void TerminateRw();

protected:
    virtual bool PrepareEngineOpenParams(rw::EngineOpenParams& params);
    virtual bool AttachPlugins() = 0;
    virtual void OnRwReady();

private:
    rw::EngineOpenParams engineOpenParams;
    bool rwInitialised;
};

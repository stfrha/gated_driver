// driver_sim_prjDoc.h : interface of the Cdriver_sim_prjDoc class
//


#pragma once

#include "characters.h"
#include "DisplayServer.h"

#define SCREEN_BUFFER_SIZE 2000


class Cdriver_sim_prjDoc : public CDocument
{
protected: // create from serialization only
	Cdriver_sim_prjDoc();
	DECLARE_DYNCREATE(Cdriver_sim_prjDoc)

// Attributes
public:
   CString  m_file;
   char*    m_fileContents;
   int      m_fileIndex;


// Operations
public:
	CDisplayServer m_myDisplay;

	char  build_character(unsigned char c, unsigned char** dst);
	unsigned int  build_message(unsigned char* str);
	void  display_screen(unsigned int offset, unsigned int bitmap_len);
	void display_message(unsigned int msg_len);
   unsigned char GetScreenByte(int offset) { return m_myDisplay.GetScreenByte(offset); }

   bool NextScrollPos( void );
   void NextMessage( void );


private:



// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Cdriver_sim_prjDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnScrollSplash();
   afx_msg void OnSelectText();
};



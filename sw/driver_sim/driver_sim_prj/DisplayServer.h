#pragma once

class CDisplayServer
{
public:
	CDisplayServer(void);
	~CDisplayServer(void);

	void	InsertByte(char c);
	bool	IsBusy(void) { return m_busy; }
	void	Overread( void );
   unsigned char GetScreenByte(int offset) { return screen[offset]; }

	char	screen[59];
	char	mem[64];
private:
	int		m_index;
	bool	m_busy;
};

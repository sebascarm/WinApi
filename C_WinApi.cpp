#include "C_WinApi.h"
#include "Contenedor.h"

#include "C_Button.h"
#include "C_Menu.h"
#include "C_ListBox.h"
#include "C_Shape.h"
#include "C_TextBox.h"
#include "C_Graphic.h"

#include <string.h>

extern std::vector <Contenedor> CONTENEDOR;

//*********************************************
//*** CREACION								***
//*********************************************
void C_WinApi::Create(HINSTANCE hInstance) {
	HICON hIcon;
	hIcon = (HICON)LoadImage(	// returns a HANDLE so we have to cast to HICON
		NULL,					// hInstance must be NULL when loading from a file
		"iconfile.ico",			// the icon file name
		IMAGE_ICON,				// specifies that the file is an icon
		0,						// width of the image (we'll specify default later on)
		0,						// height of the image
		LR_LOADFROMFILE |		// we want to load a file (as opposed to a resource)
		LR_DEFAULTSIZE |		// default metrics based on the type (IMAGE_ICON, 32x32)
		LR_SHARED				// let the system release the handle when it's no longer used
	);
	this->hInstance = hInstance;
	NombreClase = "WinApi";
	//registrar la clase windows
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = hIcon;											//LoadIcon(NULL, IDI_APPLICATION);					//nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = CreateSolidBrush(RGB(250, 250, 250));	//nullptr; //GetSysColorBrush(COLOR_3DFACE);  
	wc.lpszMenuName = nullptr;
	wc.hIconSm = nullptr;
	wc.lpszClassName = (LPSTR)NombreClase.c_str();
	//Registrar					
	RegisterClassEx(&wc);

}

string C_WinApi::GetClass() {
	return NombreClase;
}

HINSTANCE C_WinApi::Get_Instance(){
	return hInstance;
}

WNDPROC  OldButtonProc;
WNDPROC  OldTextProc;

//*********************************************
//*** DIBUJADO DE LOS ELEMENTOS				***
//*********************************************

void C_WinApi::Draw() {
	//Dibujamos solo todos los frame creados (sin mostrarlos)
	int Elemento = (int)CONTENEDOR.size();
	for (int i = 0; i < Elemento; i++) {
		if (CONTENEDOR[i].Tipo == TipoObjeto::T_FRAME) {
			CONTENEDOR[i].Draw();
		}
	}
	//Dibujar controles										
	for (int i = 0; i < Elemento; i++) {
		if (CONTENEDOR[i].Tipo != TipoObjeto::T_FRAME) {
			// No dibujamos los objetos Shape			
			if (CONTENEDOR[i].Tipo != TipoObjeto::T_SHAPE) {
				CONTENEDOR[i].Draw();
				if (CONTENEDOR[i].Tipo == TipoObjeto::T_BUTTON) {
					// Agregamos procedimiento para botons
					OldButtonProc = (WNDPROC)
					SetWindowLongPtr(CONTENEDOR[i].Get_hWnd(), GWLP_WNDPROC, (LONG_PTR)&Boton_Proc);
				} else if (CONTENEDOR[i].Tipo == TipoObjeto::T_TEXTBOX) {
					// Agregamos procedimiento para TEXTOS
					OldTextProc = (WNDPROC)
					SetWindowLongPtr(CONTENEDOR[i].Get_hWnd(), GWLP_WNDPROC, (LONG_PTR)&Text_Proc);
				}
			}
		}
	}
	//Mostramos Frames					
	for (int i = 0; i < Elemento; i++) {
		if (CONTENEDOR[i].Tipo == TipoObjeto::T_FRAME) 
			CONTENEDOR[i].Show();
	}
}

//*********************************************
//*** CALLBACK								***
//*********************************************

int ii = 0;	// para test de elementos

LRESULT CALLBACK C_WinApi::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//Debug de mensajes										
	//static WindowsMessageMap mm;							
	//OutputDebugString(mm(msg, lParam, wParam).c_str());	
	
	int ID			 = LOWORD(wParam);				// Identificador del control Win	
	int ID_Long		 = GetDlgCtrlID((HWND)lParam);  // Identificador en cambio de color	
	int Notificacion = HIWORD(wParam);				// Codigo de notificacion recibida (ej: click, doble click)
	int Elementos    = (int)CONTENEDOR.size();
		
	HDC hdc = NULL;
	PAINTSTRUCT PStruc;
	

	switch (msg) {
	//	Crear controles		//								
	case WM_CREATE:
		break;
	// DIBUJADO DE ELEMENTOS								
	case WM_PAINT:
		for (int i = 0; i < Elementos; i++) {
			// Buscamos el frame donde dibuja				
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_FRAME) {
				bool inicial = true;
				HWND*	hPadreElem;
				// REcorremos los elementos del frame		
				for (int j = 0; j < Elementos; j++) {
					// SHAPE
					if (CONTENEDOR[j].Tipo == TipoObjeto::T_SHAPE) {
						if (CONTENEDOR[j].pShape->Redibujar) {	
							hPadreElem = CONTENEDOR[j].pShape->Get_hWnd_Padre();
							if (hWnd == *hPadreElem) {
								// Iniciar pintado	
								if (inicial) {
									hdc = BeginPaint(hWnd, &PStruc);
									inicial = false;
								}
								// Dibujar			
								CONTENEDOR[j].pShape->Draw_Shape(hdc);			// Enviamos el evento 	
							}
						}
					}
					// GRAPHIC
					if (CONTENEDOR[j].Tipo == TipoObjeto::T_GRAPHIC) {
						if (CONTENEDOR[j].pGraphic->Redibujar) {
							hPadreElem = CONTENEDOR[j].pGraphic->Get_hWnd_Padre();
							if (hWnd == *hPadreElem) {
								if (inicial) {	// Iniciar pintado	
									hdc = BeginPaint(hWnd, &PStruc);
									inicial = false;
								} // Dibujar			
								CONTENEDOR[j].pGraphic->Draw_Shape(hdc);			// Enviamos el evento 	
							}
						}
					}
				}
				// Fin de pintado							
				if (!inicial) {
					EndPaint(hWnd, &PStruc);
				}
			}
		}
		break;
	
	// CAMBIAR COLOR DE FONDOS DE TODOS LOS LABELS			
	case WM_CTLCOLORSTATIC: {
		for (int i = 0; i < Elementos; i++) {
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_LABEL) {
				if (CONTENEDOR[i].Get_ID() == ID_Long) 
					return (LRESULT)CONTENEDOR[i].ColorEdit(wParam); // devuelve el pincel modificado
			}
		}
		break;
	}
	// RECEPCION DE COMANDOS								
	case WM_COMMAND: {
		for (int i = 0; i < Elementos; i++) {
			
			// **** Se debe mejorar el rendimiento via notification
			// **** Envio de click a botones (Evento propio)
			// **** Envio de change a textbox				
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_TEXTBOX) {
				int cont_ID = CONTENEDOR[i].Get_ID();
				if (CONTENEDOR[i].Get_ID() == ID){
					//Test(msg, ID, ID_Long, Notificacion, Elementos, TipoObjeto::T_TEXTBOX,true);
					if (EN_CHANGE == Notificacion) {
						CONTENEDOR[i].pTextBox->Event_Text_Change();
					}
				}
			}
			// **** Envio de click a Menu					
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_MENU) {
				//Recorremos los elementos del menu			
				for (int j = 0; j < CONTENEDOR[i].pMenu->V_ID.size(); j++) {
					if (CONTENEDOR[i].pMenu->V_ID[j] == ID) {
						CONTENEDOR[i].pMenu->Event_Click(wParam);
					}
				}
			}
			// **** List box								
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_LISTBOX) {
				// Buscamos el list que recibe el evento	
				if (CONTENEDOR[i].Get_ID() == ID) {
					// Buscamos el evento (SELL CHANGE)		
					if (LBN_SELCHANGE == Notificacion) {
						// Cambio de celda					
						CONTENEDOR[i].pListBox->Event_ChangeCell();
					} else if (LBN_DBLCLK == Notificacion) {
						// Cambio de celda	(DOBLE CLICK)	
						CONTENEDOR[i].pListBox->Event_DobleClick();
					}
				}
			}

		}
		break;
	}
	//CAMBIO DE TAMAÑO										
	case WM_SIZE: {
		//Envio resize										
		for (int i = 0; i < Elementos; i++) {
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_FRAME) {
				//Revisamos que sea la ventana que recive el event			
				if (CONTENEDOR[i].Get_hWnd() == hWnd) {
					//Evento interno para cambiar los valores de las var	
					CONTENEDOR[i].pFrame->Event_Resize(lParam);
				}
			}
		}
		break;
	}
	// CERRAR												
	case WM_CLOSE:
		// Solo cerramos si el primer objeto es cerrado FRAME 1
		if (hWnd == CONTENEDOR[0].Get_hWnd()) {
			PostQuitMessage(69);
		} else {
			// evitamos el cierre y escondemos si es otro objeto, para tener la posibilidad de habilitarlo luego
			for (int i = 0; i < Elementos; i++) {
				if (hWnd == CONTENEDOR[i].Get_hWnd()) {
					CONTENEDOR[i].pFrame->Hide();
				}
			}
			return 0;
		}
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//*********************************************
//*** CALLBACK ESPECIAL BOTON				***
//*********************************************

LRESULT CALLBACK C_WinApi::Boton_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int ID			 = LOWORD(wParam);				// Identificador del control		
	int ID_Long		 = GetDlgCtrlID((HWND)lParam);  // Identificador en cambio de color	
	int Notificacion = HIWORD(wParam);				// Codigo de notificacion recibida (ej: click, doble click)
	int Elementos = (int)CONTENEDOR.size();
	//Test(msg, ID, ID_Long, Notificacion, Elementos, TipoObjeto::T_BUTTON, false);
	switch (msg) {
	// PRECION DE BOTON										
	case WM_LBUTTONDOWN: {
		for (int i = 0; i < Elementos; i++) {
			// **** Envio de presion a botones				
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_BUTTON) {
				// Buscamos el boton que recibe el evento	
				HWND Cont = CONTENEDOR[i].Get_hWnd();
				if (Cont == hWnd) {
					CONTENEDOR[i].pButton->Event_Press();		// Enviamos el click	
					//OutputDebugString("--press--\n");
				}
			}
		}
		break;
	}
	// SOLTAR BOTON											
	case WM_LBUTTONUP: {
		for (int i = 0; i < Elementos; i++) {
			// **** Envio de presion a botones				
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_BUTTON) {
				// Buscamos el boton que recibe el evento	
				if (CONTENEDOR[i].Get_hWnd() == hWnd) {			// El id esta en el long
					CONTENEDOR[i].pButton->Event_Click();		// Enviamos el click	
					//OutputDebugString("--release--\n");
				}
			}
		}
		break;
	}
	}
	return CallWindowProc(OldButtonProc, hWnd, msg, wParam, lParam);
}
//*********************************************
//*** CALLBACK ESPECIAL TEXT BOX			***
//*********************************************
LRESULT CALLBACK C_WinApi::Text_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int ID = LOWORD(wParam);				// Identificador del control		
	int ID_Long = GetDlgCtrlID((HWND)lParam);  // Identificador en cambio de color	
	int Notificacion = HIWORD(wParam);				// Codigo de notificacion recibida (ej: click, doble click)
	int Elementos = (int)CONTENEDOR.size();
	//Test(msg, ID, ID_Long, Notificacion, Elementos, TipoObjeto::T_BUTTON, false);
	switch (msg) {
		// PRECION DE TECLA										
		case WM_KEYDOWN: {
			// Revisamos si la notificacion es (ENTER)
			if (ID == VK_RETURN) {
				for (int i = 0; i < Elementos; i++) {
					// **** Envio de presion a botones				
					if (CONTENEDOR[i].Tipo == TipoObjeto::T_TEXTBOX) {
						// Buscamos el text que recibe el evento	
						HWND Cont = CONTENEDOR[i].Get_hWnd();
						if (Cont == hWnd) {
							string tmp = CONTENEDOR[i].pTextBox->Get_Text() + "\n";
							CONTENEDOR[i].pTextBox->Set_Text(tmp);
							//CONTENEDOR[i].pTextBox->Event_Text_Change();
							OutputDebugString("--press--\n");
						}
					}
				}
			} else {
				return CallWindowProc(OldTextProc, hWnd, msg, wParam, lParam);
			}
		}
		break;
	}
	return CallWindowProc(OldTextProc, hWnd, msg, wParam, lParam);
}
//*********************************************
//*** TAB									***
//*********************************************
void C_WinApi::TeclaTab(MSG msg){
	HWND hwnd_rec = msg.hwnd;
	int Elementos = (int)CONTENEDOR.size();
	int Elemento;
	for (int i = 0; i < Elementos; i++) {
		HWND hCont = CONTENEDOR[i].Get_hWnd();
		if (hwnd_rec == hCont) {
			Elemento = NextContenedor(i);
			HWND hwnd_pas = CONTENEDOR[Elemento].Get_hWnd();
			SetFocus(hwnd_pas);
		}
	}
}

int C_WinApi::NextContenedor(int ID_Actual) {
	int ID_Next = ID_Actual + 1;
	if (ID_Next == CONTENEDOR.size()) {
		ID_Next = 0;
	};
	if ((CONTENEDOR[ID_Next].Tipo == TipoObjeto::T_FRAME) |
		(CONTENEDOR[ID_Next].Tipo == TipoObjeto::T_MENU) |
		(CONTENEDOR[ID_Next].Tipo == TipoObjeto::T_GROUPBOX) |
		(CONTENEDOR[ID_Next].Tipo == TipoObjeto::T_LABEL) |
		(CONTENEDOR[ID_Next].Tipo == TipoObjeto::T_SHAPE)) {
		ID_Next = NextContenedor(ID_Next);
	}
	return ID_Next;
}


//*********************************************
//*** LOOP									***
//*********************************************
int C_WinApi::Loop() {
	MSG msg;
	BOOL Result;
	while ((Result = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		if (msg.message == WM_KEYDOWN && msg.wParam == VK_TAB) {
			//OutputDebugString("TAB");
			TeclaTab(msg);
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_CHAR){
			//OutputDebugString("TECLA!!\n");
		}

	};
	if (Result == -1) {
		return -1;
	}
	else {
		return (int)msg.wParam;
	}
}
//*********************************************
//*** EXIT									***
//*********************************************

void C_WinApi::Exit() {
	PostQuitMessage(69);
}

//*********************************************
//*** TEST DE ELEMENTOS						***
//*********************************************

void C_WinApi::Test(UINT msg, int ID, int ID_Long, int Notificacion, int Elementos, TipoObjeto Tipo, bool Test1) {
	string tmp;
	// Test 1
	if (Test1) {
		tmp = to_string(ii) + " ID=" + to_string(ID) + " ID_LNG=" + to_string(ID_Long) + "\n";
		OutputDebugString(tmp.c_str());
		ii++;
	}
	// Test 2
	for (int i = 0; i < Elementos; i++) {
		//if (CONTENEDOR[i].Get_ID() == ID_Long) {
		if (CONTENEDOR[i].Tipo == Tipo) {
			//string tmp = to_string(ii) + "     BOT ID-" + to_string(ID_Long) + " N-" + to_string(Notificacion) + " MSG-" + to_string(msg) + "\n";
			tmp = "     ELEMENTO TESTEADO ID=" + to_string(CONTENEDOR[i].Get_ID()) + "\n";
			OutputDebugString(tmp.c_str());
			tmp = to_string(ii) + "     BOT ID=" + to_string(ID) + " ID LNG=" + to_string(ID_Long) + " NOTIF=" + to_string(Notificacion) + " MSG-" + to_string(msg) + "\n";
			OutputDebugString(tmp.c_str());
			ii++;
		}
		//}
	}
}

//*********************************************
//*** Export								***
//*********************************************

Win_Api* New_Api() {
	return new C_WinApi();
};

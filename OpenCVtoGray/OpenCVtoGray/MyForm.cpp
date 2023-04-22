#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(int argc, char *argv[]) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	OpenCVtoGray::MyForm myform;
	Application::Run(%myform);
	return 999;
}
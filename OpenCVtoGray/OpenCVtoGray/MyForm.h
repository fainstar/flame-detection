#pragma once
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <math.h>
#include "util.h"


namespace OpenCVtoGray {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;


	cv::VideoCapture vc;
	cv::Mat input;
	cv::Mat temp;
	cv::Mat output1;
	cv::Mat output2;
	cv::Mat output3;
	long frame_counts;
	double fps;


	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
	private:Bitmap^ gray;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::CheckBox^ checkBox4;
	private: System::Windows::Forms::CheckBox^ checkBox5;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::CheckBox^ checkBox6;
	private: System::Windows::Forms::CheckBox^ checkBox7;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::CheckBox^ checkBox8;
	private: System::Windows::Forms::CheckBox^ checkBox9;
		   ColorPalette^ cp;
#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		   /// 這個方法的內容。
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			   this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			   this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			   this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			   this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			   this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // button1
			   // 
			   this->button1->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->button1->Location = System::Drawing::Point(1027, 12);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(80, 40);
			   this->button1->TabIndex = 0;
			   this->button1->Text = L"Open";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Location = System::Drawing::Point(12, 12);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(480, 360);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->pictureBox1->TabIndex = 1;
			   this->pictureBox1->TabStop = false;
			   // 
			   // button2
			   // 
			   this->button2->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->button2->Location = System::Drawing::Point(1027, 58);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(80, 40);
			   this->button2->TabIndex = 2;
			   this->button2->Text = L"Start";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			   // 
			   // timer1
			   // 
			   this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			   // 
			   // checkBox1
			   // 
			   this->checkBox1->AutoSize = true;
			   this->checkBox1->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->checkBox1->Location = System::Drawing::Point(1027, 215);
			   this->checkBox1->Name = L"checkBox1";
			   this->checkBox1->Size = System::Drawing::Size(77, 28);
			   this->checkBox1->TabIndex = 3;
			   this->checkBox1->Text = L"灰階";
			   this->checkBox1->UseVisualStyleBackColor = true;
			   // 
			   // pictureBox2
			   // 
			   this->pictureBox2->Location = System::Drawing::Point(541, 12);
			   this->pictureBox2->Name = L"pictureBox2";
			   this->pictureBox2->Size = System::Drawing::Size(480, 360);
			   this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->pictureBox2->TabIndex = 4;
			   this->pictureBox2->TabStop = false;
			   // 
			   // checkBox2
			   // 
			   this->checkBox2->AutoSize = true;
			   this->checkBox2->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->checkBox2->Location = System::Drawing::Point(1027, 113);
			   this->checkBox2->Name = L"checkBox2";
			   this->checkBox2->Size = System::Drawing::Size(149, 28);
			   this->checkBox2->TabIndex = 5;
			   this->checkBox2->Text = L"相鄰相減法";
			   this->checkBox2->UseVisualStyleBackColor = true;
			   // 
			   // checkBox3
			   // 
			   this->checkBox3->AutoSize = true;
			   this->checkBox3->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->checkBox3->Location = System::Drawing::Point(1027, 295);
			   this->checkBox3->Name = L"checkBox3";
			   this->checkBox3->Size = System::Drawing::Size(77, 28);
			   this->checkBox3->TabIndex = 6;
			   this->checkBox3->Text = L"還原";
			   this->checkBox3->UseVisualStyleBackColor = true;
			   // 
			   // checkBox4
			   // 
			   this->checkBox4->AutoSize = true;
			   this->checkBox4->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->checkBox4->Location = System::Drawing::Point(1027, 261);
			   this->checkBox4->Name = L"checkBox4";
			   this->checkBox4->Size = System::Drawing::Size(125, 28);
			   this->checkBox4->TabIndex = 7;
			   this->checkBox4->Text = L"重複播放";
			   this->checkBox4->UseVisualStyleBackColor = true;
			   // 
			   // checkBox5
			   // 
			   this->checkBox5->AutoSize = true;
			   this->checkBox5->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->checkBox5->Location = System::Drawing::Point(1027, 147);
			   this->checkBox5->Name = L"checkBox5";
			   this->checkBox5->Size = System::Drawing::Size(149, 28);
			   this->checkBox5->TabIndex = 8;
			   this->checkBox5->Text = L"背景相減法";
			   this->checkBox5->UseVisualStyleBackColor = true;
			   // 
			   // pictureBox3
			   // 
			   this->pictureBox3->Location = System::Drawing::Point(12, 420);
			   this->pictureBox3->Name = L"pictureBox3";
			   this->pictureBox3->Size = System::Drawing::Size(480, 360);
			   this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->pictureBox3->TabIndex = 9;
			   this->pictureBox3->TabStop = false;
			   // 
			   // pictureBox4
			   // 
			   this->pictureBox4->Location = System::Drawing::Point(541, 420);
			   this->pictureBox4->Name = L"pictureBox4";
			   this->pictureBox4->Size = System::Drawing::Size(480, 360);
			   this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->pictureBox4->TabIndex = 10;
			   this->pictureBox4->TabStop = false;
			   // 
			   // checkBox6
			   // 
			   this->checkBox6->AutoSize = true;
			   this->checkBox6->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->checkBox6->Location = System::Drawing::Point(1027, 329);
			   this->checkBox6->Name = L"checkBox6";
			   this->checkBox6->Size = System::Drawing::Size(77, 28);
			   this->checkBox6->TabIndex = 11;
			   this->checkBox6->Text = L"框取";
			   this->checkBox6->UseVisualStyleBackColor = true;
			   // 
			   // checkBox7
			   // 
			   this->checkBox7->AutoSize = true;
			   this->checkBox7->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->checkBox7->Location = System::Drawing::Point(1027, 181);
			   this->checkBox7->Name = L"checkBox7";
			   this->checkBox7->Size = System::Drawing::Size(125, 28);
			   this->checkBox7->TabIndex = 12;
			   this->checkBox7->Text = L"火焰檢測";
			   this->checkBox7->UseVisualStyleBackColor = true;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"標楷體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->label1->Location = System::Drawing::Point(12, 375);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(60, 24);
			   this->label1->TabIndex = 13;
			   this->label1->Text = L"原始";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Font = (gcnew System::Drawing::Font(L"標楷體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->label2->Location = System::Drawing::Point(537, 375);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(73, 24);
			   this->label2->TabIndex = 14;
			   this->label2->Text = L"處理1";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Font = (gcnew System::Drawing::Font(L"標楷體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->label3->Location = System::Drawing::Point(12, 783);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(73, 24);
			   this->label3->TabIndex = 15;
			   this->label3->Text = L"處理2";
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Font = (gcnew System::Drawing::Font(L"標楷體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->label4->Location = System::Drawing::Point(537, 783);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(73, 24);
			   this->label4->TabIndex = 16;
			   this->label4->Text = L"處理3";
			   // 
			   // checkBox8
			   // 
			   this->checkBox8->AutoSize = true;
			   this->checkBox8->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->checkBox8->Location = System::Drawing::Point(1027, 375);
			   this->checkBox8->Name = L"checkBox8";
			   this->checkBox8->Size = System::Drawing::Size(88, 28);
			   this->checkBox8->TabIndex = 17;
			   this->checkBox8->Text = L"測試8";
			   this->checkBox8->UseVisualStyleBackColor = true;
			   // 
			   // checkBox9
			   // 
			   this->checkBox9->AutoSize = true;
			   this->checkBox9->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(136)));
			   this->checkBox9->Location = System::Drawing::Point(1027, 409);
			   this->checkBox9->Name = L"checkBox9";
			   this->checkBox9->Size = System::Drawing::Size(88, 28);
			   this->checkBox9->TabIndex = 18;
			   this->checkBox9->Text = L"測試9";
			   this->checkBox9->UseVisualStyleBackColor = true;
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1184, 861);
			   this->Controls->Add(this->checkBox9);
			   this->Controls->Add(this->checkBox8);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->checkBox7);
			   this->Controls->Add(this->checkBox6);
			   this->Controls->Add(this->pictureBox4);
			   this->Controls->Add(this->pictureBox3);
			   this->Controls->Add(this->checkBox5);
			   this->Controls->Add(this->checkBox4);
			   this->Controls->Add(this->checkBox3);
			   this->Controls->Add(this->checkBox2);
			   this->Controls->Add(this->pictureBox2);
			   this->Controls->Add(this->checkBox1);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->button1);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {//主程式
		long pos_now = vc.get(cv::CAP_PROP_POS_FRAMES);
		bool flag1 = 0, flag2 = 0;
		if (pos_now >= frame_counts - 1) {
			button2_Click(nullptr, nullptr);
			vc.set(cv::CAP_PROP_POS_FRAMES, 0);
			if (checkBox4->Checked) button2_Click(nullptr, nullptr);
		}
		vc >> input;
		output1 = input.clone();
		output2 = input.clone();
		output3 = input.clone();
		if (checkBox1->Checked) output1 = NULL;
		if (checkBox2->Checked) output1 = NULL;
		if (checkBox3->Checked) output1 = NULL;
		if (checkBox5->Checked) output1 = NULL;
		if (checkBox6->Checked) output1 = NULL;
		if (checkBox8->Checked) output1 = NULL;
		if (checkBox9->Checked) output1 = NULL;
		if (checkBox7->Checked) {
			Gray2(input,temp);
			temp = GaussianFilter(temp);
			temp = FD(temp);
			temp = binarization(temp, 50);
			dilate2(temp, output1, 7);
			output2 = circle(output1,4);
			output3 = fire(input, output2);
		}
		pictureBox1->Image = MatToBitmap(input);
		pictureBox2->Image = MatToBitmap(output1);
		pictureBox3->Image = MatToBitmap(output2);
		pictureBox4->Image = MatToBitmap(output3);
	}
	/*-----------------------------------------------------------------------------------------*/
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {

		if (button2->Text == "Start") {
			timer1->Enabled = true;
			button2->Text = "Stop";
		}
		else {
			timer1->Enabled = false;
			button2->Text = "Start";
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog1->FileName = "";
		openFileDialog1->Filter = "所有檔案(*.*)|*.*";
		openFileDialog1->FilterIndex = 1;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName != "") {
			const char* sc = (char*)((void*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName).ToPointer()));
			std::string s = sc;
			vc = cv::VideoCapture(s);
			fps = vc.get(cv::CAP_PROP_FPS);
			frame_counts = vc.get(cv::CAP_PROP_FRAME_COUNT);
			timer1->Interval = 1000.0 / fps;
			vc >> input;

		}
	}
	private:Bitmap^ MatToBitmap(cv::Mat mat) {
		if (mat.channels() == 3) {
			return gcnew Bitmap(mat.cols, mat.rows, mat.step, PixelFormat::Format24bppRgb, (IntPtr)mat.data);
		}
		else {
			Bitmap^ b = gcnew Bitmap(mat.cols, mat.rows, mat.step, PixelFormat::Format8bppIndexed, (IntPtr)mat.data);;
			b->Palette = cp;
			return b;
		}
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		gray = gcnew Bitmap(1, 1, PixelFormat::Format8bppIndexed);
		cp = gray->Palette;
		for (int i = 0; i < 256; i++) {
			cp->Entries[i] = Color::FromArgb(i, i, i);
		}
	}
	/*-----------------------------------------------------------------------------------------*/
};
}

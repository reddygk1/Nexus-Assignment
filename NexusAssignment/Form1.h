/******************************************************************************************************************
* Program      : Nexus                                                                                            *
* Programmed by: Gowtham Reddy                                                                                    *
* Language     : C++                                                                                              *
*                                                                                                                 *
* This Class   : Form Class                                                                                       *
* Purpose      : Creating objects and running all the methods on Timer tick and button click.                     *
*                                                                                                                 *
* *****************************************************************************************************************/
#pragma once

//Including Board and Drawer classes to FORM.
#include "Board.h"
#include "Drawer.h"


namespace NexusAssignment {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button1;
	//Initialising Board
	private: Board *board;
			 Graphics^ graphics;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(9, 33);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(445, 413);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseDown);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::MediumSeaGreen;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(484, 33);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(94, 37);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Restart";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(504, 146);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(56, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Score";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(501, 195);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"00000";
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::SandyBrown;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(484, 90);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(94, 37);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Quit";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::LightCoral;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(484, 334);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(96, 54);
			this->button3->TabIndex = 5;
			this->button3->Text = L"UNDO";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(501, 236);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(98, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"High Score";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(501, 279);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(59, 20);
			this->label4->TabIndex = 7;
			this->label4->Text = L"00000";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(611, 493);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"Form1";
			this->Text = L"Nexus 2k";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//Declaring methods for the game to load on Form load.
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 board = new Board();
				 graphics = pictureBox1->CreateGraphics();
				 Drawer::init(graphics);
				 timer1->Enabled = true;
				 board->createRandomColours();
				 label4->Text = Convert::ToString(board->getHighScore());				 
	}
			 //Every timer tick Board refreshes and the score is updated.

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 board->draw();
				 label2->Text = Convert::ToString(board->getScore());
	}
			 // Button 1 restarts the game by loading the form again.
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				
				 board = new Board();
				 graphics = pictureBox1->CreateGraphics();
				 Drawer::init(graphics);
				 timer1->Enabled = true;
				 board->createRandomColours();
				 label4->Text = Convert::ToString(board->getHighScore());
	}
			 //Mouse down selects the pic of the shape to be moved.
	private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 board->selectCell(e->X, e->Y);
	}
			 // Button 2 is to quit, this closes the form.
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 Close();
	}
			 //Button 3 calles the undo method, which takes the game back a stage.
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 board->MovebackAState();
}
};
}


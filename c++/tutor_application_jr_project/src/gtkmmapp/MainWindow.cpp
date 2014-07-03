/*
 * MainWindow.cpp
 *
 *  Created on: Feb 7, 2010
 *      Author: Matthew Hoggan
 */

#include "MainWindow.h"

MainWindow::MainWindow(int type) {
	this->tutor = NULL;
	this->student = NULL;
	this->draw_thread = NULL;
	this->chat_thread = NULL;

	const char* start_port = "3490";
	this->socket = new TCP_IP_Socket(this, (char*)start_port);

	//Login Section
	this->create_Login_Screen();
	cout << "CONNECTED" << endl;

	this->signal_realize().connect(sigc::mem_fun(*this, &MainWindow::on_realize_create));
	this->set_default_size(1024, 600);
	this->set_border_width(1);
	this->set_title("Tutor App");

	this->base_VBox = new VBox();
	this->main_HBox = new HBox();
	this->label_frame = new Frame();

	m_refActionGroup = Gtk::ActionGroup::create();
	m_refUIManager = Gtk::UIManager::create();
	m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));
	this->add_accel_group(m_refUIManager->get_accel_group());
	Glib::ustring ui_info =
	"<ui>"
	"<menubar name='MenuBar'>"
	"	<menu action='FileMenu'>"
	"	</menu>"
	"</menubar>"
	"</ui>";
	m_refUIManager->insert_action_group(m_refActionGroup);
	m_refUIManager->add_ui_from_string(ui_info);
	this->menu = m_refUIManager->get_widget("/MenuBar");

	this->mdl_Draw = new ModelDrawing(this);
	this->view_Draw = new ViewDrawing(this);
	this->cntrl_Draw = new ControlerDrawing(this, (this->mdl_Draw), (this->view_Draw));

	this->mdl_Chat = new ModelChat(this);
	this->view_Chat = new ViewChat(this);
	this->cntrl_Chat = new ControlerChat(this, (this->mdl_Chat), (this->view_Chat));

	this->status_label = manage(new Label("Welcome to The Tutor App", ALIGN_LEFT, ALIGN_LEFT, false));

	//Put it all together
	this->main_HBox->pack_start(*(this->view_Draw->get_left_VBox()));
	this->label_frame->add(*(this->status_label));
	this->base_VBox->pack_end(*(this->label_frame));
	this->main_HBox->pack_end(*(this->view_Chat->get_right_VBox()));
	this->base_VBox->pack_start(*(this->menu), Gtk::PACK_SHRINK);
	this->base_VBox->pack_end(*(this->main_HBox), true, true);

	this->label_frame->set_size_request(-1, 20);

	this->add(*(this->base_VBox));
	this->set_resizable(false);

	cout << "Showing ALL" << endl;

	this->show_all();

	this->cntrl_Chat->delete_Socket();
	this->cntrl_Chat->establish_Socket();
	this->cntrl_Chat->Set_Sensitive_Queue_Button(false);
	this->cntrl_Chat->Set_Sensitive_log_On(false);

	this->create_Student_Queue();

	//cout << "Main Window Constructed" << endl;
}

MainWindow::~MainWindow() {
}

ControlerChat* MainWindow::get_cntrl_Chat() { return this->cntrl_Chat; }
ModelChat* MainWindow::get_mdl_Chat() { return this->mdl_Chat; }
ViewChat* MainWindow::get_view_Chat() { return this->view_Chat; }
ControlerDrawing* MainWindow::get_cntrl_Draw() { return this->cntrl_Draw; }
ControlerQueue* MainWindow::get_cntrl_Que() { return this->cntrl_Que; }
ModelQueue* MainWindow::get_mdl_Que() { return this->mdl_Que; }
ViewDrawing* MainWindow::get_view_Draw() { return this->view_Draw; }
ModelDrawing* MainWindow::get_mdl_Draw() { return this->mdl_Draw; }
ViewQueue* MainWindow::get_view_Que() { return this->view_Que; }
Label* MainWindow::get_status_label() { return this->status_label; }
void MainWindow::set_status_label(Glib::ustring label) { this->status_label->set_label(label); }
TCP_IP_Socket* MainWindow::get_socket() { return this->socket; }
void MainWindow::set_Student(Student* set_std) { this->student = set_std; }
Student* MainWindow::get_Student() { return this->student; }
void MainWindow::set_Tutor(Tutor* set_tutor) { this->tutor = set_tutor; }
Tutor* MainWindow::get_Tutor() { return this->tutor; }
Glib::Thread* MainWindow::get_chat_thread() { return this->chat_thread; }
Glib::Thread* MainWindow::get_draw_thread() { return this->draw_thread; }


void MainWindow::on_menu_file_quit() {
	hide(); //Closes the main window to stop the Gtk::Main::run().
}

void MainWindow::on_menu_file_new_generic() {
	std::cout << "A File|New menu item was selected." << std::endl;
}

void MainWindow::create_Login_Screen() {
	int authenticate;
	this->login = new Login_Dialog(0, this);
	while((authenticate = (this->Login_Screen())) != VALID) {
			cout << authenticate << " != " << VALID << endl;
			printf("Invalid Login: \n");
	}
	this->login->hide();
	delete this->login;
}

int MainWindow::Login_Screen() {
	int valid_credentials = 0;
	int status;
	status = this->login->run();
	if(status == 0) {
		fprintf( stderr, "ERROR: MainWindow::Login_Screen( )" );
		exit(1);
	} else {
		Glib::ustring* uname = new Glib::ustring(this->login->get_uname());
		Glib::ustring* passwd = new Glib::ustring(this->login->get_psswd());
		if(this->tutor != NULL) {
		    delete this->tutor;
		}
		this->tutor = new Tutor(uname, passwd);
		this->login->set_uname("");
		this->login->set_psswd("");
	}
	char* header = (char*)malloc(4);
	sprintf(header, "%d", 1);
	this->socket->send_packet(header);
	const char* uname_packet = this->tutor->get_uname();
	const char* psswd_packet = this->tutor->get_psswd();
	char* packet = (char*)malloc(512);
	sprintf(packet, "%s %s", uname_packet, psswd_packet, 512);
	this->socket->send_packet(packet);
	free(packet);
	char server_status;
	cout << endl;
	server_status = (this->socket->receive_packet_login());
	valid_credentials = server_status;
	fprintf(stderr,"%d\n",valid_credentials);
	return valid_credentials;
}

void MainWindow::create_Student_Queue()
{
	//By Default Create and Open Up Student Queue
	this->mdl_Que = NULL;
	this->view_Que = NULL;
	this->cntrl_Que = NULL;
	this->mdl_Que = new ModelQueue(this);
	this->view_Que = new ViewQueue(this);
	this->cntrl_Que = new ControlerQueue(this, (this->mdl_Que), (this->view_Que));
	this->cntrl_Que->get_Data_From_Server();
	this->view_Que->get_window()->show_all();
	this->cntrl_Chat->Set_Sensitive_ALL(false);
	this->cntrl_Chat->Set_Editable_ALL(false);
	this->cntrl_Draw->Set_Sensitive_ALL(false);
}

void MainWindow::on_realize_create() {
}

void MainWindow::create_chat_thread() {
    this->chat_thread = Glib::Thread::create(sigc::bind<Glib::ustring, TextView*>(sigc::mem_fun(*(this->mdl_Chat->get_chat_socket()), &TCP_IP_Socket::recieve_Text_Data), this->student->get_first_Name(), this->view_Chat->get_Output()), false);
    //this->chat_thread = Glib::Thread::create(sigc::bind<Glib::ustring>(sigc::mem_fun(*(this->mdl_Chat->get_chat_socket()), &TCP_IP_Socket::recieve_Text_Data), this->student->get_first_Name()), false);
}

void MainWindow::create_draw_thread() {
    this->draw_thread = Glib::Thread::create(sigc::bind<int>(sigc::mem_fun(*(this->socket), &TCP_IP_Socket::recieve_Draw_Data), 10), false);
}

void MainWindow::join_chat_thread() {
    cout << "Joining Chat Thread" << endl;
    this->chat_thread->join();
}

void MainWindow::join_draw_thread() {
    cout << "Joining Draw Thread" << endl;
    this->draw_thread->join();
}



















#include <mesibo.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#define ERRORLOG(format, ...)               \
  do {                                      \
    fprintf(stderr, format, ##__VA_ARGS__); \
  } while (0)

int gDebugEnabled = 1;

int keypress();
int send_text_message(IMesibo* m_api,const char* to,const char * message);

class CNotify : public CMesiboNotify {
	
	IMesibo *m_api;
	public:
	
	void set_api(IMesibo *api) {
		m_api = api;
	}


	// You will receive the connection status here
	int on_status(int status, uint32_t substatus, uint8_t channel,
			const char *from) {
		ERRORLOG("===> on_status: %u %u\n", status, substatus);
		return 0;
	}


	// Invoked on receiving a new message or reading database messages
	// You will receive messages here.
	int on_message(tMessageParams * p, const char *from, const char *data,
			uint32_t len) {
	
		int printlen = len;
	        if (printlen > 64) printlen = 64;

		ERRORLOG(

			"===> test app message received: uid %u status %d channel %d type %u "
			"id %" PRIx64 " refid %lu groupid %u, when %" PRIu64
			" from %s, flag: %x len %d: %.*s\n",
			p->uid, p->status, p->channel, p->type, p->id, p->refid, p->groupid,
			p->when, from, p->flag, len, printlen, data);

		return 0;

	}

	// Invoked when the status of the outgoing or sent message is changed
	// You will receive the status of sent messages here
	int on_messagestatus(tMessageParams * p, const char *from, int last) {
		ERRORLOG(
			"===> on_messagestatus status %u id %u when %u ms (%u %u) from: %s\n",
			p->status, p->id, m_api->timestamp() - p->when, m_api->timestamp(),
			p->when, from ? from : "");
		return 0;
	}
};
// To exit the program on key press
int keypress() {
  struct termios old_state, new_state;
  int c;

  tcgetattr(STDIN_FILENO, &old_state);
  new_state = old_state;

  new_state.c_lflag &= ~(ECHO | ICANON);
  new_state.c_cc[VMIN] = 1;

  tcsetattr(STDIN_FILENO, TCSANOW, &new_state);

  c = getchar();

  /* restore the saved state */
  tcsetattr(STDIN_FILENO, TCSANOW, &old_state);
  return c;
}

int send_text_message(IMesibo* m_api,const char* to,const char * message){

        tMessageParams p = {};
        p.id = m_api->random32();
	p.expiry = 3600;
	int datalen = strlen(message);
        m_api->message(&p, to, message,datalen);
}

IMesibo* mesibo_init(){
	
	// Create a Mesibo Instance
	IMesibo *m_api = query_mesibo("/tmp");

	// Add Listener
	CNotify *n = new CNotify();
	m_api->set_notify(0, n, 1);
	n->set_api(m_api);
	// Set your AUTH_TOKEN obtained from the Mesibo Console
	m_api->set_credentials("3e7694e19d192588a4ffcb4eab26b6afb3d5aada54bbd41edd71400");

	// set the name of the database
	if (0 != m_api->set_database("mesibo.db")) {
		fprintf(stderr, "Database failed\n");
		return NULL;
	}

	// Set  APP_ID which you used to create AUTH_TOKEN 
	m_api->set_device(1, "MyDeviceId", "dialogflowmesibo", "1.0.0");

	return m_api;
}



int main(){

        IMesibo *m_api = mesibo_init();
	m_api->start();
	send_text_message(m_api,"Ankit","Hi from Main");
	
	keypress();
        return 0;

}

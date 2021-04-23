class MesiboListener:

    def __init__(self):
        pass

    def mesibo_on_connectionstatus(self, status):
        """
        Invoked when the connection status is changed. 
        It is also invoked when the token is about to be expired.
        Different status codes convey the state of the connection. 

        Parameters
        ----------
        status : Connection Status

        """

        return 0

    def mesibo_on_message(self, message_params, data):
        """
        Invoked on receiving a new message or reading database messages 
        
        Parameters
        ----------
        message_params: Message Parameters
        data : Message Data Bytes 
        """

        return 0

    def mesibo_on_messagestatus(self, message_params):
        """
        Invoked when the status of outgoing or sent message is changed

        Parameters
        ----------
        message_params : Message Parameters

        """

        return 0

    def mesibo_on_activity(self, msg_params, activity):
        return 0
    
    def mesibo_on_sync(self, count):
        return 0
    
    def mesibo_on_file(self, msg_params, file_params):
        return 0 

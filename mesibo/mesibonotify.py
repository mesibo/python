# mesibonotify.py
# Base class for MesiboNotify(Listeners)
# For documentation on Listeners refer https://mesibo.com/documentation/api/listeners

class MesiboNotify:

    def __init__(self):
        pass

    def on_activity(self, message_params_dict, p_from, event):
        """
        Invoked on receiving a new activity
        
        Parameters
        ----------
        message_params_dict : Message Parameters
        p_from : Peer  
        event : Event type
    
        """

        return 1


    def on_message(self, message_params, p_from, data, p_len):
        """
        Invoked on receiving a new message or reading database messages 
        
        Parameters
        ----------
        message_params: Message Parameters
        p_from : Peer 
        data : Message Data 
        """

        return 1

    def on_file(self, message_params, p_from, file_params):
        """
        Invoked on receiving a new file message or reading database messages

        Parameters
        ----------
        message_params : Message Parameters
        p_from : Peer 
        file_params : File Info

        """

        return 1

    def on_messagestatus(self, message_params, p_from):
        """
        Invoked when the status of outgoing or sent message is changed

        Parameters
        ----------
        message_params : Message Parameters
        p_from : Peer 

        """

        return 1


    def on_connectionstatus(self, status):
        """
        Invoked when the connection status is changed. 
        It is also invoked when the token is about to be expired.
        Different status codes convey the state of the connection. 

        Parameters
        ----------
        status : Connection Status

        """

        return 1

    def on_location(self,message_params, latitude, longitude, p_from):
        """
        Invoked on receiving a new location message or reading database messages

        Parameters
        ----------
        message_params: Message Paramters
        location_params: Location

        """

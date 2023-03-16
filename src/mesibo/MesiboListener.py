class MesiboListener:

    def __init__(self):
        pass

    def Mesibo_onConnectionStatus(self, status):
        """
        Invoked when the connection status is changed. 
        It is also invoked when the token is about to be expired.
        Different status codes convey the state of the connection. 

        Parameters
        ----------
        status : Connection Status

        """

        return 0

    def Mesibo_onMessage(self, message):
        """
        Invoked on receiving a new message or reading database messages 
        
        Parameters
        ----------
        message: Message Object
        """

        return 0

    def Mesibo_onMessageUpdate(self, message):
        """
        Invoked on receiving an update for existing message 
        
        Parameters
        ----------
        message: Message Object
        """

        return 0

    def Mesibo_onMessageStatus(self, message):
        """
        Invoked when the status of outgoing or sent message is changed

        Parameters
        ----------
        message: Message Object
        """

        return 0

    def Mesibo_onPresence(self, msg):
        return 0
    
    def Mesibo_onSync(self, count):
        return 0
    

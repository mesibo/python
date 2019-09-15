# mesibonotify.py
# Base class for MesiboNotify(Listeners)
# For documentation on Listeners refer https://mesibo.com/documentation/api/listeners

"""
 Copyright (c) 2019 Mesibo
 * https://mesibo.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the terms and condition mentioned on https://mesibo.com
 * as well as following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions, the following disclaimer and links to documentation and source code
 * repository.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * Neither the name of Mesibo nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Documentation
 * https://mesibo.com/documentation/
 *
 * Source Code Repository
 * https://github.com/mesibo/python

"""


class MesiboNotify:

    def __init__(self):
        pass

    def on_activity(self, message_params_dict, event):
        """
        Invoked on receiving a new activity
        
        Parameters
        ----------
        message_params_dict : Message Parameters
        p_from : Peer  
        event : Event type
    
        """

        return 1


    def on_message(self, message_params, data ):
        """
        Invoked on receiving a new message or reading database messages 
        
        Parameters
        ----------
        message_params: Message Parameters
        data : Message Data 
        """

        return 1

    def on_file(self, message_params, file_params):
        """
        Invoked on receiving a new file message or reading database messages

        Parameters
        ----------
        message_params : Message Parameters
        p_from : Peer 
        file_params : File Info

        """

        return 1

    def on_messagestatus(self, message_params):
        """
        Invoked when the status of outgoing or sent message is changed

        Parameters
        ----------
        message_params : Message Parameters

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

    def on_location(self,message_params, latitude, longitude):
        """
        Invoked on receiving a new location message or reading database messages

        Parameters
        ----------
        message_params: Message Paramters
        location_params: Location

        """

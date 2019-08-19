# mesiboNotify.py
#Base class for mesiboNotify(Listener)

class mesiboNotify:

    def __init__(self):
        pass

    def on_activity(self, message_params_dict, p_from, event):
        return 1

    def on_call(self,peer_id, call_id, status, data,
                      data_len, flags):
        return 1

    def on_error(self, error):
        return 1

    def on_key(self, key, value):
        return 1

    def on_message(self, message_params_dict, p_from, data, p_len):
        return 1

    def on_file(self, message_params_dict, p_from, bundle_params_dict):
        return 1

    def on_message_status(self,  message_params_dict, p_from, last):
        return 1

    def on_rtc(self, p_type, flags, peer_id, sdp, p_len):
        return 1

    def on_server(self, p_type, server, username, password):
        return 1

    def on_status(self, status, sub_status, channel, p_from):
        return 1

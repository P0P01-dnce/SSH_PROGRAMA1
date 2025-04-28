#include "ssh_connection.h"
#include<iostream>
ssh_session connection(const std::string& ip_host, const std::string& user, const std::string& ppwd) {
	ssh_session session = ssh_new();
	if (session == nullptr) return nullptr;
	ssh_options_set(session, SSH_OPTIONS_HOST, ip_host.c_str());
	ssh_options_set(session, SSH_OPTIONS_USER, user.c_str());
	if (ssh_connect(session) != SSH_OK) {
		ssh_free(session);
		return nullptr;
	}
	if (ssh_userauth_password(session, nullptr, ppwd.c_str()) != SSH_AUTH_SUCCESS) {
		ssh_disconnect(session);
		ssh_free(session);
		return nullptr;
	}
	return session;
}
std::string command_execution(ssh_session session, const std::string& command) {
	ssh_channel channel = ssh_channel_new(session);
	if (channel == nullptr) return "Error al crear el canal";
	ssh_channel_open_session(channel);
	ssh_channel_request_exec(channel, command.c_str());
	char buffer[256];
	std::string output;
	int nbytes;
	while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0) {
		output.append(buffer, nbytes);
	}
	ssh_channel_send_eof(channel);
	ssh_channel_close(channel);
	ssh_channel_free(channel);

	return output;

}
bool verificar(const std::string& ip_host) {
	ssh_session session = ssh_new();
	if (session == nullptr)return false;
	ssh_options_set(session, SSH_OPTIONS_HOST, ip_host.c_str());
	unsigned int port = 22;
	ssh_options_set(session, SSH_OPTIONS_PORT, &port);
	int rc = ssh_connect(session);
	if (rc == SSH_OK) {
		ssh_disconnect(session);
		ssh_free(session);
		return true;
	}
	ssh_free(session);
	return false;
}
void mostrarsesion(ssh_session session) {
	std::cout << "Estado:" << ssh_get_status(session) << "\n";
}
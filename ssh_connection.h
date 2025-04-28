#ifndef SSH_CONNECTION_H
#define SSH_CONNECTION_H
#include<string>
#include<libssh/libssh.h>
ssh_session connection(const std::string& ip_host, const std::string& user, const std::string& ppwd);
std::string command_execution(ssh_session session, const std::string& command);
bool verificar(const std::string& ip_host);
void mostrarsesion(ssh_session session);
#endif